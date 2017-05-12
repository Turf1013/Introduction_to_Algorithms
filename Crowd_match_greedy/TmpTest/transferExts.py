import os
import sys

def gao(srcFilePath, desFilePath):
	desFileSuffix = "_mem_%s" % (srcFilePath[-1])
	nameList = os.listdir(srcFilePath)
	for desFilePrefix in ["mn", "mx", "avg"]:
		tmpPath = os.path.join(desFilePath, desFilePrefix+desFileSuffix)
		if not os.path.exists(tmpPath):
			os.mkdir(tmpPath)
	for name in nameList:
		if not name.endswith(".log"):
			continue
		srcFileName = os.path.join(srcFilePath, name)
		lines = []
		with open(srcFileName, "r") as fin:
			lines = fin.readlines()
		newLines = [[], [], []]
		typeIdxDict = {"mn": 0, "mx": 1, "avg": 2}
		for i in xrange(0, len(lines), 2):
			valLine = lines[i].strip()
			resLine = lines[i+1].strip()
			if len(valLine)==0 or len(resLine)==0:
				continue
			valList = valLine.split(',')
			for valExp in valList:
				valExp = valExp.strip()
				typeName = valExp.split(' ')[0]
				typeVal = valExp.split(' ')[-1]
				newLineIdx = typeIdxDict[typeName]
				newLineList = ["RT_%s" % (typeName.upper())]
				newLineList.append( resLine.split(' ')[1] )
				newLineList.append( typeVal )
				newLineList += resLine.split(' ')[-2:]
				newLine = " ".join(newLineList)
				newLines[newLineIdx].append( newLine )
		for typeName,typeIdx in typeIdxDict.iteritems():
			desFilePrefix = typeName
			desFileName = os.path.join(desFilePath, desFilePrefix+desFileSuffix, name)
			typeLines = newLines[typeIdx]
			# print typeLines
			with open(desFileName, "w") as fout:
				fout.write("\n".join(typeLines) + "\n")
			
		


if __name__ == "__main__":
	srcFilePath = "F:\\Log"
	nameList = os.listdir(srcFilePath)
	for name in nameList:
		if not name.startswith("ExtAvg"):
			continue
		filePath = os.path.join(srcFilePath, name)
		gao(filePath, srcFilePath)