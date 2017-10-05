import os
import sys


def calc(srcFilePath):
	dirNames = os.listdir(srcFilePath)
	dirNames = filter(lambda x:not x.endswith(".gz"), dirNames)
	aDict = dict()
	for dirName in dirNames:
		execName = dirName
		faFilePath = os.path.join(srcFilePath, dirName)
		tmpNames = os.listdir(faFilePath)
		print tmpNames
		for tmpName in tmpNames:
			filePath = os.path.join(faFilePath, tmpName)
			fileNames = os.listdir(filePath)
			avgList = [0., 0., 0.]
			c = 0
			for fileName in fileNames:
				try:
					dataSetId = int(fileName[5:-4])
				except:
					continue
				fileName = os.path.join(filePath, fileName)
				with open(fileName, "r") as fin:
					line = fin.readlines()[0]
					L = line.split(' ')[1:]
					if "data" in L[0]:
						continue
					if float(L[0]) >= 1073741825:
						continue
					for i in xrange(3):
						avgList[i] += float(L[i])
					c += 1
			for i in xrange(3):
				if c>0:
					avgList[i] /= c
				else:
					avgList[i] = 0
			if tmpName not in aDict:
				aDict[tmpName] = []
			aDict[tmpName].append([execName] + avgList)
	with open("F:/tmp.txt", "w") as fout:
		for arrName,infoList in aDict.iteritems():
			fout.write("%s\n" % (arrName))
			for info in infoList:
				fout.write("%s\n" % (info))
	return aDict			

def gao(d):
	ret = ""
	for i in xrange(len(d)):
		if i == 0:
			ret += "%.3f" % (d[i])
		else:
			ret += ", %.3f" % (d[i])
	ret = "[%s]" % (ret)
	return ret
	
	
def findResult(d, arr):
	algoNames = ["RRKM", "SSPAFM", "LAFM", "AAMM"]
	tmpDict = dict()
	if arr not in d:
		for algoName in algoNames:
			tmpDict[algoName] = [0.0] * 3
		return tmpDict
	infoList = d[arr]
	for tmpList in infoList:
		tmpDict[tmpList[0]] = tmpList[1:]			
	for algoName in algoNames:
		if algoName not in tmpDict:
			tmpDict[algoName] = [0.0] * 3
	return tmpDict
	
	
def turnToLine(d, id):	
	algoNames = ["RRKM", "SSPAFM", "LAFM", "AAMM"]
	aDict = dict()
	bDict = dict()
	cDict = dict()
	algoNames = list(set(algoNames) & set(d.keys()))
	for algoName in algoNames:
		resList,timeList,memList = [],[],[]
		tmpList = d[algoName]
		for l in tmpList:
			resList.append(float(l[0]))
			timeList.append(float(l[1]))
			memList.append(float(l[2]))
		aDict[algoName] = resList
		bDict[algoName] = timeList
		cDict[algoName] = memList
	ret = ""
	for algoName in algoNames:
		if algoName == "SSPAFM":
			tmpName = "MCFM"
		else:
			tmpName = algoName
		tmpName = "%s" % (tmpName[:-1].lower())
		ret += "%s%d = %s;\n" % (tmpName, id, gao(aDict[algoName]))
	for algoName in algoNames:
		if algoName == "SSPAFM":
			tmpName = "MCFM"
		else:
			tmpName = algoName
		tmpName = "%s" % (tmpName[:-1].lower())
		ret += "%s%d = %s;\n" % (tmpName, id+1, gao(bDict[algoName]))
	for algoName in algoNames:
		if algoName == "SSPAFM":
			tmpName = "MCFM"
		else:
			tmpName = algoName
		tmpName = "%s" % (tmpName[:-1].lower())
		ret += "%s%d = %s;\n" % (tmpName, id+2, gao(cDict[algoName]))
	# ret += "\n"
	return ret
	
def updateResDict(aDict, arrName):
	filePath = "F:/result/real"
	tmpList = os.listdir(filePath)
	for algoName in tmpList:
		if algoName not in aDict:
			aDict[algoName] = []
		realPath = os.path.join(filePath, algoName)
		fileNames = os.listdir(realPath)
		fileNames = filter(lambda x:x.startswith(arrName), fileNames)
		avgList = [0] * 3
		c = 0
		for fileName in fileNames:
			fileName = os.path.join(realPath, fileName)
			with open(fileName, "r") as fin:
				line = fin.readlines()[0]
			tmpList = line.split()
			if len(tmpList) < 4:
				continue
			if float(tmpList[1]) > 573703:
				continue
			avgList[0] += float(tmpList[1])
			avgList[1] += float(tmpList[2])
			avgList[2] += float(tmpList[3])
			c += 1
		if c==0:
			c = 1
		for i in xrange(3):
			avgList[i] /= c
		aDict[algoName].append(avgList)	
		
			
def getResult(aDict):
	taskNList = [500, 1000, 2500, 5000, 10000]
	KList = [2, 4, 6, 8, 10]
	workerN = 60000
	epsilonList = [0.01, 0.05, 0.1, 0.15, 0.2]
	scal_taskNList = [10000, 20000, 30000, 40000, 50000, 100000]
	scal_workerN = 600000
	muList = [0.75, 0.80, 0.85, 0.90, 0.95]
	line = ""
	
	resDict = dict()
	idx = 1
	for taskN in taskNList:
		K = KList[2]
		epsilon = epsilonList[2]
		mu = muList[2]
		arrName = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
		tmpDict = findResult(aDict, arrName)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 3
	resDict = dict()
	
	for K in KList:
		taskN = taskNList[2]
		epsilon = epsilonList[2]
		mu = muList[2]
		arrName = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
		tmpDict = findResult(aDict, arrName)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 3
	resDict = dict()	
	
	for epsilon in epsilonList:
		taskN = taskNList[2]
		K = KList[2]
		mu = muList[2]
		arrName = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
		tmpDict = findResult(aDict, arrName)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 3
	resDict = dict()
	
	for mu in muList:
		taskN = taskNList[2]
		K = KList[2]
		epsilon = epsilonList[2]
		arrName = "%d_%d_%.2f_%.2f_N" % (taskN, K, epsilon, mu)
		tmpDict = findResult(aDict, arrName)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 3
	resDict = dict()
	
	for mu in muList:
		taskN = taskNList[2]
		K = KList[2]
		epsilon = epsilonList[2]
		arrName = "%d_%d_%.2f_%.2f_U" % (taskN, K, epsilon, mu)
		tmpDict = findResult(aDict, arrName)
		# print tmpDict, arrName
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 3
	resDict = dict()
	
	for scal_taskN in scal_taskNList:
		K = KList[2]
		epsilon = epsilonList[2]
		mu = muList[2]
		arrName = "%d_%d_%.2f_%.2f_S" % (scal_taskN, K, epsilon, mu)
		tmpDict = findResult(aDict, arrName)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 3
	resDict = dict()
	
	for place in ["NYC", "TKY"]:
		resDict = dict()
		for p in [0.12, 0.14, 0.16, 0.18, 0.2]:
			arrName = "%s_%s" % (place, p)
			updateResDict(resDict, arrName)
		line += turnToLine(resDict, idx)
		idx += 3	
		resDict = dict()
	
	with open("F:/tmp2.txt", "w") as fout:
		fout.writelines(line)

if __name__ == "__main__":
	srcFilePath = "F:/result/"
	aDict = calc(srcFilePath)
	getResult(aDict)
	