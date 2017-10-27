#!/usr/bin/env python
import os
import sys
import commands
import multiprocessing

class constForGenDataSet:
    lambdaList  = [0.0, 0.1, 0.2, 0.3, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    alphaList   = [0.0, 0.1, 0.2, 0.3, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
    rmaxList    = [500, 1000, 1500, 2000, 3000]
    bList       = [x*10**5 for x in [1.0, 2.0, 3.0, 4.0, 5.0]]
    kList       = [x*10 for x in [1, 2, 3, 4, 5]]
    defaultValue = [
        lambdaList[len(lambdaList)/2],
        alphaList[len(alphaList)/2],
        rmaxList[len(rmaxList)/2],
        bList[len(bList)/2],
        kList[len(kList)/2],
    ]

class CFGD(constForGenDataSet):
    pass


def genData(desFileName, lambda_, alpha, rmax, B, K):
    with open(desFileName, "w") as fout:
        line = "%.03f %.03f %.0f %.0f %d\n" % (lambda_, alpha, rmax, B, K)
        fout.write(line)


def genDataName(lambda_, alpha, rmax, B, K):
    ret = "%.03f_%.03f_%.0f_%.0f_%d" % (lambda_, alpha, rmax, B, K)
    return ret

def genDesFileName(dataSetId):
    ret = "data_%02d.txt" % (dataSetId)
    return ret

def genDataSet(desFilePath, dataSetN, nprocess):
    if not os.path.exists(desFilePath):
        os.mkdir(desFilePath)

    pool = multiprocessing.Pool(processes = nprocess)

    for dataSetId in xrange(dataSetN):
        # varying of lambda
        lambda_,alpha,rmax,B,K = CFGD.defaultValue
        for lambda_ in CFGD.lambdaList:
            dataName = genDataName(lambda_, alpha, rmax, B, K)
            dataFilePath = os.path.join(desFilePath, dataName)
            if not os.path.exists(dataFilePath):
                os.mkdir(dataFilePath)
            desFileName = genDesFileName(dataSetId)
            desFileName = os.path.join(dataFilePath, desFileName)
            if os.path.exists(desFileName):
                continue
            pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

        # varying of alpha
        lambda_,alpha,rmax,B,K = CFGD.defaultValue
        for alpha in CFGD.alphaList:
            dataName = genDataName(lambda_, alpha, rmax, B, K)
            dataFilePath = os.path.join(desFilePath, dataName)
            if not os.path.exists(dataFilePath):
                os.mkdir(dataFilePath)
            desFileName = genDesFileName(dataSetId)
            desFileName = os.path.join(dataFilePath, desFileName)
            if os.path.exists(desFileName):
                continue
            pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

        # varying of rmax
        lambda_,alpha,rmax,B,K = CFGD.defaultValue
        for rmax in CFGD.rmaxList:
            dataName = genDataName(lambda_, alpha, rmax, B, K)
            dataFilePath = os.path.join(desFilePath, dataName)
            if not os.path.exists(dataFilePath):
                os.mkdir(dataFilePath)
            desFileName = genDesFileName(dataSetId)
            desFileName = os.path.join(dataFilePath, desFileName)
            if os.path.exists(desFileName):
                continue
            pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

        # varying of B
        lambda_,alpha,rmax,B,K = CFGD.defaultValue
        for B in CFGD.bList:
            dataName = genDataName(lambda_, alpha, rmax, B, K)
            dataFilePath = os.path.join(desFilePath, dataName)
            if not os.path.exists(dataFilePath):
                os.mkdir(dataFilePath)
            desFileName = genDesFileName(dataSetId)
            desFileName = os.path.join(dataFilePath, desFileName)
            if os.path.exists(desFileName):
                continue
            pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

        # varying of K
        lambda_,alpha,rmax,B,K = CFGD.defaultValue
        for K in CFGD.kList:
            dataName = genDataName(lambda_, alpha, rmax, B, K)
            dataFilePath = os.path.join(desFilePath, dataName)
            if not os.path.exists(dataFilePath):
                os.mkdir(dataFilePath)
            desFileName = genDesFileName(dataSetId)
            desFileName = os.path.join(dataFilePath, desFileName)
            if os.path.exists(desFileName):
                continue
            pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

    pool.close()
    pool.join()

def exp0(dataSetN=4, nprocess=4):
    desFilePath = "../dataSet_Qiyu"
    cmdLine = "rm -rf %s" % (desFilePath)
    commands.getoutput(cmdLine)
    genDataSet(desFilePath, dataSetN, nprocess)


if __name__ == "__main__":
    exp0()
