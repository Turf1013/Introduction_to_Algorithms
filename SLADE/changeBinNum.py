import os

def gao(srcFilePath):
	dirNames = os.listdir(srcFilePath)
	tmpList = srcFilePath.split('_')
	print tmpList
	tmpList[-3] = tmpList[-3][:-1] + '5'
	desFilePath = '_'.join(tmpList)
	print desFilePath
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	for dirName in dirNames:
		srcFileName = os.path.join(srcFilePath, dirName)
		with open(srcFileName, "r") as fin:
			lines = fin.readlines()
		print lines[2]
		# lines[2] = lines[2][:-2] + '5\n'
		lines[2] = "25\n"
		print lines[2]
		desFileName = os.path.join(desFilePath, dirName)
		print desFileName
		with open(desFileName, "w") as fout:
			fout.writelines(lines)
		
		
if __name__ == "__main__":
	srcFilePath = 'F:/tmp/dataSet_SLADE/SMIC/25_10000_0.90'
	gao(srcFilePath)