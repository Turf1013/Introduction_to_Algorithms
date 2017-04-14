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
	# print info orginal name
	algoList = [
		"OPT",
		"Static",
		"RT",
		"Pure",
		"TGOA",
		"Xuan",
		#"TGOA1",
		#"TGOA50",
		#"TGOA99",
	]
	# uppercase as key
	colorDict = {
		'OPT': 		'red',
		'RT': 		'green',
		'STATIC': 	'yellow',
		'PURE': 	'blue',
		'TGOA': 	'cyan',
		'XUAN': 	'magenta',
		#'TGOA1': 	'cyan',
		#'TGOA50': 	'magenta',
		#'TGOA99': 	'peru',
	}
	markDict = {
		'OPT': 		'o',
		'RT': 		's',
		'STATIC': 	'*',
		'PURE': 	'^',
		'TGOA': 	'D',
		'XUAN': 	'd',
		#'TGOA1': 	'D',
		#'TGOA50': 	'x',
		#'TGOA99': 	'd',
	}
	
class CFDR(constForDumpResult):
	pass


def regularPara(line, fileName):
	"""
		only `mu=XXX,deg=XXX,tlen=XXX` permitted
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
	infoLine = fileName[:fileName.rindex('.')]
	taskN, workN, deg, tlen, mu = map(int, infoLine.split('_'))
	tmpDict["tlen"] = tlen
	for name in ["mu", "deg", "tlen"]:
		if name not in tmpDict:
			raise ValueError("%s is incorrect parameter")
		if name=="tlen":
			val = int(tmpDict[name])
		else:
			val = float(tmpDict[name])
		tmpList.append("%s=%s" % (name, val))
	return ",".join(tmpList)


def updateResult(line, fileName, resDict):
	algoName, paraLine, result = line.split(' ')[:3]
	paraLine = regularPara(paraLine, fileName)
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
		elif os.path.isfile(fileName) and fileName.endswith(".log"):
			print fileName
			lines = []
			with open(fileName, "r") as fin:
				lines = fin.readlines()
			for line in lines:
				line = line.strip()
				if re.match(resRe, line):
					updateResult(line, name, resDict)
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


def genParaLine(mu, deg, tlen):
	return "mu=%s,deg=%s,tlen=%s" % (str(mu), str(deg), str(tlen))


def plotPic(fileName, X, YList, title, algoNameList):
	plt.title("%s" % (title))
	mnY, mxY = 10.0**18, -10.0**18
	for i,Y in enumerate(YList):
		algoName = algoNameList[i]
		col = CFDR.colorDict[algoName.upper()]
		marker = CFDR.markDict[algoName.upper()]
		mnY = min(mnY, min(map(float, Y)))
		mxY = max(mxY, max(map(float, Y)))
		plt.plot(X, Y, color=col, linestyle='-', marker=marker, linewidth=2.5, label=algoName)
	plt.ylabel('Utiltiy')
	if title.startswith("deg"):
		plt.xlabel('mu')
	else:
		plt.xlabel('deg')
	if title.startswith("deg"):
		plt.xlim(-0.1, max(X)+0.5)
	else:
		plt.xlim(0, max(X)+4)	
	delta = (mxY - mnY) / 20.0
	plt.ylim(mnY-delta, mxY+delta)
	plt.grid(True)
	plt.legend()
	plt.savefig(fileName, dpi=200)
	plt.show()
	plt.close()


def plotPic_mu(filePath, resDict, tlen, deg, muList):
	fileName = "deg=%.3f.png" % (float(deg))
	fileName = os.path.join(filePath, fileName)
	X = muList
	YList = []
	algoNameList = []
	for algoName in CFDR.algoList:
		paraDict = resDict[algoName]
		algoNameList.append(algoName)
		tmpList = []
		for mu in muList:
			paraLine = genParaLine(mu=mu, deg=deg, tlen=tlen)
			result = paraDict[paraLine]
			tmpList.append(result)
		YList.append(tmpList)
	title = "deg=%s,mu =%s" % (deg, str(muList))
	plotPic(fileName, X, YList, title, algoNameList)



def plotPic_deg(filePath, resDict, tlen, mu, degList):
	fileName = "mu=%s.png" % (mu)
	fileName = os.path.join(filePath, fileName)
	X = range(1, len(degList)+1)
	YList = []
	algoNameList = []
	for algoName in CFDR.algoList:
		paraDict = resDict[algoName]
		algoNameList.append(algoName)
		tmpList = []
		for deg in degList:
			paraLine = genParaLine(mu=mu, deg=deg, tlen=tlen)
			result = paraDict[paraLine]
			tmpList.append(result)
		YList.append(tmpList)
	title = "mu=%s,deg=%s" % (mu, str(degList))
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
	tlenList = map(int, getParaList(resDict, "tlen"))
	tlenList.sort()
	print "degList =", degList
	print "muList =", muList
	print "tlenList =", tlenList
	for tlen in tlenList:
		curFilePath = os.path.join(filePath, "tlen=%d" % (tlen))
		if not os.path.exists(curFilePath):
			os.mkdir(curFilePath)
		for deg in degList:
			plotPic_mu(curFilePath, resDict, tlen, deg, muList)
		for mu in muList:
			plotPic_deg(curFilePath, resDict, tlen, mu, degList)	


if __name__ == "__main__":
	distNameList = [
		"exp",
		"normal",
		"uniform",
	]
	srcPathPrefix = "/home/turf/tmp/logz"
	resPathPrefix = "/home/turf/tmp/resultz"

	for distName in distNameList:	
		srcFilePath = srcPathPrefix + "_" + distName
		desFilePath = resPathPrefix + "_" + distName
		resDict = dict()
		getResult(srcFilePath, resDict)
		resDict = calcAvgVal(resDict)
		dumpRes = dumpResult(desFilePath, resDict)
		plotResult(desFilePath, resDict)
		