#!/usr/bin/env python

import os

def change(srcFilePath, desFilePath, newUmax):
	newUmax = str(newUmax)
	dirPath = srcFilePath[srcFilePath.rindex('/')+1:]
	dirList = dirPath.split('_')
	#dirList[-1] = newUmax
	dirPath = "_".join(dirList)
	desPath = os.path.join(desFilePath, dirPath)
	if not os.path.exists(desPath):
		os.mkdir(desPath)
	nameList = os.listdir(srcFilePath)
	for name in nameList:
		fileName = os.path.join(srcFilePath, name)
		lines = []
		with open(fileName, "r") as fin:
			lines = fin.readlines()
		infoLine = lines[0]
		infoList = infoLine.split()
		#print infoList
		infoList[2] = newUmax
		infoLine = " ".join(infoList) + "\n"
		lines[0] = infoLine
		desFileName = os.path.join(desPath, name)
		with open(desFileName, "w") as fout:
			fout.write("".join(lines))



def changeAll(srcFilePath, desFilePath, newUmax):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	nameList = os.listdir(srcFilePath)
	for name in nameList:
		filePath = os.path.join(srcFilePath, name)
		change(filePath, desFilePath, newUmax)


if __name__ == "__main__":
	newUmax = 150
	srcFileName = "/home/turf/tmp/dataz"
	desFileName = "/home/turf/tmp/dataz_%d" % (newUmax)
	changeAll(srcFileName, desFileName, newUmax)
