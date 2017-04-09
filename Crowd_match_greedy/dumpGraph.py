#!/usr/bin/env python

import os
import sys
import commands

def dumpGraph(srcFileName, desFileName):
	execName = "/home/turf/Code/Introduction_to_Algorithms/Crowd_match_greedy/dumpGraph"
	cmdLine = "%s %s %s" % (execName, srcFileName, desFileName)
	print cmdLine
	ret = commands.getoutput(cmdLine)
	print ret
	return ret
	

if __name__ == "__main__":
	orderN, caseN = 1, 1
	dataPath = "/home/turf/Code/SmallData"
	dirPrefix = os.path.join(dataPath, "data")
	desFilePath = "/home/turf/Code/SmallData/graph"

	for distId in xrange(4):
		dirPath = dirPrefix + str(distId)
		if not os.path.exists(dirPath):
			raise ValueError("%s not exists" % (dirPath))
		nameList = os.listdir(dirPath)
		for curDirName in nameList:
			for caseId in xrange(caseN):
				for orderId in xrange(orderN):
					if orderN == 1:
						desFileName = "%s__%d.txt" % (curDirName, caseId)
					else:
						desFileName = "%s__%d_%d.txt" % (curDirName, caseId, orderId)
					orderName = "order" + str(orderId) + ".txt"
					dirName = os.path.join(dirPath, curDirName, str(caseId), orderName)
					desFileName = os.path.join(desFilePath, desFileName)
					dumpGraph(dirName, desFileName)