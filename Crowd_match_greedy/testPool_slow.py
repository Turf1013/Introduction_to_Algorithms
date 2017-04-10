#!/usr/bin/python

import sys
import os
import commands
import multiprocessing


def runExtGreedy(execName, weightFileName, edgeFilePath, orderN, mu):
    lines = []
    for orderId in xrange(orderN):
        edgeFileName = os.path.join(edgeFilePath, "order"+str(orderId)+".txt")
        cmdLine = "%s %s %s %s" % (execName, weightFileName, edgeFileName, str(mu))
        #print cmdLine
        line = commands.getoutput(cmdLine)
        print line
        lines.append(line)
    return lines


def dumpToFile(fileName, lines):
    with open(fileName, "w") as fout:
        fout.write("\n".join(lines))


def testFunc(execName, weightFileName, edgeFilePath, orderN, mu, logFileName):
    #print "begin testFunc"
    lines = runExtGreedy(execName, weightFileName, edgeFilePath, orderN, mu)
    dumpToFile(logFileName, lines)
    #print "end testFunc"


def testPool():
    execNameList = [
        "OPT",
        "Static",
        "Pure",
        "Ext", 
        "Greedy",
    ]
    orderN = 40
    muList = [0.1, 0.3, 0.5, 0.7, 0.9]

    farFilePrefix = "/home/server/zyx/tmp/dataz"
    weightFilePrefix = "/home/server/zyx/tmp/weightz"

    # directory name: $workerN_$taskN_$degRate_$umax
    for execName in execNameList:
        if execName=="OPT" or execName=="Static":
            orderN = 1
        else:
            orderN = 40
        execPath = os.path.join("/home/server/zyx/TmpTest", execName)    
        logFilePrefix = os.path.join("/home/server/zyx/tmp/logz", execName)
        if not os.path.exists(logFilePrefix):
            os.mkdir(logFilePrefix)
        pool = multiprocessing.Pool(processes = 6)
        nameList = os.listdir(farFilePrefix)
        for mu in muList:
            weightFileName = os.path.join(weightFilePrefix, "weight"+str(int(mu*100))+".txt")
            #print weightFileName
            for name in nameList:
                filePath = os.path.join(farFilePrefix, name)
                logFileName = "%s_%s.log" % (name, str(int(mu*100)))
                logFileName = os.path.join(logFilePrefix, logFileName)
                #print filePath
                #print logFileName
                pool.apply_async(testFunc, (execPath, weightFileName, filePath, orderN, mu, logFileName, ))
        pool.close()
        pool.join()
    

if __name__ == "__main__":
    distId = 0
    if len(sys.argv) > 1:
        distId = int(sys.argv[1])
    testPool()
