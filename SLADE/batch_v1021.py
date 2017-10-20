#!/usr/bin/env python

import sys
import os
import commands
import multiprocessing

def run(execName, srcFileName, desFileName):
    cmdLine = "./%s %s" % (execName, srcFileName)
    print cmdLine
    line = commands.getoutput(cmdLine)
    print line
    lines = line.split('\n')
    resLine = lines[-1]
    with open(desFileName, "w") as fout:
        fout.write("%s\n" % (resLine))

def runBatch(dataSetN, nprocess, execNames, dirNames):
    srcFilePath = "../dataSet_SLADE/"
    desFilePath = "../result_SLADE/"
    pool = multiprocessing.Pool(processes = nprocess)
    if not os.path.exists(desFilePath):
        os.mkdir(desFilePath)
    for dataSetId in xrange(dataSetN):
        for dirName in dirNames:
            tmpFilePath = os.path.join(desFilePath, dirName)
            if not os.path.exists(tmpFilePath):
                os.mkdir(tmpFilePath)
            for execName in execNames:
                tmpFilePath = os.path.join(desFilePath, dirName, execName)
                if not os.path.exists(tmpFilePath):
                    os.mkdir(tmpFilePath)
                dataFilePath = os.path.join(srcFilePath, dirName)
                dataSetNames = os.listdir(dataFilePath)
                for dataSetName in dataSetNames:
                    tmpFilePath = os.path.join(desFilePath, dirName, execName, dataSetName)
                    if not os.path.exists(tmpFilePath):
                        os.mkdir(tmpFilePath)
                    srcFileName = "data_%02d.txt" % (dataSetId)
                    desFileName = os.path.join(desFilePath, dirName, execName, dataSetName, srcFileName)
                    if os.path.exists(desFileName):
                        continue
                    srcFileName = os.path.join(srcFilePath, dirName, dataSetName, srcFileName)
                    pool.apply_async(run, (execName, srcFileName, desFileName, ))

    pool.close()
    pool.join()

def exp0(dataSetN, nprocess):
    execNames = ["greedy", "opq", "cip"]
    dirNames = ["Jelly", "SMIC"]
    runBatch(dataSetN, nprocess, execNames, dirNames)

def exp1(dataSetN, nprocess):
    execNames = ["greedy", "opqe2", "cip"]
    dirNames = ["Heter"]
    runBatch(dataSetN, nprocess, execNames, dirNames)

if __name__ == "__main__":
    dataSetN, nprocess = 30, 16
    cmdLine = "rm -rf ../result_SLADE"
    commands.getoutput(cmdLine)
    exp0(dataSetN, nprocess)
    exp1(dataSetN, nprocess)
