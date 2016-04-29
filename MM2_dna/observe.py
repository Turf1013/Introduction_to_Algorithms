#!/usr/bin/python
import sys


def getChrId(line):
	return line.split(',')[1]


def observe_pairChrId(diff):
	if diff==0:
		filename = "./example/small5.minisam"
	elif diff==1:
		filename = "./example/medium5.minisam"
	else:
		filename = "./example/large5.minisam"
	with open(filename, "r") as fin:
		lines = fin.readlines()
	npair = len(lines)>>1
	neq = 0
	for i in xrange(npair):
		idx1 = getChrId(lines[i*2])
		idx2 = getChrId(lines[i*2+1])
		if idx1 != idx2:
			neq += 1
	print "tot = %d, neq = %d\n" % (npair, neq)


if __name__ == "__main__":
	testDifficulty = 0
	if len(sys.argv) > 1:
		testDifficulty = max(0, int(sys.argv[1]))
	observe_pairChrId(testDifficulty)
