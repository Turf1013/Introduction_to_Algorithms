#!/usr/bin/env python
import math


class constForGenRoadNetwork():
	EARTH_RADIUS = 6378137
	
class CFGR(constForGenRoadNetwork):
	pass

def calcRad(d):
	return d * math.pi / 180.0

def calcEarthDist(lat1, lon1, lat2, lon2):
	radLat1 = calcRad(lat1)
	radLat2 = calcRad(lat2)
	radLon1 = calcRad(lon1)
	radLon2 = calcRad(lon2)
	if radLat1 < 0:	 
		radLat1 = math.pi / 2.0 + math.fabs(radLat1)
	if radLat1 > 0:	 
		radLat1 = math.pi / 2.0 - math.fabs(radLat1)
	if radLon1 < 0:	 
		radLon1 = math.pi * 2.0 - math.fabs(radLon1)
	if radLat2 < 0:	 
		radLat2 = math.pi / 2.0 + math.fabs(radLat2)
	if radLat2 > 0:	 
		radLat2 = math.pi / 2.0 - math.fabs(radLat2)
	if radLon2 < 0:	 
		radLon2 = math.pi * 2.0 - math.fabs(radLon2)
		
	x1 = CFGR.EARTH_RADIUS * math.cos(radLon1) * math.sin(radLat1)	
	y1 = CFGR.EARTH_RADIUS * math.sin(radLon1) * math.sin(radLat1)	
	z1 = CFGR.EARTH_RADIUS * math.cos(radLat1)	
	x2 = CFGR.EARTH_RADIUS * math.cos(radLon2) * math.sin(radLat2)	
	y2 = CFGR.EARTH_RADIUS * math.sin(radLon2) * math.sin(radLat2)	
	z2 = CFGR.EARTH_RADIUS * math.cos(radLat2)	
	d = ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)+ (z1 - z2) * (z1 - z2)) ** 0.5 
	theta = math.acos((CFGR.EARTH_RADIUS * CFGR.EARTH_RADIUS + CFGR.EARTH_RADIUS * CFGR.EARTH_RADIUS - d * d) / (2 * CFGR.EARTH_RADIUS * CFGR.EARTH_RADIUS))  
	dist = theta * CFGR.EARTH_RADIUS  
	return dist

def genRoadNetwork(srcFileName, desFileName):
	"""
	Line 1: 	nV nE
	Line 1~nV:  x of V_i, y of V_i
	Line 1~nE:  u, v, w   (no repeated edge)
	"""
	with open(srcFileName, "r") as fin:
		edgeDict = dict()
		nodeDict = dict()
		for i,line in enumerate(fin):
			if i==0:
				continue
			line = line.strip()
			itemList = line.split(',')
			ux = float(itemList[0])
			uy = float(itemList[1])
			u = int(itemList[2])
			v = int(itemList[3])
			eid = int(itemList[4])
			l = float(itemList[5])
			t = (u, v)
			if t not in edgeDict:
				edgeDict[t] = [0, 0.]
			(preCnt,preSum) = edgeDict[t]
			# update edgeDict
			edgeDict[t] = [preCnt+1, preSum+l]
			# update nodeDict
			nodeDict[u] = (ux, uy)
	with open(desFileName, "w") as fout:
		nV = len(nodeDict)
		nE = len(edgeDict)
		# line 1
		fout.write("%d %d\n" % (nV, nE))
		idxDict = dict()
		nodeIdxs = sorted(nodeDict.keys())
		# line 1~nV
		for i,idx in enumerate(nodeIdxs):
			idxDict[idx] = i + 1
			pos = nodeDict[idx]
			fout.write("%.6lf %.6lf\n" % (pos[0], pos[1]))
		# line 1~nE
		etList = sorted(edgeDict.keys())
		for et in etList:
			(cnt, sum) = edgeDict[et]
			u,v = et
			uid = idxDict[u]
			vid = idxDict[v]
			w = sum / cnt
			fout.write("%d %d %.6lf\n" % (uid, vid, w))
			
	
def exp0():
	srcFileName = "G:/tmp/Shangai_Edgelist.csv"
	desFileName = "G:/tmp/Shanghai_roadnetwork.txt"
	genRoadNetwork(srcFileName, desFileName)
	
	
if __name__ == "__main__":
	exp0()