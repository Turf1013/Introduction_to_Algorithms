#!/usr/bin/env python

import commands
import os

def compare():
	execPrefix = "/home/turf/Code/TmpTest"
	dataDirPath = "/home/turf/tmp/dataz_150"
	weightPath = "/home/turf/tmp/weight_uniform"
	nameList = os.listdir(dataDirPath)
	for name in nameList:
		orderFileName = os.path.join(dataDirPath, name, "order0.txt")
		wnameList = os.listdir(weightPath)
		for wname in wnameList:
			weightFileName = os.path.join(weightPath, wname)
			utilites = []
			for execName in ["Pure", "Xuan"]:
				execName = os.path.join(execPrefix, execName)
				cmdLine = "%s %s %s %s" % (execName, weightFileName, orderFileName, str(0.1))
				line = commands.getoutput(cmdLine)
				tmpList = line.strip().split(' ')
				utilites.append(float(tmpList[-1]))
			if utilites[0] != utilites[1]:
				print name, wname, utilites


if __name__ == "__main__":
	compare()