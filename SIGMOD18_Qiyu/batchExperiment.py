#!/usr/bin/env python
import os
import sys
import commands
import multiprocessing
from genDataSet import genDesFileName

class constForBatchExperiment:
    dataSetN = 5
    nprocess = 4

class CFBE(constForBatchExperiment):
    pass


def run(execName, srcFileName, desFileName):
    cmdLine = "./%s %s %s" % (execName, srcFileName, desFileName)
    print cmdLine
    line = commands.getoutput(cmdLine)
    print line
    with open(desFileName, "w") as fout:
        fout.write(line)


def batchWithPool(execNames, dataSetN, nprocess, srcFilePath, desFilePath):
    if not os.path.exists(desFilePath):
        os.mkdir(desFilePath)

    pool = multiprocessing.Pool(processes = nprocess)
    dataNames = sorted(os.listdir(srcFilePath))

    for execName in execNames:
        tmpFilePath = os.path.join(desFilePath, execName)
        if not os.path.exists(tmpFilePath):
            os.mkdir(tmpFilePath)
        for dataName in dataNames:
            tmpFilePath = os.path.join(desFilePath, execName, dataName)
            if not os.path.exists(tmpFilePath):
                os.mkdir(tmpFilePath)

    for dataSetId in xrange(dataSetN):
        fileName = genDesFileName(dataSetId)
        for dataName in dataNames:
            for execName in execNames:
                srcFileName = os.path.join(srcFilePath, dataName, fileName)
                desFileName = os.path.join(desFilePath, execName, dataName, fileName)
                if os.path.exists(desFileName):
                    continue
                pool.apply_sync(run, (execName, srcFileName, desFileName, ))

	pool.close()
	pool.join()


def exp0():
    dataSetN, nprocess = CFBE.dataSetN, CFBE.nprocess
    execNames = ["bao"]
    srcFilePath = "../dataSet_Qiyu"
    desFilePath = "../result_Qiyu"
    cmdLine = "rm -rf %s" % (desFilePath)
    commands.getouptut(cmdLine)
    batchWithPool(execNames, dataSetN, nprocess, srcFilePath, desFilePath)

if __name__ == "__main__":
    exp0()
