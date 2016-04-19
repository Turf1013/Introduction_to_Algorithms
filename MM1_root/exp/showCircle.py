#!/usr/bin/python

def showCircle(ax):
	base_points = np.array([
		[178, 768], [182, 204], [70, 259], 
		[181, 520], [716, 396], [593, 853],
		[225, 855], [922, 211], [540, 870],
		[776, 532]
	])
	fig, ax = plt.subplots()
	ax.plot(base_points[:,0], base_points[:,1], 'ro')
	
	# draw two bitch circle
	cir = Circle(xy=(540, 870), radius=126.6136, alpha=0.5)
	ax.add_patch(cir)
	cir = Circle(xy=(593, 853), radius=93.4264, alpha=0.5)
	ax.add_patch(cir)
	
	# `1st cut`
	xList = [
		380, 606, 628, 628
	]
	yList = [
		714, 848, 841, 841
	]
	kList = [
		-0.511014, 1.156463, 10.337250, -0.991136
	]
	bList = [
		909.267882, 147.227556, -5660.485774, 1464.854070
	]
	ncut = 3
	for i in xrange(ncut):
		x = xList[i]
		y = yList[i]
		ax.plot([x], [y], 'go')
		k = kList[i]
		b = bList[i]
		X = np.array([x-50, x+50])
		Y = X * k + b 
		ax.plot(X, Y, 'r-')
		ax.annotate("%d-th cut" % (i+1), (x,y), (x+5, y+5))
	
	
	ax.set_xlim(0, 1024)
	ax.set_ylim(0, 1024)
	ax.grid(True)
	ax.set_title('Exp seed 4')
	plt.tight_layout()
	plt.axis('equal')
	plt.show()	
	
	
def show_exp2():
	C = [
		(288.0000, 799.0000)
	]
	R = [
		16.1245, 
	]
	fig, ax = plt.subplots()
	ax.plot(base_points[:,0], base_points[:,1], 'ro')
	
	# draw two bitch circle
	cir = Circle(xy=(540, 870), radius=126.6136, alpha=0.5)
	ax.add_patch(cir)
	cir = Circle(xy=(593, 853), radius=93.4264, alpha=0.5)
	ax.add_patch(cir)
	
	ax.set_xlim(0, 1024)
	ax.set_ylim(0, 1024)
	ax.grid(True)
	ax.set_title('Exp seed 4')
	plt.tight_layout()
	plt.axis('equal')
	plt.show()	