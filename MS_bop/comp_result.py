import json

def extract(filename, Lname):
	with open(filename, "r") as fin:
		data = fin.read()
	data = "".join(data.split("\n"))
	L = json.loads(data)
	LL = []
	flag = True
	for l in L:
		if l not in LL:
			LL.append(l)
		else:
			flag = False
			break
	if not flag:
		print "%s Error" % (Lname)
	return L
	
	
def compare(L1, L2):
	for l in L1:
		if l not in L2:
			print "%s in L1, but not L2" % (l)
			
	for l in L2:
		if l not in L1:
			print "%s in L2, but not L1" % (l)
	
	
if __name__ == "__main__":
	file1 = "F:/Qt_prj/hdoj/data.in"
	file2 = "F:/Qt_prj/hdoj/data.out"
	L1 = extract(file1, "L1")
	L2 = extract(file2, "L2")
	compare(L1, L2)
	