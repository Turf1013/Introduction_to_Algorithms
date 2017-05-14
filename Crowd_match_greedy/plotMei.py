#!/usr/bin/env python

import os
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

class constForPlot:
	colorDict = {
		'OPT': 		'red',
		'Pure':		'green',
		'MeiT_avg': 'yellow',
		'MeiT_min': 'purple',
		'MeiN_avg': 'brown',
		'MeiN_min': 'pink',
		'PureT': 	'blue',
		'PureN': 	'cyan',
	}
	execNameList = [
		"OPT",
		"Pure",
		"PureT",
		"PureN",
		"MeiT",
		"MeiN",
	]
	lineFormatDict = {
		'OPT': 'ro-',
		'Pure': 'gs-',
		'MeiT': 'bd-',
		'MeiN': 'bd-',
	}

class CFP(constForPlot):
	pass


def fetchLines(fileName):
	lines = []
	with open(fileName, "r") as fin:
		lines = fin.readlines()
	return lines


def filterLogFile(feat, fileNames):
	ret = []
	for name in fileNames:
		if feat in name:
			ret.append(name)
	return ret


def calcMeiDict(resDict):
	retMinDict = dict()
	retAvgDict = dict()
	tmpDict = dict()
	for fileName, resLine in resDict.iteritems():
		keyName = fileName[:fileName.rindex('_')] + ".log"
		if keyName not in tmpDict:
			tmpDict[keyName] = list()
		itemList = resLine.strip().split()
		utility = float(itemList[1])
		tmpDict[keyName].append(utility)

	for keyName, tmpList in tmpDict.iteritems():
		mn = min(tmpList)
		mnFileName = keyName[:keyName.index('.')] + "_min.log"
		retMinDict[mnFileName] = mn
		avg = sum(tmpList) * 1.0 / len(tmpList)
		avgFileName = keyName[:keyName.index('.')] + "_avg.log"
		retAvgDict[avgFileName] = avg
	return retMinDict, retAvgDict


def calcPureDict(resDict):
	retMinDict = dict()
	# retAvgDict = dict()
	tmpDict = dict()
	for fileName, resLine in resDict.iteritems():
		keyName = fileName[:fileName.rindex('_')] + ".log"
		if keyName not in tmpDict:
			tmpDict[keyName] = list()
		itemList = resLine.strip().split()
		utility = float(itemList[1])
		tmpDict[keyName].append(utility)

	for keyName, tmpList in tmpDict.iteritems():
		mn = min(tmpList)
		mnFileName = keyName[:keyName.index('.')] + ".log"
		retMinDict[mnFileName] = mn
		# avg = sum(tmpList) * 1.0 / len(tmpList)
		# avgFileName = keyName[:keyName.index('.')] + ".log"
		# retAvgDict[avgFileName] = avg
	return retMinDict


def calcOtherDict(resDict):
	retDict = dict()
	for fileName, resLine in resDict.iteritems():
		itemList = resLine.strip().split()
		val = float(itemList[1])
		retDict[fileName] = val
	return retDict


def getOrderId(x):
	return int(x[3:x.index('_')]) 

def getBound(x):
	return int(x[x.rindex('_')+1 : x.rindex('.')])

def getDataSetName(x):
	if x.count('_')==2:
		return x[:x.rindex('_')]
	else:
		return x[:x.rindex('.')]


def cmp_dataSetName(sx, sy):
	xid = getOrderId(sx)
	yid = getOrderId(sy)
	return cmp(xid, yid)


def plotToFile(resDict, desFilePath):
	algoNames = [
		"OPT",
		"Pure",
		"MeiT_min",
		"MeiN_min",
		"MeiT_avg",
		"MeiN_avg",
		"PureT",
		"PureN",
	]
	barWidth = 0.4
	dataSetSize = 5

	dataSetNames = resDict["OPT"].keys()
	dataSetNames.sort(cmp=cmp_dataSetName)
	# print dataSetNames
	dataSetNum = len(dataSetNames)
	for bidx in xrange(0, dataSetNum, dataSetSize):
		desFileName = "utility_%d_%d.png" % (bidx, bidx+dataSetSize)
		desFileName = os.path.join(desFilePath, desFileName)
		curDataSetNames = dataSetNames[bidx : bidx+dataSetSize]
		orderIds = map(getOrderId, curDataSetNames)
		n = len(curDataSetNames)
		ind = np.arange(n) * (barWidth*(len(algoNames)+3.5))
		mnv, mxv = 10**20, -10**20
		for i,algoName in enumerate(algoNames):
			tmpNames = map(lambda i: "res%d_%s.log" %(i, algoName), orderIds)
			tmpDict = resDict[algoName]
			# print tmpNames
			# print tmpDict
			tmpResult = map(lambda x: tmpDict[x], tmpNames)
			plt.bar(ind+i*barWidth, tmpResult, barWidth, color=CFP.colorDict[algoName], label=algoName)
			mnv = min(mnv, min(tmpResult))
			mxv = max(mxv, max(tmpResult))

		xind = (ind + (len(algoNames)-1)*barWidth/2.0)
		plt.xlabel('dataSetId')
		plt.ylabel('utility')
		plt.title('utility %s' % (str(orderIds)))
		plt.xlim(0, ind[-1]+(len(algoNames)-1)*barWidth+10.0)
		plt.xticks(xind, map(str, orderIds))
		plt.ylim(mnv*0.985, mxv*1.01)
		plt.legend()
		plt.savefig(desFileName, dpi=800, bbox_inches='tight')
		plt.show()
		plt.close()


def printResultDict(resDict):
	for algoName,tmpDict in resDict.iteritems():
		for logName,resLine in tmpDict.iteritems():
			print algoName, logName, resLine


def plotDataSet(srcFilePath, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	logFileNames = os.listdir(srcFilePath)
	resultDict = dict()
	for execName in CFP.execNameList:
		curLogFileNames = filterLogFile(execName, logFileNames)
		# print execName, curLogFileNames
		tmpDict = dict()
		for logFileName in curLogFileNames:
			curLogFileName = os.path.join(srcFilePath, logFileName)
			resLine = fetchLines(curLogFileName)[0]
			tmpDict[logFileName] = resLine
		if execName.startswith("Mei"):
			mnDict, avgDict = calcMeiDict(tmpDict)
			resultDict[execName+"_avg"] = avgDict
			resultDict[execName+"_min"] = mnDict
		elif execName.startswith("Pure") and len(execName)>4:
			mnDict = calcPureDict(tmpDict)
			resultDict[execName] = mnDict
		else:
			tmpDict = calcOtherDict(tmpDict)
			resultDict[execName] = tmpDict
	# printResultDict(resultDict)
	plotToFile(resultDict, desFilePath)


def plotResult(srcFilePath, desFileFarPath):
	if not os.path.exists(desFileFarPath):
		os.mkdir(desFileFarPath)
	dataSetNames = os.listdir(srcFilePath)
	for dataSetName in dataSetNames:
		dataSetFileName = os.path.join(srcFilePath, dataSetName)
		desFilePath = os.path.join(desFileFarPath, dataSetName)
		# print dataSetFileName
		plotDataSet(dataSetFileName, desFilePath)


def plotToFile2(execName, resDict, desFarFilePath):
	desFilePath = os.path.join(desFarFilePath, execName)
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	keyNames = resDict[execName].keys()
	dataSetNames = list(set(map(getDataSetName, keyNames)))
	boundList = list(set(map(getBound, keyNames)))
	boundList.sort()
	dataSetNum = len(dataSetNames)
	if execName=='MeiT':
		mxb = 3600
	else:
		mxb = 10**4
	rateList = map(lambda x:x*1.0/mxb, boundList)
	rateList = map(lambda x:"%.2f" %(x), rateList)
	algoNames = resDict.keys()
	xList = range(1, len(boundList)+1)

	for bidx in xrange(dataSetNum):
		desFileName = "utility_%s_%d.png" % (execName, bidx)
		desFileName = os.path.join(desFilePath, desFileName)
		curDataSetNames = dataSetNames[bidx]
		
		mnv, mxv = 10**20, -10**20
		for algoName in algoNames:
			tmpDict = resDict[algoName]
			if not algoName.startswith("Mei"):
				tmpName = "res%d_%s.log" % (bidx, algoName)
				val = tmpDict[tmpName]
				yList = [val] * len(xList)
			else:
				yList = []
				for bound in boundList:
					tmpName = "res%d_%s_%d.log" % (bidx, algoName, bound)
					val = tmpDict[tmpName]
					yList.append(val)

			plt.plot(xList, yList, CFP.lineFormatDict[algoName], linewidth=2.5, label=algoName)
			mnv = min(mnv, min(yList))
			mxv = max(mxv, max(yList))

		plt.xlabel('rate')
		plt.ylabel('utility')
		plt.title('utility %s' % (str(bidx)))
		plt.xlim(0, len(boundList)+2)
		plt.xticks(range(0, len(boundList)+2), [""]+rateList+[""])
		plt.ylim(mnv*0.985, mxv*1.01)
		plt.grid()
		plt.legend()
		plt.savefig(desFileName, dpi=400, bbox_inches='tight')
		plt.show()
		plt.close()



def plotBound(srcFilePath, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	logFileNames = os.listdir(srcFilePath)
	resDict = dict()
	for execName in ["OPT", "Pure", "MeiT", "MeiN"]:
		curLogFileNames = filterLogFile(execName, logFileNames)
		# print execName, curLogFileNames
		tmpDict = dict()
		for logFileName in curLogFileNames:
			curLogFileName = os.path.join(srcFilePath, logFileName)
			resLine = fetchLines(curLogFileName)[0]
			tmpDict[logFileName] = resLine
		tmpDict = calcOtherDict(tmpDict)
		resDict[execName] = tmpDict
		if execName.startswith("Mei"):
			plotToFile2(execName, resDict, desFilePath)
			resDict.pop(execName)


def plotResult_ByBound(srcFilePath, desFileFarPath):
	if not os.path.exists(desFileFarPath):
		os.mkdir(desFileFarPath)
	dataSetNames = os.listdir(srcFilePath)
	for dataSetName in dataSetNames:
		dataSetFileName = os.path.join(srcFilePath, dataSetName)
		desFilePath = os.path.join(desFileFarPath, dataSetName)
		plotBound(dataSetFileName, desFilePath)

if __name__ == "__main__":
	srcFilePath = "/home/turf/dataSet/dataSet_v0513/log"
	desFilePath = "/home/turf/dataSet/dataSet_v0513/result"
	# plotResult(srcFilePath, desFilePath)
	plotResult_ByBound(srcFilePath, desFilePath)
