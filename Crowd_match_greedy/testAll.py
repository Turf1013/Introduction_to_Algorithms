#!/usr/bin/python

import os
from test import runExtGreedy, dumpToFile 

def testAll(dataSetN):
	execNameList = [
		"Ext", "ExtMem",
		"Greedy", "GreedyMem",
		"Filter", "FilterMem",
		#"TGOA", "TGOAMem"
	]
	testN, orderN = 40, 100
	for execName in execNameList:
		for i in xrange(dataSetN):
			farFilePath = "/home/server/zyx/Data" + str(i)
			execPath = os.path.join("/home/server/zyx/Introduction_to_Algorithms/Crowd_match_greedy", execName)
			if execName.endswith("Mem"):
				name = execName[:execName.rindex("Mem")]
				logFileName = "%s_mem_%d.log" % (name, i)
			else:
				name = execName
				logFileName = "%s_clk_%d.log" % (name, i)
			lines = runExtGreedy(farFilePath, execPath, testN, orderN)
			dumpToFile(logFileName, lines)


if __name__ == "__main__":
	testAll(5)
