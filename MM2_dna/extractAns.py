#!/usr/bin/python 
import os
import sys

def transform(line):
	return ','.join(line.split(',')[:-1] + ["1.0"])


def extract(filename):
	ret = []
	if not filename.endswith("minisam"):
		raise ValueError, "filename not endswith `minisam`"
	with open(filename, "r") as fin:
		while True:
			try:
				line = fin.readline()
			except:
				break
			line = line.strip()
			if line:
				ret.append(transform(line))
			else:
				break
	return ret


def dump(filename, lines):
	with open(filename, "w") as fout:
		for line in lines:
			fout.write(line + "\n")


if __name__ == "__main__":
	DIR_PATH = "./example/"
	for filename in os.listdir(DIR_PATH):
		if filename.endswith("minisam"):
			lines = extract(os.path.join(DIR_PATH, filename))
			desFileName = filename[:len("minisam")]	+ "res"
			dump(os.path.join(DIR_PATH, desFileName), lines)

