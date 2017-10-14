import os
import sys

def exp():
	srcFilePath = 'C:\Users\Turf\Desktop\hst_smallresult\out_00.txt'
	with open(srcFilePath, "r") as fin:
		skyLines = fin.readlines()
	myFilePath = 'F:\eclipse_prj\workspace\hst\data.out'
	with open(myFilePath, "r") as fin:
		myLines = fin.readlines()
	n = max(len(myLines), len(skyLines))
	for i in xrange(n):
		myLine = myLines[i]
		skyLine = skyLines[i]
		mySet = map(int, myLine.strip().split(' '))
		skySet = map(int, skyLine.strip().split(' '))
		mySet.sort()
		skySet.sort()
		# print mySet, skySet
		if len(mySet) != len(skySet):
			print "!!", i
			print mySet
			print skySet
			print "\n\n"
			return 
		else:
			for x in mySet:
				if x not in skySet:
					print "!!", i
					print myLine
					print skyLine
					print "\n\n"
					return 
	
	print len(myLines), len(skyLines)	

if __name__ == "__main__":
	exp()