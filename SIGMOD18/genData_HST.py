#!/usr/bin/env python

import numpy as np
from random import randint, sample
import sys
import os

def genData_HST(desFileName, V, low, high):
	with open(desFileName, "w") as fout:
		fout.write("%d\n" % (V))
		for i in xrange(V):
			x = randint(low, high)
			y = randint(low, high)
			fout.write("%d %d\n" % (x, y))
			
			
def exp1(dataSetN = 1):
	desFilePath = "F:/tmp/hst_smallDataSet"
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	for dataSetId in xrange(dataSetN):
		fileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(desFilePath, fileName)
		V = randint(6, 8)
		genData_HST(desFileName, V, 0, 100)


if __name__ == "__main__":
	exp1()