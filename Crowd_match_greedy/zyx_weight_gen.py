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

def weightToFile(filePath, distId=0, n = 1000, m = 1000, high=10):
    fileName = os.path.join(filePath, "weight.txt")
    # print "begin weight"
    with open(fileName, "w") as fout:
    	weightList = sample(n*m, 1, high, distId)
        for i in xrange(n):
            weightRow = weightList[i*m:i*m+m]
            fout.write(" ".join(map(str, weightRow)) + "\n")
    # print "end weight"