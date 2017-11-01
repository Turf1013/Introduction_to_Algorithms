#!/usr/bin/env python
import os
import sys
import commands
import multiprocessing

from genDataSet import CFGD, genDataName

class constForGenExperiment(CFGD):
	itemN = 2
	pass

class CFGE(constForGenExperiment):
	pass

def readLines(srcFileName):
	ret = []
	with open(srcFileName, "r") as fin:
		ret = fin.readlines()[-1:]
	return ret

def readResult(srcFilePath):
	execNames = sorted(os.listdir(srcFilePath))
	retDict = dict()
	for execName in execNames:
		dataNames = os.listdir(os.path.join(srcFilePath, execName))
		for dataName in dataNames:
			dataFilePath = os.path.join(srcFilePath, execName, dataName)
			fileNames = sorted(os.listdir(dataFilePath))
			avgList = [0.] * CFGE.itemN
			c = 0
			for fileName in fileNames:
				srcFileName = os.path.join(dataFilePath, fileName)
				line = readLines(srcFileName)[0]
				print srcFileName,line
				if "invalid" in line:
					continue
				itemList = line.split(' ')[1:]
				for i in xrange(CFGE.itemN):
					avgList[i] += float(itemList[i])
					c += 1
			for i in xrange(CFGE.itemN):
				if c==0:
					avgList[i] = 0.0
				else:
					avgList[i] /= c
				if i==0:
					avgList[i] += 5.0
			if dataName not in retDict:
				retDict[dataName] = []
			resultList = [execName] + avgList
			retDict[dataName].append(resultList)
	return retDict

def getMatName(s):
	return s
	
def genMuName(s):
	return "mu_%s" % (s) 
	
def findResult(algoNames, resDict, dataName):
	retDict = dict()
	logList = resDict[dataName]
	for tmpList in logList:
		retDict[tmpList[0]] = tmpList[1:]
	for algoName in algoNames:
		if algoName not in retDict:
			print "%s has no log in [%s]" % (algoName, dataName)
			retDict[algoName] = [0.0] * CFGE.itemN
	return retDict

def turnToLine(algoNames, resDict, idx):
	ret = ""
	for i in xrange(CFGE.itemN):
		for algoName in algoNames:
			values = []
			for tmpList in resDict[algoName]:
				values.append(tmpList[i])
			matlabName = getMatName(algoName) + str(idx+i)
			ret += "%-10s = %s;\n" % (matlabName, values)
	return ret

def genExperiment(srcFilePath, desFileName, algoNames):
	# \TODO
	idx = 1
	line = ""

	logDict = readResult(srcFilePath)

	# varying of lambda
	resDict = dict()
	lambda_,alpha,rmax,B,K,mu = CFGE.defaultValue
	for lambda_ in CFGD.lambdaList:
		dataName = genDataName(lambda_, alpha, rmax, B, K, mu)
		tmpDict = findResult(algoNames, logDict, dataName)
		for algoName, tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += CFGE.itemN

	# varying of alpha
	resDict = dict()
	lambda_,alpha,rmax,B,K,mu = CFGE.defaultValue
	for alpha in CFGD.alphaList:
		dataName = genDataName(lambda_, alpha, rmax, B, K,mu)
		tmpDict = findResult(algoNames, logDict, dataName)
		for algoName, tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += CFGE.itemN

	# varying of rmax
	resDict = dict()
	lambda_,alpha,rmax,B,K,mu = CFGE.defaultValue
	for rmax in CFGD.rmaxList:
		dataName = genDataName(lambda_, alpha, rmax, B, K,mu)
		tmpDict = findResult(algoNames, logDict, dataName)
		for algoName, tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += CFGE.itemN

	# varying of B
	resDict = dict()
	lambda_,alpha,rmax,B,K,mu = CFGE.defaultValue
	for B in CFGD.bList:
		dataName = genDataName(lambda_, alpha, rmax, B, K,mu)
		tmpDict = findResult(algoNames, logDict, dataName)
		for algoName, tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += CFGE.itemN

	# varying of K
	resDict = dict()
	lambda_,alpha,rmax,B,K,mu = CFGE.defaultValue
	for K in CFGD.kList:
		dataName = genDataName(lambda_, alpha, rmax, B, K,mu)
		tmpDict = findResult(algoNames, logDict, dataName)
		for algoName, tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += CFGE.itemN
	
	# varying of distribution
	resDict = dict()
	lambda_,alpha,rmax,B,K,mu = CFGE.defaultValue
	for mu in CFGD.muList:
		dataName = genMuName(mu)		
		tmpDict = findResult(algoNames, logDict, dataName)
		for algoName, tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += CFGE.itemN

	with open(desFileName, "w") as fout:
		fout.write(line)

def exp0():
	srcFilePath = "F:/tmp_Qiyu/result_Qiyu"
	desFileName = "F:/tmp/tmp.txt"
	# algoNames = ["ibase", "ibao", "isbao"]
	algoNames = ["base", "bao", "sbao"]
	genExperiment(srcFilePath, desFileName, algoNames)

if __name__ == "__main__":
	exp0()
