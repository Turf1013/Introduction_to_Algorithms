#!/usr/bin/env python
import os
import sys
from random import randint, shuffle
import numpy as np

global P
P = 0

def genL(posList, u, v):
	ux, uy = posList[u]
	vx, vy = posList[v]
	l2 = (ux-vx)**2 + (uy-vy)**2
	l = l2 ** 0.5
	x = randint(0, P)
	if x >= P:
		return int(l)
	g = np.random.normal(0.0, 1.0, 1)
	l = l * 1.1 ** g
	return int(l)
		


def dumpDataSet(fileName):
	N = randint(10, 1000)
	pos = []
	st = set()
	for i in xrange(N):
		while True:
			x = randint(0, 700)
			y = randint(0, 700)
			p = (x, y)
			if p not in st:
				break
		st.add(p)
		pos.append(p)

	mnE = min(N-1, N*min(10, (N-1)/4))
	mxE = max(N-1, N*min(10, (N-1)/4))
	E = randint(mnE, mxE)
	ust = [0] * N
	ust[0] = randint(0, N-1)
	vst = range(N)
	vst.remove(ust[0])
	shuffle(vst)
	uc, vc = 1, N-1
	st.clear()
	for i in xrange(N):
		st.add((i, i))
	lines = []
	line = "%d\n%d\n" % (N, E*3)
	lines.append(line)
	for i in xrange(E):
		if vc > 0:
			uidx = randint(0, uc-1)
			vidx = randint(0, vc-1)
			u = ust[uidx]
			v = vst[vidx]
			ust[uc] = v
			vst[vidx] = vst[vc-1]
			uc += 1
			vc -= 1
			l = genL(pos, u, v);
			st.add((u, v))
			st.add((v, u))
		else:
			while True:
				u = randint(0, N-1)
				v = randint(0, N-1)
				p = (u, v)
				if p not in st:
					break
			st.add(p)
			l = genL(pos, u, v);
		line = "%d %d %d\n" % (u, v, l)
		lines.append(line)
	with open(fileName, "w") as fout:
		for line in lines:
			fout.write(line)
	trueName = fileName[:fileName.rindex('.')] + ".out"
	with open(trueName, "w") as fout:
		fout.write("%d\n" % (N))
		for i in xrange(N):
			x,y = pos[i]
			fout.write("%d %d\n" % (x, y))

def dataGen(dataSetN, filePath):
	for dataSetId in xrange(dataSetN):
		fileName = "data%d.in" % (dataSetId)
		fileName = os.path.join(filePath, fileName)
		P = randint(1, 10)
		dumpDataSet(fileName)


if __name__ == "__main__":
	testCase = 10
	srcFilePath = "/home/turf/Code/Introduction_to_Algorithms/MM6_DrawGraph/SmallTestCase"
	dataGen(testCase, srcFilePath)

