#!/usr/bin/python

import os
import sys
import platform
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from genResult import getResult

class constForPlotResult:
	colorList = [
		'ro-',
		'gs-',
		'y*-',
		'b^-',
		'cD-',
	]
	shortAlgoNameDict = {
		"Extend_Greedy_RT": "RT",
		"TGOA_Greedy": "TGOA",
		"Pure_Greedy": "Pure",
	}
	
class CFPR(constForPlotResult):
	pass


def plotPic(desFilePath, title, resDict):
	title = "_".join(title.split(','))
	for paraName, paraList in resDict.iteritems():
		desFileName = "%s.png" % (title)
		desFileName = os.path.join(desFilePath, paraName, desFileName)
		plt.title("%s [%s]" % (title, paraName))
		mnY, mxY = 10.0**18, -10.0**18
		for i,tmpList in enumerate(paraList):
			algoName = tmpList[0]
			if algoName in CFPR.shortAlgoNameDict:
				algoName = CFPR.shortAlgoNameDict[algoName]
			Y = tmpList[1:]
			X = range(1, len(Y)+1)
			mnY = min(mnY, min(map(float, Y)))
			mxY = max(mxY, max(map(float, Y)))
			plt.plot(X, Y, CFPR.colorList[i], linewidth=2.5, label=algoName)
		plt.ylabel(paraName)
		plt.xlabel('caseId')
		plt.xlim(0, len(Y)+2)
		if paraName=='Utility':
			plt.ylim(mnY-100.0, mxY+100.0)
		plt.grid(True)
		plt.legend()
		plt.savefig(desFileName, dpi=200)
		plt.show()
		plt.close()
		


def plotOneResult(srcFileName, desFilePath):
	algoN, paraN = 5, 3
	lines = []
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	
	lineN = len(lines)
	i = 0
	while i < lineN:
		line = lines[i].strip()
		if len(line) == 0:
			i += 1
			continue
		i += 1
		titleLine = line
		tmpDict = dict()
		for paraId in xrange(paraN):
			paraName = lines[i].strip()
			i += 1
			tmpList = []
			for algoId in xrange(algoN):
				line = lines[i].strip()
				tmpList.append(line.split())
				i += 1
			tmpDict[paraName] = tmpList
		# add parameter directory
		for paraName in tmpDict.iterkeys():
			tmpFilePath = os.path.join(desFilePath, paraName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
		plotPic(desFilePath, titleLine, tmpDict)
		
		
def plotAllResult(srcFilePath, desFilePath):
	nameList = os.listdir(srcFilePath)
	for name in nameList:
		if not name.endswith(".res"):
			continue
		srcFileName = os.path.join(srcFilePath, name)
		distName = name[:name.rindex('.')]
		plotFilePath = os.path.join(desFilePath, distName)
		if not os.path.exists(plotFilePath):
			os.mkdir(plotFilePath)
		plotOneResult(srcFileName, plotFilePath)
		
	

if __name__ == "__main__":
	srcPath = "F:/Log"
	resDesPath = "F:/Result"
	if len(sys.argv) > 1:
		srcPath = sys.argv[1]
		
	if len(sys.argv) > 2:
		resDesPath = sys.argv[2]
	if not os.path.exists(resDesPath):
		os.mkdir(resDesPath)	
	
	plotDesPath = resDesPath
	if len(sys.argv) > 3:
		plotDesPath = sys.argv[3]
	if not os.path.exists(plotDesPath):
		os.mkdir(plotDesPath)
	
		
	# getResult(srcPath, resDesPath)
	plotAllResult(resDesPath, plotDesPath)