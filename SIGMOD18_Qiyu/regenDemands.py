#!/usr/bin/env python

def gao(srcFileName, desFileName):
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	lines = filter(lambda x:len(x.strip())>0, lines);
	with open(desFileName, "w") as fout:
		nV = len(lines)
		fout.write("%d\n" % (nV))
		for line in lines:
			line = line.strip()
			id, c = line.split(' ')[:2]
			fout.write("%s\n" % (c))
			

if __name__ == "__main__":
	srcFileName = "./demand.txt"
	desFileName = "./demands.txt"
	gao(srcFileName, desFileName)
	