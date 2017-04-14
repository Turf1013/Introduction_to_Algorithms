#!/usr/bin/env python

import re
import os
import sys
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

def plotGraphInfo(infoDict):
	for tlen in infoDict.iterkeys():
		tmpDict = infoDict[tlen]
		degList = tmpDict.keys()
		degList.sort()
		rateList = []
		for deg in degList:
			rateList.append(tmpDict[deg])

		# plot the curve
		plt.title("tlen=1,deg=%s" % (degList))
		X = range(1, len(degList)+1)
		Y = rateList
		plt.plot(X, Y, 'ro-', linewidth=2.5)
		plt.ylabel('Real deg rate')
		plt.xlabel('location deg rate')
		plt.xlim(0, max(X)+1)	
		plt.xticks(range(0, len(degList)+2), [""] + map(str, degList) + [""])
		#plt.yticks(range(0, len(rateList)+2), [""] + map(float, rateList) + [""])
		plt.grid(True)
		fileName = "/home/turf/tmp/tlen=%d.png" % (tlen)
		plt.savefig(fileName, dpi=200)
		plt.show()
		plt.close()


def dumpInfoDict(fileName):
	lines = []
	with open(fileName, "r") as fin:
		lines = fin.readlines()
	nline = len(lines)
	i = 0
	retDict = dict()
	while i < nline:
		line = lines[i].strip()
		if len(line) == 0:
			i += 1
			continue
		deg = float(line)
		i += 1
		while i < nline:
			line = lines[i].strip()
			if len(line)==0 or not line.startswith("tlen"):
				break
			tmpList = line.split(' ')
			tlenExp = tmpList[0]
			rateExp = tmpList[1]
			tlenVal = tlenExp.split('=')[-1]
			rateVal = rateExp.split('=')[-1]
			tlenVal = int(float(tlenVal))
			rateVal = float(rateVal)
			if tlenVal not in retDict:
				retDict[tlenVal] = dict()
			if deg not in retDict[tlenVal]:
				retDict[tlenVal][deg] = dict()
			retDict[tlenVal][deg] = rateVal
			i += 1
	return retDict


if __name__ == "__main__":
	fileName = "/home/turf/tmp/graph_info.txt"
	tmpDict = dumpInfoDict(fileName)
	plotGraphInfo(tmpDict)

