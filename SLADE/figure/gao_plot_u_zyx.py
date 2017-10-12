
def gao(srcFileName, plotFileName):
	with open(plotFileName, "r") as fin:
		lines = fin.readlines()
	with open(srcFileName, "r") as fin:
		vecLine = fin.readlines()
	n = len(vecLine)/4*4
	i,j = 0,0
	newLines = []
	for line in lines:
		if i==n:
			newLines.append(line.rstrip())
		else:
			top3 = line[:3]
			if top3 in ["rrk", "mcf", "laf", "aam"]:
				newLines.append(vecLine[i].rstrip())
				i += 1
			else:
				newLines.append(line.rstrip())
				
	with open("F:/Introduction_to_Algorithms/ICDE18/figure/plot_u_zyx.m", "w") as fout:
		for line in newLines:
			fout.write("%s\n" % (line))
			
			
if __name__ == "__main__":
	plotFileName = "F:/Introduction_to_Algorithms/ICDE18/figure/plot_u.m"
	srcFileName = "F:/tmp2.txt"
	gao(srcFileName, plotFileName)
		