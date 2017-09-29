#!/usr/bin/env python

import os
import sys
from genData import normalGenerator
from random import randint

global lb
lb = 20

def getCheckInLoc(tmpList, token):
	tmpList = tmpList[3:]
	for i,item in enumerate(tmpList):
		if item.startswith(token):
			x = float(item)
			y = float(tmpList[i+1])
			return (x, y)
	return None


def readRealData(srcFileName, token):
	uidSet = set()
	venueLocDict = dict()
	with open(srcFileName, "r") as fin:
		for i,line in enumerate(fin):
			line = line.strip()
			if not line:
				continue
			tmpList = line.split()
			# print tmpList
			try:
				userId = int(tmpList[0])
			except:
				print i, line, tmpList
				raise ValueError("abc")
			uidSet.add(userId)
			venueId = tmpList[1]
			loc = getCheckInLoc(tmpList, token)
			if venueId not in venueLocDict:
				venueLocDict[venueId] = list()
			venueLocDict[venueId].append(loc)
	return uidSet, venueLocDict

	
def calcLoc(tmpList):
	sx, sy = 0, 0
	for t in tmpList:
		sx += t[0]
		sy += t[1]
	sx /= len(tmpList)
	sy /= len(tmpList)
	return (sx, sy)
	
def distance(a, b):
	return ((a[0]-b[0])**2 + (a[1]-b[1])**2)**0.5
	
def updateCloseDict(workerLoc, taskLocDict, cntDict):
	dmax = 500
	for taskId, taskLoc in taskLocDict.iteritems():
		if taskId not in cntDict:
			cntDict[taskId] = 0
			d = distance(workerLoc, taskLoc)
			if d<dmax:
				cnt[taskId] += 1
				
def printCloseDict(cntDict):
	with open("F:/tmp.txt", "a") as fout:
		for taskId, taskCnt in cntDict.iteritems():
			line = "%s, %s\n" % (taskId, taskCnt)
			fout.write(line)
			
def calcTaskN(locDict):
	ret = 0
	for vid, tmpList in locDict.iteritems():
		if len(tmpList) >= lb:
			ret += 1
	return ret * 3

def calcWorkerN(lines, closeSet):
	ret = 0
	for line in lines:
		tmpList = line.split()
		uid = int(tmpList[0])
		venueId = tmpList[1]
		if venueId not in closeSet:
			continue
		ret += 1
	return ret
	
def genRealData(srcFileName, desFilePath, uidSet, locDict, token, n):
	lines = []
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()	
	lines = filter(lambda x:len(x.strip())>0, lines)
	taskN = calcTaskN(locDict)
	K = 4
	epsilon = 0.1
	grt = normalGenerator(0.87, 0.05)
	uidDict = dict()
	taskLocDict = dict()
	for i,uid in enumerate(uidSet):
		uidDict[uid] = i
	for i in xrange(n):
		closeSet = set()
		placeName = srcFileName[srcFileName.rindex('_')+1:-4]
		desFileName = "%s_%02d.txt" % (placeName, i)
		desFileName = os.path.join(desFilePath, desFileName)
		with open(desFileName, "w") as fout:
			fout.write("%s %s\n" % (K, epsilon))
			copyList = []
			for vid, tmpList in locDict.iteritems():
				if len(tmpList) < lb:
					continue
				ncopy = randint(1, 5)
				copyList.append(ncopy)
			taskN = sum(copyList)
			fout.write("%s\n" % (taskN))
			i = 0
			for vid, tmpList in locDict.iteritems():
				if len(tmpList) < lb:
					continue
				closeSet.add(vid)
				loc = calcLoc(tmpList)
				taskLocDict[vid] = loc
				ncopy = copyList[i]
				i += 1
				for j in xrange(ncopy):
					x = loc[0]*111300 + randint(20, 50)
					y = loc[1]*111300 + randint(20, 50)
					fout.write("%s %s\n" % (x, y))
			
			workerN = calcWorkerN(lines, closeSet)
			fout.write("%s\n" % (workerN))
			accList = grt.gen(workerN)
			for line in lines:
				tmpList = line.split()
				uid = int(tmpList[0])
				venueId = tmpList[1]
				if venueId not in closeSet:
					continue
				acc = accList[uidDict[uid]]
				loc = getCheckInLoc(tmpList, token)
				fout.write("%s %s %s\n" % (loc[0]*111300, loc[1]*111300, acc))
		print workerN, taskN
	
			
def parameterFile(srcFilePath, desFilePath):
	epsList = [0.12, 0.14, 0.16, 0.18, 0.20]
	placeName = srcFilePath[srcFilePath.rindex('_')+1:]
	subDesFilePath = os.path.join(desFilePath, placeName)
	if not os.path.exists(subDesFilePath):
		os.mkdir(subDesFilePath)
	srcFileNames = os.listdir(srcFilePath)
	for srcFileName in srcFileNames:
		if placeName not in srcFileName:
			continue	
		tmpFileName = os.path.join(srcFilePath, srcFileName)
		with open(tmpFileName, "r") as fin:
			lines = fin.readlines()
			for epsilon in epsList:
				fileName = srcFileName[:srcFileName.index('_')] + "_" + str(epsilon) + srcFileName[srcFileName.index('_'):]
				fileName = os.path.join(subDesFilePath, fileName)
				with open(fileName, "w") as fout:
					tmpList = lines[0].split()
					l0 = "%s %s\n" % (tmpList[0], epsilon)
					newLines = [l0] + lines[1:]
					for line in newLines:
						fout.write(line)
					# fout.writelines(newLines)
	
			
if __name__ == "__main__":
	srcFilePath = "/home/server/Yihuihe/dataSet/foursquare"
	desFilePath = "/home/server/Yihuihe/dataSet"
	srcFileNames = [
		"dataset_TSMC2014_NYC.txt",
		"dataset_TSMC2014_TKY.txt",
	]
	tokens = [
		"40",
		"35",
	]
	n = 50
	for i,srcFileName in enumerate(srcFileNames):
		srcFileName = os.path.join(srcFilePath, srcFileName)
		placeName = srcFileName[srcFileName.rindex('_')+1:-4]
		subDesFilePath = os.path.join(desFilePath, "_"+placeName)
		if not os.path.exists(subDesFilePath):
			os.mkdir(subDesFilePath)
		desFileName = srcFileName[srcFileName.rindex('_')+1:]
		desFileName = os.path.join(subDesFilePath, desFileName)
		uidSet, locDict = readRealData(srcFileName, tokens[i])
		genRealData(srcFileName, subDesFilePath, uidSet, locDict, tokens[i], n)
		parameterFile(subDesFilePath, desFilePath)