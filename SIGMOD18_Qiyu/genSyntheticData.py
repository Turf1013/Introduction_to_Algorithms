#!/usr/bin/env python
import os
import sys
from random import randint
import numpy as np

class constForGenData:
    nV = 10
    nE = nV * (nV - 1)
    mu,sigma = 140*10**4,10*10**4
	rmax = 1500
    chargers = [
        [7.3, 10],
        [16.5, 12],
        [50, 15],
        [120, 30],
    ]

class CFGD(constForGenData):
    pass


def genGraph(fileName='roadNetwork.txt'):
    nV, nE = CFGD.nV, CFGD.nE
    with open(fileName, "w") as fout:
        fout.write("%d %d\n" % (nV, nE))
        for i in xrange(nV):
            x = randint(0, 10**6) / 10000.0
            y = randint(0, 10**6) / 10000.0
            fout.write("%.4f %.4f\n" % (x, y))
        for i in xrange(1, nV+1):
            for j in xrange(1, nV+1):
                if i==j:
                    continue
                w = randint(1, 10**6) / 10000.0
                fout.write("%d %d %.4f\n" % (i, j, w))

def genShortest(fileName="shortEdges.txt"):
    with open("roadNetwork.txt", "r") as fin:
        for i,line in enumerate(fin):
            line = line.strip()
            if i==0:
                nV, nE = map(int, line.split(' '))[:2]
                g = [[10**20]*nV for i in xrange(nV)]
                for j in xrange(nV):
                    g[j][j] = 0
            elif i>=1 and i<=nV:
                continue
            elif i>=nV+1 and i<=nV+nE:
                u, v, w = line.split(' ')[:3]
                u, v = int(u)-1, int(v)-1
                g[u][v] = float(w)
            else:
                break
    for k in xrange(nV):
        for i in xrange(nV):
            for j in xrange(nV):
                g[i][j] = min(g[i][j], g[i][k]+g[k][j])
    with open(fileName, "w") as fout:
        fout.write("%d\n" % (nV))
        for i in xrange(nV):
            line = ""
            for j in xrange(nV):
                line += "%.4f " % (g[i][j])
            line += "\n"
            fout.write(line)

def genDemand(fileName="demands.txt"):
    nV = CFGD.nV
    with open(fileName, "w") as fout:
        fout.write("%d\n" % (nV))
        for i in xrange(nV):
            x = randint(0, 10**4)
            fout.write("%d\n" % (x))

def genDegree(fileName="ruralDegrees.txt"):
    nV = CFGD.nV
    with open(fileName, "w") as fout:
        fout.write("%d\n" % (nV))
        for i in xrange(nV):
            x = randint(1, 10**3) / 600.0
            fout.write("%.4f\n" % (x))

def genPrice(fileName="estatePrice.txt"):
    nV = CFGD.nV
    prices = np.random.normal(CFGD.mu, CFGD.sigma, nV)
    with open(fileName, "w") as fout:
        fout.write("%d\n" % (nV))
        for i in xrange(nV):
            x = prices[i]
            fout.write("%.4f\n" % (x))

def genCharger(fileName="chargers.txt"):
    with open(fileName, "w") as fout:
        chargerN =  len(CFGD.chargers)
        fout.write("%d\n" % (chargerN))
        for item in CFGD.chargers:
            power,price = item[:2]
            fout.write("%.02f %d\n" % (1.0/power, price))

def genPara(fileName="data.in"):
    nV = CFGD.nV
    lambda_ = randint(0, 1000) / 1000.0
    alpha = randint(0, 1000) / 1000.0
    rmax = randint(50, 100) * 1.001
    K = randint(4, 20)
    B = randint(300, 800) / 1000.0 * nV * (K * 15.0 + CFGD.mu)
    with open(fileName, "w") as fout:
        fout.write("%.4f %.4f %.4f %.4f %d\n" % (lambda_, alpha, rmax, B, K))

def exp0():
    genGraph()
    genShortest()
    genDemand()
    genDegree()
    genPrice()
    genCharger()
    genPara()

if __name__ == "__main__":
    exp0()
