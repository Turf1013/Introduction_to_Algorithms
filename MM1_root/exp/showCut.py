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
	
	# first cut
	# ax.plot([485], [478], 'go')
	# k = -0.12910
	# b = 541.26187
	# X = base_points[:,0]
	# Y = X * k + b 
	# ax.plot(X, Y, 'r-')
	# ax.annotate('1st', (485,478), (490, 483))
	
	# second cut
	# ax.plot([511], [778], 'go')
	# k = 121.47292
	# b = -61318.55417
	# X = np.array([500, 520])
	# Y = X * k + b 
	# ax.plot(X, Y, 'r-')
	# ax.annotate('2nd', (511,778), (511+5, 778+5))
	
	ax.set_xlim(0, 1024)
	ax.set_ylim(0, 1024)
	ax.grid(True)
	ax.set_title('Exp seed 4')
	plt.tight_layout()
	plt.axis('equal')
	plt.show()	
	
	
if __name__ == "__main__":
	show_exp4()