#!/usr/bin/env python
import os
import sys
import commands

class constForRegen:
	desFilePath = "./testData"
	demandBound = 30
	nV = 78560
	
class CFR(constForRegen):
	pass
	

def regenDemands(srcFileName):
	ret = set()
	desFileName = os.path.join(CFR.desFilePath, srcFileName)
	with open(desFileName, "w") as fout:
		nV = 0
		with open(srcFileName, "r") as fin:
			for i,line in enumerate(fin):
				if i>0:
					d = int(line.strip())
					if d >= CFR.demandBound:
						nV += 1
				if i>=CFR.nV:
					break
		with open(srcFileName, "r") as fin:
			for i,line in enumerate(fin):
				if i==0:
					fout.write("%d\n" % (nV))
				else:
					d = int(line.strip())
					if d >= CFR.demandBound:
						ret.add(i-1)
						fout.write("%d\n" % (d))
				if i>=CFR.nV:
					break
	return ret					
	
	
def regenGraph(nodeSet, srcFileName):
	desFileName = os.path.join(CFR.desFilePath, srcFileName)
	nV = len(nodeSet)
	with open(desFileName, "w") as fout:
		with open(srcFileName, "r") as fin:
			for i,line in enumerate(fin):
				if i==0:
					fout.write("%d %d\n" % (nV, nV*(nV-1)))
				else:
					vid = i - 1
					if vid in nodeSet:
						fout.write("%s\n" % (line.strip()))
				if i>=CFR.nV:
					break
					
def regenDegrees(nodeSet, srcFileName):
	desFileName = os.path.join(CFR.desFilePath, srcFileName)
	nV = len(nodeSet)
	with open(desFileName, "w") as fout:
		with open(srcFileName, "r") as fin:
			for i,line in enumerate(fin):
				if i==0:
					fout.write("%d\n" % (nV))
				else:
					vid = i - 1
					if vid in nodeSet:
						fout.write("%s\n" % (line.strip()))
				if i>=CFR.nV:
					break			

def regenPrices(nodeSet, srcFileName):
	regenDegrees(nodeSet, srcFileName)
					
def regenEdges(nodeSet, srcFileName):
	desFileName = os.path.join(CFR.desFilePath, srcFileName)
	nV = len(nodeSet)
	nodeList = sorted(list(nodeSet))
	# print nodeList
	itemList = [0.0] * nV
	with open(desFileName, "w") as fout:
		with open(srcFileName, "r") as fin:
			for i,line in enumerate(fin):
				if i==0:
					fout.write("%d\n" % (nV))
				else:
					uid = i - 1
					if uid in nodeSet:
						tmpList = line.strip().split(' ')
						for j,vid in enumerate(nodeList):
							itemList[j] = tmpList[vid]
							# if uid==vid:
								# print itemList[j]	
						line = " ".join(itemList)
						fout.write("%s\n" % (line))
				if i>=CFR.nV:
					break
	
def regenChargers(srcFileName):
	cmdLine = "cp %s %s" % (srcFileName, CFR.desFilePath)
	commands.getoutput(cmdLine)
	
	
def gao():
	cmdLine = "rm -rf %s" % (CFR.desFilePath)
	commands.getoutput(cmdLine)
	if not os.path.exists(CFR.desFilePath):
		os.mkdir(CFR.desFilePath)
	nV = 78560
	nodeSet = regenDemands("demands.txt")
	regenGraph(nodeSet, "roadNetwork.txt")
	regenEdges(nodeSet, "shortEdges.txt")
	regenDegrees(nodeSet, "ruralDegrees.txt")
	regenPrices(nodeSet, "prices.txt")
	regenChargers("chargers.txt")

if __name__ == "__main__":
	gao()
	