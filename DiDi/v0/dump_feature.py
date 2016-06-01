#!/usr/bin/python
from collections import defaultdict
from operator import itemgetter
import numpy as np
import matplotlib.pyplot as plt
import os
import csv

global ndstrict, nslice, nday
ndistrict = 66
nslice = 144
nday = 22

def dumpLines(filename):
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	ret = []
	with open(filename, "r") as fin:
		ret = filter(lambda s:s, map(lambda s:s.strip(), fin.readlines()))
	return ret	


def dumpFeature(filename):
	"""
		1. dayId
		2. sliceId
		3. request
		4. answer
	"""
	reqDict = dict()
	ansDict = dict()
	lines = dumpLines(filename)
	for line in lines:
		L = line.split()
		districtId = int(L[3])
		sliceId = int(L[-1]) - 1
		if not districtId in reqDict:
			reqDict[districtId] = [0] * nslice
		if not districtId in ansDict:
			ansDict[districtId] = [0] * nslice
		reqDict[districtId][sliceId] += 1
		if L[1] != "NULL":
			ansDict[districtId][sliceId] += 1
	return reqDict, ansDict	
	

def extractFeature(dataPath):
	orderPath = os.path.join(dataPath, "order_data")
	if not os.path.isdir(orderPath):
		raise ValueError, "%s is unvalid directory" % (orderPath)
	nameList = os.listdir(orderPath)
	nameList.sort(cmp = lambda x, y: int(x.split('-')[-1]) - int(y.split('-')[-1]))
	reqDict = defaultdict(dict)
	ansDict = defaultdict(dict)
	for name in nameList:
		filename = os.path.join(orderPath, name)
		dayId = (int(name.split('-')[-1]) - 1) % 7
		reqTmpDict, ansTmpDict = dumpFeature(filename)
		for districtId in range(1, ndistrict+1):
			if districtId in reqTmpDict:
				assert districtId in ansTmpDict
				reqDict[districtId][dayId] = reqTmpDict[districtId]
				ansDict[districtId][dayId] = ansTmpDict[districtId]
			else:
				assert not districtId in ansTmpDict
				reqDict[districtId][dayId] = [0] * nslice
				ansDict[districtId][dayId] = [0] * nslice
	return reqDict, ansDict		
	
	
def saveFeature(filename, dataList):
	with open(filename, "wb") as fout:
		writer = csv.writer(fout, delimiter=',')
		for data in dataList:
			writer.writerow(data)
	
				
def dump(srcPath, desPath):
	reqDict, ansDict = extractFeature(srcPath)
	if not os.path.isdir(desPath):
		os.mkdir(desPath)
	for districtId in range(1, ndistrict+1):
		filename = os.path.join(desPath, "feat_%s" % (districtId))
		rDict = reqDict[districtId]
		aDict = ansDict[districtId]
		dataList = []
		for dayId in rDict.iterkeys():
			tmpList = map( lambda i: [dayId, i+1, rDict[dayId][i], aDict[dayId][i]], range(0, nslice) )
			dataList += tmpList
		saveFeature(filename, dataList)
	
				
if __name__ == "__main__":
	# dump("../data/train", "./train_feature")
	dump("../data/test", "./test_feature")
	