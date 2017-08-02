#!/usr/bin/env python
import commands
import os

def testJudge(execFileName, judgeFileName, dataFilePath):
	ret = []
	execName = execFileName[execFileName.rindex('/')+1:]
	fileNames = os.listdir(dataFilePath)
	for fileName in fileNames:
		if not fileName.endswith(".in"):
			continue
		srcFileName = os.path.join(dataFilePath, fileName)
		desFileName = "/home/turf/Code/Code_today/%s_%s_result.txt" % (execName, fileName[:-3])
		cmdLine = "%s %s %s" % (execFileName, srcFileName, desFileName)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
		ret.append(cmdLine)
		ret.append(line)
		
		cmdLine = "%s %s %s" % (judgeFileName, srcFileName, desFileName)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
		ret.append(cmdLine)
		ret.append(line)
	return ret
	

if __name__ == "__main__":
	execNames = [
		"tshare_dist",
		"bila",
		"effg",
		"tshare_km",
	]
	lines = []
	for execName in execNames:
		execFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/%s" % (execName)
		dataFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/smallDataSet"
		judgeFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/judges"
		lines += testJudge(execFilePath, judgeFilePath, dataFilePath)
	with open("share.log", "w") as fout:
		for line in lines:
			fout.write(line + "\n")
