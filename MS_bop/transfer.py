import json

with open("F:\\Qt_prj\\hdoj\\data.in", "r") as fin:
	data = fin.read()
L = json.loads(data)

with open("F:\\Qt_prj\\hdoj\\data.out", "w") as fout:
	fout.write("[")
	lines = ",\n".join(map(lambda l:"".join(str(l).split('L')), L))
	fout.write(lines)
	fout.write("]")
	

