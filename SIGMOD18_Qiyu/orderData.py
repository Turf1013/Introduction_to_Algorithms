#!/usr/bin/env python
import datetime
import os
import sys
import commands
import multiprocessing
import utm

class constForOrderData:
	MAX_X = 31 + 10
	MIN_X = 31 - 10
	MAX_Y = 121 + 10
	MIN_Y = 121 - 10

class CFOD(constForOrderData):
	pass

def getDate(s):
	if '.' in s:
		s = s[:s.rindex('.')]
	t0, t1 = s.split(' ')[:2]
	year,month,day = map(int, t0.split('-'))
	return year,month,day


def strToDateTime(s):
	if '.' in s:
		s = s[:s.rindex('.')]
	t0, t1 = s.split(' ')[:2]
	year,month,day = map(int, t0.split('-'))
	hour,minute,second = map(int, t1.split(':'))
	return datetime(year, month, day, hour, minute, second)


def strToTimestamp(s):
	if '.' in s:
		s = s[:s.rindex('.')]
	t0, t1 = s.split(' ')[:2]
	year,month,day = map(int, t0.split('-'))
	hour,minute,second = map(int, t1.split(':'))
	return second + minute*60 + hour*3600 + day*24*3600 + month*31*24*3600


def checkEntry(fileName, line):
	itemList = line.split(',')
	if len(itemList) < 4:
		return False
	carId, timeStr, xPos, yPos = itemList[:4]
	_carId = fileName[fileName.rindex('S'):-4]
	if _carId != carId:
		return False
	xPos, yPos = float(xPos), float(yPos)
	if not (xPos>=CFOD.MIN_X and xPos<=CFOD.MAX_X and yPos>=CFOD.MIN_Y and yPos<=CFOD.MAX_Y):
		return False
	year,month,day = getDate(timeStr)
	# if month != 5:
		# print month
	if year != 2016:
		return False
	return True


def orderFile(srcFileName, desFileName):
	print srcFileName
	d = dict()
	with open(srcFileName, "r") as fin:
		for line in fin:
			line = line.strip()
			if len(line)==0:
				continue
			if not checkEntry(srcFileName, line):
				continue
			try:
				carId, timeStr, xPos, yPos = line.split(',')
				ts = strToTimestamp(timeStr)
				xPos, yPos = utm.from_latlon(float(xPos), float(yPos))[:2]
				newLine = ','.join([timeStr, str(xPos), str(yPos)])
				#print newLine
				d[ts] = newLine + "\n"
			except:
				continue
	with open(desFileName, "w") as fout:
		tsList = sorted(d.keys())
		for ts in tsList:
			line = d[ts]
			fout.write(line)


def orderAllData(srcFilePath, desFilePath, nprocess=16):
	pool = multiprocessing.Pool(processes = nprocess)
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)

	dirNames = filter(lambda x:x.startswith('S'), os.listdir(srcFilePath))
	for dirName in dirNames:
		tmpFilePath = os.path.join(desFilePath, dirName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		dataFilePath = os.path.join(srcFilePath, dirName)
		dataNames = filter(lambda x:x.endswith('csv'), os.listdir(dataFilePath))
		for dataName in dataNames:
			desFileName = os.path.join(desFilePath, dirName, dataName)
			if os.path.exists(desFileName):
				continue
			srcFileName = os.path.join(srcFilePath, dirName, dataName)
			pool.apply_async(orderFile, (srcFileName, desFileName, ))

	pool.close()
	pool.join()


def exp0():
	nprocess = 24
	srcFilePath = "../rawTrajectory"
	desFilePath = "../trajectory"
	nprocess = 4
	srcFilePath = "./rawTrajectory"
	desFilePath = "./trajectory"
	orderAllData(srcFilePath, desFilePath, nprocess)

def exp1():
	srcFileName = "S013355.csv"
	desFileName = "data.in"
	orderFile(srcFileName, desFileName)

if __name__ == "__main__":
	exp0()
