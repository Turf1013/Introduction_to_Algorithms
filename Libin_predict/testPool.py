#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing


def dumpToFile(fileName, lines):
    with open(fileName, "w") as fout:
        for line in lines:
            fout.write(line + "\n")


def runGuide(execName, predictFileName, guideFileName, logFileName):
    # print "begin runGuide"
    lines = []
    cmdLine = "%s %s %s" % (execName, predictFileName, guideFileName)
    print cmdLine
    line = commands.getoutput(cmdLine)
    print line
    lines.append(line)
    dumpToFile(logFileName, lines)
    # print "end runGuide"


def runSimple(execName, scenarioFileName, logFileName):
    # print "begin runSimple"
    lines = []
    cmdLine = "%s %s" % (execName, scenarioFileName)
    print cmdLine
    line = commands.getoutput(cmdLine)
    print line
    lines.append(line)
    dumpToFile(logFileName, lines)
    # print "end runSimple"


def runOPT(execName, scenarioFileName, logFileName):
    # print "begin OPT"
    lines = []
    cmdLine = "%s %s" % (execName, scenarioFileName)
    print cmdLine
    line = commands.getoutput(cmdLine)
    print line
    lines.append(line)
    dumpToFile(logFileName, lines)
    # print "end OPT"


def testPool_Guide():
    pool = multiprocessing.Pool(processes = 6)
    execName = "/home/server/zyx/Libin_predict/Guide"

    dataSetDirPrefix = "/home/server/zyx/Data"
    dataSetDirList = ["D_r", "w"]

    for dirName in dataSetDirList:
        dataSetDirPath = os.path.join(dataSetDirPrefix, dirName)
        dirList = os.listdir(dataSetDirPath)
        for oneSetName in dirList:
            filePrefix = os.path.join(dataSetDirPath, oneSetName)
            predictFileName = os.path.join(filePrefix, "prediction.txt")
            guideFileName = os.path.join(filePrefix, "guide.txt")
            logFileName = os.path.join(filePrefix, "result_guide.txt")
            pool.apply_async(runGuide, (execName, predictFileName, guideFileName, logFileName, ))
    pool.close()
    pool.join()


def testPool_Simple():
    pool = multiprocessing.Pool(processes = 10)
    execName = "/home/server/zyx/Libin_predict/SimpleMem"

    dataSetDirPrefix = "/home/server/zyx/Data"
    dataSetDirList = ["D_r", "w"]

    for dirName in dataSetDirList:
        dataSetDirPath = os.path.join(dataSetDirPrefix, dirName)
        dirList = os.listdir(dataSetDirPath)
        for oneSetName in dirList:
            filePrefix = os.path.join(dataSetDirPath, oneSetName)
            scenarioFileName = os.path.join(filePrefix, "rscenario.txt")
            logFileName = os.path.join(filePrefix, "result_simple.txt")
            pool.apply_async(runSimple, (execName, scenarioFileName, logFileName, ))
    pool.close()
    pool.join()
    

def testPool_OPT():
    pool = multiprocessing.Pool(processes = 10)
    execName = "/home/server/zyx/Libin_predict/HungMem"

    dataSetDirPrefix = "/home/server/zyx/Data"
    dataSetDirList = ["D_r", "w"]

    for dirName in dataSetDirList:
        dataSetDirPath = os.path.join(dataSetDirPrefix, dirName)
        dirList = os.listdir(dataSetDirPath)
        for oneSetName in dirList:
            filePrefix = os.path.join(dataSetDirPath, oneSetName)
            scenarioFileName = os.path.join(filePrefix, "rscenario.txt")
            logFileName = os.path.join(filePrefix, "result_OPT.txt")
            pool.apply_async(runSimple, (execName, scenarioFileName, logFileName, ))
    pool.close()
    pool.join()


if __name__ == "__main__":
    testPool_Simple()
    testPool_OPT()
    testPool_Guide()
