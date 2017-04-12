#!/usr/bin/env python

import os
import multiprocessing
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


def genCaseFast(dirName, distId, workerN, taskN, degRate, umax, orderN):
	#print "begin genCaseFast"		
	weightToFile(dirName, distId, workerN, taskN, umax)
	orderToFile2(dirName, distId, workerN, taskN, degRate, cap=1, umax=umax, orderN=orderN)
	#print "end genCaseFast"

# distId:
#	0: norm
def genDataSetFast(distId, filePath):
	orderN, caseN = 40, 1
	numRateList = [1.0]
	numCountList = [1000, 5000]
	degRateList = [0.001, 0.002, 0.004, 0.006, 0.008, 0.01, 0.02, 0.04, 0.08, 0.10]
	umaxList = [100]

	# directory name: $workerN_$taskN_$degRate_$umax
	pool = multiprocessing.Pool(processes = 8)
	for taskN in numCountList:
		for workerRate in numRateList:
			workerN = int(taskN * workerRate)
			for degRate in degRateList:
				for umax in umaxList:
					dirName = "%d_%d_%d_%d" % (workerN, taskN, (int)(degRate*1000), umax)
					dirName = os.path.join(filePath, dirName)
					if not os.path.exists(dirName):
						os.mkdir(dirName)
					for caseId in xrange(caseN):
						caseFileName = dirName
						pool.apply_async(genCaseFast, (caseFileName, distId, workerN, taskN, degRate, umax, orderN, ))
	pool.close()
	pool.join()


if __name__ == "__main__":
	# filePrefix = "/home/sever/zyx/SmallData/data"
	filePrefix = "/home/turf/tmp/dataz"
	for i in xrange(1):
		#filePath = filePrefix + str(i)
		filePath = filePrefix
		if not os.path.exists(filePath):
			os.mkdir(filePath)
		genDataSetFast(i, filePath)
