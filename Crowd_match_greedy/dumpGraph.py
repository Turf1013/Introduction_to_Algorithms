#!/usr/bin/env python

import os
import sys
import commands

def dumpGraph(srcFileName, desFileName):
	execName = "/home/server/zyx/Introduction_to_Algorithms/Crowd_match_greedy/dumpGraph"
	cmdLine = "%s %s %s" % (execName, srcFileName, desFileName)
	print cmdLine
	ret = commands.getoutput(cmdLine)
	print ret
	return ret
	

if __name__ == "__main__":
	orderN, caseN = 1, 1
	dataPath = "/home/server/zyx/SmallData"
	dirPrefix = os.path.join(dataPath, "data")
	desFilePath = "/home/server/zyx/SmallInfo"

	for distId in xrange(4):
		dirPath = dirPrefix + str(distId)
		if not os.path.exists(dirPath):
			raise ValueError("%s not exists" % (dirPath))
		tmpPath = os.path.join(desFilePath, "data"+str(distId))
		if not os.path.exists(tmpPath):
			os.mkdir(tmpPath)
		nameList = os.listdir(dirPath)
		lines = []
		for curDirName in nameList:
			tmpPath = os.path.join(desFilePath, "data"+str(distId), curDirName)
			if not os.path.exists(tmpPath):
				os.mkdir(tmpPath)
			for caseId in xrange(caseN):
				for orderId in xrange(orderN):
					if orderN == 1:
						desFileName = "%s__%d.txt" % (curDirName, caseId)
					else:
						desFileName = "%s__%d_%d.txt" % (curDirName, caseId, orderId)
					orderName = "order" + str(orderId) + ".txt"
					dirName = os.path.join(dirPath, curDirName, str(caseId), orderName)
					desFileName = os.path.join(desFilePath, "data"+str(distId), curDirName, desFileName)
					lines.append( dumpGraph(dirName, desFileName) )
		desFileName = "graph_info_%d.txt" % (distId)
		desFileName = os.path.join(desFilePath, desFileName)
		with open(desFileName, "w") as fout:
			lineIdx = 0
			for curDirName in nameList:
				for caseId in xrange(caseN):
					for orderId in xrange(orderN):
						line = "%s_%d %s\n" % (curDirName, caseId, lines[lineIdx])
						fout.write(line)
						lineIdx += 1
