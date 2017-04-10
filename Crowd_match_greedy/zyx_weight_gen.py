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


def weightToFile2(filePath, n=1000, m=1000, umax=100, rateList=[]):
    for rate in rateList:
        if rate <= 0.5:
            low = 0
            high = umax * rate *2
        else:
            low = umax * (2*rate - 1.0) + 1e-7
            high = umax - 1e-7
        fileName = "weight" + str(int(rate*100)) + ".txt"
        fileName = os.path.join(filePath, fileName)
        weightList = np.random.uniform(low, high, n*m)
        avg = sum(weightList)*1.0 / (n * m)
        print "myrate = %.2lf, should = %.2lf" % (avg/umax, rate)
        with open(fileName, "w") as fout:
            for i in xrange(n):
                weightRow = weightList[i*m:i*m+m]
                fout.write(" ".join(map(str, weightRow)) + "\n")


if __name__ == "__main__":
    filePath = "/home/turf/tmp/weightz"    
    workerN,taskN = 1000,1000
    umax = 100
    rateList = [0.1, 0.3, 0.5, 0.7, 0.9]
    weightToFile2(filePath=filePath, n=workerN, m=taskN, umax=umax, rateList=rateList)
