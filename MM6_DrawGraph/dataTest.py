#!/usr/bin/env python

import os
import sys
import commands

def testOne(fileName):
	execName = "/home/turf/Code/Introduction_to_Algorithms/MM6_DrawGraph/base"
	cmdLine = "%s %s" % (execName, fileName)
	print cmdLine
	outLine = commands.getoutput(cmdLine)
	print outLine

def filterDataIn(x):
	return x.endswith(".in")


def testAll(filePath):
	nameList = os.listdir(filePath)
	nameList = filter(filterDataIn, nameList)
	for name in nameList:
		fileName = os.path.join(filePath, name)
		testOne(fileName)


if __name__ == "__main__":
	filePath = "/home/turf/Code/Introduction_to_Algorithms/MM6_DrawGraph/SmallTestCase"
	if len(sys.argv) > 1:
		filePath = sys.argv[1]
	testAll(filePath)

