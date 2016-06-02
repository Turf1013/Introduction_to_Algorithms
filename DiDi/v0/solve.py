#!/usr/bin/python
from collections import defaultdict
from operator import itemgetter
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVR
from sklearn.preprocessing import StandardScaler
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
	return np.array(ret, float)
	
	
def getTest(districtId = 1):
	dataPath = os.path.join("./test_feature", "feat_%s" % (districtId))
	ret = []
	with open(dataPath, 'rb') as fin:
		reader = csv.reader(fin, delimiter=',')
		for data in reader:
			# req not NULL then have that slice info
			if int(data[2]):	
				ret.append( data )
	return np.array(ret, float)
	

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
		clf = SVR(kernel='rbf', C=1e3, gamma=0.5, shrinking=False)
		BaseSolver.__init__(self, clf)
		
		
	@staticmethod	
	def calcScore(testY, predY):
		assert testY.shape == predY.shape
		return sum(abs(testY-predY))
		
		
	def solve(self, trainData, testData):
		scalerX = StandardScaler()
		scalerY = StandardScaler()
		trainX = trainData[:,:-1]
		for data in trainX:
			print data
		trainY = trainData[:,-1]
		testX = testData[:,:-1]
		testY = testData[:,-1]
		trainX = scalerX.fit_transform(trainX)
		trainY = scalerY.fit_transform(trainY)
		print trainX
		print trainY
		testX = scalerX.transform(testX)
		self.train(trainX, trainY)
		predY = self.clf.predict(testX)
		score = self.clf.score(testX, scalerY.transform(testY))
		print "score =", score
		predY = predY * scalerY.std_ + scalerY.mean_
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
	# for i in xrange(1, 2):
		# solve(i)
	solve(62)
	
def showData(districtId):
	trainData = getTrain(districtId)
	trainReqData = trainData[:,:-1]
	trainX = trainReqData[:,:-1]
	trainY = trainReqData[:,-1]
	X = [0] * trainY.shape[0]
	for i,dataX in enumerate(trainX):
		X[i] = dataX[0] * 1440 + (dataX[1]-1) * 10
	for i,x in enumerate(X):
		print x, trainY[i]
	plt.figure()
	plt.scatter(X, trainY, c='k', label='training samples')
	plt.xlabel('time')
	plt.ylabel('request')
	plt.title('Show training data')
	plt.show()
	
	
if __name__ == "__main__":
	# solveAll()
	showData(62)