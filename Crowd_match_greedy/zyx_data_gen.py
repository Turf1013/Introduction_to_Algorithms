#!/usr/bin/python

import os
import sys
import random
import numpy as np
import bisect
import math
from zyx_dist import sample

def sampleOne(low=1, high=100, distId=0):
	ret = sample(1, low, high, distId)[0]
	return ret
	

def orderToFile(filePath, distId=0, wn=1000, rn=1000, cap=1, umax=10):
	deg=wn*cap+rn
	timeList=[0] * (wn+rn)
	for i in range(wn+rn):
		timeList[i] = int(sampleOne(distId))
	timeList.sort()
	k=0
	prev=0
	for i in range(wn+rn):
	    if timeList[i]!=prev:
	        # print k
	        k=0
	    prev=timeList[i]
	    k+=1

	obj=[]
	for i in xrange(wn):
		x=sampleOne(distId)
		y=sampleOne(distId)
		d=4
		c=1#
		r=20
		ratio=1
		nob=['w',i,x,y,r,cap,d,ratio]
		obj.append(nob)

	for i in xrange(rn):
		x=sampleOne(distId)
		y=sampleOne(distId)
		d=4
		c=1
		r=20
		pay=1
		nob=['t',i,x,y,d,pay]
		obj.append(nob)

	s="order"
	for i in range(100):
		fs=s+str(i)+".txt"
		fileName = os.path.join(filePath, fs)
		fp=open(fileName,'w')
		fp.write('%d %d %d %d\n'%(wn,rn,umax,deg))
		random.shuffle(obj)
		for j in range(wn+rn):
			nob=obj[j]
			if nob[0]=='w':
				fp.write('%d w %d %f %f %f %d %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5],nob[6],nob[7]))
			else:
				fp.write('%d t %d %f %f %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5]))
		fp.close()

def Distance(workerLoc, taskLoc):
	ret = (workerLoc[0] - taskLoc[0])**2 + (workerLoc[1] - taskLoc[1])**2
	return ret ** 0.5

def Distance2(workerLoc, taskLoc):
	ret = (workerLoc[0] - taskLoc[0])**2 + (workerLoc[1] - taskLoc[1])**2
	return ret

def orderToFile2(filePath, distId=0, workerN=1000, taskN=1000, degRate=1.0, cap=1, umax=10, orderN=100):
	# handle degree
	eps = 1e-3
	if degRate < eps:
		degRate = eps * 1.1
	if degRate > 1.0:
		degRate = 1.0
	degList = np.random.uniform(degRate-eps, degRate+eps, workerN)
	
	workerLocList = []
	for i in xrange(workerN):
		x=sampleOne(distId)
		y=sampleOne(distId)
		workerLocList.append([x, y])

	taskLocList = []
	for i in xrange(taskN):
		x=sampleOne(distId)
		y=sampleOne(distId)
		taskLocList.append([x, y])

	# print len(workerLocList), len(degList), len(taskLocList)

	workerRadList = [0.0] * workerN
	for workerId in xrange(workerN):
		distList = [0.0] * taskN
		degNum = min(taskN, int(degList[workerId] * taskN))
		degNum = max(0, degNum)
		degList[workerId] = degNum
		for taskId in xrange(taskN):
			distList[taskId] = Distance(workerLocList[workerId], taskLocList[taskId])
		distList.sort()
		# print degNum
		if degNum == 0:
			workerRadList[workerId] = 0.0
		else:
			workerRadList[workerId] = math.sqrt(distList[degNum-1]) + eps	
	random.shuffle(taskLocList)	
	sumDeg = sum(degList)

	# print degList

	# handle time stamp
	timeList=[0] * (workerN + taskN)
	for i in xrange(workerN + taskN):
		timeList[i] = int(sampleOne(distId))
	timeList.sort()
	k=0
	prev=0
	for i in xrange(workerN + taskN):
	    if timeList[i]!=prev:
	        # print k
	        k=0
	    prev=timeList[i]
	    k+=1

	# handle others
	obj=[]
	for workerId in xrange(workerN):
		x, y = workerLocList[workerId]
		r = workerRadList[workerId]
		d = 4
		ratio = 1
		nob = ['w',i,x,y,r,cap,d,ratio]
		obj.append(nob)

	for taskId in xrange(taskN):
		x, y = taskLocList[taskId]
		d = 4
		pay = 1
		nob = ['t',i,x,y,d,pay]
		obj.append(nob)

	s="order"
	for i in range(orderN):
		fs=s+str(i)+".txt"
		fileName = os.path.join(filePath, fs)
		fp=open(fileName,'w')
		fp.write('%d %d %d %d\n'%(workerN, taskN, umax, sumDeg))
		random.shuffle(obj)
		for j in range(workerN + taskN):
			nob=obj[j]
			if nob[0]=='w':
				fp.write('%d w %d %f %f %f %d %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5],nob[6],nob[7]))
			else:
				fp.write('%d t %d %f %f %d %f\n' %(timeList[j],nob[1],nob[2],nob[3],nob[4],nob[5]))
		fp.close()

if __name__ == "__main__":
	orderToFile2("/home/turf/tmp/data0", distId=0, workerN=100, taskN=100, degRate=0.25, cap=1, umax=10)
	orderToFile2("/home/turf/tmp/data1", distId=0, workerN=100, taskN=100, degRate=0.5, cap=1, umax=10)
	orderToFile2("/home/turf/tmp/data2", distId=0, workerN=100, taskN=100, degRate=0.75, cap=1, umax=10)
	orderToFile2("/home/turf/tmp/data3", distId=0, workerN=100, taskN=100, degRate=1.0, cap=1, umax=10)