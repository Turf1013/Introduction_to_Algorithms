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
	lines = line.split('\n')
	resLine = lines[-1]
	with open(desFileName, "w") as fout:
		fout.write("%s\n" % (resLine))

def exp1(n = 10, nprocess=4):
	execNames = ["greedy", "opq", "base"]
	srcFilePath = "../dataSet/"
	desFilePath = "../result_SLADE/"
	pool = multiprocessing.Pool(processes = nprocess)

	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	dirNames = os.listdir(srcFilePath)
	dirNames = filter(lambda x:x[0]=='e', dirNames)
	for execName in execNames:
		tmpFilePath = os.path.join(desFilePath, execName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		for dirName in dirNames:
			tmpFilePath = os.path.join(desFilePath, execName, dirName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			for i in xrange(0, n):
				srcFileName = "data_%02d.txt" % (i)
				desFileName = os.path.join(tmpFilePath, srcFileName)
				srcFileName = os.path.join(srcFilePath, dirName, srcFileName)
				pool.apply_async(run, (execName, srcFileName, desFileName, ))

	pool.close()
	pool.join()


def exp2(n = 10, nprocess=4):
	execNames = ["greedy", "opqe", "base"]
	srcFilePath = "../dataSet/"
	desFilePath = "../result_SLADE/"
	pool = multiprocessing.Pool(processes = nprocess)

	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	dirNames = os.listdir(srcFilePath)
	dirNames = filter(lambda x:x[0]!='e', dirNames)
	for execName in execNames:
		tmpFilePath = os.path.join(desFilePath, execName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		for dirName in dirNames:
			tmpFilePath = os.path.join(desFilePath, execName, dirName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			for i in xrange(0, n):
				srcFileName = "data_%02d.txt" % (i)
				desFileName = os.path.join(tmpFilePath, srcFileName)
				if os.path.exists(desFileName):
					continue
				srcFileName = os.path.join(srcFilePath, dirName, srcFileName)
				pool.apply_async(run, (execName, srcFileName, desFileName, ))

	pool.close()
	pool.join()


if __name__ == "__main__":
	dataSetN = 30
	exp1(dataSetN, 12)
	exp2(dataSetN, 12)
