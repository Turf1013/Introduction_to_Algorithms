#!/usr/bin/python
from collections import defaultdict
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import os
from time import sleep
import json

def getLines(filename):
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	ret = []
	with open(filename, "r") as fin:
		ret = filter(lambda s:s, map(lambda s:s.strip(), fin.readlines()))
	return ret
	

def getRA(filename, sliceList):
	nslice = len(sliceList)
	lines = getLines(filename)
	sliceDict = dict(zip(sliceList, range(nslice)))
	reqDict = dict()
	ansDict = dict()
	for line in lines:
		L = line.split()
		districtId = int(L[3])
		sliceId = int(L[-1])
		if sliceId not in sliceDict:
			continue
		if not reqDict.has_key(districtId):
			reqDict[districtId] = [0] * nslice
		idx = sliceDict[sliceId]
		if L[1]=="NULL":
			reqDict[districtId][idx] += 1
		else:
			reqDict[districtId][idx] += 1
			ansDict[districtId][idx] += 1
	return reqDict, ansDict
	
	
def getAllRA(datapath, sliceList):
	n = 66
	nslice = len(sliceList)
	orderPath = os.path.join(datapath, "order_data")
	nameList = os.listdir(orderPath)
	reqDict = defaultdict(list)
	ansDict = defaultdict(list)
	nameList.sort(cmp = lambda x, y: int(x.split('-')[-1]) - int(y.split('-')[-1]) )
	for i in xrange(1, n+1):
		reqDict[i] = [0] * nslice
		ansDict[i] = [0] * nslice
	for name in nameList:
		reqTmpDict, ansTmpDict = getRA(os.path.join(orderPath, name), sliceList)
		dateId = int(name.split('-')[-1])
		print name
		for districtId in range(1, n+1):
			if districtId in reqTmpDict:
				for j in xrange(nslice):
					reqDict[districtId][j] += reqTmpDict[districtId][j]
			if districtId in ansTmpDict:
				for j in xrange(nslice):
					ansDict[districtId][j] += ansTmpDict[districtId][j]
	return reqDict, ansDict
	
	
def	genGapDict(reqDict, ansDict):
	gapDict = defaultdict(list)
	for districtId in reqDict.iterkeys():
		rList = reqDict[districtId]
		aList = ansDict[districtId]
		assert len(rList) == len(aList)
		gList = [0] * len(rList)
		for i in xrange(len(gList)):
			gList[i] = rList[i] - aList[i]
		gapDict[districtId] = gList
	return gapDict
	
	
def dumpToFile(d, namePrefix):
	filename = namePrefix + ".json"
	js = json.dumps(d)
	with open(filename, "w") as fout:
		fout.write(js)
		
		
def getAllRA_fast():
	with open("req.json", "r") as fin:
		line = fin.read()
	reqDict = json.loads(line)
	with open("ans.json", "r") as fin:
		line = fin.read()
	ansDict = json.loads(line)
	return reqDict, ansDict
	
	
def show_districtBySlice(datapath):
	sliceList = [46, 58, 70, 82, 94, 106, 118, 130, 142]
	reqDict, ansDict = getAllRA(datapath, sliceList)
	dumpToFile(reqDict, "req")
	dumpToFile(ansDict, "ans")
	reqDict, ansDict = getAllRA_fast()
	gapDict = genGapDict(reqDict, ansDict)
	styles = [
		'bo-',
		'rs-',
		'y*-',
	]
	
	for districtId in reqDict.iterkeys():
		reqList = reqDict[districtId]
		ansList = ansDict[districtId]
		gapList = gapDict[districtId]
		ndays = len(reqList)
		assert ndays%7 == 0
		
		plt.subplot(3, 1, 1)
		plt.title('request of %s' % (districtId))
		# plt.xlabel('day')
		plt.ylabel('num')
		for i in xrange(0, ndays, 7):
			style = styles[i/7]
			plt.plot(range(0, 7), reqList[i:i+7], style)
			
		plt.subplot(3, 1, 2)
		plt.title('answer of %s' % (districtId))
		# plt.xlabel('day')
		plt.ylabel('num')
		for i in xrange(0, ndays, 7):
			style = styles[i/7]
			plt.plot(range(0, 7), ansList[i:i+7], style)
			
		plt.subplot(3, 1, 3)
		plt.title('gap of %s' % (districtId))
		# plt.xlabel('day')
		plt.ylabel('num')
		for i in xrange(0, ndays, 7):
			style = styles[i/7]
			plt.plot(range(0, 7), gapList[i:i+7], style)
		
		# plt.show()
		plt.savefig('slice_%s.png' % (districtId))
		plt.close()
	
	
if __name__ == "__main__":
	show_districtBySlice("I:/DiDi/data/train")
	
	
	