#!/usr/bin/env python

import os
import sys

def fetch(srcFilePath, dirName, execNames):
	st = set()
	for i,execName in enumerate(execNames):
		tmpFilePath = os.path.join(srcFilePath, execName, dirName)
		fileNames = os.listdir(tmpFilePath)
		if i == 0:
			st = set(fileNames)
		else:
			st &= set(fileNames)
	ret = []
	for fileName in st:
		resList = []
		for execName in execNames:
			srcFileName = os.path.join(srcFilePath, execName, dirName, fileName)
			with open(srcFileName, "r") as fin:
				line = fin.readlines()[0]
			# if "sigma" in dirName:
				# print line
			tmpList = line.split(' ')
			resList.append(float(tmpList[1]))
		if resList[0] <= resList[1]:
			ret.append(fileName)
			# if "sigma" in dirName:
				# print resList
	return ret
			
			
def select(srcFilePath, desFilePath, execNames, dataFilePath=None):			
	_execNames = execNames + ["cip"]
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	dirNames = os.listdir(os.path.join(srcFilePath, execNames[0]))
	for execName in _execNames:
		tmpFilePath = os.path.join(desFilePath, execName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		for dirName in dirNames:
			tmpFilePath = os.path.join(desFilePath, execName, dirName)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
	with open("F:/tmp/tmp.txt", "w") as fout:
		dirNames = sorted(dirNames)
		fetchDict = dict()
		fetchSet = set(dirNames)
		prefix = ""
		for dirName in dirNames:
			tmpList = fetch(srcFilePath, dirName, execNames)
			_prefix = dirName.split('_')[1]
			if prefix != _prefix:
				if prefix:
					fetchDict[prefix] = fetchSet
				fetchSet = set(tmpList)
				prefix = _prefix
			else:
				fetchSet &= set(tmpList)
			# print dirName, _prefix, len(fetchSet), len(tmpList), tmpList
		if prefix:
			fetchDict[prefix] = fetchSet
		
		for dirName in dirNames:
			_prefix = dirName.split('_')[1]
			tmpList = list(fetchDict[_prefix])
			tmpList.sort()
			line = "%20s %d %s\n" % (dirName, len(tmpList), tmpList)
			fout.write(line)
			
			if dataFilePath:
				_dataFilePath = dataFilePath + "_"
				if not os.path.exists(_dataFilePath):
					os.mkdir(_dataFilePath)
				tmpFilePath = os.path.join(_dataFilePath, dirName)
				if not os.path.exists(tmpFilePath):
					os.mkdir(_tmpFilePath)
				for i,fileName in enumerate(tmpList):
					srcFileName = os.path.join(dataFilePath, dirName, fileName)
					with open(srcFileName, "r") as fin:
						lines = fin.readlines()
					tmpFileName = "data_%02d.txt" % (i)
					desFileName = os.path.join(_dataFilePath, dirName, tmpFileName)
					with open(desFileName, "w") as _fout:
						_fout.writelines(lines) 
			
			for execName in _execNames:
				for i,fileName in enumerate(tmpList):
					srcFileName = os.path.join(srcFilePath, execName, dirName, fileName)
					if not os.path.exists(srcFileName) and execName==_execNames[-1]:
						continue
					with open(srcFileName, "r") as fin:
						lines = fin.readlines()
					tmpFileName = "data_%02d.txt" % (i)
					desFileName = os.path.join(desFilePath, execName, dirName, tmpFileName)
					with open(desFileName, "w") as _fout:
						_fout.writelines(lines)

def getHomoName(binN, relia, taskN):
	return "%02d_%05d_%.02f" % (binN, taskN, relia)
	
	
def getBinLines(srcFileNames):
	ret = []
	with open(srcFileNames, "r") as fin:
		for i,line in enumerate(fin):
			if i>=3 and len(line) > 1:
				ret.append(line)
	return ret
	
	
def transfer(srcFilePath, desFilePath, b, e):	
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	for i,dataSetId in enumerate(range(b, e)):
		srcFileName = "data_%02d.txt" % (dataSetId)
		srcFileName = os.path.join(srcFilePath, srcFileName)
		binLines = getBinLines(srcFileName)
	
		# varying of binN
		binN,relia,taskN = 20,0.9,10**4 
		binList = [2,4,6,8,10,15,20,25,30,35,40]
		for binN in binList:
			dataFilePath = getHomoName(binN, relia, taskN)
			tmpFilePath = os.path.join(desFilePath, dataFilePath)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			desFileName = "data_%02d.txt" % (i)
			desFileName = os.path.join(desFilePath, dataFilePath, desFileName)
			with open(desFileName, "w") as fout:
				fout.write("%s\n" % (taskN))
				itemList = [str(relia)] * taskN
				line = " ".join(itemList)
				fout.write("%s\n" % (line))
				fout.write("%s\n" % (binN))
				for j in xrange(binN):
					line = binLines[j].strip()
					fout.write("%s\n" % (line))
		
		# varying of relia
		binN,relia,taskN = 20,0.9,10**4 
		reliaList = [0.88, 0.90, 0.92, 0.94, 0.96]
		for relia in reliaList:
			dataFilePath = getHomoName(binN, relia, taskN)
			tmpFilePath = os.path.join(desFilePath, dataFilePath)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			desFileName = "data_%02d.txt" % (i)
			desFileName = os.path.join(desFilePath, dataFilePath, desFileName)
			with open(desFileName, "w") as fout:
				fout.write("%s\n" % (taskN))
				itemList = [str(relia)] * taskN
				line = " ".join(itemList)
				fout.write("%s\n" % (line))
				fout.write("%s\n" % (binN))
				for j in xrange(binN):
					line = binLines[j].strip()
					fout.write("%s\n" % (line))
					
		
		# varying of scalability
		binN,relia,taskN = 20,0.9,10**4 
		taskNList = [1000, 3000, 5000, 10000, 15000, 20000, 30000, 50000, 75000, 100000]
		for taskN in taskNList:
			dataFilePath = getHomoName(binN, relia, taskN)
			tmpFilePath = os.path.join(desFilePath, dataFilePath)
			if not os.path.exists(tmpFilePath):
				os.mkdir(tmpFilePath)
			desFileName = "data_%02d.txt" % (i)
			desFileName = os.path.join(desFilePath, dataFilePath, desFileName)
			with open(desFileName, "w") as fout:
				fout.write("%s\n" % (taskN))
				itemList = [str(relia)] * taskN
				line = " ".join(itemList)
				fout.write("%s\n" % (line))
				fout.write("%s\n" % (binN))
				for j in xrange(binN):
					line = binLines[j].strip()
					fout.write("%s\n" % (line))
	

def select_Jelly(srcFilePath, desFilePath):
	transfer(srcFilePath, desFilePath, 0, 20)
	
def select_SMIC(srcFilePath, desFilePath):
	transfer(srcFilePath, desFilePath, 20, 40)
	
def exp_Jelly():
	# srcFilePath = "F:/tmp/dataSet2/Heter/varying_binN_40"
	# dataFilePath = "F:/tmp/dataSet2/Jelly"
	# select_Jelly(srcFilePath, dataFilePath)		
	srcFilePath = "F:/tmp/result_SLADE_old/result_SLADE/Jelly"
	desFilePath = "F:/tmp/result_SLADE_Fetch/Jelly"	
	execNames = ["opq", "greedy"]
	select(srcFilePath, desFilePath, execNames)	
	
	
def exp_SMIC():
	# srcFilePath = "F:/tmp/dataSet2/Heter/varying_binN_40"
	# desFilePath = "F:/tmp/dataSet2/SMIC"
	# select_SMIC(srcFilePath, desFilePath)		
	srcFilePath = "F:/tmp/result_SLADE_old/result_SLADE/SMIC"
	desFilePath = "F:/tmp/result_SLADE_Fetch/SMIC"
	execNames = ["opq", "greedy"]
	select(srcFilePath, desFilePath, execNames)	
	
def exp_Heter():
	srcFilePath = "F:/tmp/result_SLADE/Heter"
	desFilePath = "F:/tmp/result_SLADE_Fetch/Heter"
	dataFilePath = "F:/tmp/"
	execNames = ["opqe2", "greedy"]
	select(srcFilePath, desFilePath, execNames)	
	
if __name__ == "__main__":
	# exp_Heter()
	exp_Jelly()
	exp_SMIC()