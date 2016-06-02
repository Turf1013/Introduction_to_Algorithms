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
	dataPath = "./train_feature/feat_%s" % (districtId)
	ret = []
	with open(dataPath, 'rb') as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			ret.append(data)
	return np.array(ret, float)
				
							
def solve(districtId = 1):
	trainData = getTrainData(districtId)
	reqDict = defaultdict(dict)
	ansDict = defaultdict(dict)
	for trainRow in trainData:
		dateId, sliceId, reqNum, ansNum = trainRow
		dayId = dateId % 7
		if not sliceId in Qslice:
			continue
		if not sliceId in reqDict[dayId]:
			reqDict[dayId][sliceId] = []
		if not sliceId in ansDict[dayId]:
			ansDict[dayId][sliceId] = []
		reqDict[dayId][sliceId].append(reqNum)
		ansDict[dayId][sliceId].append(ansNum)
	
	ret = []	
	for dateId, slices in QDict.iteritems():
		dayId = dateId % 7
		for sliceId in slices:
			reqNumList = np.array( reqDict[dayId][sliceId] ) 
			ansNumList = np.array( ansDict[dayId][sliceId] ) 
			assert reqNumList.shape[0] == 3
			assert ansNumList.shape[0] == 3
			reqNum = reqNumList.mean()
			ansNum = ansNumList.mean()
			gapNum = reqNum - ansNum
			if districtId == 1:
				print reqNumList, ansNumList
				print reqNum, ansNum, gapNum
			# gapNum = max(0, reqNum - ansNum)
			ret.append([districtId, dateId, sliceId, gapNum])
	return ret	
	
	
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
	
	
def solveAll():
	ans = []
	for districtId in xrange(1, ndistrict+1):
		ans += solve(districtId)
	saveAns(ans)
	return ans
	

def saveAns(ans, filename = "gap.csv"):
	ans = map(lambda item: "%s,2016-01-%s-%s,%s" % (item[0], item[1], item[2], item[3]), ans)
	with open(filename, "w") as fout:
		fout.write("\n".join(ans) + "\n")
	

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
	ax.plot(X, Y1, "bo-", label="cur result")
	ax.plot(X, Y2, "rs-", label="pre result")
	plt.ylabel('gap')
	plt.xlabel('item')
	plt.legend()
	
	ax = plt.subplot(2, 1, 2)
	ax.plot(X, Y3, "rs-")
	plt.ylabel('diff')
	plt.xlabel('item')
	
	plt.show()
	

if __name__ == "__main__":
	getQuery("F:\Qt_prj\hdoj\data.in")
	ans = solveAll()
	ans_ = loadAns("gap.out")
	print len(ans), len(ans_)
	calcDiff(ans, ans_)
	
