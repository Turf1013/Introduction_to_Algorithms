#!/usr/bin/python

import os
import sys
import random
import numpy as np
import bisect

from zyx_dist import sample

def sampleOne(low=1, high=100, distId=0):
    ret = sample(1, low, high, distId=0)[0]
    return ret

def weightToFile(filePath, distId=0, n = 1000, m = 1000):
    fileName = os.path.join(filePath, "weight.txt")
    with open(fileName, "w") as fout:
        for i in xrange(n):
            W = sample(m, 1, 10, distId)
            fout.write(" ".join(map(str, W)) + "\n")
