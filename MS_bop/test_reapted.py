import json


with open("F:/Qt_prj/hdoj/data.in", "r") as fin:
	G = []
	for line in fin:
		line = line.strip()
		if not line.startswith("["):
			print line
			continue
		G.append(line)
		if line.endswith("]"):
			data = "".join(G)
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
				print "Error"
			G = []
			