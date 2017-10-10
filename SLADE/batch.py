#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing

def run(execName, srcFileName, desFileName):
	cmdLine = "./%s %s" % (execName, srcFileName)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	with open(desFileName, "w") as fout:
		fout.write("%s\n" % (line))

def exp1(n = 10):
	execNames = ["greedy", "opqe"]
	srcFilePath = "../dataSet/"
	desFilePath = "../result_SLADE/"
	pool = multiprocessing.Pool(processes = 10)
	
	dirNames = os.listdir(srcFilePath)
	dirNames = filter(lambda x:x[0]=='e', dirNames)
	for execName in execNames:
		tmpFilePath = os.path.join(desFilePath, execName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		for dirName in dirNames:
			tmpFilePath = os.path.join(tmpFilePath, dirName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			for i in xrange(0, n):
				srcFileName = "data_%02d.txt" % (i)
				desFileName = os.path.join(tmpFilePath, srcFileName)
				srcFileName = os.path.join(srcFilePath, dirName, srcFileName)
				pool.apply_async(run, (execName, srcFileName, desFileName, ))
			
	pool.close()
	pool.join()

	
def exp2(n = 10):
	execNames = ["greedy", "opqe"]
	srcFilePath = "../dataSet/"
	desFilePath = "../result_SLADE/"
	pool = multiprocessing.Pool(processes = 10)
	
	dirNames = os.listdir(srcFilePath)
	dirNames = filter(lambda x:x[0]!='e', dirNames)
	for execName in execNames:
		tmpFilePath = os.path.join(desFilePath, execName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		for dirName in dirNames:
			tmpFilePath = os.path.join(tmpFilePath, dirName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			for i in xrange(0, n):
				srcFileName = "data_%02d.txt" % (i)
				desFileName = os.path.join(tmpFilePath, srcFileName)
				srcFileName = os.path.join(srcFilePath, dirName, srcFileName)
				pool.apply_async(run, (execName, srcFileName, desFileName, ))
			
	pool.close()
	pool.join()


if __name__ == "__main__":
	dataSetN = 10
	exp1(dataSetN)
	exp2(dataSetN)
