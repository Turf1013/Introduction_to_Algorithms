#!/usr/bin/env python

import os
from random import randint, shuffle
from copy import deepcopy

def dumpLines(srcFileName):
	lines = []
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	return lines
	

def fetchType_work(line):
	itemList = line.strip().split()
	return itemList[1]=='w'

def fetchType_task(line):
	itemList = line.strip().split()
	return itemList[1]=='t'


def updateDeadline(lines):
	ret = []
	for line in lines:
		itemList = line.strip().split()
		itemList[-2] = "720"
		line = " ".join(itemList)
		ret.append(line)
	return ret


def mergeData():
	fileName1 = "/home/turf/Code/Code_today/work_1000.txt"
	fileName2 = "/home/turf/Code/Code_today/task_5000.txt"
	desFileName = "/home/turf/Code/Code_today/order.txt"
	lines1 = dumpLines(fileName1)[1:]
	lines1 = filter(fetchType_work, lines1)
	lines1 = updateDeadline(lines1)
	lines2 = dumpLines(fileName2)[1:]
	lines2 = filter(fetchType_task, lines2)
	lines2 = map(lambda x:x.strip(), lines2)
	lines = lines1 + lines2
	shuffle(lines)
	firstLine = "%d %d %d %d\n" % (1000, 5000, 10.0, 10000)
	with open(desFileName, "w") as fout:
		fout.write(firstLine)
		for line in lines:
			fout.write("%s\n" % (line))


def dumpMultipleOrder(srcFileName, desFilePath, dl):
	lines = dumpLines(srcFileName)
	itemN = 6005
	for orderId in xrange(100):
		begTimeList = [randint(1, 3600)-1 for i in xrange(itemN)]
		begTimeList.sort()
		desFileName = "order%d.txt" % (orderId)
		desFileName = os.path.join(desFilePath, desFileName)
		with open(desFileName, "w") as fout:
			for i in xrange(len(lines)):
				line = lines[i].strip()
				if i > 0:
					itemList = [str(begTimeList[i-1])] + line.split()[1:]
					if itemList[1]=='w':
						itemList[-2] = str(dl)
					line = " ".join(itemList)
				fout.write("%s\n" % (line))



def gao(srcFileName, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	for deadLine in [30, 50, 100]:
		setPathName = "dl_%d" % (deadLine)
		setPathName = os.path.join(desFilePath, setPathName)
		if not os.path.exists(setPathName):
			os.mkdir(setPathName)
		dumpMultipleOrder(srcFileName, setPathName, deadLine)


if __name__ == "__main__":
	srcFileName = "/home/turf/Code/Code_today/order.txt"
	desFilePath = "/home/turf/dataSet/dataSet_v0513/data"
	gao(srcFileName, desFilePath)
	# mergeData()