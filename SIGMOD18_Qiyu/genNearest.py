#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing
import utm

class constForGenNearest:
	timeWindow = 300
	radius = 1000
	execName = "./cnt"

class CFGN(constForGenNearest):
	pass


def toNearest(srcFileName, desFileName):
	cmdLine = "%s %s %s %s %s" % (CFGN.execName, srcFileName, desFileName, CFGN.timeWindow, CFGN.radius)
	print cmdLine
	commands.getoutput(cmdLine)


def handleAllData(srcFilePath, desFilePath, nprocess=16):
	pool = multiprocessing.Pool(processes = nprocess)
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)

	dirNames = filter(lambda x:x.startswith('S'), os.listdir(srcFilePath))
	for dirName in dirNames:
		tmpFilePath = os.path.join(desFilePath, dirName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		dataFilePath = os.path.join(srcFilePath, dirName)
		dataNames = filter(lambda x:x.endswith('csv'), os.listdir(dataFilePath))
		for dataName in dataNames:
			desFileName = os.path.join(desFilePath, dirName, dataName)
			if os.path.exists(desFileName):
				continue
			srcFileName = os.path.join(srcFilePath, dirName, dataName)
			#print srcFileName, desFileName
			pool.apply_async(toNearest, (srcFileName, desFileName, ))

	pool.close()
	pool.join()


def exp0():
	nprocess = 24
	srcFilePath = "../trajectory"
	desFilePath = "../nearest"
	handleAllData(srcFilePath, desFilePath, nprocess)


if __name__ == "__main__":
	exp0()
