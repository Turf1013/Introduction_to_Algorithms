#!/usr/bin/env python

import numpy as np
from random import randint, sample
import sys
import os

class constForDataSet:
	locRng = [0, 100]

class CFDS(constForDataSet):
	pass

class baseGenerator:

	def gen(self, n):
		pass

class randomGenerator(baseGenerator):

	def __init__(self, mx):
		self.mx = mx

	def gen(self, n):
		ret = np.random.random_integers(0, mx, n)
		return ret

class normalGenerator(baseGenerator):

	def __init__(self, mu, sigma):
		self.mu = mu
		self.sigma = sigma

	def gen(self, n, lb = None, rb = None):
		# print lb, rb
		ret = np.random.normal(self.mu, self.sigma, n)
		for i in xrange(n):
			if lb is not None and ret[i]<lb:
				ret[i] = lb
			if rb is not None and ret[i]>rb:
				ret[i] = rb
		# print ret
		return ret

	def setMu(self, mu):
		self.mu = mu

	def setSigma(self, sigma):
		self.sigma = sigma


class uniformGenerator(baseGenerator):

	def __init__(self, low, high):
		self.low = low
		self.high = high

	def gen(self, n, lb = None, rb = None):
		ret = np.random.uniform(self.low, self.high, n)
		for i in xrange(n):
			if lb is not None and ret[i]<lb:
				ret[i] = lb
			if rb is not None and ret[i]>rb:
				ret[i] = rb
		return ret

	def setLow(self, low):
		self.low = low

	def setHigh(self, high):
		self.high = high

class expGenerator(baseGenerator):

	def __init__(self, mu):
		self.mu = mu

	def gen(self, n, lb = None, rb = None):
		ret = np.random.exponential(self.mu, n)
		for i in xrange(n):
			if lb is not None and ret[i]<lb:
				ret[i] = lb
			if rb is not None and ret[i]>rb:
				ret[i] = rb
		return ret

	def setMu(self, mu):
		self.mu = mu

def genLoc(n, low, high):		
	ret = []
	st = set()
	for i in xrange(n):
		while True:
			x = randint(low, high)
			y = randint(low, high)
			t = (x, y)
			if t not in st:
				break
		ret.append(t)
		st.add(t)
	return ret
		
		
def genData(V, N, C, M, desFileName):
	with open(desFileName, "w") as fout:
		line = "%s %s %s %s\n" % (V, N, C, M)
		fout.write(line)
		points = genLoc(V, 0, 100)
		for i in xrange(V):
			line = "%s %s\n" % (points[i][0], points[i][1])
			fout.write(line)
		tids = []
		for i in xrange(M):
			tid = randint(1, 1440)
			tids.append(tid)
		tids.sort()
		for i in xrange(M):
			tid = tids[i]
			sid = randint(1, V)
			eid = randint(1, V)
			line = "%s %s %s\n" % (tid, sid, eid)
			fout.write(line)

			
def exp1(dataSetN = 5):
	desFilePath = "F:/tmp/dial"
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	V = 100
	N = 20
	C = 12
	M = 500
	for i in xrange(dataSetN):
		V = randint(50, 100)
		N = randint(10, 30)
		C = randint(5, 12)
		M = randint(300, 500)
		desFileName = "data_%02d.txt" % (i)
		desFileName = os.path.join(desFilePath, desFileName)
		genData(V, N, C, M, desFileName)
 
	
if __name__ == "__main__":
	exp1()
	