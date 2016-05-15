

def test_two_pointer_1(filename1, filename2):
	G = []
	with open(filename1, "r") as fin:
		grp = ""
		for line in fin:
			line = line.strip()
			# print grp, line
			if line.startswith("rids = "):
				# print "grp =", grp
				if grp:
					rids_str = "".join(grp[1:-1].split(" "))
					if rids_str:
						rids = map(lambda s:long(s), rids_str.split(','))
					else:
						rids = []
					G.append(rids)
				grp = line[len("rids = "):]
				# print "grp =", grp
			else:
				grp += line
	print G
	with open(filename2, "r") as fin:
		line = fin.read()
		line = "".join(line.split("\n"))
		eds = map(lambda s:long(s), line[1:-1].split(','))
	edSet = set(eds)
	for i,g in enumerate(G):
		st = set(g)
		ans = st & edSet
		print "%d: %s" % (i+1, str(ans))
		
	
if __name__ == "__main__":
	src1 = "F:\Qt_prj\hdoj\data.in"
	src2 = "F:\workspace\cpp_hdoj\data.in"
	test_two_pointer_1(src1, src2)