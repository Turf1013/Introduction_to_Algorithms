#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing
import numpy as np

global cntDict
cntDict = dict()

class constForGenPrice:
    mu, sigma = 10**4, 200

class CFGP(constForGenPrice):
    pass

def readNV(srcFileName):
    with open(srcFileName, "r") as fin:
        for line in fin:
            nV, nE = map(int, line.strip().split(' '))
            return nV
    return None


def genPrice(nV, desFileName):
    prices = np.random.normal(CFGD.mu, CFGD.sigma, nV)
    with open(desFileName, "w") as fout:
        fout.write("%d\n" % (nV))
        for i in xrange(nV):
            fout.write("%.4f\n" % (prices[i]))

def exp0():
    desFileName = "estatePrice.txt"
    nV = readNV("roadnetwork.txt")
    print nV
    genPrice(nV, desFileName)

if __name__ == "__main__":
    exp0()
