#!/usr/bin/env python
import os
import sys
import commands
import multiprocessing

from genDataSet import CFGD, genDataName

class constForGenExperiment(CFGD):
    itemN = 2
    pass

class CFGE(constForGenExperiment):
    pass

def readLines(srcFileName):
    ret = []
    with open(srcFileName, "r") as fin:
        ret = fin.readlines()
    return ret

def readResult(srcFilePath):
    execNames = sorted(os.listdir(srcFilePath))
    retDict = dict()
    for execName in execNames:
        dataNames = os.listdir(os.path.join(srcFilePath, execName))
        for dataName in dataNames:
            dataFilePath = os.path.join(srcFilePath, execName, dataName)
            fileNames = sorted(os.listdir(dataFilePath))
            avgList = [0.] * itemN
            c = 0
            for fileName in fileNames:
                srcFileName = os.path.join(dataFilePath, fileName)
                line = readLines(srcFileName)[0]
                if "invalid" in line:
                    continue
                itemList = line.split(' ')[1:]
                for i in xrange(itemN):
                    avgList[i] += float(itemList[i])
                    c += 1
            for i in xrange(itemN):
                if c==0:
                    avgList[i] = 0.0
                else:
                    avgList[i] /= c
            if dataName not in retDict:
                retDict[dataName] = []
            resultList = [execName] + avgList
            retDict[dataName].append(resultList)
    return ret

def findResult(algoNames, resDict, dataName):
    retDict = dict()
    logList = resDict[dataName]
    for tmpList in logList:
        retDict[tmpList[0]] = tmpList[1:]
    for algoName in algoNames:
        if algoName not in retDict:
            print "%s has no log in [%s]" % (algoName, dataName)
            retDict[algoName] = [0.0] * CFGE.itemN
    return retDict

def turnToLine(algoNames, resDict, idx):
    ret = ""
    for i in xrang(CFGE.itemN):
        for algoName in algoNames:
            values = []
            for tmpList in resDict[algoName]:
                values.append(tmpList[i])
            matlabName = getMatName(algoName) + str(idx+i)
            ret += "%-10s = %s;\n" % (matlabName, values)
    return ret

def genExperiment(srcFilePath, desFileName):
    # \TODO
    algoNames = []
    idx = 1
    line = ""

    logDict = readResult(srcFilePath)

    # varying of lambda
    resDict = dict()
    lambda_,alpha,rmax,B,K = CFGE.defaultValue
    for lambda_ in CFGD.lambdaList:
        dataName = genDataName(lambda_, alpha, rmax, B, K)
        tmpDict = findResult(alogNames, logDict, dataName)
        for algoName, tmpList in tmpDict:
            if algoName not in resDit:
                resDict[algoName] = []
            resDict[algoName].append(tmpList)
    line += turnToLine(algoNames, resDict, idx)
    idx += itemN

    # varying of alpha
    resDict = dict()
    lambda_,alpha,rmax,B,K = CFGE.defaultValue
    for alpha in CFGD.alphaList:
        dataName = genDataName(lambda_, alpha, rmax, B, K)
        tmpDict = findResult(alogNames, logDict, dataName)
        for algoName, tmpList in tmpDict:
            if algoName not in resDit:
                resDict[algoName] = []
            resDict[algoName].append(tmpList)
    line += turnToLine(algoNames, resDict, idx)
    idx += itemN

    # varying of rmax
    resDict = dict()
    lambda_,alpha,rmax,B,K = CFGE.defaultValue
    for rmax in CFGD.rmaxList:
        dataName = genDataName(lambda_, alpha, rmax, B, K)
        tmpDict = findResult(alogNames, logDict, dataName)
        for algoName, tmpList in tmpDict:
            if algoName not in resDit:
                resDict[algoName] = []
            resDict[algoName].append(tmpList)
    line += turnToLine(algoNames, resDict, idx)
    idx += itemN

    # varying of B
    resDict = dict()
    lambda_,alpha,rmax,B,K = CFGE.defaultValue
    for B in CFGD.bList:
        dataName = genDataName(lambda_, alpha, rmax, B, K)
        tmpDict = findResult(alogNames, logDict, dataName)
        for algoName, tmpList in tmpDict:
            if algoName not in resDit:
                resDict[algoName] = []
            resDict[algoName].append(tmpList)
    line += turnToLine(algoNames, resDict, idx)
    idx += itemN

    # varying of K
    resDict = dict()
    lambda_,alpha,rmax,B,K = CFGE.defaultValue
    for K in CFGD.kList:
        dataName = genDataName(lambda_, alpha, rmax, B, K)
        tmpDict = findResult(alogNames, logDict, dataName)
        for algoName, tmpList in tmpDict:
            if algoName not in resDit:
                resDict[algoName] = []
            resDict[algoName].append(tmpList)
    line += turnToLine(algoNames, resDict, idx)
    idx += itemN

    with open(desFileName, "w") as fout:
        fout.write(line)

def exp0():
    srcFilePath = "../result_Qiyu"
    desFileNmae = "../resultLog.txt"
    genExperiment(srcFilePath, desFileNmae)

if __name__ == "__main__":
    exp0()
