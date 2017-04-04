#!/usr/bin/python

import os
import sys
import random
import numpy as np
import bisect
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
