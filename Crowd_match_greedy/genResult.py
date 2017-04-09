#!/usr/bin/python

import os
import sys
import platform

class constForGenResult:
	WORKERN = "workerN"
	TASKN = "taskN"
	DEGRATE = "degRate"
	UMAX = "Umax"
	paraNameList = [
		"Utility",
		"Time(s)",
		"Memory(MB)",
	]
	
	
class CFGR(constForGenResult):	
	pass
	

def getDistId(s):
	if '.' in s:
		s = s.split('.')[0]
	distId = s[s.rindex('_')+1:]
	return int(distId)
	
	
def getDataSetInfo(s):
	if '.' in s:
		s = s.split('.')[0]
	infoList = map(int, s.split('_'))
	retDict = dict()
	retDict[CFGR.WORKERN] = infoList[0]
	retDict[CFGR.TASKN] = infoList[1]
	retDict[CFGR.DEGRATE] = infoList[2] / 100.0
	retDict[CFGR.UMAX] = infoList[3]
	return retDict
	
	
def getDistSetList(filePath):	
	if not os.path.exists(filePath):
		return []
	distSet = set()
	nameList = os.listdir(filePath)
	for name in nameList:
		distId = getDistId(name)
		distSet.add(distId)
	return list(distSet)
	

def getDataSetList(filePath):
	if not os.path.exists(filePath):
		return []
	nameList = os.listdir(filePath)
	dataNameSet = set()
	inWindows = 'Windows' in platform.system()
	for name in nameList:
		if inWindows:
			tmpPath = filePath + "/" + name
		else:
			tmpPath = os.path.join(filePath, name)
		if os.path.isdir(tmpPath):
			tmpList = os.listdir(tmpPath)
			dataNameSet |= set(tmpList)
	return list(dataNameSet)
	

def toParaList(itemList):
	ret = []
	for item in itemList:
		if item.endswith('KB'):
			item = float(item[:-2])
			item /= 1024.0	# tansfer to MB
		elif item.endswith('s'):
			item = float(item[:-1])
		else:
			item = float(item)
			# try:
				# item = float(item)
			# except:
				# print itemList
		ret.append(item)
	return ret
	
	
def accParaList(aList, bList):	
	bList = toParaList(bList)
	if len(aList) == 0:
		aList.extend(bList)
		return 
		
	if len(aList) != len(bList):
		raise ValueError("accumulate with not equal lists: %d %d" % (len(aList), len(bList)))
	for i in xrange(len(aList)):
		aList[i] += bList[i]
	

def getResultFromFile(fileName):
	ret = []
	with open(fileName, "r") as fin:
		preDataSetName = ""
		paraList = []
		orderN = 0
		execName = ""
		for line in fin:
			itemList = line.strip().split()
			if len(itemList) <= 2:
				print line
				continue
			execName = itemList[0]
			tmpName = itemList[1]
			orderIdx = int(tmpName[tmpName.rindex('order')+5 : tmpName.index('.')])
			curDataSetName = tmpName[:tmpName.rindex('/')]
			if curDataSetName != preDataSetName:
				if orderN > 0:
					tmpList = [execName, int(preDataSetName[preDataSetName.rindex('/')+1:])]
					tmpList.extend(map(lambda x:x*1.0/orderN, paraList))
					ret.append(tmpList)
				# finish accumulate one orders
				paraList = []
				preDataSetName = curDataSetName
				orderN = 0
			orderN += 1
			accParaList(paraList, itemList[2:])
		if orderN > 0:
			tmpList = [execName, int(preDataSetName[preDataSetName.rindex('/')+1:])]
			tmpList.extend(map(lambda x:x*1.0/orderN, paraList))
			ret.append(tmpList)
	return ret
	
	
def getAlgoSet(allResults):
	algoNameSet = set()
	for resultList in allResults:
		for result in resultList:
			algoName = result[0]
			algoNameSet.add(algoName)
	return algoNameSet

	
def getAlgoNum(allResults):
	return getAlgoSet(allResults)
	
	
def dumpResult(allResults):	
	caseSet = set()
	algoNameSet = set()
	algoDict = dict()
	paraN = 0
	for resultList in allResults:
		for result in resultList:
			algoName = result[0]
			algoNameSet.add(algoName)
			caseId = result[1]
			caseSet.add(caseId)
			if algoName not in algoDict:
				algoDict[algoName] = dict()
			algoDict[algoName][caseId] = result[2:]
			paraN = len(result) - 2
	ret = []
	for paraId in xrange(paraN):
		ret.append(CFGR.paraNameList[paraId])
		for algoName in algoNameSet:
			line = algoName
			for caseId in caseSet:
				tmpList = algoDict[algoName][caseId]
				line += " " + str(tmpList[paraId])
			ret.append(line)
	return ret
	
	
def dumpDictToFile(fileName, aDict):
	with open(fileName, "w") as fout:
		for name, allResults in aDict.iteritems():
			dataInfo = name.split('.')[0].split('_')
			workerN = int(dataInfo[0])
			taskN = int(dataInfo[1])
			degRate = int(dataInfo[2]) / 100.0
			Umax = int(dataInfo[3])
			infoLine = "workerN=%d,taskN=%d,degRate=%.2f,Umax=%d" % (workerN, taskN, degRate, Umax)
			fout.write(infoLine + "\n")
			lines = dumpResult(allResults)
			fout.write("\n".join(lines) + "\n")
			fout.write("\n\n")	
	
	
def getResult(srcPath, desPath):
	if not os.path.exists(srcPath):
		raise ValueError("PATH [%s] not exists" % (srcPath))
	if not os.path.exists(desPath):
		os.mkdir(desPath)
	dataSetNameList = getDataSetList(srcPath)
	typeNameList = os.listdir(srcPath)
	typeNameList.sort()
	distIdSet = set(map(getDistId, typeNameList))
	inWindows = 'Windows' in platform.system()
	
	# print dataSetNameList
	# print typeNameList
	# print distIdSet
	
	for distId in distIdSet:
		tmpDict = dict()
		dirList = filter(lambda s:s.endswith(str(distId)), typeNameList)
		for dirName in dirList:
			if inWindows:
				farDataPath = srcPath + "/" + dirName
			else:
				farDataPath = os.path.join(srcPath, dirName)
			curDataSetNameList = os.listdir(farDataPath)
			curDataSetNameList.sort()
			for dataSetName in curDataSetNameList:
				if inWindows:
					dataFileName = farDataPath + "/" + dataSetName
				else:
					dataFileName = os.path.join(farDataPath, dataSetName)
				tmpList = getResultFromFile(dataFileName)
				if dataSetName not in tmpDict:
					tmpDict[dataSetName] = []
				tmpDict[dataSetName].append(tmpList)
		desFileName = "dist_%d.res" % (distId)
		if inWindows:
			desFileName = desPath + "/" + desFileName
		else:
			desFileName = os.path.join(desPath, desFileName)
		dumpDictToFile(desFileName, tmpDict)
	
	
if __name__ == "__main__":
	srcPath = "F:/Log"
	desPath = "F:/Result"
	if len(sys.argv) > 1:
		srcPath = sys.argv[1]
	if len(sys.argv) > 2:
		desPath = sys.argv[2]
	if not os.path.exists(desPath):
		os.mkdir(desPath)
		
	getResult(srcPath, desPath)
	