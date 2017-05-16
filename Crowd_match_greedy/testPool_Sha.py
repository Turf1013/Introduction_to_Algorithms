#!/usr/bin/env python

import os
import commands
import multiprocessing

def dumpToFile(logFileName, lines):
	with open(logFileName, "w") as fout:
		for line in lines:
			line = line.strip() + "\n"
			fout.write(line)


def runProg(execName, srcFileName, logFileName):
	lines = []
	cmdLine = "%s %s" % (execName, srcFileName)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	lines.append(line)
	dumpToFile(logFileName, lines)


def runMei(execName, srcFileName, bound, logFileName):
	lines = []
	cmdLine = "%s %s %s" % (execName, srcFileName, bound)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	lines.append(line)
	dumpToFile(logFileName, lines)

def runPureX(execName, srcFileName, bound, logFileName):
	lines = []
	cmdLine = "%s %s %s" % (execName, srcFileName, bound)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	lines.append(line)
	dumpToFile(logFileName, lines)

def testPool():
	execNameList = [
		"OPT",
		"Pure",
		"PureT",
		"PureN",
		"MeiT",
		"MeiN",
		"ShaT",
		"ShaN",
	]
	execFilePath = "/home/server/zyx_TGOA/TmpTest/"
	srcFilePath = "/home/server/zyx_TGOA/data"
	logFilePath = "/home/server/zyx_TGOA/log"
	timeBoundList = [7, 18, 30, 60, 120, 300, 600, 900]
	numBoundList = [0.002, 0.005, 0.01, 0.02, 0.05, 0.1, 0.2, 0.5]
	sumDeg = 10**4
	orderN = 100

	numBoundList = map(lambda x:int(x*sumDeg), numBoundList)
	dataSetNameList = os.listdir(srcFilePath)
	if not os.path.exists(logFilePath):
		os.mkdir(logFilePath)

	for progName in execNameList:
		execName = os.path.join(execFilePath, progName)
		for dataSetName in dataSetNameList:
			dataSetPath = os.path.join(srcFilePath, dataSetName)
			logSetPath = os.path.join(logFilePath, dataSetName)
			if not os.path.exists(logSetPath):
				os.mkdir(logSetPath)

			pool = multiprocessing.Pool(processes = 20)
			for orderId in xrange(orderN):
				dataFileName = "order%d.txt" % (orderId)
				dataFileName = os.path.join(dataSetPath, dataFileName)
				logFileName = "res%d_%s.log" % (orderId, progName)
				logFileName = os.path.join(logSetPath, logFileName)

				if progName.startswith("Mei") or progName.startswith("Sha"):
					boundList = []
					if "T" in progName:
						boundList = timeBoundList
					elif "N" in progName:
						boundList = numBoundList
					for bound in boundList:
						logFileName = "res%d_%s_%s.log" % (orderId, progName, bound)
						logFileName = os.path.join(logSetPath, logFileName)
						pool.apply_async(runMei, (execName, dataFileName, bound, logFileName, ))
				elif progName.startswith("Pure") and len(progName)>4:
					boundList = []
					if "T" in progName:
						boundList = timeBoundList
					elif "N" in progName:
						boundList = numBoundList
					for bound in boundList:
						logFileName = "res%d_%s_%s.log" % (orderId, progName, bound)
						logFileName = os.path.join(logSetPath, logFileName)
						pool.apply_async(runPureX, (execName, dataFileName, bound, logFileName, ))
				else:
					pool.apply_async(runProg, (execName, dataFileName, logFileName, ))
					
			pool.close()
			pool.join()


if __name__ == "__main__":
	testPool()
