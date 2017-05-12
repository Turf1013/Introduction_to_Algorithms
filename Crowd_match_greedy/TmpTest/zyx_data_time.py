#!/usr/bin/env python

import os
import multiprocessing

from zyx_data_gen_time import orderToFile3



def genCaseFast(dirName, distId, workerN, taskN, degRate, umax, orderN, timeLen):
	#print "begin genCaseFast"		
	#weightToFile(dirName, n=workerN, m=taskN, umax=umax)
	orderToFile3(dirName, workerN, taskN, degRate, cap=1, umax=umax, orderN=orderN, timeLen=timeLen)
	#print "end genCaseFast"

# distId:
#	0: norm
def genDataSetFast(distId, filePath):
	orderN, caseN = 1, 1
	numRateList = [1.0]
	numCountList = [1000]
	degRateList = [0.005, 0.01, 0.02, 0.04, 0.08, 0.10, 0.20, 0.30, 0.50]
	timeLenList = [1, 2, 3, 4, 5]
	umaxList = [100, 150]

	# directory name: $workerN_$taskN_$degRate_$umax
	pool = multiprocessing.Pool(processes = 8)
	for taskN in numCountList:
		for workerRate in numRateList:
			workerN = int(taskN * workerRate)
			for degRate in degRateList:
				umax = umaxList[0]
				for tlen in timeLenList[:1]:
					dirName = "%d_%d_%d_%d" % (workerN, taskN, (int)(degRate*1000), tlen)
					dirName = os.path.join(filePath, dirName)
					if not os.path.exists(dirName):
						os.mkdir(dirName)
					caseFileName = dirName
					pool.apply_async(genCaseFast, (caseFileName, distId, workerN, taskN, degRate, umax, orderN, tlen, ))
	pool.close()
	pool.join()

	
	srcPath = filePath
	for taskN in numCountList:
		for workerRate in numRateList:
			workerN = int(taskN * workerRate)
			for umax in umaxList:
				# make another dataset directory
				desPath = srcPath[:srcPath.rindex('/')]
				desPath = os.path.join(desPath, "dataz_%d" % (umax))
				if not os.path.exists(desPath):
					os.mkdir(desPath)

				for degRate in degRateList:
					# make destination directory
					for tlen in timeLenList:
						dirName = "%d_%d_%d_%d" % (workerN, taskN, (int)(degRate*1000), tlen)
						dirName = os.path.join(desPath, dirName)
						if not os.path.exists(dirName):
							os.mkdir(dirName)
					
					srcDirName = "%d_%d_%d_%d" % (workerN, taskN, (int)(degRate*1000), timeLenList[0])
					srcDirName = os.path.join(srcPath, srcDirName)
					for orderId in xrange(orderN):
						srcFileName = "order%d.txt" % (orderId)
						srcFileName = os.path.join(srcDirName, srcFileName)
						srcLines = []
						with open(srcFileName, "r") as fin:
							srcLines = fin.readlines()
						srcInfoLine = srcLines[0].strip()
						srcInfoList = srcInfoLine.split(' ')
						for tlen in timeLenList:
							desDirName = "%d_%d_%d_%d" % (workerN, taskN, (int)(degRate*1000), tlen)
							desDirName = os.path.join(desPath, desDirName)
							if not os.path.exists(dirName):
								os.mkdir(dirName)
							desFileName = "order%d.txt" % (orderId)
							desFileName = os.path.join(desDirName, desFileName)
							desInfoList = srcInfoList[:2] + [str(umax), str(tlen)]
							desInfoLine = " ".join(desInfoList) + "\n"
							desLines = [desInfoLine] + srcLines[1:]
							with open(desFileName, "w") as fout:
								fout.writelines(desLines)


if __name__ == "__main__":
	# filePrefix = "/home/sever/zyx/SmallData/data"
	filePrefix = "/home/turf/tmp/dataz"
	for i in xrange(1):
		#filePath = filePrefix + str(i)
		filePath = filePrefix
		if not os.path.exists(filePath):
			os.mkdir(filePath)
		genDataSetFast(i, filePath)
