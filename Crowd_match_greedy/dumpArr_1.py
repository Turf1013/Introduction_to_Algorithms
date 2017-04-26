#!/usr/bin/env python

import os
import sys
from copy import deepcopy


algoDict = {
	"OPT" : "opt",
	"TGIA": "fgoa",
	"Greedy": "fgoag",
	"Ext": "extended",
	"Pure": "simg",
}

def calcNewFileName(s):
	ret = s[:s.rindex('.')] + ".out"
	return ret


def dump(fileName, lines):
	with open(fileName, "w") as fout:
		fout.writelines(lines)

def gaoSenderNewLines(allDict, fileName):
	capList = [1, 2, 5, 10, 20]
	ret = []
	for i in xrange(1, 4):
		for algo in algoDict.itervalues():
			tmpDict = allDict[algo]
			tmpList = []
			for cap in capList:
				info = "EverySender_cap%d" % (cap)
				line = tmpDict[info].strip()
				item = line.split(' ')[i]
				tmpList.append(item)
			tmpLine = "[" + ", ".join(tmpList) + "]"
			line = "%s = %s;\n" % (algo, tmpLine)
			ret.append(line)
		ret.append("\n")
	ret.append("\n\n")
	return ret

def gaogMisNewLines(allDict, fileName):
	capList = [1, 2, 3]
	ret = []
	for i in xrange(1, 4):
		algoList = algoDict.values()
		for algo in algoList:
			tmpDict = allDict[algo]
			tmpList = []
			for cap in capList:
				info = "gMission_cap%d" % (cap)
				line = tmpDict[info].strip()
				item = line.split(' ')[i]
				tmpList.append(item)
			tmpLine = "[" + ", ".join(tmpList) + "]"
			line = "%s = %s;\n" % (algo, tmpLine)
			ret.append(line)
		ret.append("\n")
	ret.append("\n\n")
	return ret

def gaoExpNewLines(allDict, fileName):
	eList = [1, 3, 5, 7, 9]
	ret = []
	for i in xrange(1, 4):
		for algo in algoDict.itervalues():
			tmpDict = allDict[algo]
			tmpList = []
			for e in eList:
				info = "e%d_500_2500_5_20_5_10_6" % (e)
				line = tmpDict[info].strip()
				item = line.split(' ')[i]
				tmpList.append(item)
			tmpLine = "[" + ", ".join(tmpList) + "]"
			line = "%s = %s;\n" % (algo, tmpLine)
			ret.append(line)
		ret.append("\n")
	ret.append("\n\n\n\n")

	pList = [2, 5, 10, 20, 50]
	for i in xrange(1, 4):
		for algo in algoDict.itervalues():
			tmpDict = allDict[algo]
			tmpList = []
			for p in pList:
				info = "e5_500_2500_5_20_5_%d_6" % (p)
				line = tmpDict[info].strip()
				item = line.split(' ')[i]
				tmpList.append(item)
			tmpLine = "[" + ", ".join(tmpList) + "]"
			line = "%s = %s;\n" % (algo, tmpLine)
			ret.append(line)
		ret.append("\n")
	ret.append("\n\n\n\n")
	return ret


def gaoNSNewLines(allDict, fileName):
	nList = [1.25,2.5,3.75,5,6.25]
	ret = []
	for i in xrange(1, 4):
		for algo in algoDict.itervalues():
			tmpDict = allDict[algo]
			tmpList = []
			for n in nList:
				info = "ns%s_500_2500_5_20_5_10_6" % (str(n))
				line = tmpDict[info].strip()
				item = line.split(' ')[i]
				tmpList.append(item)
			tmpLine = "[" + ", ".join(tmpList) + "]"
			line = "%s = %s;\n" % (algo, tmpLine)
			ret.append(line)
		ret.append("\n")
	ret.append("\n\n\n\n")
	return ret


def gaoNormNewLines(allDict, fileName):
	nList = [2.5,3.75,5,6.25,7.5]
	ret = []
	for i in xrange(1, 4):
		for algo in algoDict.itervalues():
			tmpDict = allDict[algo]
			tmpList = []
			for n in nList:
				info = "n%s_500_2500_5_20_5_10_6" % (str(n))
				line = tmpDict[info].strip()
				item = line.split(' ')[i]
				tmpList.append(item)
			tmpLine = "[" + ", ".join(tmpList) + "]"
			line = "%s = %s;\n" % (algo, tmpLine)
			ret.append(line)
		ret.append("\n")
	ret.append("\n\n\n\n")

	pList = [2, 5, 10, 20, 50]
	for i in xrange(1, 4):
		for algo in algoDict.itervalues():
			tmpDict = allDict[algo]
			tmpList = []
			for p in pList:
				info = "n5_500_2500_5_20_5_%d_6" % (p)
				line = tmpDict[info].strip()
				item = line.split(' ')[i]
				tmpList.append(item)
			tmpLine = "[" + ", ".join(tmpList) + "]"
			line = "%s = %s;\n" % (algo, tmpLine)
			ret.append(line)
		ret.append("\n")
	ret.append("\n\n\n\n")
	return ret

def gaoSCANewLines(allDict, fileName):
	tList = [1,2,3,4,5,10]
	ret = []
	for algo in ["simg", "fgoag"]:
		ret.append("%s\n" % (algo))
		for i in xrange(1, 4):
			for workerN in [500, 1000, 2500]:
				tmpDict = allDict[algo]
				tmpList = []
				for t in tList:
					info = "sca%d%dw" % (workerN, t)
					line = tmpDict[info].strip()
					item = line.split(' ')[i]
					tmpList.append(item)
				tmpLine = "[" + ", ".join(tmpList) + "]"
				line = "%s = %s;\n" % (algo, tmpLine)
				ret.append(line)
			ret.append("\n")
		ret.append("\n\n\n\n")
	return ret


def gaoNewLines(tmpDict, fileName):
	if "Sender" in fileName:
		return gaoSenderNewLines(tmpDict, fileName)
	elif "exp" in fileName:
		return gaoExpNewLines(tmpDict, fileName)
	elif "normal" in fileName:
		return gaoNormNewLines(tmpDict, fileName)
	elif "gMission" in fileName:
		return gaogMisNewLines(tmpDict, fileName)
	elif "sca" in fileName:
		return gaoSCANewLines(tmpDict, fileName)
	elif "ns" in fileName:
		return gaoNSNewLines(tmpDict, fileName)
	else:
		raise ValueError("invalid gao new lines")


def dumpPlotArray(fileName):
	with open(fileName, "r") as fin:
		lines = fin.readlines()
	newLines = []
	n = len(lines)
	i = 0
	allDict = dict()
	while i < n:
		line = lines[i].strip()
		if line:
			if line in algoDict:
				algoName = algoDict[line]
			else:
				algoName = "fgoa"
			i += 1
			tmpDict = dict()
			while i<n:
				line = lines[i].strip()
				if not line:
					break
				info = line[:line.index(':')]
				tmpDict[info] = line[line.index(':')+1:]
				i += 1
			allDict[algoName] = tmpDict
		else:
			i += 1
	newLines = gaoNewLines(allDict, fileName)
	dump(calcNewFileName(fileName), newLines)

class constForPlotPaper:
	algoNameList = [
		"Ext",
		"Greedy",
		"TGOA",
		"Pure",
		"OPT",
	]
	algoReNameDict = {
		"Ext" : "extended",
		"Greedy": "tgoag",
		"TGOA": "tgoa",
		"Pure": "simg",
		"OPT": "opt",
	}
	colorDict = {
		'Ext': 		'blue',
		'Pure': 	'black',
		'Greedy': 	'green',
		'OPT': 		'pink',
		'TGOA':		'red'
	}
	markDict = {
		'Ext': 		'o',
		'Pure': 	'*',
		'Greedy': 	'd',
		'OPT': 		's',
		'TGOA': 	'x',
	}

class CFPP(constForPlotPaper):
	pass


def resultDict(filePath):
	retDict = dict()
	algoList = os.listdir(filePath)
	for algoName in algoList:
		curFilePath = os.path.join(filePath, algoName)
		retDict[algoName] = dict()
		nameList = filter(lambda x:x.endswith(".log"), os.listdir(curFilePath))
		for name in nameList:
			fileName = os.path.join(curFilePath, name)
			with open(fileName, "r") as fin:
				line = fin.readlines()[0].strip()
			if line:
				info = name[:name.rindex('.')]
				retDict[algoName][info] = line
	return retDict


def mergeTime(aDict):
	algoSet = filter(lambda x:not x.endswith("Mem"), aDict.keys())
	retDict = dict()
	for algoName in algoSet:
		retDict[algoName] = dict()
		if algoName not in aDict:
			continue
		clkDict = aDict[algoName]
		if algoName+"Mem" in aDict:
			memDict = aDict[algoName+"Mem"]
		else:
			memDict = None
		for infoName in clkDict.iterkeys():
			clkLine = clkDict[infoName]
			if memDict:
				memLine = memDict[infoName]
			else:
				memLine = "%s %s" % (clkLine.rstrip(), "0.0")
			tmpList = memLine.split(' ')
			tmpClk = float(clkLine.split(' ')[-1])
			# print tmpClk, float(tmpList[-2])
			tmpClk = min(tmpClk, float(tmpList[-2]))
			tmpList[-2] = str(tmpClk)
			tmpList[-1] = str(float(tmpList[-1]) / 1024.0)
			# print tmpList
			line = " ".join(tmpList)
			retDict[algoName][infoName] = line
	return retDict


def dumpResult(aDict, desFileName):
	with open(desFileName, "w") as fout:
		for algoName,memDict in aDict.iteritems():
			fout.write(algoName + "\n")
			for infoName,resLine in memDict.iteritems():
				line = "%s: %s\n" % (infoName, resLine)
				fout.write(line)
			fout.write("\n\n")


def mergeResult(srcFilePath, desFilePath):
	desFileName = "result.txt"
	desFileName = os.path.join(desFilePath, desFileName)
	resDict = resultDict(srcFilePath)
	resDict = mergeTime(resDict)
	dumpResult(resDict, desFileName)
	return resDict


def dumpAllResult(srcFilePath, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	resDict = mergeResult(srcFilePath, desFilePath)
	return resDict

if __name__ == "__main__":
	dataSetNameList = [
		"exp",
		"normal",
		"EverySender",
		"gMission",
		"sca",
		"ns",
		#"uniform",
	]

	for dataSetName in dataSetNameList[-1:]:
		srcFilePath = "/home/turf/dataSet/new_v0424_25/%s_log" % (dataSetName)
		desFilePath = "/home/turf/dataSet/new_v0424_25/%s_result" % (dataSetName)
		#print srcFilePath, desFilePath
		dumpAllResult(srcFilePath, desFilePath)
		resFileName = os.path.join(desFilePath, "result.txt")
		dumpPlotArray(resFileName)
