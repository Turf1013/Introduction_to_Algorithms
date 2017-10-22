def readNV(srcFileName):
    with open(srcFileName, "r") as fin:
        for line in fin:
            nV, nE = map(int, line.strip().split(' '))
            return nV
    return None
	
def gao():
	filePath = "F:/tmp/shortPaths"
	nV = readNV("G:/tmp/Shanghai_roadnetwork.txt")
	for i in xrange(1, nV+1):
		fileName = "%05d.txt" % (i)
		fileName = filePath + "/" + fileName
		with open(fileName, "w") as fout:
			fout.write("%s\n" % (i))
	 
gao()