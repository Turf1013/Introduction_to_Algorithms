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
			tmpList = line.split(' ')
			resList.append(float(tmpList[1]))
		if resList[0] <= resList[1]:
			ret.append(fileName)
	return ret
			
			
def select(srcFilePath, desFilePath, execNames):			
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	dirNames = os.listdir(os.path.join(srcFilePath, execNames[0]))
	with open("F:/tmp/tmp.txt", "w") as fout:
		for dirName in dirNames:
			tmpList = fetch(srcFilePath, dirName, execNames[:2])
			line = "%20s %d %s\n" % (dirName, len(tmpList), tmpList)
			fout.write(line)
			
			for execName in execNames:
				tmpFilePath = os.path.join(desFilePath, execName)
				if not os.path.exists(tmpFilePath):
					os.mkdir(tmpFilePath)
				tmpFilePath = os.path.join(tmpFilePath, dirName)
				if not os.path.exists(tmpFilePath):
					os.mkdir(tmpFilePath)
				if not os.path.exists(tmpFilePath):
					os.mkdir(tmpFilePath)
				for i,fileName in enumerate(tmpList):
					srcFileName = os.path.join(srcFilePath, execName, dirName, fileName)
					with open(srcFileName, "r") as fin:
						lines = fin.readlines()
					tmpFileName = "data_%02d.txt" % (i)
					desFileName = os.path.join(desFilePath, execName, dirName, tmpFileName)
					with open(desFileName, "w") as _fout:
						_fout.writelines(lines)
					
			
			
if __name__ == "__main__":
	srcFilePath = "F:/tmp_SLADE/result_SLADE_tmp/Heter"
	desFilePath = "F:/tmp_SLADE/result_SLADE_/Heter"
	execNames = ["greedy", "cip", "opqe"]
	# execNames = ["opqe2", "greedy", "cip"]
	select(srcFilePath, desFilePath, execNames)