#!/usr/bin/python

import os
from zyx_weight_gen import weightToFile
from zyx_data_gen import orderToFile

def genDataSet(dataSetN, filePath):
	for i in xrange(dataSetN):
		dirName = os.path.join(filePath, str(i))
		if not os.path.exists(dirName):
			os.mkdir(dirName)
		weightToFile(dirName, i/2)
		orderToFile(dirName, i/2)

if __name__ == "__main__":
	genDataSet(8, "/home/turf/Code/Data2/")
