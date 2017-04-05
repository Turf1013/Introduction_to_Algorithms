#!/usr/bin/python

import sys
import os
import commands
import multiprocessing

from test import runExtGreedy, dumpToFile

def testFunc(farFilePath, execPath, dataSetN, orderN, logFileName):
    # print "begin testFunc"
    lines = runExtGreedy(farFilePath, execPath, dataSetN, orderN)
    dumpToFile(logFileName, lines)
    # print "end testFunc"


def testPool(distId):
    execNameList = [
        #"Ext", 
        #"ExtMem",
        #"Greedy", 
        #"GreedyMem",
        #"Filter", 
        #"FilterMem",
        #"TGOA", 
        #"TGOAMem",
        #"OPT",
        "OPTMem",
    ]
    orderN, caseN = 1, 20
    numRateList = [0.25, 0.5, 1.0]
    numCountList = [100, 200, 400, 1000]
    degRateList = [0.25, 0.5, 0.75, 1.0]
    umaxList = [10, 100, 1000, 100000]

    #farFilePrefix = "/home/turf/tmp/data" + str(distId)
    farFilePrefix = "/home/server/zyx/BigData/data" + str(distId)

    # directory name: $workerN_$taskN_$degRate_$umax
    for execName in execNameList:
        #execPath = os.path.join("/home/turf/Code/Introduction_to_Algorithms/Crowd_match_greedy", execName)    
        execPath = os.path.join("/home/server/zyx/Introduction_to_Algorithms/Crowd_match_greedy", execName)
        if execName.endswith("Mem"):
            name = execName[:execName.rindex("Mem")]
            logFilePrefix = "/home/server/zyx/BigLog/%s_mem_%d" % (name, distId)
        else:
            name = execName
            logFilePrefix = "/home/server/zyx/BigLog/%s_clk_%d" % (name, distId)
        if not os.path.exists(logFilePrefix):
            os.mkdir(logFilePrefix)
        pool = multiprocessing.Pool(processes = 10)
        for taskN in numCountList:
            for workerRate in numRateList:
                workerN = int(taskN * workerRate)
                for degRate in degRateList:
                    for umax in umaxList:
                        dataSetSuffix = "%d_%d_%d_%d" % (workerN, taskN, (int)(degRate*100), umax)
                        logFileName = os.path.join(logFilePrefix, dataSetSuffix+".log")
                        farFilePath = os.path.join(farFilePrefix, dataSetSuffix)
                        pool.apply_async(testFunc, (farFilePath, execPath, caseN, orderN, logFileName, ))
        pool.close()
        pool.join()
    

if __name__ == "__main__":
    distId = 0
    if len(sys.argv) > 1:
        distId = int(sys.argv[1])
    for distId in xrange(4):
        testPool(distId)
