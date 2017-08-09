#!/usr/bin/env python
import commands
import os

def testJudge(execFileName, judgeFileName, dataFilePath, windowSize=None):
	ret = []
	execName = execFileName[execFileName.rindex('/')+1:]
	fileNames = os.listdir(dataFilePath)
	for fileName in fileNames:
		if not fileName.endswith(".in"):
			continue
		srcFileName = os.path.join(dataFilePath, fileName)
		desFileName = "/home/turf/Code/Code_today/%s_%s_result.txt" % (execName, fileName[:-3])
		if windowSize is None:
			cmdLine = "%s %s %s" % (execFileName, srcFileName, desFileName)
		else:
			cmdLine = "%s %s %s %s" % (execFileName, srcFileName, desFileName, windowSize)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
		#ret.append(cmdLine)
		#ret.append(line)
		
		cmdLine = "%s %s %s" % (judgeFileName, srcFileName, desFileName)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
		#ret.append(cmdLine)
		
		ans = line.split()[-1]
		dataId = fileName[:-3]
		if windowSize is None:
			resLine = "%s %s %s" % (execName, dataId, ans)
		else:
			resLine = "%s %s %s %s" % (execName, windowSize, dataId, ans)
		print resLine
		ret.append(resLine)

	return ret
	

if __name__ == "__main__":
	execNames = [
		#"tshare_dist",
		"tshare_km",
	]
	windowList = []
	for p in [0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2]:
		windowSize = int(p * 1500)
		windowList.append(windowSize)
	lines = []
	for execName in execNames:
		execFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/%s" % (execName)
		dataFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/zyxDataSet"
		judgeFilePath = "/home/turf/Code/Introduction_to_Algorithms/Tong_taxi/judges"
		if "km" in execName:
			for windowSize in windowList:
				lines += testJudge(execFilePath, judgeFilePath, dataFilePath, windowSize)
		else:
			lines += testJudge(execFilePath, judgeFilePath, dataFilePath)
	with open("share.log", "w") as fout:
		for line in lines:
			fout.write(line + "\n")
