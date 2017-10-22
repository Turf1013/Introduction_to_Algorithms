#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing
import utm

global cntDict
cntDict = dict()

class constForGenDemand:
	unitTimeWindow = 300

class CFGD:
	pass

	
def getDate(s):
	if '.' in s:
		s = s[:s.rindex('.')]
	t0, t1 = s.split(' ')[:2]
	year,month,day = map(int, t0.split('-'))
	return year,month,day

	
def genDateStamp(year, month, day):
	return year * 31 * 12 + (month-1) * 31 + day - 1
	
	
def updateDict(timeStr, tid, vid):
	year,month,day = getDate(timeStr)
	ds = genDateStamp(year, month, day)
	if vid not in cntDict:
		cntDict[vid] = dict()
	if tid not in cntDict[vid]:
		cntDict[vid][tid] = dict()
	if ds not in cntDict[vid][tid]:
		cntDict[vid][tid][ds] = 0
	c = cntDict[vid][tid][ds] + 1
	print vid, tid, ds, c
	cntDict[vid][tid][ds] = c
	
	
def mergeDemand(srcFileName, timeWindow):
	print srcFileName
	if timeWindow < CFGD.unitTimeWindow:
		timeWindow = CFGD.unitTimeWindow
	scale = int(timeWindow / CFGD.unitTimeWindow) 
	with open(srcFileName, "r") as fin:
		for line in fin:
			line = line.strip()
			timeStr, tid, cnt = line.split(' ')
			updateDict(timeStr, tid/scale, vid)
	print len(cntDict)	
			
def mergeAllData(srcFilePath, timeWindow, nprocess=16):
	pool = multiprocessing.Pool(processes = nprocess)

	dirNames = filter(lambda x:x.startswith('S'), os.listdir(srcFilePath))
	for dirName in dirNames:
		dataFilePath = os.path.join(srcFilePath, dirName)
		dataNames = filter(lambda x:x.endswith('csv') and x.startswith('S'), os.listdir(dataFilePath))
		for dataName in dataNames:
			srcFileName = os.path.join(srcFilePath, dirName, dataName)
			pool.apply_async(mergeDemand, (srcFileName, timeWindow, ))

	pool.close()
	pool.join()
	
	
def dumpData(desFileName, nV):
	tmpDict = dict()
	for vid,vidDict in cntDict.iteritems():
		s,c = 0,0
		for tid,tidDict in vidDict.iteritems():
			for ds,val in tidDict.iteritems():
				s += val
				c += 1
		#s = (s + c - 1) / c
		tmpDict[vid] = s
	with open(desFileName, "w") as fout:
		for vid in xrange(1, nV+1):
			if vid in tmpDict:
				s = tmpDict[vid]
			else:
				s = 0
			if s>0:
				print vid, s
			line = "%d %d\n" % (vid, s)
			fout.write(line)

			
def readNV(srcFileName):
	with open(srcFileName, "r") as fin:
		for line in fin:
			nV, nE = map(int, line.strip().split(' '))
			return nV
	return None
	
	
def exp0(timeWindow=300, radius=1000, nprocess=4):
	cntDict.clear()
	srcFilePath = "../nearest_%05d_%05d" % (timeWindow, radius)
	desFilePath = "../demand_%05d_%05d" % (timeWindow, radius)
	srcFilePath = "./nearest" 
	desFilePath = "./demand_%05d_%05d" % (timeWindow, radius)
	mergeAllData(srcFilePath, timeWindow, nprocess)
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	desFilePath = os.path.join(desFilePath, "windowSize_%d" % (timeWindow))
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	desFileName = os.path.join(desFilePath, "demand.txt")
	nV = readNV("./Shanghai_roadnetwork.txt")
	print nV
	dumpData(desFileName, nV)

	
if __name__ == "__main__":
	exp0()

