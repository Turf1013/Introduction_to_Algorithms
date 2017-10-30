import utm

with open("F:/tmp/tmp.txt", "r") as fin:
	lines = fin.readlines()
	
pos = []
st = set()
for line in lines:
	line = line.strip()
	if len(line) <= 0:
		continue
	# x, y = map(float, line.split(' '))[:2]
	# x, y = utm.to_latlon(x, y, 51, 'R')[:2]
	x, y = map(float, line.split(' '))[:2]
	
	ix, iy = int(x*10), int(y*10)
	t = (ix*10+int((x*100-ix*10)/5), iy*10+int((y*100-iy*10)/5))
	if t not in st:
		st.add(t)
		pos.append([x, y])
	
with open("F:/tmp/tmp2.txt", "w") as fout:
	# fout.write("lat\tlon\n")
	line = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
	fout.write(line + "\n")
	line = "<kml xmlns=\"http://earth.google.com/kml/2.1\" >"
	fout.write(line + "\n")
	line = "\t<Document>"
	fout.write(line + "\n")
	for i,lst in enumerate(pos):
		x,y = lst
		# fout.write("p%d,%.6lf,%.6lf\n" % (i,x, y))
		# fout.write("%.6lf\t%.6lf\n" % (y, x))
		if i<=500:
			line = "\t\t<Placemark><name>P%d</name><styleUrl>#Pt_STYLE</styleUrl><Point><coordinates>%.6lf,%.6lf,0</coordinates></Point></Placemark>\n" % (i, y, x)
			fout.write(line)
	line = "\t</Document>"
	fout.write(line + "\n")
	line = "</kml>"
	fout.write(line + "\n")
	