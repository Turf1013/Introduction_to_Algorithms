#!/usr/bin/env python
import commands
import os

def testJudge(execFileName, judgeFileName, dataFilePath):
	fileNames = os.listdir(dataFilePath)
	for fileName in fileNames:
		if not fileName.endswith(".in"):
			continue
		srcFileName = os.path.join(dataFilePath, fileName)
		desFileName = "/home/turf/Code/Code_today/result.txt"
		cmdLine = "%s %s %s" % (execFileName, srcFileName, desFileName)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
		
		cmdLine = "%s %s %s" % (judgeFileName, srcFileName, desFileName)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
	

if __name__ == "__main__":
	execFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/hotp"
	dataFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/smallDataSet"
	judgeFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/judge"
	testJudge(execFilePath, judgeFilePath, dataFilePath)
