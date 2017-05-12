#!/usr/bin/env python

import os
import commands
import multiprocessing

def dumpToFile(fileName, lines):
	with open(fileName, "w") as fout:
		for line in lines:
			fout.write("%s\n" % (line))


def runMei(execName, srcFileName, bound, logFileName):
	lines = []
	cmdLine = "%s %s %s" % (execName, srcFileName, bound)
	line = commands.getoutput(cmdLine)
	print cmdLine
	print line
	lines.append(line)
	dumpToFile(logFileName, lines)


def runMeiTime(execName, srcFileName, timeBound, logFileName):
	runMei(execName, srcFileName, timeBound, logFileName)


def runMeiNum(execName, srcFileName, numBound, logFileName):
	runMei(execName, srcFileName, numBound, logFileName)


def testPool(execName, srcFileName, boundList):
	pool = multiprocessing.Pool(processes = 4)
	dataSetName = srcFileName[srcFileName.rindex('/')+1 : srcFileName.rindex('.')]
	execProgName = execName[execName.rindex('/')+1:]

	for bound in boundList:
		logFileName = "%s_%s_%s.log" % (execName, dataSetName, bound)
		print logFileName
		pool.apply_async(runMei, (execName, srcFileName, bound, logFileName, ))
	pool.close()
	pool.join()
	del(pool)


def testPool_Num(execName, srcFileName, boundList = range(500, 3001, 500)):
	testPool(execName, srcFileName, boundList)

def testPool_Time(execName, srcFileName, boundList = range(200, 1001, 200)):
	testPool(execName, srcFileName, boundList)


if __name__ == "__main__":
	execName = "/home/turf/Code/Introduction_to_Algorithms/Crowd_match_greedy/MeiN"
	srcFileName = "/home/turf/Code/Introduction_to_Algorithms/Crowd_match_greedy/order.in"
	#testPool_Num(execName, srcFileName)
	execName = "/home/turf/Code/Introduction_to_Algorithms/Crowd_match_greedy/MeiNMem"
	testPool_Num(execName, srcFileName)
