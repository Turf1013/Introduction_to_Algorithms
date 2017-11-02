#!/usr/bin/env python
import os
import sys
import commands


def runSmallData(algoNames, dataFilePath):
	for algoName in algoNames:
		cmdLine = "%s %s" % (algoName, dataFilePath)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
		
		
def exp0():
	algoNames = [
		"base",
		"bao",
		"sbao"
	]
	dataFilePath = "./data.txt"
	algoNames = map(lambda s:os.path.join("../", s), algoNames)
	runSmallData(algoNames, dataFilePath)
	
if __name__ == "__main__":
	exp0()
		