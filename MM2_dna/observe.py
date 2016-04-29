#!/usr/bin/python
import sys


def getChrId(line):
	return line.split(',')[1]

def getChrPos(line):
	return map(int, line.split(',')[2:4])


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


def observe_pairDis(diff):
	if diff==0:
		filename = "./example/small5.minisam"
	elif diff==1:
		filename = "./example/medium5.minisam"
	else:
		filename = "./example/large5.minisam"
	mxdis = -1
	overlap = 0
	nline = 0
	with open(filename, "r") as fin:
		while True:
			try:
				l1 = fin.readline()
				l2 = fin.readline()
				nline += 2
			except:
				break
			l1 = l1.strip()
			l2 = l2.strip()
			if not l1 or not l2:
				break
			st1, ed1 = getChrPos(l1)
			st2, ed2 = getChrPos(l2)
			if ed1 < st2:
				mxdis = max(mxdis, st2-ed1-1)
			elif ed2 < st1:
				mxdis = max(mxdis, st1-ed2-1)
			else:
				overlap += 1
	print nline
	print "mxdis = %d, overlap = %d\n" % (mxdis, overlap)


if __name__ == "__main__":
	testDifficulty = 0
	if len(sys.argv) > 1:
		testDifficulty = max(0, int(sys.argv[1]))
	# observe_pairChrId(testDifficulty)
	observe_pairDis(testDifficulty)
