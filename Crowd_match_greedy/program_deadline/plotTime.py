#!/usr/bin/env python
import matplotlib.pyplot as plt

def plot(aDict):
	X = aDict.keys()
	X.sort()
	Y = []
	for x in X:
		y = aDict[x]
		Y.append(y)
	plt.title("time distribute")
	plt.plot(X, Y, "ro-", linewidth=2.5)
	plt.ylabel("count")
	plt.xlabel("time")
	plt.xlim(0, 288)
	mnY = min(Y)
	mxY = max(Y)
	plt.ylim(0, mxY+10)
	plt.grid(True)
	plt.show()
	plt.close()		


def dumpTime(filePath):
	lines = []
	with open(filePath, "r") as fin:
		lines = fin.readlines()
	ret = map(lambda x:int(x.strip()), lines)
	return ret


def calcDict(lst):
	ret = dict()
	for x in lst:
		if x not in ret:
			ret[x] = 1
		ret[x] += 1
	return ret	


if __name__ == "__main__":
	filePath = "/home/turf/Code/Code_today/data.in"
	timeList = dumpTime(filePath)
	timeDict = calcDict(timeList)
	plot(timeDict)

