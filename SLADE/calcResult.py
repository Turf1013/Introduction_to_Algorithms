import os
import sys


def calc(srcFilePath):
	itemN = 2
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
			avgList = [0.] * itemN
			c = 0
			for fileName in fileNames:
				try:
					dataSetId = int(fileName[5:7])
					if dataSetId >= 10:
						continue
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
					for i in xrange(itemN):
						avgList[i] += float(L[i])
					c += 1
			for i in xrange(itemN):
				if c>0:
					avgList[i] /= c
				else:
					avgList[i] = 0
			if tmpName not in aDict:
				aDict[tmpName] = []
			# avgList.append(0.0)
			aDict[tmpName].append([execName] + avgList)
	with open("F:/tmp/tmp.txt", "w") as fout:
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
	
def getALGO(s):
	if s=='opq':
		return 'OPQ'
	elif s=='opqe':
		return 'OPQ_Extended'
	elif s=='base':
		return 'Baseline'
	elif s=='greedy':
		return 'Greedy'
	else:
		return 'None'
	
def findResult(d, arr):
	itemN = 3
	algoNames = ["base", "greedy", "opqe", "opq"]
	tmpDict = dict()
	if arr not in d:
		for algoName in algoNames:
			tmpDict[algoName] = [0.0] * itemN
		return tmpDict
	infoList = d[arr]
	for tmpList in infoList:
		tmpDict[tmpList[0]] = tmpList[1:]			
	for algoName in algoNames:
		if algoName not in tmpDict:
			tmpDict[algoName] = [0.0] * itemN
	return tmpDict
	
	
def turnToLine(d, id):	
	algoNames = ["base", "greedy", "opqe", "opq"]
	aDict = dict()
	bDict = dict()
	algoNames = list(set(algoNames) & set(d.keys()))
	for algoName in algoNames:
		resList,timeList = [],[]
		tmpList = d[algoName]
		for l in tmpList:
			resList.append(float(l[0]))
			timeList.append(float(l[1]))
		aDict[algoName] = resList
		bDict[algoName] = timeList
	ret = ""
	for algoName in algoNames:
		preName = getALGO(algoName)
		tmpName = preName + str(id)
		ret += "%-14s = %s;\n" % (tmpName, gao(aDict[algoName]))
	for algoName in algoNames:
		preName = getALGO(algoName)
		tmpName = preName + str(id+1)
		ret += "%-14s = %s;\n" % (tmpName, gao(bDict[algoName]))
	return ret
			
def getResult(aDict):
	resDict = dict()
	idx = 1
	line = ""
	taskN = 10 ** 4
	
	# varying of binN
	binList = [1,2,5,10,20,30,40,50]
	for binN in binList:
		tmpFilePath = "evarying_binN_%02d" % (binN)
		tmpDict = findResult(aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 2
	resDict = dict()
	
	# varying of binN
	binList = [1,2,5,10,20,30,40,50]
	for binN in binList:
		tmpFilePath = "varying_binN_%02d" % (binN)
		tmpDict = findResult(aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 2
	resDict = dict()
	
	# varying of distribution of threshold(uniform)
	binN = 20
	meanList = [0.87, 0.9, 0.92, 0.95, 0.97]
	for mean in meanList:
		tmpFilePath = "varying_umean_%s" % (mean)
		tmpDict = findResult(aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 2
	resDict = dict()
	
	# varying of distribution of threshold(heavy tailed)
	binN = 20
	meanList = [0.87, 0.9, 0.92, 0.95, 0.97]
	for mean in meanList:
		tmpFilePath = "varying_emean_%s" % (mean)
		tmpDict = findResult(aDict, tmpFilePath)
		for algoName,tmpList in tmpDict.iteritems():
			if algoName not in resDict:
				resDict[algoName] = []
			resDict[algoName].append(tmpList)
	line += turnToLine(resDict, idx)
	idx += 2
	resDict = dict()
	
	with open("F:/tmp/tmp2.txt", "w") as fout:
		fout.writelines(line)

		
if __name__ == "__main__":
	srcFilePath = "F:/tmp/result_SLADE/"
	aDict = calc(srcFilePath)
	getResult(aDict)
	