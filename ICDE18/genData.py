#!/usr/bin/env python

import numpy as np
from random import randint
import sys
import os

class constForDataSet:
    locRng = [0, 3]

class CFDS(constForDataSet):
    pass

class baseGenerator:

    def gen(self, n):
        pass

class randomGenerator(baseGenerator):

    def __init__(self, mx):
        self.mx = mx

    def gen(self, n):
        ret = np.random.random_integers(0, mx, n)
        return ret

class normalGenerator(baseGenerator):

    def __init__(self, mu, sigma):
        self.mu = mu
        self.sigma = sigma

    def gen(self, n, lb = None, rb = None):
        ret = np.random.normal(self.mu, self.sigma, n)
        for i in xrange(n):
            if lb is not None and ret[i]<lb:
                ret[i] = lb
            if rb is not None and ret[i]>rb:
                ret[i] = rb
        return ret


class uniformGenerator(baseGenerator):

    def __init__(self, low, high):
        self.low = low
        self.high = high

    def gen(self, n, lb = None, rb = None):
        ret = np.random.uniform(self.low, self.high, n)
        for i in xrange(n):
            if lb is not None and ret[i]<lb:
                ret[i] = lb
            if rb is not None and ret[i]>rb:
                ret[i] = rb
	    return ret

class locGenerator(baseGenerator):

    def __init__(self, low, high):
        self.low = low
        self.high = high

    def gen(self, n, permitLayer = True):
        if permitLayer==False and (self.high - self.low + 1) ** 2 < n:
            raise ValueError("Not enough poi in 2D places")
        locSet = set()
        ret = []
        for i in xrange(n):
            while True:
                x = randint(self.low, self.high)
                y = randint(self.low, self.high)
                loc = (x, y)
                if permitLayer or loc not in locSet:
                    break
            locSet.add(loc)
            ret.append(loc)
        return ret


def genData(desFile, taskN, workerN, K, epsilon, grt):
    locGrt = locGenerator(CFDS.locRng[0], CFDS.locRng[1])
    taskLoc = locGrt.gen(taskN, False)
    workerLoc = locGrt.gen(workerN, True)
    workerAcc = grt.gen(workerN)
    with open(desFile, "w") as fout:
        line = "%s %s\n" % (K, epsilon)
        fout.write(line)
        line = "%s\n" % (taskN)
        fout.write(line)
        for i in xrange(taskN):
            line = "%s %s\n" % (taskLoc[i][0], taskLoc[i][1])
            fout.write(line)
        line = "%s\n" % (workerN)
        fout.write(line)
        for i in xrange(workerN):
            line = "%s %s %.2f\n" % (workerLoc[i][0], workerLoc[i][1], workerAcc[i])
            fout.write(line)


def genDataBatch(desFilePath, n, taskN, workerN, K, epsilon, grt):
    for i in xrange(n):
        desFileName = "data_%03d.txt" % (i)
        desFileName = os.path.join(desFilePath, desFileName)
        genData(desFileName, taskN, workerN, K, epsilon, grt)


def genDataSet(desFilePath):
    taskN = 6
    K = 2
    workerN = 25
    epsilon = 0.32
    grt = uniformGenerator(0.84, 0.96)
    genDataBatch(desFilePath, 10, taskN, workerN, K, epsilon, grt)


if __name__ == "__main__":
    desFilePath = "/home/turf/Code/Introduction_to_Algorithms/ICDE18/dataSet"
    genDataSet(desFilePath)
