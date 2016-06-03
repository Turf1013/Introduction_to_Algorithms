#!/usr/bin/python
from collections import defaultdict
from operator import itemgetter
import numpy as np
import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import AdaBoostRegressor
from sklearn.svm import SVR
from sklearn.preprocessing import StandardScaler
import os
import csv
import logging


global ndstrict, nslice, nday, Qslice, QDict
ndistrict = 66
nslice = 144
ndays = 21
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
	return np.array(ret, int)
	
	
def getTestData(districtId):
	dataPath = "../v0/test_feature/feat_%s" % (districtId)
	ret = []
	with open(dataPath, 'rb') as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			ret.append(data)
	return np.array(ret, int)
	
	
def calcDayId(dateId):
	dayId = (dateId + 3) % 7
	return 0 if dayId<5 else 1
				
				
def getTrainData_ByDistrict(districtId):
	trainData = getTrainData(districtId)
	reqDict = dict()
	ansDict = dict()
	for i in xrange(1, nslice+1):
		reqDict[i] = [0] * ndays
		ansDict[i] = [0] * ndays
	for trainRow in trainData:
		dateId, sliceId, reqNum, ansNum = trainRow
		reqDict[sliceId][dateId-1] = reqNum
		ansDict[sliceId][dateId-1] = ansNum
	return reqDict, ansDict
	
	
def getTestData_ByDistrict(districtId, period):
	trainData = getTestData(districtId)
	reqDict = defaultdict(dict)
	ansDict = defaultdict(dict)
	for trainRow in trainData:
		dateId, sliceId, reqNum, ansNum = trainRow
		perId = (sliceId - 1) / period
		if perId not in reqDict[dateId]:
			reqDict[dateId][perId] = 0
		if perId not in ansDict[dateId]:
			ansDict[dateId][perId] = 0
		reqDict[dateId][perId] += reqNum
		ansDict[dateId][perId] += ansNum
	return reqDict, ansDict
	
	
def transfer(reqDict, ansDict, period):
	reqTmpDict = dict()
	ansTmpDict = dict()
	for i in xrange(0, ndays):
		dayId = calcDayId(i+1)
		reqTmpDict[dayId] = defaultdict(list)
		ansTmpDict[dayId] = defaultdict(list)
	for bSlice in xrange(0, nslice, period):
		perId = bSlice / period
		for j in xrange(0, period):
			sliceId = bSlice + j + 1
			reqList = reqDict[sliceId]
			ansList = ansDict[sliceId]
			# skip 1.1~1.3
			for i in xrange(3, ndays):
				dayId = calcDayId(i+1)
				reqTmpDict[dayId][perId].append( reqList[i] )
				ansTmpDict[dayId][perId].append( ansList[i] )
		
	reqDict.clear()
	reqDict.update(reqTmpDict)
	ansDict.clear()
	ansDict.update(ansTmpDict)
	
	
def train(data):
	data = np.array(data, float)
	X = data[:,:-1]
	Y = data[:,-1]
	regr = AdaBoostRegressor(DecisionTreeRegressor(max_depth=6), n_estimators=300)
	regr.fit(X, Y)
	return regr
	

def show():
	plt.subplot(1, 1, 1)
	plt.scatter(X, Y, c="k", label="training samples")
	# plt.scatter(X_, Y_, c='b', linewidth=2.5, label="n_estimators=300")
	plt.plot(X_, Y_, c='r', linestyle="-", linewidth=2.5, label="n_estimators=300")
	plt.xlabel("data")
	plt.ylabel("target")
	plt.title("Boosted Decision Tree Regression")
	plt.legend()
	plt.show()
	
			
def trainAll(dataDict, segList):
	retDict = dict()
	for dayId, perDict in dataDict.iteritems():
		retDict[dayId] = []
		for i in xrange(1, len(segList)):
			trainData = []
			for perId in xrange(segList[i-1], segList[i]):
				trainData += map(lambda c: [perId, c], perDict[perId])
			regr = train(trainData)
			retDict[dayId].append( regr )
	return retDict		
	
	
def getSegId(segList, perId):
	for i in xrange(1, len(segList)):
		if perId < segList[i]:
			return i - 1
	return -1
				
				
def solve(districtId = 14, period = 6):
	segList = [0, 5, 11, 16, 19, 20, 24]
	reqTrainDict, ansTrainDict = getTrainData_ByDistrict(districtId)
	transfer(reqTrainDict, ansTrainDict, period)
	reqRegrDict = trainAll(reqTrainDict, segList)
	ansRegrDict = trainAll(ansTrainDict, segList)
	
	reqTestDict, ansTestDict = getTestData_ByDistrict(districtId, period)
	
	ret = []	
	for dateId, slices in QDict.iteritems():
		dayId = calcDayId(dateId)
		for sliceId in slices:
			print "sliceId =", sliceId
			perId = (sliceId - 1) / period
			segId = getSegId(segList, perId)
			# print "perId = %s, seg = %s" % (perId, segId)
			# print len(reqRegrDict[dayId]), len(ansRegrDict[dayId])
			
			reqRegr = reqRegrDict[dayId][segId]
			tmpNum = reqRegr.predict([[perId]])[0]
			curNum = reqTestDict[dateId][perId]
			reqNum = tmpNum - curNum
			print "tmpNum = %s, curNum = %s, reqNum = %s" % (tmpNum, curNum, reqNum)
			
			ansRegr = ansRegrDict[dayId][segId]
			tmpNum = ansRegr.predict([[perId]])[0]
			curNum = ansTestDict[dateId][perId]
			ansNum = tmpNum - curNum
			print "tmpNum = %s, curNum = %s, ansNum = %s" % (tmpNum, curNum, ansNum)
			
			gapNum = reqNum - ansNum
			
			ret.append([districtId, dateId, sliceId, gapNum])
	return ret	
	
	
def solveAll():
	ans = []
	for districtId in xrange(1, ndistrict+1):
		ans += solve(districtId)
	return ans
	


if __name__ == "__main__":
	getQuery("../query.in")
	solve()
	