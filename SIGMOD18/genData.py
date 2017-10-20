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

	def setMx(self, mx):
		self.mx = mx

	def gen(self, n):
		ret = [0] * n
		for i in xrange(n):
			x = randint(1, self.mx)
			ret[i] = x
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
			tid = randint(1, 40)
			tids.append(tid)
		tids.sort()
		for i in xrange(M):
			tid = tids[i]
			sid = randint(1, V)
			eid = randint(1, V)
			line = "%s %s %s\n" % (tid, sid, eid)
			fout.write(line)


def genDataSet(V, N, C, M, points, tids, sids, eids, desFileName):
	print desFileName
	with open(desFileName, "w") as fout:
		line = "%s %s %s %s\n" % (V, N, C, M)
		fout.write(line)
		for i in xrange(V):
			line = "%s %s\n" % (points[i][0], points[i][1])
			fout.write(line)
		for i in xrange(M):
			tid = tids[i]
			sid = sids[i]
			eid = eids[i]
			line = "%s %s %s\n" % (tid, sid, eid)
			fout.write(line)

def genTmpFileName(N, C, M, Tmax):
	return "%02d_%02d_%04d_%03d" % (N, C, M, Tmax)


def sampleOrder(_tids, _sids, _eids, M):
	N = len(_tids)
	idxs = sample(xrange(N), M)
	idxs.sort()
	tids, sids, eids = [],[],[]
	for i in idxs:
		tids.append(_tids[i])
		sids.append(_sids[i])
		eids.append(_eids[i])
	return tids, sids, eids


def batchDataSet(desFilePath, nV = 50, dataSetId = 2):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	Mmax = 3000
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120
	rng = randomGenerator(Tmax)
	points = genLoc(V, 0, 100)
	rng.setMx(Tmax)
	bigTids = rng.gen(Mmax)
	rng.setMx(V)
	bigSids = rng.gen(Mmax)
	bigEids = rng.gen(Mmax)

	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)

	# varying of workerN
	workerNList = [10, 20, 30, 40, 50]
	tids, sids, eids = sampleOrder(bigTids, bigSids, bigEids, M)
	for N in workerNList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		genDataSet(V, N, C, M, points, tids, sids, eids, desFileName)
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120


	# varying of capacity
	capacityList = range(1, 16)
	for C in capacityList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		genDataSet(V, N, C, M, points, tids, sids, eids, desFileName)
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120


	# varying of orderN
	orderNList = [200, 500, 1000, 2000, 3000]
	for M in orderNList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		_tids, _sids, _eids = sampleOrder(bigTids, bigSids, bigEids, M)
		genDataSet(V, N, C, M, points, _tids, _sids, _eids, desFileName)
	V, N, C, M, Tmax = nV, 30, 8, 1000, 120

	# varying of denisty
	# TmaxList = [30, 60, 120, 180, 240]
	# for Tmax in TmaxList:
		# rng.setMx(Tmax)
		# _tids = rng.gen(M)
		# _tids.sort()
		# tmpFilePath = genTmpFileName(N, C, M, Tmax)
		# tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		# if not os.path.exists(tmpFilePath):
			# os.mkdir(tmpFilePath)
		# desFileName = "data_%02d.txt" % (dataSetId)
		# desFileName = os.path.join(tmpFilePath, desFileName)
		# if os.path.exists(desFileName):
			# continue
		# genDataSet(V, N, C, M, points, _tids, sids, eids, desFileName)
	# V, N, C, M, Tmax = 50, 30, 8, 1000, 120

def batchDataSet2(desFilePath, nV = 50, dataSetId = 2):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	Mmax = 500
	V, N, C, M, Tmax = nV, 1, 8, 200, 120
	rng = randomGenerator(Tmax)
	points = genLoc(V, 0, 100)
	rng.setMx(Tmax)
	bigTids = rng.gen(Mmax)
	rng.setMx(V)
	bigSids = rng.gen(Mmax)
	bigEids = rng.gen(Mmax)
	tids, sids, eids = sampleOrder(bigTids, bigSids, bigEids, M)

	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)

	# varying of capacity
	capacityList = range(1, 16)
	for C in capacityList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		genDataSet(V, N, C, M, points, tids, sids, eids, desFileName)
	V, N, C, M, Tmax = nV, 1, 8, 200, 120

	# varying of orderN
	orderNList = [50, 100, 200, 300, 500]
	for M in orderNList:
		tmpFilePath = genTmpFileName(N, C, M, Tmax)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		_tids, _sids, _eids = sampleOrder(bigTids, bigSids, bigEids, M)
		genDataSet(V, N, C, M, points, _tids, _sids, _eids, desFileName)
	V, N, C, M, Tmax = nV, 1, 8, 200, 120

	# varying of denisty
	# TmaxList = [30, 60, 120, 180, 240]
	# for Tmax in TmaxList:
		# rng.setMx(Tmax)
		# _tids = rng.gen(M)
		# _tids.sort()
		# tmpFilePath = genTmpFileName(N, C, M, Tmax)
		# tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		# if not os.path.exists(tmpFilePath):
			# os.mkdir(tmpFilePath)
		# desFileName = "data_%02d.txt" % (dataSetId)
		# desFileName = os.path.join(tmpFilePath, desFileName)
		# if os.path.exists(desFileName):
			# print "4"
			# continue
		# genDataSet(V, N, C, M, points, _tids, sids, eids, desFileName)
	# V, N, C, M, Tmax = nV, 1, 8, 200, 120

def exp1():
	desFilePath = "../dataSet_SIGMOD_0"
	desFilePath_1 = "../dataSet_SIGMOD_1"
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	if not os.path.exists(desFilePath_1):
		os.mkdir(desFilePath_1)
	dataSetN = 2
	nVs = [100, 500, 1000, 2000]
	for nV in nVs:
		tmpFileName = "nV_%d" % (nV)
		tmpFilePath = os.path.join(desFilePath, tmpFileName)
		for dataSetId in xrange(dataSetN):
		 	batchDataSet(tmpFilePath, nV, dataSetId)
		tmpFilePath = os.path.join(desFilePath_1, tmpFileName)
		for dataSetId in xrange(dataSetN):
			batchDataSet2(tmpFilePath, nV, dataSetId)


if __name__ == "__main__":
	exp1()
	# exp3()
