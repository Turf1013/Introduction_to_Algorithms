#!/usr/bin/env python
import os
import sys
import commands

class constForRegen:
	desFilePath = "./smallData"
	demandBound = 6
	nV = 78560
	
class CFR(constForRegen):
	pass
	

def getDemands(srcFileName):
	ret = set()
	with open(srcFileName, "r") as fin:
		for i,line in enumerate(fin):
			if i>0:
				d = int(line.strip())
				if d >= CFR.demandBound:
					ret.add(i)
			if i>=CFR.nV:
				break
	return ret					
	
	
def calcEdge(nodeSet, srcFileName):
	desFileName = os.path.join(CFR.desFilePath, srcFileName)
	nV = len(nodeSet)
	nE = 0
	with open(srcFileName, "r") as fin:
		for i,line in enumerate(fin):
			if i>CFR.nV:
				itemList = line.split(' ')
				u, v = map(int, itemList[:2])
				if u in nodeSet and v in nodeSet:
					nE += 1
	print nV, nE
	
	
def gao():
	cmdLine = "rm -rf %s" % (CFR.desFilePath)
	commands.getoutput(cmdLine)
	if not os.path.exists(CFR.desFilePath):
		os.mkdir(CFR.desFilePath)
	nV = 78560
	nodeSet = getDemands("demands.txt")
	calcEdge(nodeSet, "./bigData/roadNetwork.txt")
	

if __name__ == "__main__":
	gao()
	