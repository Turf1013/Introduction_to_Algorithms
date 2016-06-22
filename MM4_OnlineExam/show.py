#!/usr/bin/python
import os


def extract(filename):
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	with open(filename, "r") as fin:
		# skip first line
		lines = fin.readlines()[1:]
		ret = []
		for line in lines:
			line = line.strip()
			if line:
				L = line.split()
				ret.append( L[-1] )
		return ret

		
def getVid(s):
	return int( s[s.rindex('v')+1:-4] )
	
		
		
def show(vid, ncase=99):
	if isinstance(vid, int):
		filename = "result_v%d.out" % (vid)
	else:
		filename = vid
	resList = map(int, extract(filename))
	score = sum(resList)
	vid = getVid(filename)
	print "%d: tot = %d, avg = %.3lf" % (vid, score, score*1.0/ncase)
	
		
	
def showAll(filepath="./"):
	nameList = filter(lambda s:s.endswith(".out"), os.listdir())
	for name in nameList:
		filename = os.path.join(filepath, name)
		show(name)
		

if __name__ == "__main__":
	show(0)
