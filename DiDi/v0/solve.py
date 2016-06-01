#!/usr/bin/python
from collections import defaultdict
from operator import itemgetter
import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm
import os
import csv
import logging

global ndstrict, nslice, nday, Qslice
ndistrict = 66
nslice = 144
nday = 22
Qslice = [46, 58, 70, 82, 94, 106, 118, 130, 142]

def initLog(lda):
	logging.basicConfig(
				level=logging.DEBUG,
                format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                datefmt='%a, %d %b %Y %H:%M:%S',
                filename='solver_v0.log',
                filemode='w')
				

def getTrain(districtId = 1):
	dataPath = os.path.join("./test_feature", "feat_%s" % (districtId))
	ret = []
	with open(dataPath, 'rb') as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			ret.append(data)
	return np.array(ret, int)
	
	
def getTest(districtId = 1):
	dataPath = os.path.join("./test_feature", "feat_%s" % (districtId))
	ret = []
	with open(dataPath, 'rb') as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			# req not NULL then have that slice info
			if int(data[2]):	
				ret.append( data )
	return np.array(ret, int)
	

class BaseSolver(object):

	def __init__(self, clf):
		self.clf = clf
		
	def train(self, X, y):
		self.clf.fit(X, y)
		
	def predict(self, X):
		return self.clf.predict(X)
		
	def __str__(self):
		return str(self.clf)
	
	
class svmSolver(BaseSolver):
	
	def __init__(self):
		clf = svm.SVR(kernel='rbf', C=1.0, gamma=0.5, shrinking=False)
		BaseSolver.__init__(self, clf)
		
		
	@staticmethod	
	def calcScore(testY, predY):
		assert testY.shape == predY.shape
		return sum(abs(testY-predY))
		
		
	def solve(self, trainData, testData):
		trainX = trainData[:,:-1]
		trainY = trainData[:,-1]
		testX = testData[:,:-1]
		testY = testData[:,-1]
		self.train(trainX, trainY)
		predY = self.clf.predict(testX)
		print trainY
		print predY
		print testY
		score = svmSolver.calcScore(testY, predY)
		logging.debug(
			'SVR with kernel = %s, C = %s, gamma = %s, score = %s' % (self.clf.kernel, self.clf.C, self.clf.gamma, score)
		)
		print 'SVR with kernel = %s, C = %s, gamma = %s, score = %s' % (self.clf.kernel, self.clf.C, self.clf.gamma, score)
		

def solve(districtId):
	solver = svmSolver()
	trainData = getTrain(districtId)
	testData = getTest(districtId)
	trainReqData = trainData[:,:-1]
	testReqData = testData[:,:-1]
	# learn request curve
	solver.solve(trainReqData, testReqData)
	
	
def solveAll():
	for i in xrange(1, 2):
		solve(i)
		
		
if __name__ == "__main__":
	solveAll()
	