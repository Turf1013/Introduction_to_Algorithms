#!/usr/bin/python

import sys
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
			print line
			lines.append(line)
	return lines


def dumpToFile(fileName, lines):
	with open(fileName, "w") as fout:
		fout.write("\n".join(lines))


if __name__ == "__main__":
	farFilePath = "/home/turf/Code/Data/Data0/"
	execPath = "/home/turf/Code/Introduction_to_Algorithms/Crowd_match_greedy/Filter"
	logFileName = "Ext_clk.log"
	if len(sys.argv) >= 2:
		farFilePath = sys.argv[1]
	if len(sys.argv) >= 3:
		execPath = sys.argv[2]
	if len(sys.argv) >= 4:
		logFileName = sys.argv[3]

	lines = runExtGreedy(farFilePath, execPath, 4, 6)
	dumpToFile(logFileName, lines)
