#!/usr/bin/env python

import numpy as np
from random import randint
import sys
import os
import commands

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

def genBins(binN, theshGrt, reliaGrt, ic, ir, lr):
	reliaList = list(reliaGrt.gen(binN, 0.65, 0.999))
	reliaList.sort(reverse=True)
	ret = []
	for i in xrange(binN):
		relia = reliaList[i]
		if i == 0:
			cost = ic
			curUc = ic
		else:
			p = reliaList[i] / reliaList[i-1]
			curUc = preUc * (1000 - randint(1, 20)) / 1000
		preUc = curUc
		cost = curUc * (i+1)
		if relia <= lr:
			relia = lr
		ret.append([cost, relia])
	return ret

def genData(desFileName, taskN, tasks, binN, bins):
	with open(desFileName, "w") as fout:
		fout.write("%s\n" % (taskN))
		for i in xrange(taskN):
			fout.write("%.3f " % (tasks[i]))
		fout.write("\n")
		fout.write("%d\n" % (binN))
		for i in xrange(binN):
			fout.write("%s %.3f %.3f\n" % (i+1, bins[i][0], bins[i][1]))

def getHomoName(binN, taskN, relia):
	return "%02d_%05d_%.02f" % (binN, taskN, relia)

def genDataSet_Homo(desFilePath, dataSetId = 0, ir=0.95, ic=0.1, lr=0.75):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	threshGrt = normalGenerator(0.9, 0.03)
	reliaGrt = normalGenerator(0.80, 0.04)
	maxBinN = 40
	bins = genBins(maxBinN, threshGrt, reliaGrt, ic, ir, lr)
	binN,relia,taskN = 20,0.9,10**4

	# varying of relia
	reliaList = [0.87, 0.9, 0.92, 0.95, 0.97]
	for relia in reliaList:
		tmpFilePath = getHomoName(binN, taskN, relia)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		tasks = [relia] * taskN
		genData(desFileName, taskN, tasks, binN, bins)
	binN,relia,taskN = 20,0.9,10**4

	# varying of binN
	binList = range(2, maxBinN+1, 2)
	for binN in binList:
		tmpFilePath = getHomoName(binN, taskN, relia)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		tasks = [relia] * taskN
		genData(desFileName, taskN, tasks, binN, bins)
	binN,relia,taskN = 20,0.9,10**4

	# varying of scalability
	taskNList = [1000, 3000, 5000, 10000, 15000, 20000, 30000, 50000, 75000, 100000]
	for taskN in taskNList:
		tmpFilePath = getHomoName(binN, taskN, relia)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		tasks = [relia] * taskN
		genData(desFileName, taskN, tasks, binN, bins)
	binN,relia,taskN = 20,0.9,10**4

def readBins(srcFilePath, dataSetId):
	tmpFilePath = getHomoName(40, 10**4, 0.9)
	dataFileName = "data_%02d.txt" % (dataSetId)
	tmpFilePath = os.path.join(srcFilePath, tmpFilePath, dataFileName)
	ret = []
	with open(tmpFilePath, "r") as fin:
		lines = fin.readlines()[3:]
		for i in xrange(40):
			line = lines[i].strip()
			tmpList = map(float, line.split(' '))[1:3]
			ret.append(tmpList)
	return ret


def genDataSet_Hete(binFilePath, desFilePath, dataSetId = 0):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	reliaGrt = normalGenerator(0.80, 0.04)
	maxBinN = 40
	bins = readBins(binFilePath, dataSetId)
	binN,relia,taskN = 20,0.9,10**4

	# varying of distribution of threshold(normal)
	muList = [0.87, 0.9, 0.92, 0.95, 0.97]
	sigma = 0.03
	for mu in muList:
		tmpFilePath = "normal_%.02f_%.02f" % (mu, sigma)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		threshGrt = normalGenerator(mu, sigma)
		tasks = threshGrt.gen(taskN, 0.80, 0.999)
		genData(desFileName, taskN, tasks, binN, bins)

	sigmaList = [0.01, 0.02, 0.03, 0.04, 0.05]
	mu = 0.92
	for sigma in sigmaList:
		tmpFilePath = "normal_%.02f_%.02f" % (mu, sigma)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		threshGrt = normalGenerator(mu, sigma)
		tasks = threshGrt.gen(taskN, 0.65, 0.999)
		genData(desFileName, taskN, tasks, binN, bins)

	# varying of distribution of threshold(uniform)
	meanList = [0.87, 0.9, 0.92, 0.95, 0.97]
	for mean in meanList:
		tmpFilePath = "uniform_%.02f" % (mean)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		low = 2*mean - 0.999
		high = 0.999
		threshGrt = uniformGenerator(low, high)
		tasks = threshGrt.gen(taskN, 0.65, 0.999)
		genData(desFileName, taskN, tasks, binN, bins)

	# varying of distribution of threshold(heavy tailed)
	meanList = [0.87, 0.9, 0.92, 0.95, 0.97]
	for mean in meanList:
		tmpFilePath = "exp_%.02f" % (mean)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		threshGrt = expGenerator(mean)
		tasks = threshGrt.gen(taskN, 0.65, 0.999)
		genData(desFileName, taskN, tasks, binN, bins)


def exp0(dataSetN, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	# generate jelly
	dataFilePath = os.path.join(desFilePath, "Jelly")
	if not os.path.exists(dataFilePath):
		os.mkdir(dataFilePath)
	ir,ic,lr = 0.95,0.1,0.75
	for dataSetId in xrange(dataSetN):
		genDataSet_Homo(dataFilePath, dataSetId, ir, ic, lr)
	# generate SMIC
	dataFilePath = os.path.join(desFilePath, "SMIC")
	if not os.path.exists(dataFilePath):
		os.mkdir(dataFilePath)
	ir,ic,lr = 0.83,0.1,0.65
	for dataSetId in xrange(dataSetN):
		genDataSet_Homo(dataFilePath, dataSetId, ir, ic, lr)


def exp1(dataSetN, desFilePath):
	binFilePath = os.path.join(desFilePath, "Jelly")
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	dataFilePath = os.path.join(desFilePath, "Heter")
	for dataSetId in xrange(dataSetN):
		genDataSet_Hete(binFilePath, dataFilePath, dataSetId)

if __name__ == "__main__":
	dataSetN = 60
	desFilePath = "../dataSet_SLADE"
	cmdLine = "rm -rf %s" % (desFilePath)
	commands.getoutput(cmdLine)
	exp0(dataSetN, desFilePath)
	exp1(dataSetN, desFilePath)
