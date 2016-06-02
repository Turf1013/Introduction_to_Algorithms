#!/usr/bin/python
from collections import defaultdict
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import os
from time import sleep
import json

global nslice, ndistrict
ndistrict = 66
nslice = 144


def getLines(filename):
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	ret = []
	with open(filename, "r") as fin:
		ret = filter(lambda s:s, map(lambda s:s.strip(), fin.readlines()))
	return ret
	

def getRA(filename):
	lines = getLines(filename)
	reqDict = dict()
	ansDict = dict()
	for line in lines:
		L = line.split()
		districtId = int(L[3])
		sliceId = int(L[-1]) - 1
		if not reqDict.has_key(districtId):
			reqDict[districtId] = [0] * nslice
		if not ansDict.has_key(districtId):
			ansDict[districtId] = [0] * nslice
		if L[1]=="NULL":
			reqDict[districtId][sliceId] += 1
		else:
			reqDict[districtId][sliceId] += 1
			ansDict[districtId][sliceId] += 1
	return reqDict, ansDict
	
	
def getAllRA(datapath):
	orderPath = os.path.join(datapath, "order_data")
	nameList = os.listdir(orderPath)
	reqDict = defaultdict(list)
	ansDict = defaultdict(list)
	nameList.sort(cmp = lambda x, y: int(x.split('-')[-1]) - int(y.split('-')[-1]) )
	for name in nameList:
		reqTmpDict, ansTmpDict = getRA(os.path.join(orderPath, name))
		dateId = int(name.split('-')[-1])
		print name
		for districtId in range(1, ndistrict+1):
			if districtId in reqTmpDict:
				reqDict[districtId].append( reqTmpDict[districtId] )
			else:
				reqDict[districtId].append( [0] * nslice )
			if districtId in ansTmpDict:
				ansDict[districtId].append( ansTmpDict[districtId] )
			else:
				ansDict[districtId].append( [0] * nslice )
	return reqDict, ansDict
	
	
def	genGapDict(reqDict, ansDict):
	gapDict = defaultdict(list)
	for districtId in reqDict.iterkeys():
		rList = reqDict[districtId]
		aList = ansDict[districtId]
		assert len(rList) == len(aList)
		ndays = len(rList)
		for i in xrange(ndays):
			gList = [0] * nslice
			assert len(rList[i])==nslice and len(aList[i])==nslice
			for j in xrange(nslice):
				gList[j] = rList[i][j] - aList[i][j]
			gapDict[districtId].append( gList )
	return gapDict
	
	
def dumpToFile(desPath, districtId, reqList, ansList, gapList):
	filename = os.path.join(desPath, "all_%s" % (districtId))
	ndays = len(reqList)
	with open(filename, "w") as fout:
		fout.write("req:\n")
		for i in range(0, ndays):
			line = " ".join(map(str, reqList[i])) + "\n"
			fout.write(line)
		fout.write("ans:\n")
		for i in range(0, ndays):
			line = " ".join(map(str, ansList[i])) + "\n"
			fout.write(line)
		fout.write("gap:\n")
		for i in range(0, ndays):
			line = " ".join(map(str, gapList[i])) + "\n"
			fout.write(line)
			
	
def show_districtBySlice(datapath, desPath):
	reqDict, ansDict = getAllRA(datapath)
	gapDict = genGapDict(reqDict, ansDict)
	for districtId in reqDict:
		reqList = reqDict[districtId]
		ansList = ansDict[districtId]
		gapList = gapDict[districtId]
		dumpToFile(desPath, districtId, reqList, ansList, gapList)
	
	
if __name__ == "__main__":
	desPath = "F:\Introduction_to_Algorithms\DiDi\dataset\\all"
	if not os.path.isdir(desPath):
		os.mkdir(desPath)
	show_districtBySlice("I:/DiDi/data/train", desPath)
	
	
	