#!/usr/bin/env python

import os
import sys

def calInfo(filePath):
	nameList = os.listdir(filePath)
	degDict = dict()
	cntDict = dict()
	for name in nameList:
		if not name.startswith("graph_info"):
			continue
		print name
		fileName = os.path.join(filePath, name)
		lines = []
		with open(fileName, "r") as fin:
			lines = fin.readlines()
		for line in lines:
			tmpList = line.strip().split()
			workerN = int(tmpList[0].split('_')[0])
			taskN = int(tmpList[0].split('_')[1])
			if workerN != taskN or workerN==1000:
				continue
			# print tmpList[0]
			workerVar = float(tmpList[2].split('=')[-1])
			taskVar = float(tmpList[4].split('=')[-1])
			degRate = float(tmpList[0].split('_')[2]) / 100.0
			if degRate not in degDict:
				degDict[degRate] = [0.0, 0.0]
				cntDict[degRate] = 0
			degDict[degRate][0] += workerVar
			degDict[degRate][1] += taskVar
			cntDict[degRate] += 1
	for degRate, varList in degDict.iteritems():
		workerAvgVar = varList[0] / cntDict[degRate]
		taskAvgVar = varList[1] / cntDict[degRate]
		print "%lf: workerAvgVar = %.2f, taskAvgVar = %.2f" % (degRate, workerAvgVar, taskAvgVar)
	print "\n"


if __name__ == "__main__":
	srcFilePath = "/home/turf/tmp"
	calInfo(srcFilePath)
