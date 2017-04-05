#!/usr/bin/python

import os
import sys
import random
import numpy as np
import bisect

# https://docs.scipy.org/doc/numpy/reference/routines.random.html

def normDist(size, low, high):
    mu = 0.5 + random.randint(0,99) / 100.0
    signma = 0.5 + random.randint(0,99) / 1000.0
    delta = high - low
    ret = np.random.normal(mu, signma, size)
    mx = max(ret)
    for i in xrange(size):
        ret[i] = ret[i] / mx
        if ret[i] < 0:
            ret[i] = low
        elif ret[i] > 1.0:
            ret[i] = high
        else:
            ret[i] = low + ret[i] * delta
    return ret


def expDist(size, low, high):
    delta = high - low
    ret = np.random.exponential(1.0, size)
    mx = max(ret)
    for i in xrange(size):
        ret[i] = ret[i] / mx
        if ret[i] < 0:
            ret[i] = low
        elif ret[i] > 1.0:
            ret[i] = high
        else:
            ret[i] = low + ret[i] * delta
    return ret


def uniDist(size, low, high): 
	ret = np.random.uniform(low, high, size)
	return ret


def logDist(size, low, high, mu, sigma):
    mu = 0.5 + random.randint(0,99) / 100.0
    signma = 0.5 + random.randint(0,99) / 1000.0
    delta = high - low
    ret = np.random.exponential(mu, sigma, size)
    mx = max(ret)
    for i in xrange(size):
        ret[i] = ret[i] / mx
        if ret[i] < 0:
            ret[i] = low
        elif ret[i] > 1.0:
            ret[i] = high
        else:
            ret[i] = low + ret[i] * delta
    return ret


def sample(size, low, high, distId):
    if distId == 0:
	    ret = normDist(size, low, high)
    elif distId == 1:
        ret = expDist(size, low, high)
    elif distId == 2:
	    ret = uniDist(size, low, high)
    else:
        ret = logDist(size, low, high)
    return ret
