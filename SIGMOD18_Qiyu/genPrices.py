#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing
import numpy as np
from genDataSet import constForGenDataSet

class constForGenPrice(constForGenDataSet):
	pass

class CFGP(constForGenPrice):
	pass

def readNV(srcFileName):
	with open(srcFileName, "r") as fin:
		for line in fin:
			nV, nE = map(int, line.strip().split(' '))
			return nV
	return None


def genPrice(nV, desFileName, mu, sigma=CFGP.sigma):
	prices = np.random.normal(mu, sigma, nV)
	with open(desFileName, "w") as fout:
		fout.write("%d\n" % (nV))
		for i in xrange(nV):
			fout.write("%.4f\n" % (prices[i]))

			
def genAll(nV, desFilePath):		
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	for mu in CFGP.muList:
		desFileName = "prices_%d.txt" % (mu)
		desFileName = os.path.join(desFilePath, desFileName)
		genPrice(nV, desFileName, mu)
		
			
if __name__ == "__main__":
	genAll(20337, "F:/tmp_Qiyu/prices")
	
