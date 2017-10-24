#!/usr/bin/env python
import os
import commands

def getResult(line):
	tmpList = line.strip().split(' ')
	return float(tmpList[1])
	

def compareTwoGreedy(srcFilePath):
	fileNames = os.listdir(srcFilePath)
	for fileName in fileNames:
		srcFileName = os.path.join(srcFilePath, fileName)
		cmdLine1 = "./greedy %s" % (srcFileName)
		print cmdLine1
		line1 = commands.getoutput(cmdLine1)
		print line1
		cmdLine2 = "./greedyf %s" % (srcFileName)
		print cmdLine2
		line2 = commands.getoutput(cmdLine2)
		print line2
		res1 = getResult(line1)
		res2 = getResult(line2)
		if res1 != res2:
			print "not equal", res1, res2
	
def exp0():
	srcFilePath = "./dataSet"
	compareTwoGreedy(srcFilePath)
	
if __name__ == "__main__":
	exp0()
	