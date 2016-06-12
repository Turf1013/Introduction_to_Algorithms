#!/usr/bin/python
from collections import defaultdict
from operator import itemgetter
import numpy as np
import matplotlib
matplotlib.use('Agg')
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
	
	
def local_getTestData_ByDistrict(districtId, period):
	trainData = getTestData(districtId)
	reqDict = defaultdict(dict)
	ansDict = defaultdict(dict)
	for trainRow in trainData:
		dateId, sliceId, reqNum, ansNum = trainRow
		reqDict[dateId][sliceId] = reqNum
		ansDict[dateId][sliceId] = ansNum
	return reqDict, ansDict
	
	
def transfer(dataDict, period):
	retDict = dict()
	for i in xrange(0, ndays):
		dayId = calcDayId(i+1)
		retDict[dayId] = defaultdict(list)

	# skip 1.1~1.3
	for i in xrange(3, ndays):
		dayId = calcDayId(i+1)
		for bSlice in xrange(0, nslice, period):
			perId = bSlice / period
			tot = 0.0
			for j in xrange(0, period):
				sliceId = bSlice + j + 1
				tot += dataDict[sliceId][i]
			retDict[dayId][perId].append( tot )
			
	return retDict
	
	
def getFreq(dataDict, period):
	tmpDict = dict()
	for i in xrange(0, ndays):
		dayId = calcDayId(i+1)
		tmpDict[dayId] = defaultdict(list)
	# skip 1.1~1.3
	for i in xrange(3, ndays):
		dayId = calcDayId(i+1)
		for bSlice in xrange(0, nslice, period):
			perId = bSlice / period
			tot = 0.0 + 1e-6
			for j in xrange(0, period):
				sliceId = bSlice + j + 1
				tot += dataDict[sliceId][i]
			tmpList = [dataDict[bSlice+j+1][i]/tot for j in xrange(0, period)] 
			tmpDict[dayId][perId].append(tmpList) 
	retDict = dict()
	for dayId, perDict in tmpDict.iteritems():
		retDict[dayId] = dict()
		for perId, freqList in perDict.iteritems():
			retDict[dayId][perId] = np.array(freqList).mean(axis=0)
	return retDict
	

def train(data):
	data = np.array(data, float)
	X = data[:,:-1]
	Y = data[:,-1]
	regr = AdaBoostRegressor(DecisionTreeRegressor(max_depth=6), n_estimators=300)
	regr.fit(X, Y)
	# showPeriod(regr, X, Y)
	return regr
	

def showPeriod(regr, X, Y):
	X_ = np.array(list(set(X[:,0])))
	X_ = X_.reshape(len(X_), 1)
	Y_ = regr.predict(X_)
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
				# print perId, len(perDict[perId])
				trainData += map(lambda c: [perId, c], perDict[perId])
			# for data in trainData:
				# print data
			regr = train(trainData)
			retDict[dayId].append( regr )
	return retDict		
	
	
def getSegId(segList, perId):
	for i in xrange(1, len(segList)):
		if perId < segList[i]:
			return i - 1
	return -1
				

def showAllCurve(dataDict, regrDict, period, segList):
	colorList = [
		'#ff0000',
		'#ffff00',
		'#00ff00',
		'#00ffff',
		'#ff9900',
		'#4589f9',
		'#0000ff',
		'#9900ff',
		'#ff00ff',
		'#980000',
		'#783f04',
		'#c0ff3e',
		'#8b008b',
		'#7ac5cd',
		'#698b22',
		'#00e5ee',
		'#6959cd',
		'#8b7d6b',
		'#ff82ab',
		'#cc6633',
		'#eea2ad',
	]
	
	dayDict = defaultdict(list)
	for i in xrange(3, ndays):
		dayId = calcDayId(i+1)
		dayDict[dayId].append(i)
	plt.figure()
	X = [i/period for i in range(0, nslice, period)]
	for dayId, dateList in dayDict.iteritems():
		for i,dateId in enumerate(dateList):
			Y = []
			# get train data
			for bSlice in xrange(0, nslice, period):
				perId = bSlice / period
				tot = 0.0
				for j in xrange(0, period):
					tot += dataDict[bSlice+1+j][dateId]
				Y.append(tot)
				
			plt.plot(X, Y, c=colorList[i], linestyle='--', linewidth=1.5)
			
		# get predict value
		Y_ = []
		for perId in X:
			segId = getSegId(segList, perId)				
			regr = regrDict[dayId][segId]
			tot = regr.predict([[perId]])
			Y_.append(tot)
				
		plt.plot(X, Y_, 'ro-', linewidth=3.5)		
		
		plt.show()
		
				
				
def solve(districtId = 14, period = 6):
	segList = [0, 5, 11, 16, 19, 24]
	reqTrainTmpDict, ansTrainTmpDict = getTrainData_ByDistrict(districtId)
	reqTrainDict = transfer(reqTrainTmpDict, period)
	ansTrainDict = transfer(ansTrainTmpDict, period)
	reqTrainFreq = getFreq(reqTrainTmpDict, period)
	ansTrainFreq = getFreq(ansTrainTmpDict, period)
	reqRegrDict = trainAll(reqTrainDict, segList)
	ansRegrDict = trainAll(ansTrainDict, segList)
	
	ret = []	
	for dateId, slices in QDict.iteritems():
		dayId = calcDayId(dateId)
		for sliceId in slices:
			# print "sliceId =", sliceId
			perId = (sliceId - 1) / period
			segId = getSegId(segList, perId)
			# print "perId = %s, seg = %s" % (perId, segId)
			# print len(reqRegrDict[dayId]), len(ansRegrDict[dayId])
			
			reqRegr = reqRegrDict[dayId][segId]
			tmpNum = reqRegr.predict([[perId]])[0]
			reqNum = tmpNum * reqTrainFreq[dayId][perId][(sliceId-1)%period]
			
			ansRegr = ansRegrDict[dayId][segId]
			tmpNum = ansRegr.predict([[perId]])[0]
			ansNum = tmpNum * ansTrainFreq[dayId][perId][(sliceId-1)%period]
			
			gapNum = max(0, reqNum - ansNum)
			
			ret.append([districtId, dateId, sliceId, gapNum])
	return ret	
	
	
def calcMAPE(pred, gt):
	if gt == 0:
		return 0
	return abs(pred-gt) / gt
	
	
def localSolve(districtId = 14, period = 6):
	segList = [0, 5, 11, 16, 19, 24]
	reqTrainTmpDict, ansTrainTmpDict = getTrainData_ByDistrict(districtId)
	reqTrainDict = transfer(reqTrainTmpDict, period)
	ansTrainDict = transfer(ansTrainTmpDict, period)
	reqTrainFreq = getFreq(reqTrainTmpDict, period)
	ansTrainFreq = getFreq(ansTrainTmpDict, period)
	reqRegrDict = trainAll(reqTrainDict, segList)
	ansRegrDict = trainAll(ansTrainDict, segList)
	
	# showAllCurve(reqTrainTmpDict, reqRegrDict, period, segList)
	reqTestDict, ansTestDict = local_getTestData_ByDistrict(districtId, period)
	desPath = "./local/%s" % (districtId)
	if not os.path.isdir(desPath):
		os.mkdir(desPath)
	ret = []	
	for dateId, slices in QDict.iteritems():
		dayId = calcDayId(dateId)
		rY1 = []
		rY2 = []
		rY3 = []
		aY1 = []
		aY2 = []
		aY3 = []
		mapeList = []
		for sliceId in slices:
			perId = (sliceId - 1) / period
			segId = getSegId(segList, perId)
			
			reqRegr = reqRegrDict[dayId][segId]
			tmpNum = reqRegr.predict([[perId]])[0]
			# reqNum = tmpNum / period
			gtNum = reqTestDict[dateId][sliceId]
			reqNum = tmpNum * reqTrainFreq[dayId][perId][(sliceId-1)%period]
			print "gtNum = %s, reqNum = %s" % (gtNum, reqNum)
			
			rY1.append(gtNum)
			rY2.append(reqNum)
			rY3.append(tmpNum/period)
			
			ansRegr = ansRegrDict[dayId][segId]
			tmpNum = ansRegr.predict([[perId]])[0]
			# ansNum = tmpNum / period
			gtNum = ansTestDict[dateId][sliceId]
			ansNum = tmpNum * ansTrainFreq[dayId][perId][(sliceId-1)%period]
			print "gtNum = %s, ansNum = %s" % (gtNum, ansNum)
			
			aY1.append(gtNum)
			aY2.append(ansNum)
			aY3.append(tmpNum/period)
			
			gapNum = max(0, reqNum - ansNum)
			gtNum = reqTestDict[dateId][sliceId] - ansTestDict[dateId][sliceId]
			
			# print "sliceId = %s, reqNum = %s, ansNum = %s, gapNum = %s" % (sliceId, reqNum, ansNum, gapNum)
			print "districtId = %s, dateId = %s, sliceId = %s, gapNum = %s, gtNum = %s" % (districtId, dateId, sliceId, gapNum, gtNum)
			ret.append([districtId, dateId, sliceId, gapNum])
			
			mape = calcMAPE(gapNum, gtNum)
			mapeList.append(mape)
		
		plt.title("predict 01-%2s" % (dateId))
		plt.subplot(2, 1, 1)
		plt.plot(slices, rY1, 'ro-', linewidth=3.5, label='ground truth')
		plt.plot(slices, rY2, 'gs-', linewidth=3.5, label='weight')
		plt.plot(slices, rY3, 'y*-', linewidth=3.5, label='mean')
		plt.legend()
		
		plt.subplot(2, 1, 2)
		plt.plot(slices, aY1, 'ro-', linewidth=3.5, label='ground truth')
		plt.plot(slices, aY2, 'gs-', linewidth=3.5, label='weight')
		plt.plot(slices, aY3, 'y*-', linewidth=3.5, label='mean')
		plt.legend()
		plt.savefig(os.path.join(desPath, '%s_predict.png' % (dateId)), dpi=400)
		plt.show()
		plt.close()
		
		plt.title("MAPE 01-%2s" % (dateId))
		plt.plot(slices, mapeList, 'ro-', linewidth=2.5)
		plt.ylabel('mape')
		plt.xlabel('query')
		plt.grid(True)
		plt.savefig(os.path.join(desPath, '%s_mape.png' % (dateId)), dpi=400)
		plt.show()
		plt.close()
	
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
	plt.savefig("diff.png", dpi=400)
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
	
	
def local_test(districtId = 14):
	getLocalQuery("../query.in")
	ans = localSolve(districtId, period=6)
	localAns = getLocalAns_fast("../local_gap.csv")
	localAns = filter(lambda item: item[0]==districtId, localAns)
	assert len(ans) == len(localAns)
	n = len(ans)
	i = 0
	# show ground truth with predict Result perday.
	desPath = "./local/%s" % (districtId)
	while i < n:
		plt.figure()
		j = i
		while i<n and ans[i][1]==ans[j][1]:
			i += 1
		X = map(lambda item:item[2], ans[j:i])
		Y = map(lambda item:item[3], localAns[j:i])
		Y_ = map(lambda item:item[3], ans[j:i])
		X = np.array(X).reshape(i-j, 1)
		plt.plot(X, Y, 'ro-', linewidth=2.5, label='Ground Truth')
		plt.plot(X, Y_, 'ys-', linewidth=2.5, label='Predict Result')
		plt.title("01-%2d" % (ans[j][1]))
		plt.xlabel('slice')
		plt.ylabel('num')
		plt.legend()
		plt.grid(True)
		plt.savefig(os.path.join(desPath, '%s_gap.png' % (ans[j][1])), dpi=400)
		plt.show()
		plt.close()
		
	
def local_testAll():
	getLocalQuery("../query.in")
	localAns = getLocalAns_fast("local_gap.csv")
	ans = solveAll()
	saveAns(ans, "gap_.csv")
	sliceLen = len(ans) / ndistrict
	tot = 0.0
	totList = []
	for i in xrange(0, len(ans), sliceLen):
		subAns = ans[i:i+sliceLen]
		subAns_ = localAns[i:i+sliceLen]
		for j in xrange(sliceLen):
			if subAns_[j][-1] == 0:
				continue
			tmp = abs((subAns[j][-1] - subAns_[j][-1]) / subAns_[j][-1])
			tot += tmp
			totList.append(tmp)
	score = tot / len(ans)
	print "score = ", score
	
	calcDiff(ans, localAns)
	
	with open("tot.out", "w") as fout:
		fout.write(" ".join(map(str, totList)))

		
if __name__ == "__main__":
	getQuery("../query.in")
	ans = solveAll()
	saveAns(ans)
	
	# local_test(14)
	# for i in xrange(1, ndistrict+1):
		# local_test(i)
	
	# local_testAll()