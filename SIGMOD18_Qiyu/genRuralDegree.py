#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing
import utm

def readCenter(fileName):
	ret = []
	with open(fileName, "r") as fin:
		for line in fin:
			line = line.strip()
			if not line:
				continue
			itemList = line.split(' ')
			x, y = map(float, itemList[1:3])
			x, y = utm.from_latlon(float(x), float(y))[:2]
			ret.append([x, y])
	return ret

	
def readVertex(graphFileName):
	ret = []
	with open(graphFileName, "r") as fin:
		for i,line in enumerate(fin):
			if i == 0:
				nV, nE = map(int, line.split(' '))[:2]
			elif i>nV:
				break
			else:
				x, y = map(float, line.split(' '))[:2]
				ret.append([x, y])
	return ret
	
	
def Distance(a, b):
	return ((a[0]-b[0])**2 + (a[1]-b[1])**2) ** 0.5
	
	
def calcRuralDegree(graphFileName, centerFileName, desFileName):
	centers = readCenter(centerFileName)
	positions = readVertex(graphFileName)
	nV = len(positions)
	distances = [0.0] * nV
	for i,pos in enumerate(positions):
		mnVal = 10 ** 25
		for center in centers:
			tmp = Distance(pos, center)
			if tmp < mnVal:
				mnVal = tmp
		distances[i] = mnVal
	with open(desFileName, "w") as fout:
		fout.write("%d\n" % (nV))
		for i in xrange(nV):
			fout.write("%.6f\n" % (distances[i]))
		
	
def exp0():
	centerFileName = "./shanghaiCenter.txt"
	graphFileName = "./Shanghai_roadnetwork.txt"
	desFileName = "./ruralDegree.txt"
	calcRuralDegree(graphFileName, centerFileName, desFileName)
	
	
if __name__ == "__main__":
	exp0()
	