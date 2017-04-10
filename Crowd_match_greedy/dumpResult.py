#!/usr/bin/env python

import re
import os
import sys
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt


global resRe
resRe = "^\w+ \w+=[+-\.\d]+,\w+=[+-.\d]+ [+-\.\d]+$"

class constForDumpResult:
	colorDict = {
		'OPT': 		'ro-',
		'RT': 		'gs-',
		'STATIC': 	'y*-',
		'PURE': 	'b^-',
		'TGOA': 	'cD-',
	}
	
class CFDR(constForDumpResult):
	pass


def regularPara(line):
	"""
		only `mu=XXX,deg=XXX` permitted
	"""
	exprList = line.split(',')
	tmpDict = dict()
	for expr in exprList:
		name = expr.split('=')[0]
		val = expr.split('=')[-1]
		if name=="degrate":
			name="deg"
		tmpDict[name] = val
	tmpList = []
	for name in ["mu", "deg"]:
		if name not in tmpDict:
			raise ValueError("%s is incorrect parameter")
		val = float(tmpDict[name])
		tmpList.append("%s=%s" % (name, val))
	return ",".join(tmpList)


def updateResult(line, resDict):
	algoName, paraLine, result = line.split(' ')[:3]
	paraLine = regularPara(paraLine)
	if algoName not in resDict:
		resDict[algoName] = dict()
	if paraLine not in resDict[algoName]:
		resDict[algoName][paraLine] = []
	resDict[algoName][paraLine].append(float(result.strip()))


def getResult(filePath, resDict):
	if not os.path.exists(filePath):
		return
	nameList = os.listdir(filePath)
	for name in nameList:
		fileName = os.path.join(filePath, name)
		if os.path.isdir(fileName):
			getResult(fileName, resDict)
		elif os.path.isfile(fileName):
			lines = []
			with open(fileName, "r") as fin:
				lines = fin.readlines()
			for line in lines:
				line = line.strip()
				if re.match(resRe, line):
					updateResult(line, resDict)
				else:
					print "%s INVALID FORMAT" % (line)


def calcAvgVal(resDict):
	ret = dict()
	for algoName,paraDict in resDict.iteritems():
		ret[algoName] = dict()
		for paraLine, resList in paraDict.iteritems():
			sumVal = sum(resList)
			avgVal = sum(resList) / len(resList)
			ret[algoName][paraLine] = avgVal
	return ret


def dumpResult(filePath, resDict):
	if not os.path.exists(filePath):
		os.mkdir(filePath)
	fileName = "result.txt"
	fileName = os.path.join(filePath, fileName)
	with open(fileName, "w") as fout:
		for algoName,paraDict in resDict.iteritems():
			for paraLine, resVal in paraDict.iteritems():
				line = "%s %s %s\n" % (algoName, paraLine, resVal)
				fout.write(line)


def getParaVal(line, paraName):
	exprList = line.split(',')
	for expr in exprList:
		name = expr.split('=')[0]
		val = expr.split('=')[-1]
		if name == paraName:
			return val
	return None


def getParaList(resDict, paraName):
	paraLineSet = set()
	for algoName,paraDict in resDict.iteritems():
		paraLineSet |= set(paraDict.keys())
	valSet = set()
	for line in paraLineSet:
		val = getParaVal(line, paraName)
		if val:
			valSet.add(val)
	return list(valSet)


def genParaLine(mu, deg):
	return "mu=%s,deg=%s" % (str(mu), str(deg))


def plotPic(fileName, X, YList, title, algoNameList):
	plt.title("%s" % (title))
	mnY, mxY = 10.0**18, -10.0**18
	for i,Y in enumerate(YList):
		algoName = algoNameList[i]
		col = CFDR.colorDict[algoName.upper()]
		mnY = min(mnY, min(map(float, Y)))
		mxY = max(mxY, max(map(float, Y)))
		plt.plot(X, Y, col, linewidth=2.5, label=algoName)
	if 'sky' in fileName:
		plt.ylabel('Utility/mu')
	else:
		plt.ylabel('Utiltiy')
	if title.startswith("deg"):
		plt.xlabel('mu')
	else:
		plt.xlabel('deg')
	plt.xlim(-0.1, max(X)+0.5)
	delta = (mxY - mnY) / 20.0
	plt.ylim(mnY-delta, mxY+delta)
	plt.grid(True)
	plt.legend()
	plt.savefig(fileName, dpi=200)
	plt.show()
	plt.close()


def plotPic_mu(filePath, resDict, deg, muList):
	fileName = "deg=%s.png" % (deg)
	fileName = os.path.join(filePath, fileName)
	X = muList
	YList = []
	algoNameList = []
	for algoName,paraDict in resDict.iteritems():
		algoNameList.append(algoName)
		tmpList = []
		for mu in muList:
			paraLine = genParaLine(mu=mu, deg=deg)
			result = paraDict[paraLine]
			tmpList.append(result)
		YList.append(tmpList)
	title = "deg = %s, mu = %s" % (deg, str(muList))
	plotPic(fileName, X, YList, title, algoNameList)


def plotPic_mu2(filePath, resDict, deg, muList):
	fileName = "sky_deg=%s.png" % (deg)
	fileName = os.path.join(filePath, fileName)
	X = muList
	YList = []
	algoNameList = []
	for algoName,paraDict in resDict.iteritems():
		algoNameList.append(algoName)
		tmpList = []
		for mu in muList:
			paraLine = genParaLine(mu=mu, deg=deg)
			result = paraDict[paraLine]
			tmpList.append(result)
		tmpList = map(lambda x:x/mu, tmpList)
		YList.append(tmpList)
	title = "deg = %s, mu = %s" % (deg, str(muList))
	plotPic(fileName, X, YList, title, algoNameList)



def plotPic_deg(filePath, resDict, mu, degList):
	fileName = "mu=%s.png" % (mu)
	fileName = os.path.join(filePath, fileName)
	X = degList
	YList = []
	algoNameList = []
	for algoName,paraDict in resDict.iteritems():
		algoNameList.append(algoName)
		tmpList = []
		for deg in degList:
			paraLine = genParaLine(mu=mu, deg=deg)
			result = paraDict[paraLine]
			tmpList.append(result)
		YList.append(tmpList)
	title = "mu = %s, deg = %s" % (mu, str(degList))
	plotPic(fileName, X, YList, title, algoNameList)


def plotResult(filePath, resDict):
	if not os.path.exists(filePath):
		os.mkdir(filePath)
	"""
	1. \forall deg \in [0.005, 0.01, 0.02, 0.05, 0.10, 0.20, 0.5, 0.75, 1.00], all mu & algorithms in the same pic;
	2. \forall mu \in [0.1, 0.3, 0.5, 0.7, 0.9], all deg & algorithms in the same pic;
	3. Here should generate |degs|+|mus| pics.
	"""
	degList = map(float, getParaList(resDict, "deg"))
	degList.sort()
	muList = map(float, getParaList(resDict, "mu"))
	muList.sort()
	print "degList =", degList
	print "muList =", muList
	for deg in degList:
		plotPic_mu(filePath, resDict, deg, muList)
	for mu in muList:
		plotPic_deg(filePath, resDict, mu, degList)	
	# skyxuan
	for deg in degList:
		plotPic_mu2(filePath, resDict, deg, muList)


if __name__ == "__main__":
	srcFilePath = "/home/turf/tmp/logz"
	desFilePath = "/home/turf/tmp/resultz"
	resDict = dict()
	getResult(srcFilePath, resDict)
	resDict = calcAvgVal(resDict)
	dumpRes = dumpResult(desFilePath, resDict)
	plotResult(desFilePath, resDict)