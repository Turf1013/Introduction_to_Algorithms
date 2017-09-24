#!/usr/bin/env python

import sys
import os
import commands

def batchRound(srcFilePath, n):
    execList = [
        "RR",
        "LAF",
        "AAM",
        "MCF",
    ]
    for i in xrange(n):
        srcFileName = "data_%03d.txt" % (i)
        srcFileName = os.path.join(srcFilePath, srcFileName)
        for execName in execList:
            cmdLine = "./%s %s data.out" % (execName, srcFileName)
            print cmdLine
            commands.getoutput(cmdLine)
            with open("data.out", "r") as fin:
                line = fin.readlines()[-1]
            print line


if __name__ == "__main__":
    srcFilePath = "./dataSet"
    batchRound(srcFilePath, 10)
