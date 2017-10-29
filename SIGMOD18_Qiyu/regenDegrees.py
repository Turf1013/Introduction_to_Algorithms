#!/usr/bin/env python

def gao(srcFileName, desFileName):
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	nV = int(lines[0].strip())
	lines = filter(lambda x:len(x.strip())>0, lines[1:])
	values = map(lambda s:float(s.strip()), lines)
	mx = max(values)
	mn = min(values)
	fm = mx + min(mn, 10)
	with open(desFileName, "w") as fout:
		fout.write("%d\n" % (nV))
		for line in lines:
			x = float(line.strip())
			x /= fm
			fout.write("%.4f\n" % (x))
			

if __name__ == "__main__":
	srcFileName = "./ruralDegree.txt"
	desFileName = "./ruralDegrees.txt"
	gao(srcFileName, desFileName)
	