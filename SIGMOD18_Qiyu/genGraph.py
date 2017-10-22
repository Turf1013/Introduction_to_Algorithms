import sys
import string
from random import randint

	
def genGraph(fileName, n, m):
	with open(fileName, "w") as fout:
		fout.write("%d %d\n" % (n, m))
		for i in xrange(m):
			u = randint(1, n+1)
			v = randint(1, n+1)
			w = randint(1, 1000000) * 1.0 / 1000
			fout.write("%s %s %.6f\n" % (u, v, w))

			
def genCompleteGraph(fileName, n):
	m = n * (n-1)
	with open(fileName, "w") as fout:
		fout.write("%d %d\n" % (n, m))
		for u in xrange(1, n+1):
			for v in xrange(1, n+1):
				if u==v:
					continue				
				w = randint(1, 1000000) * 1.0 / 1000
				fout.write("%s %s %.6f\n" % (u, v, w))			
			
			
def exp0(nV = 2000):
	nE = int(nV + nV * (randint(100, 200)*1.0/100))
	desFileName = "F:\eclipse_prj\workspace\hdoj\data.in"
	genCompleteGraph(desFileName, nV)
			
			
if __name__ == "__main__":
	exp0()
	