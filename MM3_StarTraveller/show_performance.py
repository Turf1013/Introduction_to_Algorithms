#!/usr/env/python
import numpy as np
import matplotlib.pyplot as plt


def getData(filename):
	with open(filename, "r") as fin:
		lines = fin.readlines()
	n = len(lines)
	ret = []
	for i in xrange(0, n, 3):
		if i+2 >= n:
			break
		line = lines[i+2].strip()
		entries = line.split(',')
		score = float(entries[0].split(' ')[-1])
		t = float(entries[1].split(' ')[-1][:-3])
		ret.append([score, t])
	return np.array(ret)
	
def showData(datas):
	styles = [
		'yo-',
		'rs-',
		'y*-',
	]
	
	n = datas[0].shape[0]
	x = np.array(range(n))
	plt.subplot(2, 1, 1)
	plt.title('Performance compare')
	plt.ylabel('score')
	plt.xlabel('case')
	for i,data in enumerate(datas):
		plt.plot(x, data[:, 0], styles[i])
	
	plt.subplot(2, 1, 2)
	plt.title('Time compare')
	plt.ylabel('time(ms)')
	plt.xlabel('case')
	for i, data in enumerate(datas):
		plt.plot(x, data[:, 1], styles[i])
	
	plt.show()
	
	
if __name__ == "__main__":
	baseData = getData("base.res")
	starData = getData("star.res")
	allData = [baseData, starData]
	print allData
	showData(allData)
	
	