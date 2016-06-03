#!/usr/bin/python
from collections import defaultdict
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import os
from time import sleep
from random import randint ,shuffle
import json

ndistrict = 66
nslice = 144
ndays = 21

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
		if districtId not in reqDict:
			reqDict[districtId] = [0] * nslice
		if districtId not in ansDict:
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
		assert len(reqDict[districtId]) == len(ansDict[districtId]) and len(reqDict[districtId])==ndays
		for j in range(ndays):				
			rList = reqDict[districtId][j]
			aList = ansDict[districtId][j]
			gList = [0] * nslice
			for i in range(nslice):
				gList[i] = rList[i] - aList[i]
			gapDict[districtId].append(gList)
	return gapDict
	
	
def dumpToFile(d, filename):
	js = json.dumps(d)
	with open(filename, "w") as fout:
		fout.write(js)
		
		
def getAllRA_fast(desPath):
	with open(os.path.join(desPath, "req.json"), "r") as fin:
		line = fin.read()
	reqDict = json.loads(line)
	with open(os.path.join(desPath, "ans.json"), "r") as fin:
		line = fin.read()
	ansDict = json.loads(line)
	with open(os.path.join(desPath, "gap.json"), "r") as fin:
		line = fin.read()
	gapDict = json.loads(line)
	return reqDict, ansDict, gapDict
	
	
def merge(L, k):
	n = len(L)
	ret = []
	for i in xrange(0, n, k):
		ret.append( sum(L[i:i+k]) )
	return ret
	
	
def transfer(period, reqDict, ansDict, gapDict):
	assert nslice % period == 0
	reqTmpDict = defaultdict(list)
	ansTmpDict = defaultdict(list)
	gapTmpDict = defaultdict(list)
	for districtId in xrange(1, ndistrict+1):
		districtId_s = str(districtId)
		for j in xrange(0, ndays):
			reqTmpDict[districtId].append( merge(reqDict[districtId_s][j], period) )
			ansTmpDict[districtId].append( merge(ansDict[districtId_s][j], period) )
			gapTmpDict[districtId].append( merge(gapDict[districtId_s][j], period) )
	
	reqDict.clear()
	reqDict.update(reqTmpDict)
	ansDict.clear()
	ansDict.update(ansTmpDict)
	gapDict.clear()
	gapDict.update(gapTmpDict)
	
	
	
def show_districtByPeriod(datapath, period, desPath):
	if os.path.isfile(os.path.join(desPath, "req.json")) and\
		os.path.isfile(os.path.join(desPath, "ans.json")) and\
		os.path.isfile(os.path.join(desPath, "gap.json")):
		reqDict, ansDict, gapDict = getAllRA_fast(desPath)
	else:
		reqDict, ansDict = getAllRA(datapath)
		gapDict = genGapDict(reqDict, ansDict)
		dumpToFile(reqDict, os.path.join(desPath, "req.json"))
		dumpToFile(ansDict, os.path.join(desPath, "ans.json"))
		dumpToFile(gapDict, os.path.join(desPath, "gap.json"))
		
	transfer(period, reqDict, ansDict, gapDict)
	colorList = [
		'#ff0000',
		'#ffff00',
		'#00ff00',
		'#00ffff',
		'#ff9900',
		'#4589f9',
		'#0000ff',
		'#9900ff',
		'#ff00ff',
		'#980000',
		'#783f04',
		'#c0ff3e',
		'#8b008b',
		'#7ac5cd',
		'#698b22',
		'#00e5ee',
		'#6959cd',
		'#8b7d6b',
		'#ff82ab',
		'#cc6633',
		'#eea2ad',
	]
	
	shuffle(colorList)
	X = range(0, nslice/period)
	for districtId in xrange(1, ndistrict+1):
		reqList = reqDict[districtId]
		ansList = ansDict[districtId]
		gapList = gapDict[districtId]
		
		# save request
		plt.subplot(1, 1, 1)
		plt.title('request of %s' % (districtId))
		plt.xlabel('date')
		plt.ylabel('num')
		for i in xrange(0, ndays):
			plt.plot(X, reqList[i], color=colorList[i], linewidth=1.5, linestyle='-', label='01-%2d' % (i+1))
		# plt.legend()
		plt.savefig(os.path.join(desPath, '%s_req.png' % (districtId)), dpi=400)
		plt.close()
		
		# save answer
		plt.subplot(1, 1, 1)
		plt.title('answer of %s' % (districtId))
		plt.xlabel('date')
		plt.ylabel('num')
		for i in xrange(0, ndays):
			plt.plot(X, ansList[i], color=colorList[i], linewidth=1.5, linestyle='-', label='01-%2d' % (i+1))
		# plt.legend()
		plt.savefig(os.path.join(desPath, '%s_ans.png' % (districtId)), dpi=400)
		plt.close()
		
		# show gap
		plt.subplot(1, 1, 1)
		plt.title('gap of %s' % (districtId))
		plt.xlabel('date')
		plt.ylabel('num')
		for i in xrange(0, ndays):
			plt.plot(X, gapList[i], color=colorList[i], linewidth=1.5, linestyle='-', label='01-%2d' % (i+1))
		# plt.legend()
		plt.savefig(os.path.join(desPath, '%s_gap.png' % (districtId)), dpi=400)
		plt.close()
	
	
if __name__ == "__main__":
	desPath = "./period"
	if not os.path.isdir(desPath):
		os.mkdir(desPath)
	show_districtByPeriod("I:/DiDi/data/train", period=6, desPath=desPath)
	
	
	