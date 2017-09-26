#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing

def batchRound(srcFilePath, n):
	execList = [
		"RR",
		"LAF",
		"AAM",
		"MCF",
	]
	for i in xrange(n):
		srcFileName = "data_%03d.txt" % (i)
		srcFileName = os.path.join(srcFilePath, srcFileName)
		for execName in execList:
			cmdLine = "./%s %s data.out" % (execName, srcFileName)
			print cmdLine
			commands.getoutput(cmdLine)
			with open("data.out", "r") as fin:
				line = fin.readlines()[-1]
			print line

def batchSubExp(execName, srcFilePath, bid, eid, desFilePath):
	for i in xrange(bid, eid):
		srcFileName = "data_%03d.txt" % (i)
		srcFileName = os.path.join(srcFilePath, srcFileName)
		desFileName = "data_%03d.txt" % (i)
		desFileName = os.path.join(desFilePath, desFileName)
		cmdLine = "./%s %s" % (execName, srcFileName)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line
		with open(desFileName, "w") as fout:
			fout.write(line)

def batchExp(execName, srcFilePath, bid, eid, desFilePath):
	dirNames = os.listdir(srcFilePath)
	for dirName in dirNames:
		# if dirName.endswith('S'):
			# continue
		subSrcFilePath = os.path.join(srcFilePath, dirName)
		subDesFilePath = os.path.join(desFilePath, dirName)
		if not os.path.exists(subDesFilePath):
			os.mkdir(subDesFilePath)
		batchSubExp(execName, subSrcFilePath, bid, eid, subDesFilePath)

def batchExec(execNames, srcFilePath, bid, eid, desFilePath):
	for execName in execNames:
		batchExp(execName, srcFilePath, bid, eid, desFilePath)

def poolExp(execName, srcFilePath, bid, eid, desFilePath):
	pool = multiprocessing.Pool(processes = 12)
	dirNames = os.listdir(srcFilePath)
	for dirName in dirNames:
		if not dirName.endswith('S'):
			continue
		subSrcFilePath = os.path.join(srcFilePath, dirName)
		if '/' in execName:
			tmpName = execName[execName.rindex('/'):]
		else:
			tmpName = execName
		subDesFilePath = os.path.join(desFilePath, tmpName)
		if not os.path.exists(subDesFilePath):
			os.mkdir(subDesFilePath)
		subDesFilePath = os.path.join(subDesFilePath, dirName)
		if not os.path.exists(subDesFilePath):
			os.mkdir(subDesFilePath)
		pool.apply_async(batchSubExp, (execName, subSrcFilePath, bid, eid, subDesFilePath, ))
	pool.close()
	pool.join()


def poolExec(execNames, srcFilePath, bid, eid, desFilePath):
	for execName in execNames:
		poolExp(execName, srcFilePath, bid, eid, desFilePath)


def exp1():
	execNames = ["LAFM", "AAMM", "MCFM"]
	srcFilePath = "/home/server/Yihuihe/dataSet/"
	desFilePath = "/home/server/Yihuihe/result/"
	bid = 0
	eid = 50
	poolExec(execNames, srcFilePath, bid, eid, desFilePath)


if __name__ == "__main__":
	exp1()
