import matplotlib.pyplot as plt


def readMarker(fileName):
	with open(fileName, "r") as fin:
		lines = map(lambda s:s.strip(), fin.readlines())
	lines = filter(lambda x:len(x)>0, lines)
	ret = []
	for line in lines[1:]:
		tmpList = map(float, line.split(' '))
		ret.append(tmpList)
	return ret
	

def readLine(fileName):
	with open(fileName, "r") as fin:
		lines = map(lambda s:s.strip(), fin.readlines())
	lines = filter(lambda x:len(x)>0, lines)
	ret = []
	for line in lines:
		tmpList = map(float, line.split(' '))
		ret.append(tmpList)
	return ret

	
def plot(points, markers, desFileName="F:/voroni.png"):
	X,Y = [],[]
	for marker in markers:
		X.append(marker[0])
		Y.append(marker[1])
	plt.scatter(X, Y, c='r', marker='.', linewidth=5)
	for p4 in points:
		X = [p4[0], p4[2]]
		Y = [p4[1], p4[3]]
		plt.plot(X, Y, 'r-', linewidth=5)
	plt.xlim(290000, 450000)
	plt.ylim(3380000, 3530000)
	plt.savefig(desFileName, dpi=600)
	plt.show()
	
	
	
if __name__ == "__main__":
	markers = readMarker("F:/tmp_Qiyu/realData/centers.txt")
	points = readLine("F:/tmp_Qiyu/voroniLine.txt")
	plot(points, markers)