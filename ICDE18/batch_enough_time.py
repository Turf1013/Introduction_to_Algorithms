#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing

def batchSubExp(execName, srcFilePath, i, desFilePath):
	srcFileName = "data_%03d.txt" % (i)
	srcFileName = os.path.join(srcFilePath, srcFileName)
	desFileName = "data_%03d.txt" % (i)
	desFileName = os.path.join(desFilePath, desFileName)
	if os.path.exists(desFileName):
		return 
	cmdLine = "./%s %s" % (execName, srcFileName)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	with open(desFileName, "w") as fout:
		fout.write(line)
		
		
def poolExp(execName, srcFilePath, bid, eid, desFilePath):
	pool = multiprocessing.Pool(processes = 12)
	dirNames = os.listdir(srcFilePath)
	dirNames = filter(lambda x:x.endswith('S'), dirNames)
	for dirName in dirNames:
		for id in xrange(bid, eid):
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
			pool.apply_async(batchSubExp, (execName, subSrcFilePath, id, subDesFilePath, ))
	pool.close()
	pool.join()
	
	
def exp5():
	srcFilePath = "/home/server/Yihuihe/dataSet"
	desFilePath = "/home/server/Yihuihe/result"
	execNames = ["RRKM", "LAFM", "AAMM"]
	bid, eid = 0, 50
	for execName in execNames:
		poolExp(execName, srcFilePath, bid, eid, desFilePath)
	
	
if __name__ == "__main__":
	exp5()
	