#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing
import numpy as np

global cntDict
cntDict = dict()

class constForGenPrice:
	mu, sigma = 1600000, 100000

class CFGP(constForGenPrice):
	pass

def readNV(srcFileName):
	with open(srcFileName, "r") as fin:
		for line in fin:
			nV, nE = map(int, line.strip().split(' '))
			return nV
	return None


def genPrice(nV, desFileName):
	prices = np.random.normal(CFGP.mu, CFGP.sigma, nV)
	with open(desFileName, "w") as fout:
		fout.write("%d\n" % (nV))
		for i in xrange(nV):
			fout.write("%.4f\n" % (prices[i]))

if __name__ == "__main__":
	desFileName = "F:/prices_1600000.txt"
	genPrice(20337, desFileName)
