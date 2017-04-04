#!/usr/bin/python

import os
import sys
import random
import numpy as np
import bisect

# https://docs.scipy.org/doc/numpy/reference/routines.random.html

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

def weightToFile(filePath, n = 1000, m = 1000):
    fileName = os.path.join(filePath, "weight.txt")
    with open(fileName, "w") as fout:
        for i in xrange(n):
            W = [0.0] * m
            for j in xrange(m):
                W[j] = norm(1, 10, 5, 2.5)
            fout.write(" ".join(map(str, W)) + "\n")
