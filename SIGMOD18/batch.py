#!/usr/bin/env python
import commands
import os
import sys
from random import randint

def genData(execName, filePath, caseN):
	for caseId in xrange(caseN):
		fileName = "data%02d.in" % (caseId)
		fileName = os.path.join(filePath, fileName)
		seedNum = randint(1, 1000000)
		cmdLine = "%s %s %s" % (execName, fileName, seedNum)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line


def testGenData(caseN):
	execName = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/datas"	
	dataFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/zyxDataSet"
	genData(execName, dataFilePath, caseN)


if __name__ == "__main__":
	testGenData(20)

