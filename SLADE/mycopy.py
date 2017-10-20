import os
import sys

def gao21(desFilePath, srcFilePath, dirNames, dataSetId, commonLines):
	for dirName in dirNames:
		tmpFilePath = os.path.join(desFilePath, dirName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		fileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(desFilePath, dirName, fileName)
		srcFileName = os.path.join(srcFilePath, dirName, fileName)
		with open(desFileName, "w") as fout:
			for i,line in enumerate(commonLines):
				if i==2:
					binN = int(dirName[dirName.rindex('_')+1:])
					newLine = "%d\n" % (binN)
				else:
					newLine = "%s\n" % (line.rstrip())
				fout.write(newLine)
		
		
def gao22(desFilePath, srcFilePath, dirNames, dataSetId, commonLines):
	for dirName in dirNames:
		tmpFilePath = os.path.join(desFilePath, dirName)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		fileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(desFilePath, dirName, fileName)
		srcFileName = os.path.join(srcFilePath, dirName, fileName)
		with open(srcFileName, "r") as fin:
			srcLines = fin.readlines()
		with open(desFileName, "w") as fout:
			for i,line in enumerate(commonLines):
				if i==1:
					newLine = "%s\n" % (srcLines[i].rstrip())
				else:
					newLine = "%s\n" % (line.rstrip())
				fout.write(newLine)
					

def gao2(filePath, dirNames, dataSetN = 60):
	desFilePath = "F:/tmp/dataSet"
	numList = map(lambda s:float(s[s.rindex('_')+1:]), dirNames)
	mxNum = max(numList)
	for dirName in dirNames:
		v = float(dirName[dirName.rindex('_')+1:])
		if v != mxNum:
			continue
		for dataSetId in xrange(dataSetN):
			fileName = "data_%02d.txt" % (dataSetId)
			fileName = os.path.join(filePath, dirName, fileName)
			with open(fileName, "r") as fin:
				lines = fin.readlines()
			if "binN" in dirName:
				gao21(desFilePath, filePath, dirNames, dataSetId, lines)
			else:
				gao22(desFilePath, filePath, dirNames, dataSetId, lines)
			
	

def gao(filePath):
	dirNames = os.listdir(filePath)
	for prefix in ["evarying_binN", "varying_binN", "varying_emean", "varying_nmu", "varying_nsigma", "varying_umean"]:
		dirs = filter(lambda x:x.startswith(prefix), dirNames)
		gao2(filePath, dirs)


if __name__ == "__main__":
	gao("F:/tmp/dataSet_SLADE")