#!/usr/bin/python

import os
import commands

def runExtGreedy(farFilePath, execName = ".Ext", dataSetN=10, orderN=10):
	lines = []
	for dataSetId in xrange(dataSetN):
		filePath = os.path.join(farFilePath, str(dataSetId))
		for orderId in xrange(orderN):
			fileName = os.path.join(filePath, "order"+str(orderId)+".txt")
			cmdLine = "%s %s" % (execName, fileName)
			# print cmdLine
			line = commands.getoutput(cmdLine)
			# print line
			lines.append(line)
	return lines


def dumpToFile(fileName, lines):
	with open(fileName, "w") as fout:
		fout.write("\n".join(lines))


if __name__ == "__main__":
	lines = runExtGreedy("/home/turf/Code/Data/", "/home/turf/Code/Introduction_to_Algorithms/Crowd_match_greedy/Ext")
	dumpToFile("Ext_clk.log", lines)