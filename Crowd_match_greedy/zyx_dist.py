#!/usr/bin/python

import os
import sys
import random
import numpy as np
import bisect

# https://docs.scipy.org/doc/numpy/reference/routines.random.html

def normDist(tot, low, high, mu,sigma):
    ret = [0.0] * tot
    i = 0
    while i<tot:
        sample=np.random.normal(mu, sigma)
        if sample>=low and sample<=high:
            ret[i] = sample
            i+=1
    return ret

def expDist(tot, low, high, lambd):
    ret = [0.0] * tot
    i=0
    while i<tot:
        sample=np.random.exponential(lambd)
        if sample>=low and sample<=high:
            ret[i] = sample
            i+=1
    return ret


def uniDist(tot, low, high): 
	ret = np.random.uniform(low, high, tot)
	for i in xrange(tot):
		if ret[i] < low:
			ret[i] = low
		elif ret[i] > high:
			ret[i] = high
	return ret


def logDist(tot, low, high, mu, sigma):
    ret = [0.0] * tot
    i=0
    while i<tot:
        sample=np.random.lognormal(mu, sigma)
        if sample>=low and sample<=high:
            ret[i] = sample
            i+=1
    return ret


def sample(size, low, high, distId):
    if distId == 0:
	    ret = normDist(size, low, high, 50,25)
    elif distId == 1:
        ret = expDist(size, low, high, 50)
    elif distId == 2:
	    ret = uniDist(size, low, high)
    else:
        ret = logDist(size, low, high, 50, 25)
    return ret
