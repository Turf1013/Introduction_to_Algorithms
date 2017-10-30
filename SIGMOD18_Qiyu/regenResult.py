#!/usr/bin/env python
import os
import sys
from genDataSet import genDesFileName, genDataName
from genDataSet import constForGenDataSet

class constForRegenResult(constForGenDataSet):
	dataSetN = 1
	nprocess = 12

class CFRR(constForRegenResult):
	pass
	

def collectResult(execName, srcFilePath):
	retDict = dict()
	tmpFilePath = os.path.join(srcFilePath, execName)
	dataNames = os.listdir(tmpFilePath)
	for dataName in dataNames:
		dataFilePath = os.path.join(srcFilePath, execName, dataName)
		fileName = "data_00.txt"
		fileName = os.path.join(dataFilePath, fileName)
		lines = []
		with open(fileName, "r") as fin:
			lines = map(lambda x:x.strip(), fin.readlines())
			lines = filter(lambda s:len(s)>0, lines)
		retDict[dataName] = lines
	return retDict
	
	
def parseDataName(s):
	lambda_, alpha, rmax, B, K, mu = s.split(' ')[:6]
	lambda_, alpha = float(lambda_), float(alpha)
	rmax, B, K, mu = int(rmax), int(B), int(K), int(mu)
	return lambda_,alpha,rmax,B,K,mu
	
def parseLine1(s):
	tmpDict = dict()
	tmpList = map(lambda s:s.strip(), s.split(','))
	for s in tmpList:
		itemList = map(lambda s:s.strip(), s.split(' '))
		k = itemList[0]
		v = itemList[2]
		tmpDict[k] = v
	ret = []
	for k in ["costt", "costb", "benefit", "cost"]:
		ret.append(tmpDict[k])
	return ret	
	
	
def dumpResult(execName, tmpDict, desFilePath):
	"""dataName lambda_ alpha costt costb benefit cost execName result time """
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	desFileName = "collect_%s.txt" % (execName)
	desFileName = os.path.join(desFilePath, desFileName)
	with open(desFileName, "w") as fout:
		for dataName,lines in tmpDict.iteritems():
			if "mu" in dataName:
				lambda_,alpha,rmax,B,K,mu = CFBE.defaultValue
			else:
				lambda_,alpha,rmax,B,K,mu = parseDataName(dataName)
			costt, costb, benefit, cost = parseLine1(lines[0])
			line = "%s %.03f %.03f %s %s %s %s %s\n" % (dataName, lambda_, alpha, costtt, costb, benefit, cost, line)
			
	
def exp0():
	srcFilePath = "./result_Qiyu"
	desFilePath = "./collect_Qiyu"
	execNames = ["base", "bao", "sbao"]
	for execName in execNames:
		tmpDict = collectResult(execName, srcFilePath)
		dumpResult(execName, tmpDict)
	
	
if __name__ == "__main__":
	exp0()
	