#!/usr/bin/env python

import sys
import os
import commands

def gao(filePath):
	nameList = os.listdir(filePath)
	for name in nameList:
		name1 = os.path.join(filePath, name)
		name2 = '_'.join(name.split('_')[1:])
		name2 = os.path.join(filePath, name2)
		cmdLine = "mv %s %s" % (name1, name2)
		print cmdLine
		line = commands.getoutput(cmdLine)
		print line


if __name__ == "__main__":
	srcFilePath = "/home/turf/dataz/dataSet_v0424"
	nameList = os.listdir(srcFilePath)
	for name in nameList:
		if name=='exp' or name=='normal':
			filePath = os.path.join(srcFilePath, name)
			gao(filePath)