#!/usr/bin/env python
import os
import sys
import commands
import multiprocessing
from genDataSet import genDesFileName

class constForBatchExperiment:
	dataSetN = 1
	nprocess = 4

class CFBE(constForBatchExperiment):
	pass


def run(execName, srcFileName, desFileName, muFileName):
	cmdLine = "./%s %s %s %s" % (execName, srcFileName, desFileName, muFileName)
	print cmdLine
	line = commands.getoutput(cmdLine)
	print line
	# with open(desFileName, "w") as fout:
		# fout.write(line)


def batchWithPool(execNames, dataSetN, nprocess, srcFilePath, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)

	pool = multiprocessing.Pool(processes = nprocess)
	dataNames = filter(lambda x:not x.endswith(".txt"), os.listdir(srcFilePath))
	dataNames = sorted(dataNames)
	print dataNames

	for execName in execNames:
		tmpFilePath = os.path.join(desFilePath, execName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		for dataName in dataNames:
			tmpFilePath = os.path.join(desFilePath, execName, dataName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)

	for dataSetId in xrange(dataSetN):
		fileName = genDesFileName(dataSetId)
		for dataName in dataNames:
			mu = int(dataName[dataName.rindex('_')+1:])
			muFileName = "prices_%d.txt" % (mu)
			muFileName = os.path.join(srcFilePath, muFileName)
			for execName in execNames:
				srcFileName = os.path.join(srcFilePath, dataName, fileName)
				desFileName = os.path.join(desFilePath, execName, dataName, fileName)
				if os.path.exists(desFileName):
					continue
				pool.apply_async(run, (execName, srcFileName, desFileName, muFileName, ))

	pool.close()
	pool.join()


def exp0():
	dataSetN, nprocess = CFBE.dataSetN, CFBE.nprocess
	execNames = ["base"]
	srcFilePath = "../dataSet_Qiyu"
	desFilePath = "../result_Qiyu"
	cmdLine = "rm -rf %s" % (desFilePath)
	commands.getoutput(cmdLine)
	batchWithPool(execNames, dataSetN, nprocess, srcFilePath, desFilePath)

if __name__ == "__main__":
	exp0()
