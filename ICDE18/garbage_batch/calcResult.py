import os
import sys


def calc(srcFilePath):
	dirNames = os.listdir(srcFilePath)
	aDict = dict()
	for dirName in dirNames:
		execName = dirName
		faFilePath = os.path.join(srcFilePath, dirName)
		tmpNames = os.listdir(faFilePath)
		for tmpName in tmpNames:
			filePath = os.path.join(faFilePath, tmpName)
			fileNames = os.listdir(filePath)
			avgList = [0., 0., 0.]
			c = 0
			for fileName in fileNames:
				fileName = os.path.join(filePath, fileName)
				with open(fileName, "r") as fin:
					line = fin.readlines()[0]
					L = line.split(' ')[1:]
					for i in xrange(3):
						avgList[i] += float(L[i])
					c += 1
			for i in xrange(3):
				avgList[i] /= c
			if tmpName not in aDict:
				aDict[tmpName] = []
			aDict[tmpName].append([execName] + avgList)
	with open("F:/tmp.txt", "w") as fout:
		for arrName,infoList in aDict.iteritems():
			fout.write("%s\n" % (arrName))
			for info in infoList:
				fout.write("%s\n" % (info))
				
				

if __name__ == "__main__":
	srcFilePath = "F:/result/"
	calc(srcFilePath)