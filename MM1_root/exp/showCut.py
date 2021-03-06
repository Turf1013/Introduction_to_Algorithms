# coding: utf-8
#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
# import matplotlib.patches.Circle as Circle
from matplotlib.patches import Circle
from random import randint


def show_exp1():
	base_points = np.array([
		[603, 795], [884, 341], [384, 205], [928, 748], [484, 774]
	])
	fig, ax = plt.subplots()
	ax.plot(base_points[:,0], base_points[:,1], 'ro')
	
	# first cut
	ax.plot([485], [478], 'go')
	k = -0.12910
	b = 541.26187
	X = base_points[:,0]
	Y = X * k + b 
	ax.plot(X, Y, 'r-')
	ax.annotate('1st', (485,478), (490, 483))
	
	# second cut
	ax.plot([511], [778], 'go')
	k = 121.47292
	b = -61318.55417
	X = np.array([500, 520])
	Y = X * k + b 
	print X, Y
	ax.plot(X, Y, 'r-')
	ax.annotate('2nd', (511,778), (511+5, 778+5))
	
	ax.set_xlim(0, 1024)
	ax.set_ylim(0, 1024)
	ax.grid(True)
	ax.set_title('Exp seed 1')
	plt.tight_layout()
	plt.axis('equal')
	plt.show()
	
	
def show_exp4():
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
	
	
if __name__ == "__main__":
	show_exp4()