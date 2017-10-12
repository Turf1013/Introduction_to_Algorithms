#!/usr/bin/env python
import os
import sys
import commands
from time import sleep

def run(srcFilePath):
    execNames = ["opqe", "opqe2", "greedy"]
    dirNames = os.listdir(srcFilePath)
    dirNames.sort()
    for dirName in dirNames:
        srcFileName = os.path.join(srcFilePath, dirName, "data_00.txt")
        for execName in execNames:
            cmdLine = "./%s %s" % (execName, srcFileName)
            print cmdLine
            line = commands.getoutput(cmdLine)
            print line
        print "\n\n"
        sleep(1)

if __name__ == "__main__":
    srcFilePath = "./dataSet"
    run(srcFilePath)
