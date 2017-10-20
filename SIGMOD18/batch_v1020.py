#!/usr/bin/env python
import commands
import os
import sys
from random import randint
import multiprocessing

def run(execName, srcFileName, desFileName):
	cmdLine = "./%s %s" % (execName, srcFileName)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	with open(desFileName, "w") as fout:
		fout.write(line)


def batch(desFilePath, srcFilePath, dataSetN, nprocess=12):	
	execNames = ["gi", "newsjf", "newfifo", "hybrid", "mft", "staticsjf", "staticfifo", "staticdd", "srhstfifo", "srhstsjf", "srrndfifo", "srrndsjf"]
	pool = multiprocessing.Pool(processes = nprocess)	
	
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	dirNames = os.listdir(srcFilePath)
	for execName in execNames:
		tmpFilePath = os.path.join(desFilePath, execName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		for dirName in dirNames:
			tmpFilePath = os.path.join(desFilePath, execName, dirName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			for dataSetId in xrange(dataSetN):
				srcFileName = "data_%02d.txt" % (dataSetId)
				desFileName = os.path.join(desFilePath, execName, dirName, srcFileName)
				srcFileName = os.path.join(srcFilePath, dirName, srcFileName)
				pool.apply_async(run, (execName, srcFileName, desFileName, ))

	pool.close()
	pool.join()
	
	
def exp0(dataSetN=10, nprocess=12, srcFilePath, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	tmpFileNames = os.listdir(srcFilePath)
	for tmpFileName in tmpFileNames:
		tmpSrcFilePath = os.path.join(srcFilePath, tmpFileName)
		tmpDesFilePath = os.path.join(desFilePath, tmpFileName)
		batch(tmpDesFilePath, tmpSrcFilePath, dataSetN, nprocess)
	
	
def exp2(dataSetN=10, nprocess=12):
	srcFilePathList = [
		"../dataSet_SIGMOD",
		"../dataSet_SIGMOD_1",
	]
	desFilePathList = [
		"../result_SIGMOD",
		"../result_SIGMOD_1",
	]
	for i in xrange(len(srcFilePathList)):
		srcFilePath = srcFilePathList[i]
		desFilePath = desFilePathList[i]
		exp0(dataSetN, nprocess, srcFilePath, desFilePath)
	
	
if __name__ == "__main__":
	dataSetN = 20
	nprocess = 16
	exp1(dataSetN, nprocess)

