import os

def printRN_nodeSet(lines):
	st = set()
	for line in lines:
		itemList = line.strip().split(',')
		if len(itemList)<6:
			continue
		ux = float(itemList[0])
		uy = float(itemList[1])
		u = int(itemList[2])
		v = int(itemList[3])
		eid = int(itemList[4])
		l = float(itemList[5])
		st.add(u)
		st.add(v)
	V = sorted(list(st))
	print len(st), V

def printRN_edgeSet(lines):
	d = dict()
	for line in lines:
		itemList = line.strip().split(',')
		if len(itemList)<6:
			continue
		ux = float(itemList[0])
		uy = float(itemList[1])
		u = int(itemList[2])
		v = int(itemList[3])
		eid = int(itemList[4])
		l = float(itemList[5])
		t = (u, v)
		if t in d and d[t]!=l:
			print "d(%d,%d) != d(%d,%d)" % (v,u,u,v) 
		d[t] = l
		d[(v,u)] = l
	
def printRNInfo(srcFileName):
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()[1:]
	printRN_edgeSet(lines)
			
			
if __name__ == "__main__":
	srcFileName = "G:/tmp/Shangai_Edgelist.csv"
	printRNInfo(srcFileName)