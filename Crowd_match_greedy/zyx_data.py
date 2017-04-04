#!/usr/bin/python

import os
from zyx_weight_gen import weightToFile
from zyx_data_gen import orderToFile

def genDataSet(dataSetN, filePath):
	workerN, taskN = 250, 500
	for i in xrange(dataSetN):
		dirName = os.path.join(filePath, str(i))
		if not os.path.exists(dirName):
			os.mkdir(dirName)
		weightToFile(dirName, i/10, workerN, taskN)
		orderToFile(dirName, i/10, workerN, taskN)

if __name__ == "__main__":
	genDataSet(40, "/home/turf/Code/Data2/")
