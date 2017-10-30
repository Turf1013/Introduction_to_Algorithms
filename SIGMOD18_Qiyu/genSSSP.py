#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing
import utm

class constForGenSSSP:
	execName = "./sssp"
	srcFileName = "./roadNetwork.txt"

class CFGS(constForGenSSSP):
	pass


def calcSSSP(desFileName, startId):
	cmdLine = "%s %s %s %s" % (CFGS.execName, CFGS.srcFileName, desFileName, startId)
	print cmdLine
	commands.getoutput(cmdLine)

def readNV(srcFileName):
    with open(srcFileName, "r") as fin:
        for line in fin:
            nV, nE = map(int, line.strip().split(' '))
            return nV
    return None
	
def handleAllData(desFilePath, nprocess=16):
	pool = multiprocessing.Pool(processes = nprocess)
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
		
	nV = readNV(CFGS.srcFileName)
	# nV = 5
	for startId in xrange(1, nV+1):
		desFileName = "%05d.txt" % (startId)
		desFileName = os.path.join(desFilePath, desFileName)
		# desFileName = desFilePath + "/" + desFileName
		# print desFileName
		pool.apply_async(calcSSSP, (desFileName, startId, ))
		
	pool.close()
	pool.join()


def exp0(nprocess=24):
	desFilePath = "../shortPaths"
	handleAllData(desFilePath, nprocess)


if __name__ == "__main__":
	exp0()
