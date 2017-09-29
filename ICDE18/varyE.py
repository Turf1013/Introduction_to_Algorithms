import os

def gao(srcFileName, desFilePath):
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	l0 = lines[0]
	tmpList = l0.split()
	for e in [0.10, 0.12, 0.14, 0.16, 0.18]:
		fileName = srcFileName[-7:-4] + "_" + str(e) + ".txt"
		desFileName = os.path.join(desFilePath, fileName)
		line = "%s %s\n" % (tmpList[0], e)
		newLines = [line] + lines[1:]
		print desFileName
		with open(desFileName, "w") as fout:
			for line in newLines:
				fout.write(line)
			
if __name__ == "__main__":
	srcFilePath = "/home/server/Yihuihe/dataSet"
	desFilePath = "/home/server/Yihuihe/dataSet"
	fileNames = ["NYC.txt", "TKY.txt"]
	for fileName in fileNames:
		srcFileName = os.path.join(srcFilePath, fileName)
		gao(srcFileName, desFilePath)