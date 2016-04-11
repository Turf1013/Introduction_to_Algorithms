from random import randint
import string
import sys
import getopt
import os

global lc
lc = list(string.lowercase)

def dumpWord(maxlen):
	length = randint(1, maxlen)
	line = "".join([lc[randint(0, 25)] for i in xrange(length)])
	return line

def dumpWords(n=100,maxlen=20):
#	n = randint(1, maxn)
	L = [dumpWord(maxlen) for i in xrange(n)]
	return L

def dumpToFile(filepath, maxn, maxl):
	if not os.path.isdir(filepath):
		raise RunetimeError, "%s is not dir" % (filepath)
	filename = os.path.join(filepath, "data_%d_%d.in" % (maxn, maxl))
	with open(filename, "w") as fout:
		L = dumpWords(maxn, maxl)
		fout.write("\n".join(L) + "\n")

def usage():
	print "-f filepath"
	print "-l max length of word"
	print "-n number of word"
	print "-h help"
	print "--file=filepath"
	print "--maxl=max-length"
	print "--maxn=max-number"
	print "--help"

if __name__ == "__main__":
	desFileName = "./"
	maxl = 30
	maxn = 100
	try:
		options, args = getopt.getopt(sys.argv[1:], "hf:l:n:", ["help", "file=", "maxl=", "maxn="])
	except getopt.GetoptError:
		raise getopt.GetoptError
		sys.exit()
	for option,value in options:
		if option in ("-h", "--help"):
			usage()
			sys.exit()
		elif option in ("-f", "--file"):
			desFileName = value
		elif option in ("-l", "--maxl"):
			maxl = int(value)
		elif option in ("-n", "--maxn"):
			maxn = int(value)
	dumpToFile(desFileName, maxn, maxl)

