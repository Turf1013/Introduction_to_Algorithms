#!/usr/bin/python

import os
from zyx_weight_gen import weightToFile
from zyx_data_gen import orderToFile, orderToFile2

def genDataSet(dataSetN, filePath):
	workerN, taskN = 100, 100
	for i in xrange(dataSetN):
		dirName = os.path.join(filePath, str(i))
		if not os.path.exists(dirName):
			os.mkdir(dirName)
		degRate = (i%10 + 1) * 0.1
		weightToFile(dirName, i/10, workerN, taskN)
		orderToFile2(dirName, i/10, workerN, taskN, degRate)

if __name__ == "__main__":
	genDataSet(40, "/home/turf/tmp/data0/")
