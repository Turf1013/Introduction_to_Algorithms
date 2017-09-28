#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing

def batchRound(execName, srcFilePath, i):
	srcFileName = "data_%03d.txt" % (i)
	srcFileName = os.path.join(srcFilePath, srcFileName)
	cmdLine = "./%s %s" % (execName, srcFileName)
	print cmdLine
	line = commands.getoutput(cmdLine)
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
	desNames = [
	'2500_10_0.10_0.85_N', 
	'2500_6_0.01_0.85_N', 
	'2500_6_0.10_0.75_N', 
	'2500_6_0.10_0.85_N', 
	'2500_6_0.10_0.90_N', 
	'2500_6_0.10_0.90_U', 
	'2500_6_0.20_0.85_N', 
	]
	for dirName in dirNames:
		if dirName.endswith('S') or dirName not in desNames or not dirName.startwith('2500'):
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
	execNames = ["SSPAM", "AAMM"]
	srcFilePath = "/home/server/Yihuihe/dataSet/"
	desFilePath = "/home/server/Yihuihe/result/"
	bid = 0
	eid = 1
	poolExec(execNames, srcFilePath, bid, eid, desFilePath)

def exp2():
	execNames = ["SSPAM"]
	srcFilePath = "/home/turf/Code/dataSet/500_6_0.10_0.80_N"
	desFilePath = 
	n = 6
	pool = multiprocessing.Pool(processes = 3)
	for i in xrange(1,n):
		for execName in execNames:
			pool.apply_async(batchRound, (execName, srcFilePath, i, ))
	pool.close()
	pool.join()

def exp3():
	execNames = ["RRKM", "LAM", "AAMM"]
	srcFilePath = "/home/server/Yihuihe/dataSet/2500_6_0.10_0.85_U"
	n = 50
	pool = multiprocessing.Pool(processes = 8)
	for execName in execNames:
		desFilePath = "/home/server/Yihuihe/result/%s/2500_6_0.10_0.85_U" % (execName)
		if not os.exists(desFilePath):
			os.mkdir(desFilePath)
		pool.apply_async(batchSubExp, (execName, srcFilePath, 0, n, desFilePath, ))
	pool.close()
	pool.join()
	
	
if __name__ == "__main__":
	exp3()
