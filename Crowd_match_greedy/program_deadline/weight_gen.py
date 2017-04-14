#!/usr/bin/env python
import sys
import random
import numpy as np
import bisect

def norm(tot,n,mu,sigma):
    i=0
    while i<tot:
        sample=np.random.normal(mu, sigma)
        if sample>=0 and sample<n:
            return sample
            i+=1
    return sample
def ex(tot,n,lambd):
    i=0
    while i<tot:
        sample=np.random.exponential(lambd)
        if sample>=0 and sample<n:
            return sample
            i+=1
    return sample
#-40 20 50 80 140
#1500 38 10
umax=150
mean=0.1*umax
sigma=0.25*umax
num=1000
fp="/home/turf/weight/weight_uniform/weight"
k=[1,3,5,3,1]
for j in range(1, 10):
	s=fp+str(j*10)+".txt"
	print(s)
	fp1=open(s,"w")
	if j <= 5:
		low = 0
		high = j * 2.0 / 10.0 * umax
	else:
		low = umax * (j*2.0/10.0 - 1.0)
		high = umax
	avg = 0
	for i in range(num*num):
		x = random.uniform(low, high)
		avg += x
		fp1.write(str(x)+'\n')
	avg /= (num*num*umax)
	print "uni: avg = %.3f, should = %.3f" % (avg, j*1.0/10)
	fp1.close()
sys.exit(0)
fp="/home/turf/weight/weight_normal/weight"
for j in range(1, 10):
	s=fp+str(j*10)+".txt"
	print(s)
	avg = 0
	fp1=open(s,"w")
	for i in range(num*num):
		x = norm(1,umax,j/10.0*umax,0.25*umax)
		avg += x
		fp1.write(str(x)+'\n')
	avg /= (num*num*umax)
	print "nor: avg = %.3f, should = %.3f" % (avg, j*1.0/10)
	fp1.close()
fp="/home/turf/weight/weight_exp/weight"
for j in range(1, 10):
	s=fp+str(j*10)+".txt"
	print(s)
	avg = 0
	fp1=open(s,"w")
	for i in range(num*num):
		x = ex(1,umax,j/10.0*umax)
		avg += x
		fp1.write(str(x)+'\n')
	avg /= (num*num*umax)
	print "exp: avg = %.3f, should = %.3f" % (avg, j*1.0/10)
	fp1.close()
