#!/usr/bin/python

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
	print "begin genCaseFast"		
	weightToFile(dirName, distId, workerN, taskN, umax)
	orderToFile2(dirName, distId, workerN, taskN, degRate, cap=1, umax=umax, orderN=orderN)
	print "end genCaseFast"

# distId:
#	0: norm
def genDataSetFast(distId, filePath):
	orderN, caseN = 2, 5
	numRateList = [0.25, 0.5, 1.0]
	numCountList = [100, 200, 400]
	degRateList = [0.25, 0.5, 0.75, 1.0]
	umaxList = [10, 100, 1000]

	# directory name: $workerN_$taskN_$degRate_$umax
	pool = multiprocessing.Pool(processes = 8)
	for taskN in numCountList:
		for workerRate in numRateList:
			workerN = int(taskN * workerRate)
			for degRate in degRateList:
				for umax in umaxList:
					dirName = "%d_%d_%d_%d" % (workerN, taskN, (int)(degRate*100), umax)
					dirName = os.path.join(filePath, dirName)
					if not os.path.exists(dirName):
						os.mkdir(dirName)
					for caseId in xrange(caseN):
						caseFileName = os.path.join(dirName, str(caseId))
						if not os.path.exists(caseFileName):
							os.mkdir(caseFileName)
						pool.apply_async(genCaseFast, (caseFileName, distId, workerN, taskN, degRate, umax, orderN, ))
	pool.close()
	pool.join()


if __name__ == "__main__":
	genDataSetFast(0, "/home/turf/tmp/data0/")
