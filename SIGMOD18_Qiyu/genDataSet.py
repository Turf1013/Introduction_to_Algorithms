#!/usr/bin/env python
import os
import sys
import commands
import multiprocessing
from random import randint, gauss


class constForGenDataSet:
	# desired EVC [100, 2000]
	lambdaList	= [0.0, 0.1, 0.2, 0.3, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
	alphaList	= [0.0, 0.1, 0.2, 0.3, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0]
	rmaxList	= [500, 1000, 1500, 2000, 2500]
	bList		= [x*10**4 for x in [5000, 10000, 15000, 20000, 25000]]
	kList		= [2, 4, 6, 8, 10] # add 50
	muList		= [40000, 45000, 50000, 55000, 60000] 
	sigma		= 10000
	# estate price normal
	defaultValue = [
		lambdaList[len(lambdaList)/2-1],
		alphaList[len(alphaList)/2-1],
		rmaxList[len(rmaxList)/2],
		bList[len(bList)/2],
		kList[len(kList)/2],
		muList[len(muList)/2],
	]

class CFGD(constForGenDataSet):
	pass


def genData(desFileName, lambda_, alpha, rmax, B, K):
	with open(desFileName, "w") as fout:
		line = "%.03f %.03f %.0f %.0f %d\n" % (lambda_, alpha, rmax, B, K)
		fout.write(line)


def genDataName(lambda_, alpha, rmax, B, K, mu):
	ret = "%.03f_%.03f_%.0f_%.0f_%d_%d" % (lambda_, alpha, rmax, B, K, mu)
	return ret

def genDesFileName(dataSetId):
	ret = "data_%02d.txt" % (dataSetId)
	return ret
	
def readNV(srcFileName="./roadNetwork.txt"):
	with open(srcFileName, "r") as fin:
		for line in fin:
			nV, nE = map(int, line.strip().split(' '))
			return nV
	return None

def genDataSet(desFilePath, dataSetN, nprocess):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
		
	pool = multiprocessing.Pool(processes = nprocess)

	for dataSetId in xrange(dataSetN):
		# varying of lambda
		lambda_,alpha,rmax,B,K,mu = CFGD.defaultValue
		for lambda_ in CFGD.lambdaList:
			dataName = genDataName(lambda_, alpha, rmax, B, K, mu)
			dataFilePath = os.path.join(desFilePath, dataName)
			if not os.path.exists(dataFilePath):
				os.mkdir(dataFilePath)
			desFileName = genDesFileName(dataSetId)
			desFileName = os.path.join(dataFilePath, desFileName)
			if os.path.exists(desFileName):
				continue
			pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

		# varying of alpha
		lambda_,alpha,rmax,B,K,mu = CFGD.defaultValue
		for alpha in CFGD.alphaList:
			dataName = genDataName(lambda_, alpha, rmax, B, K, mu)
			dataFilePath = os.path.join(desFilePath, dataName)
			if not os.path.exists(dataFilePath):
				os.mkdir(dataFilePath)
			desFileName = genDesFileName(dataSetId)
			desFileName = os.path.join(dataFilePath, desFileName)
			if os.path.exists(desFileName):
				continue
			pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

		# varying of rmax
		lambda_,alpha,rmax,B,K,mu = CFGD.defaultValue
		for rmax in CFGD.rmaxList:
			dataName = genDataName(lambda_, alpha, rmax, B, K, mu)
			dataFilePath = os.path.join(desFilePath, dataName)
			if not os.path.exists(dataFilePath):
				os.mkdir(dataFilePath)
			desFileName = genDesFileName(dataSetId)
			desFileName = os.path.join(dataFilePath, desFileName)
			if os.path.exists(desFileName):
				continue
			pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

		# varying of B
		lambda_,alpha,rmax,B,K,mu = CFGD.defaultValue
		for B in CFGD.bList:
			dataName = genDataName(lambda_, alpha, rmax, B, K, mu)
			dataFilePath = os.path.join(desFilePath, dataName)
			if not os.path.exists(dataFilePath):
				os.mkdir(dataFilePath)
			desFileName = genDesFileName(dataSetId)
			desFileName = os.path.join(dataFilePath, desFileName)
			if os.path.exists(desFileName):
				continue
			pool.apply_async(genData, (desFileName, lambda_,alpha,rmax,B,K, ))

		# varying of K
		lambda_,alpha,rmax,B,K,mu = CFGD.defaultValue
		for K in CFGD.kList:
			dataName = genDataName(lambda_, alpha, rmax, B, K, mu)
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
	
	# varying of mu
	nV = readNV()
	sigma = CFGD.sigma
	for mu in CFGD.muList:
		prices = [gauss(mu, sigma) for i in xrange(nV)]
		desFileName = "prices_%d.txt" % (mu)
		desFileName = os.path.join(desFilePath, desFileName)
		with open(desFileName, "w") as fout:
			fout.write("%d\n" % (nV))
			for price in prices:
				fout.write("%.2lf\n" % (price))
		

def exp0(dataSetN=1, nprocess=4):
	desFilePath = "../dataSet_Qiyu"
	cmdLine = "rm -rf %s" % (desFilePath)
	commands.getoutput(cmdLine)
	genDataSet(desFilePath, dataSetN, nprocess)


if __name__ == "__main__":
	exp0()
