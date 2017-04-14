#!/usr/bin/env python

import os
import sys
import commands

weightFilePath = "/home/turf/tmp/weight10.txt"

def dumpGraph(srcFileName, desFileName):
	execName = "/home/turf/Code/TmpTest/dumpGraph"
	cmdLine = "%s %s %s" % (execName, srcFileName, weightFilePath)
	#print cmdLine
	ret = commands.getoutput(cmdLine)
	with open(desFileName, "a") as fout:
		fout.write(ret + "\n")
	return ret


def dumpInfo(orderN, srcFilePath, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	if not os.path.exists(srcFilePath):
		raise ValueError("%s not exists" % (srcFilePath))
	nameList = os.listdir(srcFilePath)
	tmpDict = dict()
	for curDirName in nameList:
		srcDirPath = os.path.join(srcFilePath, curDirName)
		if not os.path.isdir(srcDirPath):
			continue
		tmpPath = os.path.join(desFilePath, curDirName)
		if not os.path.exists(tmpPath):
			os.mkdir(tmpPath)

		lines = []
		for orderId in xrange(orderN):
			desFileName = "%s__%d.txt" % (curDirName, orderId)
			orderName = "order" + str(orderId) + ".txt"
			orderFilePath = os.path.join(srcFilePath, curDirName, orderName)
			desFileName = os.path.join(desFilePath, curDirName, desFileName)
			infoLine = dumpGraph(orderFilePath, desFileName)
			lines.append(infoLine)

		should = float(curDirName.split('_')[-2]) / 1000.0
		tlen = int(curDirName.split('_')[-1].strip())
		if should not in tmpDict:
			tmpDict[should] = [""] * 5
		infoLine = "tlen = %f %s" % (tlen, lines[0])
		tmpDict[should][tlen-1] = infoLine

	summaryFileName = os.path.join(desFilePath, "graph_info.txt")
	with open(summaryFileName, "w") as fout:
		rateList = tmpDict.keys()
		rateList.sort()
		for should in rateList:
			lines = tmpDict[should]
			fout.write(str(should) + "\n")
			for line in lines:
				fout.write(line + "\n")
			fout.write("\n")


if __name__ == "__main__":
	orderN = 1
	srcFilePath = "/home/turf/tmp/dataz"	
	desFilePath = "/home/turf/tmp/infoz"
	dumpInfo(orderN, srcFilePath, desFilePath)
