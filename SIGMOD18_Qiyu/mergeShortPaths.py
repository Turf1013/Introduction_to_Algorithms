#!/usr/bin/env python
import sys
import os
import commands

class constForMergeSP:
	srcFileName = "./Shanghai_roadnetwork.txt"
	desFileName = "./shortEdges.txt"
	
class CFMS(constForMergeSP):
	pass

def readNV(srcFileName):
	with open(srcFileName, "r") as fin:
		for line in fin:
			nV, nE = map(int, line.strip().split(' '))
			return nV
	return None

def merge(srcFilePath, desFileName, nV):
	fileNames = sorted(os.listdir(srcFilePath))
	tmpSet = set(fileNames)
	if len(fileNames) != nV:
		print "miss %d files" % (nV - len(fileNames))
		return 
	with open(desFileName, "w") as fout:
		for vid in xrange(1, nV+1):
			fileName = "%05d.txt" % (vid)
			if fileName not in tmpSet:
				print "miss %s" % (fileName)
				return 
			srcFileName = os.path.join(srcFilePath, fileName)
			with open(srcFileName, "r") as fin:
				line = fin.readlines()[0]
			line = line.strip() + "\n"
			fout.write(line)
	
	
if __name__ == "__main__":
	srcFilePath = "../shortPaths"
	desFileName = CFMS.desFileName
	nV = readNV(CFMS.srcFileName)
	merge(srcFilePath, desFileName, nV)
	