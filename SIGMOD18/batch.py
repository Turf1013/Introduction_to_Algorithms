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
	execNames = ["sjf", "fifo", "gi"]
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
			for dataSetId in dataSetN:
				srcFileName = "data_%02d.txt" % (dataSetId)
				desFileName = os.path.join(desFilePath, execName, dirName, srcFileName)
				srcFileName = os.path.join(srcFilePath, dirName, srcFileName)
				pool.apply_async(run, (execName, srcFileName, desFileName, ))

	pool.close()
	pool.join()
	
	
def exp1(dataSetN=10, nprocess=12):
	srcFilePath = "../dataSet_SIGMOD_1"
	desFilePath = "../result_SIGMOD_1"
	batch(desFilePath, srcFilePath, dataSetN, nprocess)
	
	
def exp2(dataSetN=10, nprocess=12):
	srcFilePath = "../dataSet_SIGMOD"
	desFilePath = "../result_SIGMOD"
	batch(desFilePath, srcFilePath, dataSetN, nprocess)
	
	
if __name__ == "__main__":
	dataSetN = 20
	nprocess = 16
	exp1(dataSetN, nprocess)
	exp2(dataSetN, nprocess)

