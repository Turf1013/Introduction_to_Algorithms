#!/usr/bin/python

import sys
import os
import commands
import multiprocessing


def runExtGreedy(execName, edgeFileName):
	lines = []	
	cmdLine = "%s %s" % (execName, edgeFileName)
	#print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	lines.append(line)
	return lines


def dumpToFile(fileName, lines):
	with open(fileName, "w") as fout:
		fout.write("\n".join(lines))


def testFunc(execName, edgeFileName, logFileName):
	#print "begin testFunc"
	lines = runExtGreedy(execName, edgeFileName)
	dumpToFile(logFileName, lines)
	#print "end testFunc"


def getMaxV(a):
	return 10
	a = '_'.join(a.strip().split('_')[1:])
	a = a[:a.rindex('.')]
	aworkerN, ataskN, acap = map(int, a.strip().split('_')[:3])
	aworkerN *= acap
	return max(ataskN, aworkerN)


def mycomp(a, b):
	va = getMaxV(a)
	vb = getMaxV(b)
	return va - vb


def filterDataSet(filePath):
	bound = 10 ** 20
	tmpList = os.listdir(filePath)
	tmpList.sort(mycomp)
	ret = []
	for tmp in tmpList:
		#print getMaxV(tmp), tmp
		v = getMaxV(tmp)
		if v < bound:
			ret.append(tmp)
	print ret
	return ret


def testPool():
	execNameList = [
		#"OPT",
		#"OPTMem",
		#"Pure",
		#"PureMem",
		#"Ext", 
		#"ExtMem",
		"Greedy",
		#"GreedyMem",
		#"GreedyNew",
		#"GreedyNewMem",
		"GreedyF",
		#"TGOAMem",
		#"TGOANew",
		#"TGOANewMem",
	]

	dataFilePath = "/home/turf/Code/data_exp"
	execFilePath = "/home/turf/Code/TmpTest"
	logPrefix = "/home/turf/Code/log_exp"

	dataNameList = filterDataSet(dataFilePath)
	print execNameList[-2:]
	print dataNameList

	# directory name: $workerN_$taskN_$degRate_$umax_$tlen
	for dataFileName in dataNameList:
		if getMaxV(dataFileName) > 2500:
			nprocess = 12
		else:
			nprocess = 12
		edgeFileName = os.path.join(dataFilePath, dataFileName)
		pool = multiprocessing.Pool(processes = nprocess)
		for execName in execNameList[-2:]:
			logCurPrefix = os.path.join(logPrefix, execName)
			if not os.path.exists(logCurPrefix):
				os.mkdir(logCurPrefix)

			execPath = os.path.join(execFilePath, execName)
			dataInfo = dataFileName[:dataFileName.rindex(".")]
			logFileName = "%s.log" % (dataInfo)
			logFileName = os.path.join(logCurPrefix, logFileName)

			pool.apply_async(testFunc, (execPath, edgeFileName, logFileName, ))
		pool.close()
		pool.join()
	

if __name__ == "__main__":
	testPool()