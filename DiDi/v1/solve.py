#!/usr/bin/python
from collections import defaultdict
from operator import itemgetter
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVR
from sklearn.preprocessing import StandardScaler
import os
import csv
import logging

global ndstrict, nslice, nday, Qslice
ndistrict = 66
nslice = 144
nday = 22
Qslice = [46, 58, 70, 82, 94, 106, 118, 130, 142]
Qdata = [22, 24, 26, 28, 30]
QDict = dict()

def initLog(lda):
	logging.basicConfig(
				level=logging.DEBUG,
                format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                datefmt='%a, %d %b %Y %H:%M:%S',
                filename='solver_v0.log',
                filemode='w')

				
def getQuery(filename):
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	ret = defaultdict(set)
	with open(filename, "r") as fin:
		for line in fin:
			line = line.strip()
			if not line:
				continue
			dateId, sliceId = map(int, line.split('-')[-2:])
			ret[dateId].add(sliceId)
	QDict.clear()
	for dateId, sliceSet in ret.iteritems():
		QDict[dateId] = sorted(list(sliceSet))
	return ret
				
				
def getTrainData(districtId):
	dataPath = "../v0/train_feature/feat_%s" % (districtId)
	ret = []
	with open(dataPath, 'rb') as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			ret.append(data)
	return np.array(ret, float)
	
	
def getTestData(districtId):
	dataPath = "../v0/test_feature/feat_%s" % (districtId)
	ret = []
	with open(dataPath, 'rb') as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			ret.append(data)
	return np.array(ret, float)
	
	
def calcDayId(dateId):
	dayId = (dateId + 3) % 7
	return 0 if dayId<5 else 1
				
							
def solve(districtId = 1):
	trainData = getTrainData(districtId)
	reqDict = defaultdict(dict)
	ansDict = defaultdict(dict)
	for trainRow in trainData:
		dateId, sliceId, reqNum, ansNum = trainRow
		# skip 1.1 - 1.3 
		if dateId <= 3:
			continue
		dayId = calcDayId(dateId)
		if not sliceId in reqDict[dayId]:
			reqDict[dayId][sliceId] = []
		if not sliceId in ansDict[dayId]:
			ansDict[dayId][sliceId] = []
		reqDict[dayId][sliceId].append(reqNum)
		ansDict[dayId][sliceId].append(ansNum)
	
	ret = []	
	for dateId, slices in QDict.iteritems():
		dayId = calcDayId(dateId)
		for sliceId in slices:
			reqNumList = np.array( reqDict[dayId][sliceId] ) 
			ansNumList = np.array( ansDict[dayId][sliceId] ) 
			reqNum = reqNumList.mean()
			ansNum = ansNumList.mean()
			gapNum = reqNum - ansNum
			ret.append([districtId, dateId, sliceId, gapNum])
	return ret	
	
	
def solveAll():
	ans = []
	for districtId in xrange(1, ndistrict+1):
		ans += solve(districtId)
	return ans
	

def saveAns(ans, filename = "gap.csv"):
	ans = map(lambda item: "%s,2016-01-%s-%s,%s" % (item[0], item[1], item[2], item[3]), ans)
	with open(filename, "w") as fout:
		fout.write("\n".join(ans) + "\n")	
	
	
def loadAns(filename):	
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	ret = []
	with open(filename, "r") as fin:
		for line in fin:
			line = line.strip()
			if not line:
				continue
			L = line.split(',')
			districtId = int(L[0])
			gapNum = float(L[-1])
			dateId, sliceId = map(int, L[1].split('-')[-2:])
			ret.append( [districtId, dateId, sliceId, gapNum] )
	return ret

	
def calcDiff(cur, pre):
	assert len(cur) == len(pre)
	cur = np.array(cur)
	pre = np.array(pre)
	n = cur.shape[0]
	X = range(n)
	Y2 = pre[:,-1]
	Y1 = cur[:,-1]
	Y3 = Y1 - Y2
	score = sum(abs(Y3))
	print "score = ", score
	plt.figure()
	ax = plt.subplot(2, 1, 1)
	ax.plot(X, Y1, "b-", label="pred result")
	ax.plot(X, Y2, "r-", label="ground truth")
	plt.ylabel('gap')
	plt.xlabel('item')
	plt.legend()
	
	ax = plt.subplot(2, 1, 2)
	ax.plot(X, Y3, "r-")
	plt.ylabel('diff')
	plt.xlabel('item')
	
	plt.show()
	
def getLocalQuery(filename):
	tmpDict = getQuery(filename)
	QDict.clear()
	for dateId, slices in tmpDict.iteritems():
		tmpList = reduce(lambda x,y:x+y, map(lambda x:[x-1,x-2,x-3], slices))
		tmpList.sort()
		QDict[dateId] = tmpList
	
	
def getLocalAns():	
	ret = []
	slices = reduce(lambda x,y:x+y, map(lambda x:[x-1,x-2,x-3], Qslice))
	slices.sort()
	for districtId in xrange(1, ndistrict+1):
		testData = getTestData(districtId)
		gapDict = defaultdict(dict)
		for testRow in testData:
			dateId, sliceId, reqNum, ansNum = testRow
			gapDict[dateId][sliceId] = reqNum - ansNum
		for dateId, Qslices in QDict.iteritems():
			for sliceId in Qslices:
				ret.append( [districtId, dateId, sliceId, gapDict[dateId][sliceId]] )
	return ret		
	
def getLocalAns_fast(filename):	
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	ret = []
	with open(filename, "rb") as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			districtId, dateLine, gapNum = data
			dateId, sliceId = dateLine.split('-')[-2:]
			ret.append([int(districtId), int(dateId), int(sliceId), float(gapNum)])
	return ret
	

def local_test():
	getLocalQuery("F:\Qt_prj\hdoj\data.in")
	localAns = getLocalAns_fast("local_gap.csv")
	ans = solveAll()
	saveAns(ans, "gap_.csv")
	assert len(ans) == len(localAns)
	assert len(ans) % ndistrict == 0
	sliceLen = len(ans) / ndistrict
	tot = 0.0
	for i in xrange(0, len(ans), sliceLen):
		subAns = ans[i:i+sliceLen]
		subAns_ = localAns[i:i+sliceLen]
		assert len(subAns) == len(subAns_)
		assert len(subAns) == sliceLen
		for j in xrange(sliceLen):
			if subAns_[j][-1] == 0:
				continue
			assert subAns[j][:-1] == subAns_[j][:-1]
			tot += abs((subAns[j][-1] - subAns_[j][-1]) / subAns_[j][-1])
	score = tot / len(ans)
	print "score = ", score
	
	calcDiff(ans, localAns)
	

if __name__ == "__main__":
	getQuery("F:\Qt_prj\hdoj\data.in")
	ans = solveAll()
	saveAns(ans)
	ans_ = loadAns("../v0/gap.csv")
	print len(ans), len(ans_)
	calcDiff(ans, ans_)
	
	# getLocalQuery("F:\Qt_prj\hdoj\data.in")
	# ans = getLocalAns()
	# saveAns(ans, "local_gap.csv")
	
	# local_test()
	