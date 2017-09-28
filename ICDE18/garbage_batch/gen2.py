#!/usr/bin/env python

import numpy as np
from random import randint
import sys
import os

class constForDataSet:
    locRng = [0, 5000]

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

    def setMu(self, mu):
        self.mu = mu

    def setSigma(self, sigma):
        self.sigma = sigma


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

    def setLow(self, low):
        self.low = low

    def setHigh(self, high):
        self.high = high

class locGenerator(baseGenerator):

    def __init__(self, low, high):
        self.low = low
        self.high = high

    def setLow(self, low):
        self.low = low

    def setHigh(self, high):
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
    workerLoc = locGrt.gen(workerN, False)
    workerAcc = grt.gen(workerN)
    with open(desFile, "w") as fout:
        line = "%s %s\n" % (K, epsilon)
        fout.write(line)
        line = "%s\n" % (taskN)
        fout.write(line)
        for i in xrange(taskN):
            line = "%s %s\n" % (taskLoc[i][0]/10.0, taskLoc[i][1]/10.0)
            fout.write(line)
        line = "%s\n" % (workerN)
        fout.write(line)
        for i in xrange(workerN):
            line = "%s %s %.2f\n" % (workerLoc[i][0]/10.0, workerLoc[i][1]/10.0, workerAcc[i])
            fout.write(line)


def genDataBatch(desFilePath, n, taskN, workerN, K, epsilon, grt):
    for i in xrange(n):
        desFileName = "data_%03d.txt" % (i)
        desFileName = os.path.join(desFilePath, desFileName)
        genData(desFileName, taskN, workerN, K, epsilon, grt)


def genDataSet(desFilePath):
    runTime = 50
    normalGrt = normalGenerator(0.0, 0.05)
    uniformGrt = uniformGenerator(0.0, 0.0)
    taskNList = [500, 1000, 2500, 5000, 10000]
    KList = [2, 4, 6, 8, 10]
    workerN = 60000
    epsilonList = [0.01, 0.05, 0.1, 0.15, 0.2]
    scal_taskNList = [10000, 20000, 30000, 40000, 50000, 100000]
    scal_workerN = 600000
    muList = [0.75, 0.80, 0.85, 0.90, 0.95]
    # for taskN in taskNList:
        # K = KList[2]
        # epsilon = epsilonList[2]
        # mu = muList[2]
        # normalGrt.setMu(mu)
        # subDesFilePath = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
        # subDesFilePath = os.path.join(desFilePath, subDesFilePath)
        # if not os.path.exists(subDesFilePath):
            # os.mkdir(subDesFilePath)
        # genDataBatch(subDesFilePath, runTime, taskN, workerN, K, epsilon, normalGrt)
    # for K in KList:
        # if K == KList[2]:
            # continue
        # taskN = taskNList[2]
        # epsilon = epsilonList[2]
        # mu = muList[2]
        # normalGrt.setMu(mu)
        # subDesFilePath = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
        # subDesFilePath = os.path.join(desFilePath, subDesFilePath)
        # if not os.path.exists(subDesFilePath):
            # os.mkdir(subDesFilePath)
        # genDataBatch(subDesFilePath, runTime, taskN, workerN, K, epsilon, normalGrt)
    # for epsilon in epsilonList:
        # if epsilon == epsilonList[2]:
            # continue
        # taskN = taskNList[2]
        # K = KList[2]
        # mu = muList[2]
        # normalGrt.setMu(mu)
        # subDesFilePath = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
        # subDesFilePath = os.path.join(desFilePath, subDesFilePath)
        # if not os.path.exists(subDesFilePath):
            # os.mkdir(subDesFilePath)
        # genDataBatch(subDesFilePath, runTime, taskN, workerN, K, epsilon, normalGrt)
    for mu in muList[:1]:
        if mu == muList[2]:
            continue
        taskN = taskNList[2]
        K = KList[2]
        epsilon = epsilonList[2]
        normalGrt.setMu(mu)
        subDesFilePath = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
        subDesFilePath = os.path.join(desFilePath, subDesFilePath)
        if not os.path.exists(subDesFilePath):
            os.mkdir(subDesFilePath)
        genDataBatch(subDesFilePath, runTime, taskN, workerN, K, epsilon, normalGrt)
    for mu in muList[:1]:
            if mu == muList[2]:
                continue
            taskN = taskNList[2]
            K = KList[2]
            epsilon = epsilonList[2]
            if mu <= 0.85:
                low = 0.7
                high = 2*mu - low
            else:
                high = 1.0
                low = 2*mu - high
            uniformGrt.setLow(low)
            uniformGrt.setHigh(high)
            subDesFilePath = "%d_%d_%.2f_%.2f_U" % (taskN, K, epsilon, mu)
            subDesFilePath = os.path.join(desFilePath, subDesFilePath)
            if not os.path.exists(subDesFilePath):
                os.mkdir(subDesFilePath)
            genDataBatch(subDesFilePath, runTime, taskN, workerN, K, epsilon, uniformGrt)
    return
    for scal_taskN in scal_taskNList:
        K = KList[2]
        epsilon = epsilonList[2]
        mu = muList[2]
        normalGrt.setMu(mu)
        subDesFilePath = "%d_%d_%.2f_%.2f_S" % (scal_taskN, K, epsilon, mu)
        subDesFilePath = os.path.join(desFilePath, subDesFilePath)
        if not os.path.exists(subDesFilePath):
            os.mkdir(subDesFilePath)
        genDataBatch(subDesFilePath, runTime, scal_taskN, scal_workerN, K, epsilon, normalGrt)

if __name__ == "__main__":
    desFilePath = "../dataSet"
    genDataSet(desFilePath)
