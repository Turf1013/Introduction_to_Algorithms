#!/usr/bin/env python

import numpy as np
from random import randint
import sys
import os

class constForDataSet:
	locRng = [0, 5000]

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


def genData(desFileName, taskN, binN, threshGrt, reliaGrt, ic, ir):
	print desFileName
	with open(desFileName, "w") as fout:
		fout.write("%s\n" % (taskN))
		tmpList = threshGrt.gen(taskN, 0.7, 0.999)
	#	tmpList = [0.97] * taskN
		for thresh in tmpList:
			fout.write("%.3f " % (thresh))
		fout.write("\n")
		fout.write("%s\n" % (binN))
		reliaList = list(reliaGrt.gen(binN, 0.55, 0.999))
		reliaList.sort(reverse=True)
		for i in xrange(binN):
			relia = reliaList[i]
			if i == 0:
				cost = ic
				curUc = ic
			else:
				p = reliaList[i] / reliaList[i-1]
				curUc = preUc * (100 - randint(1, 10)) / 100
			preUc = curUc
			cost = curUc * (i+1)
			fout.write("%s %.3f %.3f\n" % (i+1, cost, relia))


def genDataN(desFilePath, dataSetN, taskN, binN, threshGrt, reliaGrt, ic, ir):
	for dataSetId in xrange(dataSetN):
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(desFilePath, desFileName)
		genData(desFileName, taskN, binN, threshGrt, reliaGrt, ic, ir)


def exp1():
	desFilePath = "./dataSet/"
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	threshGrt = normalGenerator(0.85, 0.03)
	reliaGrt = normalGenerator(0.8, 0.10)
	ir,ic = 0.9, 0.2
	dataSetN = 10
	for i in xrange(dataSetN):
		desFileName = "data_%03d.txt" % (i)
		desFileName = os.path.join(desFilePath, desFileName)
		taskN = randint(800, 1000)
		binN = randint(20, 30)
		genData(desFileName, taskN, binN, threshGrt, reliaGrt, ic, ir)


def exp2(dataSetN = 20):
	desFilePath = "../dataSet/"
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	threshGrt = normalGenerator(0.9, 0.01)
	reliaGrt = normalGenerator(0.8, 0.10)
	ir,ic = 0.9, 0.2

	# varying of binN
	taskN = 10 ** 3
	binList = [1,2,5,10,20,30,40,50]
	for binN in binList:
		tmpFilePath = "varying_binN_%02d" % (binN)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		genDataN(tmpFilePath, dataSetN, taskN, binN, threshGrt, reliaGrt, ic, ir)

	# varying of binN
	binList = [1,2,5,10,20,30,40,50]
	threshGrt = uniformGenerator(0.9, 0.9)
	for binN in binList:
		tmpFilePath = "evarying_binN_%02d" % (binN)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		genDataN(tmpFilePath, dataSetN, taskN, binN, threshGrt, reliaGrt, ic, ir)


	# varying of distribution of threshold(uniform)
	binN = 20
	meanList = [0.97, 0.95, 0.92, 0.9, 0.87]
	for mean in meanList:
		tmpFilePath = "varying_umean_%s" % (mean)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		low = 2*mean - 0.99
		high = 0.99
		threshGrt = uniformGenerator(low, high)
		genDataN(tmpFilePath, dataSetN, taskN, binN, threshGrt, reliaGrt, ic, ir)

	# varying of distribution of threshold(heavy tailed)
	binN = 20
	meanList = [0.97, 0.95, 0.92, 0.9, 0.87]
	for mean in meanList:
		tmpFilePath = "varying_emean_%s" % (mean)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		threshGrt = expGenerator(mean)
		genDataN(tmpFilePath, dataSetN, taskN, binN, threshGrt, reliaGrt, ic, ir)


if __name__ == "__main__":
	#exp1()
	exp2(30)
