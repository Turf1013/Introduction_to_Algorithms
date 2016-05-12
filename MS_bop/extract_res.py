#!/usr/bin/python
import json
import sys

def extract(filename):
	with open(filename, "r") as fin:
		data = fin.read()
	data = "".join(data.split("\n"))
	L = json.loads(data)
	ret = []
	for l in L:
		if l not in ret:
			ret.append(l)
	return ret
	
	
def dump(filename, L):
	with open(filename, "w") as fout:
		for l in L:
			fout.write("%s\n" % (l))
	
if __name__ == "__main__":
	srcFilename = "F:\Qt_prj\hdoj\data.in"
	desFilename = "F:\Qt_prj\hdoj\data.out"
	if len(sys.argv)>1:
		srcFilename = sys.argv
	res = extract(srcFilename)
	dump(desFilename, res)
	