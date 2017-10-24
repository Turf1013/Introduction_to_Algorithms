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
					if dataSetId >= 10:
						continue
				except:
					continue
				fileName = os.path.join(filePath, fileName)
				with open(fileName, "r") as fin:
					line = fin.readlines()[0]
					L = line.split(' ')[1:]
					if "data" in L[0]:
						continue
					if float(L[0]) >= 1073741825:
						continue
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
			# avgList.append(0.0)
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
	if s=='opq':
		return 'OPQ'
	elif s=='opqe' or s=='opqe2':
		return 'OPQ_Extended'
	elif s=='cip':
		return 'Baseline'
	elif s=='greedy' or s=='greedyf':
		return 'Greedy'
	else:
		return 'None'
	
def findResult(algoNames, d, arr):
	itemN = 3
	# algoNames = ["cip", "greedy", "opqe", "opq"]
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
	
	
def turnToLine(algoNames, d, id):	
	# algoNames = ["cip", "greedy", "opqe", "opq"]
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
		ret += "%-14s = %s;\n" % (tmpName, gao(aDict[algoName]))
	for algoName in algoNames:
		preName = getALGO(algoName)
		tmpName = preName + str(id+1)
		if algoName=='cip':
			ret += "%-14s = 5 * %s;\n" % (tmpName, gao(bDict[algoName]))
		else:
			ret += "%-14s = %s;\n" % (tmpName, gao(bDict[algoName]))
	return ret
	
def getHomoName(binN, taskN, relia):
	return "%02d_%05d_%.02f" % (binN, taskN, relia)
	
def getResult_Heter(aDict):
	algoNames = ["cip", "greedy", "opqe2"]
	resDict = dict()
	idx = 1
	line = ""
	taskN = 10 ** 4
	
	# varying of distribution of threshold(normal)
	muList = [0.88, 0.90, 0.92, 0.94, 0.96]
	sigma = 0.03
	for mu in muList:
		tmpFilePath = "varying_nmu_%.02f" % (mu)
		tmpDict = findResult(algoNames, aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += 2
	resDict = dict()
	
	sigmaList = [0.01, 0.02, 0.03, 0.04, 0.05]
	mu = 0.92
	for sigma in sigmaList:
		tmpFilePath = "varying_nsigma_%.02f" % (sigma)
		tmpDict = findResult(algoNames, aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += 2
	resDict = dict()
	
	# varying of distribution of threshold(uniform)
	meanList = [0.88, 0.90, 0.92, 0.94, 0.96]
	for mean in meanList:
		tmpFilePath = "varying_umean_%.02f" % (mean)
		tmpDict = findResult(algoNames, aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += 2
	resDict = dict()

	# varying of distribution of threshold(heavy tailed)
	meanList = [0.88, 0.90, 0.92, 0.94, 0.96]
	for mean in meanList:
		tmpFilePath = "varying_emean_%.02f" % (mean)
		tmpDict = findResult(algoNames, aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += 2
	resDict = dict()
	
	with open("F:/tmp/tmp2.txt", "w") as fout:
		fout.writelines(line)

def getResult_Home(aDict):
	algoNames = ["cip", "greedy", "opq"]
	resDict = dict()
	idx = 1
	line = ""
	binN,relia,taskN = 20,0.9,10**4
	
	# varying of relia
	reliaList = [0.88, 0.90, 0.92, 0.94, 0.96]
	for relia in reliaList:
		tmpFilePath = getHomoName(binN, taskN, relia)
		tmpDict = findResult(algoNames, aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += 2
	resDict = dict()
	binN,relia,taskN = 20,0.9,10**4
	
	# varying of binN
	binList = [2,4,6,8,10,15,20,25,30,35,40]
	for binN in binList:
		tmpFilePath = getHomoName(binN, taskN, relia)
		tmpDict = findResult(algoNames, aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += 2
	resDict = dict()
	binN,relia,taskN = 20,0.9,10**4
	
	# varying of scalability
	taskNList = [10000, 20000, 30000, 50000, 75000, 100000]
	for taskN in taskNList:
		tmpFilePath = getHomoName(binN, taskN, relia)
		tmpDict = findResult(algoNames, aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(algoNames, resDict, idx)
	idx += 2
	resDict = dict()
	binN,relia,taskN = 20,0.9,10**4
	
	with open("F:/tmp/tmp2.txt", "w") as fout:
		fout.writelines(line)
		
	
def exp_Heter():
	srcFilePath = "F:/tmp/result_SLADE_Fetch/Heter"
	aDict = calc(srcFilePath)
	getResult_Heter(aDict)
	
def exp_Jelly():
	srcFilePath = "F:/tmp/result_SLADE_Fetch/Jelly"
	aDict = calc(srcFilePath)
	getResult_Home(aDict)

def exp_SMIC():
	srcFilePath = "F:/tmp/result_SLADE_Fetch/SMIC"
	aDict = calc(srcFilePath)
	getResult_Home(aDict)	
	
	
if __name__ == "__main__":
	exp_Heter()
	# exp_Jelly()
	# exp_SMIC()
	
	