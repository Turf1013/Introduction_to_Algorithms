#!/usr/bin/env python

def gao(srcFileName, desFileName):
	nV = 78560
	with open(desFileName, "w") as fout:
		fout.write("%d\n" % (nV))
		with open(srcFileName, "r") as fin:
			for line in fin:
				line = line.strip() + "\n"
				fout.write(line)
			

if __name__ == "__main__":
	srcFileName = "./shortEdge.txt"
	desFileName = "./shortEdges.txt"
	gao(srcFileName, desFileName)
	