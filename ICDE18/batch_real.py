#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing

def batchSubExp(execName, srcFileName, desFileName):
	if os.path.exists(desFileName):
		return 
	cmdLine = "./%s %s" % (execName, srcFileName)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	with open(desFileName, "w") as fout:
		fout.write(line)
		
		
def poolExp(execName, srcFilePath, desFilePath):
	pool = multiprocessing.Pool(processes = 6)
	dataNames = ["TKY.txt", "NYC.txt"]
	for dataName in dataNames:
		srcFileName = os.path.join(srcFilePath, dataName)
		if '/' in execName:
			tmpName = execName[execName.rindex('/'):]
		else:
			tmpName = execName
		subDesFilePath = os.path.join(desFilePath, tmpName)
		if not os.path.exists(subDesFilePath):
			os.mkdir(subDesFilePath)
		desFileName = os.path.join(subDesFilePath, dataName)
		pool.apply_async(batchSubExp, (execName, srcFileName, desFileName, ))
	pool.close()
	pool.join()
	
	
def exp6():
	srcFilePath = "/home/server/Yihuihe/dataSet"
	desFilePath = "/home/server/Yihuihe/result/real"
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	execNames = ["RRKM", "LAFM", "AAMM"]
	for execName in execNames:
		poolExp(execName, srcFilePath, desFilePath)
	
	
if __name__ == "__main__":
	exp6()
	