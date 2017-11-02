import os
from math import fabs

def readRoad(src, des):
	with open(src, "r") as fin:
		lines = fin.readlines()
	# print lines, '\n', len(lines)
	with open(des, "w") as fout:
		fout.writelines(lines)
	nV, nE = map(int, lines[0].split(' '))
	retDict = dict()
	for i in xrange(1, nV+1):
		sxy = lines[i].strip()
		if sxy not in retDict:
			retDict[sxy] = i
	print retDict
	return retDict
		
def dcmp(x):
	if fabs(x) < 0.001:
		return 0
	if x > 0:
		return 1
	else:
		return -1
	
def findKey(s, d):
	x, y = map(float, s.split(' '))
	for ss in d.iterkeys():
		xx, yy = map(float, ss.split(' '))
		if dcmp(xx-x)==0 and dcmp(yy-y)==0:
			return ss
	return None
		
def getVid(src, aDict):
	with open(src, "r") as fin:
		lines = fin.readlines()
	ret = []
	visitDict = dict()
	nV, nE = map(int, lines[0].split(' '))
	for i in xrange(1, nV+1):
		sxy = lines[i].strip()
		k = findKey(sxy, aDict) 
		if k and k not in visitDict:
			visitDict[k] = 1
			ret.append(i)
	print ret
	return ret	
		
def genNormal(src, des, ids, attrStr):
	ret = []
	with open(src, "r") as fin:
		j = 0
		for i,line in enumerate(fin.readlines()):
			# print i, j, ids[j]
			if i==ids[j]:
				ret.append(line.strip())
				j += 1
			if j == len(ids):
				break
	print "j = %d" % (j)
	print "%s: %d, %d" % (attrStr, len(ret), len(ids))
	with open(des, "w") as fout:
		fout.write("%d\n" % (len(ret)))
		for line in ret:
			fout.write("%s\n" % (line))
	return ret		
			
def genDemands(src, des, ids):
	genNormal(src, des, ids, "demands")
	
def genDegrees(src, des, ids):
	genNormal(src, des, ids, "degrees")

def genPrices(src, des, ids):
	genNormal(src, des, ids, "prices")
	
	
def Length(i, j, p):
	i -= 1
	j -= 1
	ret = fabs(p[i][0]-p[j][0]) + fabs(p[i][1]-p[j][1])
	ret *= 2.0
	return ret
	
	
def genEdges(src, des, ids, pos):
	ret = []
	print len(ids)
	with open(src, "r") as fin:
		j = 0
		for i,line in enumerate(fin.readlines()):
			if j==len(ids):
				break
			if i!=ids[j]:
				continue
			tmpList = line.split(' ')
			itemList = []
			for kk,k in enumerate(ids):
				val = float(tmpList[k-1])
				if val<=0:
					val = Length(j, kk, pos)
				val = "%.2f" % (val)
				itemList.append(val)
			ret.append(itemList)
			j += 1
			if j == len(ids):
				break
	print "j = %d" % (j)
	print "edges: %d, %d" % (len(ret), len(ids))
	nV = len(ret)
	with open(des, "w") as fout:
		fout.write("%d\n" % (nV))
		for itemList in ret:
			line = " ".join(itemList)
			fout.write("%s\n" % (line))
	return ret
	
	
def genPosition(aDict, vids):
	tmpDict = dict()
	for line,id in aDict.iteritems():
		x, y = map(float, line.split(' '))
		vid = vids[id-1]
		tmpDict[vid] = [x, y]
	print tmpDict.keys()
	print "vids =", vids
	ret = []
	for vid in vids:
		x, y = tmpDict[vid]
		ret.append([x, y])
	return ret
	
	
def exp0():
	tmpDict = readRoad("F:/tmp_Qiyu/roadNetwork_nV20.txt", "F:/tmp_Qiyu/synData/roadNetwork.txt")
	print tmpDict
	vids = getVid("F:/tmp_Qiyu/realData/roadNetwork.txt", tmpDict)
	pos = genPosition(tmpDict, vids)
	# print len(pos), len(vids)
	genDemands("F:/tmp_Qiyu/realData/demands.txt", "F:/tmp_Qiyu/synData/demands.txt", vids)
	genDegrees("F:/tmp_Qiyu/realData/ruralDegrees.txt", "F:/tmp_Qiyu/synData/ruralDegrees.txt", vids)
	genEdges("F:/tmp_Qiyu/realData/shortEdges.txt", "F:/tmp_Qiyu/synData/shortEdges.txt", vids, pos)
	genPrices("F:/tmp_Qiyu/realData/prices.txt", "F:/tmp_Qiyu/synData/prices.txt", vids)
	
def exp1():
	tmpDict = readRoad("./roadNetwork_nV20.txt", "./synData/roadNetwork.txt")
	print tmpDict
	vids = getVid("./roadNetwork.txt", tmpDict)
	pos = genPosition(tmpDict, vids)
	# print len(pos), len(vids)
	genDemands("./demands.txt", "./synData/demands.txt", vids)
	genDegrees("./ruralDegrees.txt", "./synData/ruralDegrees.txt", vids)
	genEdges("./shortEdges.txt", "./synData/shortEdges.txt", vids, pos)
	genPrices("./prices.txt", "./synData/prices.txt", vids)
	
if __name__ == "__main__":
	exp1()
	