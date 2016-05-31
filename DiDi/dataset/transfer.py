#!/usr/bin/python
from operator import itemgetter
from collections import defaultdict
import os



def dumpLines(filename):
	if not os.path.isfile(filename):
		raise ValueError, "%s is unvalid filename" % (filename)
	with open(filename, "r") as fin:
		lines = filter(lambda s:s, map(lambda s:s.strip(), fin.readlines()))
	return lines

	
def dumpCluster(filename):
	lines = dumpLines(filename)
	ret = dict()
	for line in lines:
		key, val = line.split()
		ret[key] = int(val)
	return ret
	
	
def getSliceId(s):
	L = s.split(':')
	tot = int(L[0]) * 60 + int(L[1])
	return tot/10 + 1
	
	
def dumpOrder(filename, clusterDict):
	"""
		1. transfer `time-stamp` to `slice-id`;
		2. transfer start & end district `Hash` value to `Id` value;
	"""
	lines = dumpLines(filename)
	ret = []
	for line in lines:
		L = line.split()
		order_id = L[0]
		driver_id = L[1]
		passenger_id = L[2]
		stDistrict_id = clusterDict.get(L[3])
		if not stDistrict_id:
			stDistrict_id = -1
		edDistrict_id = clusterDict.get(L[4])
		if not edDistrict_id:
			edDistrict_id = -1
		price = float(L[5])
		slice_id = getSliceId(L[-1])
		l = [order_id, driver_id, passenger_id, stDistrict_id, edDistrict_id, price, slice_id]
		ret.append(l)
	ret = map(lambda l: " ".join(map(str, l)), ret)
	return ret
	
	
def dumpPOI(filename, clusterDict):
	"""
		1. transfer district `Hash` value to `Id` value;
		2. merge POI information according 1-level type, sorted By 1-level;
		3. all entry sorted by district-Id;
	"""
	lines = dumpLines(filename)
	ret = []
	for line in lines:
		L = line.split()
		district_id = clusterDict.get(L[0])
		if not district_id:
			district_id = -1
		d = defaultdict(int)
		for item in L[1:]:
			kind, cnt = item.split(':')
			if '#' in kind:
				level = kind[:kind.find('#')]
			else:
				level = kind
			d[level] += int(cnt)
		L = sorted(d.iteritems(), key=itemgetter(0));
		l = [district_id] + map(lambda item:"%s:%s" % (item), L)
		ret.append(l)
	ret.sort(key = itemgetter(0))
	ret = map(lambda l: " ".join(map(str, l)), ret)
	return ret
	
		
def dumpTraffic(filename, clusterDict):
	"""
		1. transfer district `Hash` value to `Id` value;
		2. transfer `time-stamp` to `slice-id`;
		3. all entry sorted by district-Id and slice-id
	"""
	lines = dumpLines(filename)
	ret = []
	for line in lines:
		L = line.split()
		district_id = clusterDict.get(L[0])
		if not district_id:
			district_id = -1
		jamList = L[1:5]
		slice_id = getSliceId(L[-1])
		l = [district_id] + jamList + [slice_id]
		ret.append(l)
	ret.sort(key = itemgetter(0, -1))
	ret = map(lambda l: " ".join(map(str, l)), ret)
	return ret
	
	
def dumpWeather(filename, clusterDict=None):
	"""
		1. transfer `time-stamp` to `slice-id`;
		2. all entry sorted by slice-id
	"""
	lines = dumpLines(filename)
	ret = []
	for line in lines:
		L = line.split()
		slice_id = getSliceId(L[1])
		l = [slice_id] + L[2:]
		ret.append(l)
	ret.sort(key = itemgetter(0))
	ret = map(lambda l: " ".join(map(str, l)), ret)
	return ret

	
def saveFile(filename, lines):
	with open(filename, "w") as fout:
		fout.write("\n".join(lines))

		
def copyFile(srcFileName, desFileName):
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	with open(desFileName, "w") as fout:
		fout.write("".join(lines))	
	
	
def transferData(srcPath, desPath, dataType, dumpFunc, clusterDict=None):
	srcDataPath = os.path.join(srcPath, dataType)
	if not os.path.isdir(srcDataPath):
		raise ValueError, "%s is unvalid datapath" % (srcDataPath)
	print "transfering %s" % (dataType)
	desDataPath = os.path.join(desPath, dataType) 
	if not os.path.isdir(desDataPath):
		os.mkdir(desDataPath)
	nameList = os.listdir(srcDataPath)
	for name in nameList:
		if name[0] == '.':	# Mac useless
			continue
		lines = dumpFunc(os.path.join(srcDataPath, name), clusterDict)
		saveFile(os.path.join(desDataPath, name), lines)
		
	
def dumpDataSet(srcPath, desPath):
	if not os.path.isdir(desPath):
		os.mkdir(desPath)
	# copy `cluster_map`
	clusterDict = dumpCluster(os.path.join(srcPath, "cluster_map", "cluster_map"))
	if not os.path.isdir(os.path.join(desPath, "cluster_map")):
		os.mkdir(os.path.join(desPath, "cluster_map"))
	copyFile(os.path.join(srcPath, "cluster_map", "cluster_map"), os.path.join(desPath, "cluster_map", "cluster_map"))
	
	# transfer `order_data`
	transferData(srcPath, desPath, "order_data", dumpOrder, clusterDict)
	# transfer `poi_data`
	transferData(srcPath, desPath, "poi_data", dumpPOI, clusterDict)
	# transfer `traffic_data`
	transferData(srcPath, desPath, "traffic_data", dumpTraffic, clusterDict)
	# transfer `weather_data`
	transferData(srcPath, desPath, "weather_data", dumpWeather, clusterDict)
		
		
def dumpAll(dataPath, desPath):
	if not os.path.isdir(dataPath):
		raise ValueError, "%s is unvalid directory path" % (dataPath)
	dumpDataSet(os.path.join(dataPath, "training_data"), os.path.join(desPath, "train"))
	dumpDataSet(os.path.join(dataPath, "test_set_1"), os.path.join(desPath, "test"))
	
	
if __name__ == "__main__":
	dumpAll("I:\DiDi\season_1", "I:\DiDi\data")
	