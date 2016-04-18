# coding: utf-8
#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
# import matplotlib.patches.Circle as Circle
from matplotlib.patches import Circle
from random import randint
from math import sqrt, atan2, acos, cos, sin

global eps
eps = 1e-6

class circle:

	def __init__(self, c, r):
		self.c = c
		self.r = r
		
		
	def point(double a):
		return self.c + [cos(a)*c.r, sin(a)*c.r]
	

	def __str__(self):
		return "c = %s, r = %s" % (self.c, self.r)
		

def rand_data(n = 16):
	return 100.0 * np.random.random((n, 2))
	
	
def rand_circle(n = 16):
	o = 100.0 * np.random.random((n, 2))
	r = 10.0 * np.random.random((n, 1))
	return np.hstack((o, r))
	
	
def show_data(arr):
	n = arr.shape[0]
	x = arr[:, 0]
	y = arr[:, 1]
	fig, ax = plt.subplots()
	ax.scatter(x, y, c='r')
	ax.set_xlabel(r'X', fontsize=20)
	ax.set_ylabel(r'Y', fontsize=20)
	ax.set_title('random points')
	
	ax.grid(True)
	fig.tight_layout()
	plt.show()
	
	
def show_circle(arr):
	n = arr.shape[0]
	o = arr[:, :2]
	r = arr[:, 2]
	fig, ax = plt.subplots()
	for i in xrange(n):
		print o[i], r[i]
		cir = Circle(xy=tuple(o[i]), radius=r[i], alpha=0.5)
		ax.add_patch(cir)
		
	ax.set_xlabel(r'X', fontsize=20)
	ax.set_ylabel(r'Y', fontsize=20)
	ax.set_xlim(0, 100)
	ax.set_ylim(0, 100)
	ax.set_title('random circle')
	
	# ax.grid(True)
	# fig.tight_layout()
	plt.axis('equal')
	plt.show()	
	
	
def choose_circle(arr):
	n = arr.shape[0]
	if n <= 1:
		raise ValueError, "|circle| <= 1"
	idx1 = randint(0, n-1)
	while True:
		idx2 = randint(0, n-1)
		if idx2 != idx1:
			break
	return np.hstack(arr[idx1, ], arr[idx2, ])
	
	
def angle(arr):
	return atan2(arr[1], arr[0])
	
	
def	Length(c1, c2):
	return sqrt((c1[0]-c2[0])*(c1[0]-c2[0]) + (c1[1]-c2[1])*(c1[1]-c2[1]))

	
def dcmp(d):
	if fabs(d) < eps:
		return 0
	return 1 if d > 0 else -1
	
	
def circle_circle_intersection(arr1, arr2):
	if not isinstance(arr1, circle):
		c1 = circle(arr1[, :2], arr1[2])
	else:
		c1 = arr1
	if not isinstance(arr2, circle):
		c2 = circle(arr2[, :2], arr2[2])
	else:
		c2 = arr2
	d = Length(c1.c, c2.c)
	if dcmp(d) == 0:
		if dcmp(c1.r-c2.r)==0:		# 重合
			return 0, []
		return -1, []				# 大套小
		
	if dcmp(c1.r+c2.r-d) < 0:		# 相离
		return -2, []
	if dcmp(fabs(c1.r-c2.r)-d) > 0:
		return -3, []				# 内含
	
	a = angle(c1.c - c2.c)
	da = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2*c1.r*d))
	
	p1 = c1.point(a - da)
	p2 = c1.point(a + da)
	
	if p1[0]==p2[0] and p1[1]==p2[1]:
		return 1, [p1]
	return 2, [p1, p2]

	
	
if __name__ == "__main__":
	# arr = rand_data()
	# show_data(arr)
	arr = rand_circle()
	show_circle(arr)
