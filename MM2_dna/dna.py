#!/usr/bin/python


def fetchLine(chrId, fr, to):
	filename = "./example/chromatid%d.fa" % (chrId)
	refer = ""
	with open(filename, "r") as fin:
		lines = fin.readlines()[1:]
		for line in lines:
			refer += line.strip()
	return refer[fr-1:to]


def fetchLines(chrId, rngList):
	filename = "./example/chromatid%d.fa" % (chrId)
	refer = ""
	with open(filename, "r") as fin:
		lines = fin.readlines()[1:]
		for line in lines:
			refer += line.strip()
	ret = []
	for fr,to in rngList:
		ret.append(refer[fr-1:to])
	return ret


def dumpRange():
	filename = "./example/small5.minisam"
	ret = []
	with open(filename, "r") as fin:
		for line in fin:
			L = line.split(',')
			ret.append((int(L[2]), int(L[3])))
	return ret


def dumpPairs(chrId):
	filename = "./example/small5.minisam"
	rngList = []
	readList = []
	with open(filename, "r") as fin:
		for line in fin:
			L = line.split(',')
			rngList.append((int(L[2]), int(L[3])))
			readList.append(L[-1].strip())
	chromatList = fetchLines(chrId, rngList)
	print len(chromatList), len(readList)
	with open("data.out", "w") as fout:
		n = min(len(chromatList), len(readList))
		for i in xrange(n):
			fout.write("%s\n" % (readList[i]))
			fout.write("%s\n" % (chromatList[i]))


if __name__ == "__main__":
	chrId = 20
	dumpPairs(chrId)
	

