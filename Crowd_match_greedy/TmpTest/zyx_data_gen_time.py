#!/usr/bin/python

import os
import sys
import random
import numpy as np
import bisect
import math
from zyx_dist import sample

from zyx_weight_gen import weightToFile, weightToFile2
						   
def sampleOne(distId=0, low=1, high=100):
	ret = sample(1, low, high, distId)[0]
	return ret

def Distance(workerLoc, taskLoc):
	ret = (workerLoc[0] - taskLoc[0])**2 + (workerLoc[1] - taskLoc[1])**2
	return ret ** 0.5

def Distance2(workerLoc, taskLoc):
	ret = (workerLoc[0] - taskLoc[0])**2 + (workerLoc[1] - taskLoc[1])**2
	return ret

def norm(tot,n,mu,sigma):
    i=0
    while i<tot:
        sample=np.random.normal(mu, sigma)
        if sample>=0 and sample<n:
            return sample
            i+=1
    return sample
	
def orderToFile2(filePath, distId=0, workerN=1000, taskN=1000, degRate=0.5, cap=1, umax=10, orderN=1):
	# print "begin orderToFile2"
	# handle degree
	if degRate == 1.0:
		degList = [taskN] * workerN
	else:
		degList = np.random.normal(degRate*taskN, 1.0, workerN)
	
	xList = random.sample(xrange(10**4), workerN)
	yList = random.sample(xrange(10**4), workerN)
	workerLocList = []
	for i in xrange(workerN):
		x = xList[i]
		y = yList[i]
		workerLocList.append([x, y])

	xList = random.sample(xrange(10**4), taskN)
	yList = random.sample(xrange(10**4), taskN)
	taskLocList = []
	for i in xrange(taskN):
		x = xList[i]
		y = yList[i]
		taskLocList.append([x, y])

	# print len(workerLocList), len(degList), len(taskLocList)

	workerRadList = [0.0] * workerN
	for workerId in xrange(workerN):
		distList = [0.0] * taskN
		degNum = min(taskN, int(degList[workerId]))
		degNum = max(0, degNum)
		degList[workerId] = degNum
		for taskId in xrange(taskN):
			distList[taskId] = Distance2(workerLocList[workerId], taskLocList[taskId])
		distList.sort()
		# print degNum
		if degNum == 0:
			workerRadList[workerId] = 0.0
		else:
			workerRadList[workerId] = distList[degNum-1] ** 0.5 + 1e-6	
	random.shuffle(taskLocList)	
	sumDeg = sum(degList)

	# print degList

	# handle time stamp
	wn, rn = workerN, taskN
	timeList=[]
	for i in range((wn+rn)/20*8):
		timeList.append(int(norm(1,288,96,24)))
	for i in range((wn+rn)/20*8):
		timeList.append(int(norm(1,288,204,24)))
	for i in range((wn+rn)/5):
		timeList.append(int(random.uniform(0,288)))
	#timeList = sample(workerN+taskN, 1, 1000, distId)
	timeList.sort()
	#print timeList

	# handle others
	obj=[]
	for workerId in xrange(workerN):
		x, y = workerLocList[workerId]
		r = workerRadList[workerId]
		d = 4
		ratio = 1
		nob = ['w',workerId,x,y,r,cap,d,ratio]
		obj.append(nob)

	for taskId in xrange(taskN):
		x, y = taskLocList[taskId]
		d = 4
		pay = 1
		nob = ['t',taskId,x,y,d,pay]
		obj.append(nob)

	s="order"
	for i in xrange(orderN):
		fs=s+str(i)+".txt"
		fileName = os.path.join(filePath, fs)
		with open(fileName, "w") as fp:
			fp.write('%d %d %d %d\n'%(workerN, taskN, umax, sumDeg))
			random.shuffle(obj)
			for j in range(workerN + taskN):
				nob=obj[j]
				if nob[0]=='w':
					fp.write('%d w %d %f %f %f %d %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5],nob[6],nob[7]))
				else:
					fp.write('%d t %d %f %f %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5]))
	# print "end orderToFile2"

def orderToFile3(filePath, workerN=1000, taskN=1000, degRate=0.5, cap=1, umax=10, orderN=1, timeLen=5):
	if degRate == 1.0:
		degList = [taskN] * workerN
	else:
		degList = np.random.normal(degRate*taskN, 1.0, workerN)
	
	xList = random.sample(xrange(10**4), workerN)
	yList = random.sample(xrange(10**4), workerN)
	workerLocList = []
	for i in xrange(workerN):
		x = xList[i]
		y = yList[i]
		workerLocList.append([x, y])

	xList = random.sample(xrange(10**4), taskN)
	yList = random.sample(xrange(10**4), taskN)
	taskLocList = []
	for i in xrange(taskN):
		x = xList[i]
		y = yList[i]
		taskLocList.append([x, y])

	workerRadList = [0.0] * workerN
	for workerId in xrange(workerN):
		distList = [0.0] * taskN
		degNum = min(taskN, int(degList[workerId]))
		degNum = max(0, degNum)
		degList[workerId] = degNum
		for taskId in xrange(taskN):
			distList[taskId] = Distance2(workerLocList[workerId], taskLocList[taskId])
		distList.sort()
		# print degNum
		if degNum == 0:
			workerRadList[workerId] = 0.0
		else:
			workerRadList[workerId] = distList[degNum-1] ** 0.5 + 1e-6	
	random.shuffle(taskLocList)	
	sumDeg = sum(degList)

	# handle time stamp
	wn, rn = workerN, taskN
	timeList=[]
	for i in range((wn+rn)/20*8):
		timeList.append(int(norm(1,288,96,24)))
	for i in range((wn+rn)/20*8):
		timeList.append(int(norm(1,288,204,24)))
	for i in range((wn+rn)/5):
		timeList.append(int(random.uniform(0,288)))
	timeList.sort()

	# handle others
	obj=[]
	for workerId in xrange(workerN):
		x, y = workerLocList[workerId]
		r = workerRadList[workerId]
		d = timeLen
		ratio = 1
		nob = ['w',workerId,x,y,r,cap,d,ratio]
		obj.append(nob)

	for taskId in xrange(taskN):
		x, y = taskLocList[taskId]
		d = timeLen
		pay = 1
		nob = ['t',taskId,x,y,d,pay]
		obj.append(nob)

	s="order"
	for i in xrange(orderN):
		fs=s+str(i)+".txt"
		fileName = os.path.join(filePath, fs)
		with open(fileName, "w") as fp:
			fp.write('%d %d %d %d\n'%(workerN, taskN, umax, timeLen))
			random.shuffle(obj)
			for j in range(workerN + taskN):
				nob=obj[j]
				if nob[0]=='w':
					fp.write('%d w %d %f %f %f %d %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5],nob[6],nob[7]))
				else:
					fp.write('%d t %d %f %f %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5]))


if __name__ == "__main__":
	filePath = "/home/turf/tmp/data"
	workerN, taskN = 100, 100
	timeLen, umax = 5, 100
	weightRateList = [0.5]
	weightToFile2(filePath, n=workerN, m=taskN, umax=umax, rateList=weightRateList) 
	orderToFile3(filePath, workerN=workerN, taskN=taskN, degRate=0.5, umax=umax, orderN=1, timeLen=timeLen)
	#for i in xrange(8):
		#filePath = os.path.join("/home/turf/tmp/dataz", str(i))
		#if not os.path.exists(filePath):
		#	os.mkdir(filePath)
		#taskN = 50
		#workerN = taskN - 3 * i
		# print "file %d" % (i)
		#weightToFile(filePath, distId=i%4, n=workerN, m=taskN, high=10*(i+1)) 
		#orderToFile2(filePath, distId=i%4, workerN=workerN, taskN=taskN, degRate=0.1*(i+1), cap=1, umax=10*(i+1), orderN=20)
	# orderToFile2("/home/turf/tmp/data1", distId=0, workerN=100, taskN=100, degRate=0.5, cap=1, umax=10)
	# orderToFile2("/home/turf/tmp/data2", distId=0, workerN=100, taskN=100, degRate=0.75, cap=1, umax=10)
	# orderToFile2("/home/turf/tmp/data3", distId=0, workerN=100, taskN=100, degRate=1.0, cap=1, umax=10)
