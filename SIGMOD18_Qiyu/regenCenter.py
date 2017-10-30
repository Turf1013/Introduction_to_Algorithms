#!/usr/bin/env python
import utm

def regenCenter(srcFileName, desFileName):
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	n = len(lines)
	with open(desFileName, "w") as fout:
		fout.write("%d\n" % (n))
		for line in lines:
			x, y = map(float, line.split(' '))[:2]
			xPos, yPos = utm.from_latlon(x, y)[:2]
			fout.write("%.6f %.6f\n" % (xPos, yPos))
	
	
def exp0():
	srcFileName = "./center.txt"
	desFileName = "./centers.txt"
	regenCenter(srcFileName, desFileName)
	
	
if __name__ == "__main__":
	exp0()
	