#!/usr/bin/env python

import os
import sys


def calc(srcFilePath):
	itemN = 2
	dirNames = os.listdir(srcFilePath)
	dirNames.sort()
	aDict = dict()
	for dirName in dirNames:
		execName = dirName
		faFilePath = os.path.join(srcFilePath, dirName)
		tmpNames = os.listdir(faFilePath)
		print tmpNames
		for tmpName in tmpNames:
			filePath = os.path.join(faFilePath, tmpName)
			fileNames = os.listdir(filePath)
			avgList = [0.] * itemN
			c = 0
			for fileName in fileNames:
				try:
					dataSetId = int(fileName[5:7])
					if dataSetId >= 20:
						continue
				except:
					continue
				fileName = os.path.join(filePath, fileName)
				with open(fileName, "r") as fin:
					line = fin.readlines()[0]
					L = line.split(' ')[1:]
					if "data" in L[0]:
						continue
					# if float(L[0]) >= 1e30:
						# continue
					for i in xrange(itemN):
						avgList[i] += float(L[i])
					c += 1
			for i in xrange(itemN):
				if c>0:
					avgList[i] /= c
				else:
					avgList[i] = 0
			if tmpName not in aDict:
				aDict[tmpName] = []
			aDict[tmpName].append([execName] + avgList)
	with open("F:/tmp/tmp.txt", "w") as fout:
		arrNames = aDict.keys()
		arrNames.sort()
		for arrName in arrNames:
			infoList = aDict[arrName]
			fout.write("%s\n" % (arrName))
			for info in infoList:
				fout.write("%s\n" % (info))
	return aDict

def gao(d):
	ret = ""
	for i in xrange(len(d)):
		if i == 0:
			ret += "%.3f" % (d[i])
		else:
			ret += ", %.3f" % (d[i])
	ret = "[%s]" % (ret)
	return ret

def getALGO(s):
	if s=='gi':
		return 'GreedyInsert'
	elif s=='newsjf':
		return 'newSJF'
	elif s=='newfifo':
		return 'newFIFO'
	elif s=='hybrid':
		return 'Hybrid'
	elif s=='mft':
		return 'MFT'
	elif s=='staticdd':
		return 'tspDD'
	elif s=='staticsjf' or s=='srrndsjf':
		return 'tspSJF'
	elif s=='staticfifo' or s=='srrndfifo':
		return 'tspFIFO'
	elif s=='staticHSTsjf' or s=='srhstsjf':
		return 'hstSJF'
	elif s=='staticHSTfifo' or s=='srhstfifo':
		return 'hstFIFO'
	else:
		return 'None'

def findResult(d, arr, algoNames):
	itemN = 3
	tmpDict = dict()
	if arr not in d:
		for algoName in algoNames:
			tmpDict[algoName] = [0.0] * itemN
		return tmpDict
	infoList = d[arr]
	for tmpList in infoList:
		tmpDict[tmpList[0]] = tmpList[1:]
	for algoName in algoNames:
		if algoName not in tmpDict:
			tmpDict[algoName] = [0.0] * itemN
	return tmpDict


def turnToLine(d, id, algoNames):
	# algoNames = ["gi", "newsjf", "newfifo", "hybrid", "mft", "staticsjf", "staticfifo", "staticdd", "srhstfifo", "srhstsjf", "srrndfifo", "srrndsjf"]
	aDict = dict()
	bDict = dict()
	algoNames = list(set(algoNames) & set(d.keys()))
	for algoName in algoNames:
		resList,timeList = [],[]
		tmpList = d[algoName]
		for l in tmpList:
			resList.append(float(l[0]))
			timeList.append(float(l[1]))
		aDict[algoName] = resList
		bDict[algoName] = timeList
	ret = ""
	for algoName in algoNames:
		preName = getALGO(algoName)
		tmpName = preName + str(id)
		# ret += "%-14s = %s;\n" % (tmpName, gao(aDict[algoName]))
		ret += "%-14s = log(%s);\n" % (tmpName, gao(aDict[algoName]))
	for algoName in algoNames:
		preName = getALGO(algoName)
		tmpName = preName + str(id+1)
		# ret += "%-14s = %s;\n" % (tmpName, gao(bDict[algoName]))
		ret += "%-14s = log(%s);\n" % (tmpName, gao(bDict[algoName]))
	return ret

def genTmpFileName(N, C, M, Tmax):
	return "%02d_%02d_%04d_%03d" % (N, C, M, Tmax)

def getResult(aDict, nV):
	algoNames = ["gi", "newsjf", "newfifo", "hybrid", "mft", "srhstfifo", "srhstsjf", "srrndfifo", "srrndsjf"]
	resDict = dict()
	idx = 1
	line = ""
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120

	# varying of binN
	workerNList = [10, 20, 30, 40, 50]
	for N in workerNList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpDict = findResult(aDict, tmpFilePath, algoNames)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx, algoNames)
	idx += 2
	resDict = dict()
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120

	# varying of capacity
	capacityList = range(1, 16)
	for C in capacityList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpDict = findResult(aDict, tmpFilePath, algoNames)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx, algoNames)
	idx += 2
	resDict = dict()
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120

	# varying of orderN
	orderNList = [200, 500, 1000, 2000, 3000]
	for M in orderNList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpDict = findResult(aDict, tmpFilePath, algoNames)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx, algoNames)
	idx += 2
	resDict = dict()
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120

	return line


def getResult1(aDict, nV):
	algoNames = ["gi", "newsjf", "newfifo", "hybrid", "mft", "srhstfifo", "srhstsjf", "staticfifo", "staticsjf", "staticdd"]
	resDict = dict()
	idx = 3
	line = ""
	V, N, C, M, Tmax = nV, 1, 8, 200, 120

	# varying of capacity
	capacityList = range(1, 16)
	for C in capacityList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpDict = findResult(aDict, tmpFilePath, algoNames)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx, algoNames)
	idx += 2
	resDict = dict()
	V, N, C, M, Tmax = nV, 1, 8, 200, 120

	# varying of orderN
	orderNList = [50, 100, 200, 300, 500]
	for M in orderNList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpDict = findResult(aDict, tmpFilePath, algoNames)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx, algoNames)
	idx += 2
	resDict = dict()
	V, N, C, M, Tmax = nV, 1, 8, 200, 120

	return line

def exp1():
	desFilePath = "F:/tmp/experiment_v1020"
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	for i in xrange(1,4):
		srcFilePath = "F:/tmp/result_SIGMOD_%d" % (i)
		if not os.path.exists(srcFilePath):
			continue
		fileNames = os.listdir(srcFilePath)
		for fileName in fileNames:
			nV = int(fileName[fileName.rindex('_')+1:])
			tmpFilePath = os.path.join(srcFilePath, fileName)
			aDict = calc(tmpFilePath)
			if i%2==0:
				line = getResult(aDict, nV)
			else:
				line = getResult1(aDict, nV)
			if i<=1:	
				desTmpName = "mutliVehicles"
			else:
				desTmpName = "oneVehicle"
			desTmpName = os.path.join(desFilePath, desTmpName)
			if not os.path.exists(desTmpName):
				os.mkdir(desTmpName)
			desFileName = "result_nV_%d.txt" % (nV)
			desFileName = os.path.join(desTmpName, desFileName)
			with open(desFileName, "w") as fout:
				fout.writelines(line)
			
if __name__ == "__main__":
	exp1()
