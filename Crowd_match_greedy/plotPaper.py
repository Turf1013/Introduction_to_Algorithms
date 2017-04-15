#!/usr/bin/env python

import os
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

class constForPlotPaper:
	algoNameList = [
		"Ext",
		"Greedy",
		"Pure",
		"OPT",
	]
	colorDict = {
		'Ext': 		'blue',
		'Pure': 	'black',
		'Greedy': 	'green',
		'OPT': 		'pink',
	}
	markDict = {
		'Ext': 		'o',
		'Pure': 	'*',
		'Greedy': 	'd',
		'OPT': 		's',
	}

class CFPP(constForPlotPaper):
	pass


def resultDict(filePath):
	retDict = dict()
	algoList = os.listdir(filePath)
	for algoName in algoList:
		curFilePath = os.path.join(filePath, algoName)
		retDict[algoName] = dict()
		nameList = filter(lambda x:x.endswith(".log"), os.listdir(curFilePath))
		for name in nameList:
			fileName = os.path.join(curFilePath, name)
			with open(fileName, "r") as fin:
				line = fin.readlines()[0].strip()
			info = name[:name.rindex('.')]
			retDict[algoName][info] = line
	return retDict



def mergeTime(aDict):
	algoSet = filter(lambda x:not x.endswith("Mem"), aDict.keys())
	retDict = dict()
	for algoName in algoSet:
		retDict[algoName] = dict()
		clkDict = aDict[algoName]
		memDict = aDict[algoName+"Mem"]
		for infoName in clkDict.iterkeys():
			clkLine = clkDict[infoName]
			memLine = memDict[infoName]
			tmpList = memLine.split(' ')
			tmpClk = float(clkLine.split(' ')[-1])
			# print tmpClk, float(tmpList[-2])
			tmpClk = min(tmpClk, float(tmpList[-2]))
			tmpList[-2] = str(tmpClk)
			tmpList[-1] = str(int(tmpList[-1]) / 1024)
			# print tmpList
			line = " ".join(tmpList)
			retDict[algoName][infoName] = line
	return retDict


def dumpResult(aDict, desFileName):
	with open(desFileName, "w") as fout:
		for algoName,memDict in aDict.iteritems():
			fout.write(algoName + "\n")
			for infoName,resLine in memDict.iteritems():
				line = "%s: %s\n" % (infoName, resLine)
				fout.write(line)
			fout.write("\n\n")


def mergeResult(srcFilePath, desFilePath):
	desFileName = "result.txt"
	desFileName = os.path.join(desFilePath, desFileName)
	resDict = resultDict(srcFilePath)
	resDict = mergeTime(resDict)
	dumpResult(resDict, desFileName)
	return resDict


def genLogName(taskN, workerN, cap, rad, rate, dl, pay):
	ret = "%d_%d_%d_%d_%d_%d_%d" % (workerN, taskN, cap, int(rad*10), int(rate*10), pay, dl)
	return ret


def updateDataDict(logInfo, resDict, dataDict):
	for algoName in CFPP.algoNameList:
		memDict = resDict[algoName]
		if logInfo not in memDict:
			print "miss %s %s" % (algoName, logInfo)
			return 
		resLine = memDict[logInfo]
		tmpList = map(float, resLine.split(' ')[1:])
		if algoName not in dataDict:
			dataDict[algoName] = list()
		dataDict[algoName].append(tmpList)


def plotPic(desFileName, X, yList, varName, varList, ytitle):
	# plot the curve
	if '(' in ytitle:
		title = "%s of varying %s" % (ytitle[:ytitle.index('(')], varName)
	else:
		title = "%s of varying %s" % (ytitle, varName)
	plt.title(title)
	for i,algoName in enumerate(CFPP.algoNameList):
		Y = yList[i]
		col = CFPP.colorDict[algoName]
		marker = CFPP.markDict[algoName]
		plt.plot(X, Y, color=col, linestyle='-', marker=marker, linewidth=2.5, label=algoName)
	plt.ylabel(ytitle)
	plt.xlabel(varName)
	plt.xlim(0, len(X)+3)	
	plt.xticks(range(0, len(X)+2), [""] + map(str, varList) + [""])
	plt.legend()
	plt.savefig(desFileName, dpi=200)
	plt.show()
	plt.close()


def plotPics(desFilePath, dataDict, varName, varList):
	ytitleList = [
		"Utility",
		"Time(secs)",
		"Memory(MB)",
	]
	desNameList = [
		"utility",
		"time",
		"memory",
	]
	for i in xrange(3):
		yList = []
		for algoName in CFPP.algoNameList:
			Y = []
			nY = len(dataDict[algoName])
			for j in xrange(nY):
				val = dataDict[algoName][j][i]
				Y.append(val)
			yList.append(Y)
		X = range(1, nY+1)
		desFileName = "%s_%s.png" % (desNameList[i], varName)
		desFileName = os.path.join(desFilePath, desFileName)
		ytitle = ytitleList[i]
		plotPic(desFileName, X, yList, varName, varList, ytitle)


def plotAllPic(resDict, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)

	# $workerN_$taskN_$cap_$rad_$rate_$pay_$deadline
	taskNumList = [500, 1000, 2500, 5000, 10000]
	workerNumList = [100, 200, 500, 1000, 5000]
	capNumList = [1, 2, 5, 10, 20]
	radLenList = [1.0, 1.5, 2.0, 2.5, 3.0]
	rateList = [0.1, 0.3, 0.5, 0.7, 0.9]
	dlList = [2, 4, 6, 8, 10]
	payList = [2, 5, 10, 20, 50]

	_taskN = taskNumList[2]
	_workerN = workerNumList[2]
	_cap = capNumList[2]
	_rad = radLenList[2]
	_rate = rateList[2]
	_dl = dlList[2]
	_pay = payList[2]

	# taskN is variable
	taskN, workerN, cap, rad, rate, dl, pay = _taskN, _workerN, _cap, _rad, _rate, _dl, _pay
	dataDict = dict()
	for taskN in taskNumList:
		logName = genLogName(taskN, workerN, cap, rad, rate, dl, pay)
		updateDataDict(logName, resDict, dataDict)
	plotPics(desFilePath, dataDict, "taskN", taskNumList)

	# workerN is variable
	taskN, workerN, cap, rad, rate, dl, pay = _taskN, _workerN, _cap, _rad, _rate, _dl, _pay
	dataDict = dict()
	for workerN in workerNumList:
		logName = genLogName(taskN, workerN, cap, rad, rate, dl, pay)
		updateDataDict(logName, resDict, dataDict)
	plotPics(desFilePath, dataDict, "workerN", workerNumList)

	# cap is variable
	taskN, workerN, cap, rad, rate, dl, pay = _taskN, _workerN, _cap, _rad, _rate, _dl, _pay
	dataDict = dict()
	for cap in capNumList:
		logName = genLogName(taskN, workerN, cap, rad, rate, dl, pay)
		updateDataDict(logName, resDict, dataDict)
	plotPics(desFilePath, dataDict, "workerN", workerNumList)

	# rad is variable
	taskN, workerN, cap, rad, rate, dl, pay = _taskN, _workerN, _cap, _rad, _rate, _dl, _pay
	dataDict = dict()
	for rad in radLenList:
		logName = genLogName(taskN, workerN, cap, rad, rate, dl, pay)
		updateDataDict(logName, resDict, dataDict)
	plotPics(desFilePath, dataDict, "rad", radLenList)

	# rate is variable
	taskN, workerN, cap, rad, rate, dl, pay = _taskN, _workerN, _cap, _rad, _rate, _dl, _pay
	dataDict = dict()
	for rate in rateList:
		logName = genLogName(taskN, workerN, cap, rad, rate, dl, pay)
		updateDataDict(logName, resDict, dataDict)
	plotPics(desFilePath, dataDict, "rate", rateList)

	# deadline is variable
	taskN, workerN, cap, rad, rate, dl, pay = _taskN, _workerN, _cap, _rad, _rate, _dl, _pay
	dataDict = dict()
	for dl in dlList:
		logName = genLogName(taskN, workerN, cap, rad, rate, dl, pay)
		updateDataDict(logName, resDict, dataDict)
	plotPics(desFilePath, dataDict, "deadline", dlList)

	# pay is variable
	taskN, workerN, cap, rad, rate, dl, pay = _taskN, _workerN, _cap, _rad, _rate, _dl, _pay
	dataDict = dict()
	for pay in payList:
		logName = genLogName(taskN, workerN, cap, rad, rate, dl, pay)
		updateDataDict(logName, resDict, dataDict)
	plotPics(desFilePath, dataDict, "pay", payList)


def plotAllResult(srcFilePath, desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	resDict = mergeResult(srcFilePath, desFilePath)
	plotAllPic(resDict, desFilePath)


if __name__ == "__main__":
	srcFilePath = "/home/turf/tmp/logz"
	desFilePath = "/home/turf/tmp/resultz"
	plotAllResult(srcFilePath, desFilePath)
