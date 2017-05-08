#!/usr/bin/env python

import sys
import os

def countWorkerN(lines):
	ret = 0
	for line in lines:
		line = line.strip()
		if line:
			itemList = line.split()
			ret += int(itemList[-2])
	return ret


def countTaskN(lines):
	ret = 0
	for line in lines:
		line = line.strip()
		if line:
			itemList = line.split()
			ret += int(itemList[-1])
	return ret

def readPredict(fileName):
	lines = []
	with open(fileName, "r") as fin:
		lines = fin.readlines()[1:]
	workerN = countWorkerN(lines)
	taskN = countTaskN(lines)
	print "workerN = %d, taskN = %d" % (workerN, taskN)


if __name__ == "__main__":
	srcFileName = "prediction.in"
	if len(sys.argv) > 1:
		srcFileName = sys.argv[1];
	readPredict(srcFileName)