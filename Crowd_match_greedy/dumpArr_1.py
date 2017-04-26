#!/usr/bin/env python

import os
import sys

algoDict = {
	"OPT" : "opt",
	"GreedyNew": "fgoagn",
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
		algoList.append("fgoa")
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

def gaoNewLines(tmpDict, fileName):
	if "Sender" in fileName:
		return gaoSenderNewLines(tmpDict, fileName)
	elif "exp" in fileName:
		return gaoExpNewLines(tmpDict, fileName)
	elif "normal" in fileName:
		return gaoNormNewLines(tmpDict, fileName)
	elif "gMission" in fileName:
		return gaogMisNewLines(tmpDict, fileName)
	else:
		raise ValueError("invalid gao new lines")


def gao(fileName):
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


if __name__ == "__main__":
	filePath = "/home/turf/dataSet/dataSet_v0424/gMission_result"
	fileName = os.path.join(filePath, "result.txt")
	gao(fileName)