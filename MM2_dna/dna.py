#!/usr/bin/python


def fetchLine(chrId, fr, to):
	filename = "./example/chromatid%d.fa" % (chrId)
	refer = ""
	with open(filename, "r") as fin:
		lines = fin.readlines()[1:]
		for line in lines:
			refer += line.strip()
	return refer[fr-1:to]


if __name__ == "__main__":
	chrId = 20
	rangeList = [
		(26871291,26871440),
		(26870879,26871027),
	]
	with open("data.out", "w") as fout:
		for rng in rangeList:
			line = fetchLine(chrId, rng[0], rng[1])
			fout.write(line + "\n")

