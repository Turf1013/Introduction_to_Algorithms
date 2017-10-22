#!/usr/bin/env python

def printMinMax():
    with open("Shanghai_roadnetwork.txt", "r") as fin:
        lines = fin.readlines()
        nV, nE = map(int, lines[0].strip().split(' '))[:2]
        X, Y = [0.0]*nV,[0.0]*nV
        for i in xrange(1, nV+1):
            line = lines[i]
            x,y = map(float, line.split(' '))[:2]
            X[i-1] = x
            Y[i-1] = y
        print min(X), max(X)
        print min(Y), max(Y)


if __name__ == "__main__":
    printMinMax()
