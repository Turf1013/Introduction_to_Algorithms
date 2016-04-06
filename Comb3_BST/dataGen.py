import sys
import string
from random import randint

	
def GenData(fileName):
	with open(fileName, "w") as fout:
		t = 5
		bound = 1000
		opL = [
			"Insert",
			"Delete",
			"Pred",
			"Succ",
			"Memb",
			"Max",
			"Min",
		]
		fout.write("%d\n" % (t))
		for tt in xrange(t):
			n = randint(1, bound)
			m = randint(10, bound)
			fout.write("%d %d\n" % (n, m))
			st = set()
			for i in xrange(m):
				idx = randint(0, 6)
				if idx <= 4:
					x = randint(0, n-1)
					fout.write("%s %d\n" % (opL[idx], x))
				else:
					fout.write("%s\n" % (opL[idx]))
		
		
def MovData(srcFileName, desFileName):
	with open(srcFileName, "r") as fin:
		lines = fin.readlines()
	with open(desFileName, "w") as fout:
		fout.write("".join(lines))
		
			
if __name__ == "__main__":
	srcFileName = "F:\Qt_prj\hdoj\data.in"
	desFileName = "F:\workspace\cpp_hdoj\data.in"
	GenData(srcFileName)
	MovData(srcFileName, desFileName)
	