# coding: utf-8
#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
# import matplotlib.patches.Circle as Circle
from matplotlib.patches import Circle
from random import randint
from math import sqrt, atan2, acos, cos, sin, fabs, pi

global eps
eps = 1e-6

class circle:

	def __init__(self, c, r):
		self.c = c
		self.r = r
		# print self.c, self.r
		
	def point(self, a):
		return self.c + [cos(a)*self.r, sin(a)*self.r]
	

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
	

def Length2(c1, c2):
	return (c1[0]-c2[0])*(c1[0]-c2[0]) + (c1[1]-c2[1])*(c1[1]-c2[1])

def	Length(c1, c2):
	return sqrt((c1[0]-c2[0])*(c1[0]-c2[0]) + (c1[1]-c2[1])*(c1[1]-c2[1]))

	
def dcmp(d):
	if fabs(d) < eps:
		return 0
	return 1 if d > 0 else -1
	
	
def circle_circle_intersection(arr1, arr2):
	if not isinstance(arr1, circle):
		c1 = circle(arr1[:2], arr1[2])
	else:
		c1 = arr1
	if not isinstance(arr2, circle):
		c2 = circle(arr2[:2], arr2[2])
	else:
		c2 = arr2
	d = Length(c1.c, c2.c)
	# print d
	if dcmp(d) == 0:
		if dcmp(c1.r-c2.r)==0:		# 重合
			return 0, []
		return 0, []				# 大套小
		
	if dcmp(c1.r+c2.r-d) < 0:		# 相离
		return -1, []
	if dcmp(fabs(c1.r-c2.r)-d) > 0:
		return -2, []				# 内含
	
	a = angle(c2.c - c1.c)
	tmp = min(1.0, (c1.r*c1.r + d*d - c2.r*c2.r) / (2.0*c1.r*d))
	da = acos(tmp)
	
	p1 = c1.point(a - da)
	p2 = c1.point(a + da)
	
	if p1[0]==p2[0] and p1[1]==p2[1]:
		return 1, [p1]
	return 2, [p1, p2]

	
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


def test_intersect_circle():
	o1 = 30.0 * np.random.random(2)
	o2 = o1 + [6.0, 8.0]
	R1 = [4, 3, 13, 8]
	R2 = [4, 7, 3, 7]

	for i in xrange(4):
		r1 = R1[i]
		r2 = R2[i]
		c1 = circle(o1, r1);
		c2 = circle(o2, r2);
		st, pts = circle_circle_intersection(c1, c2)
		print pts

		ax = plt.subplot(2, 2, i+1)
		cir = Circle(xy=tuple(o1), radius=r1, alpha=0.5)
		ax.add_patch(cir)
		cir = Circle(xy=tuple(o2), radius=r2, alpha=0.7)
		ax.add_patch(cir)

		if st == 0:
			title = 'concide circle'
		elif st == -1:
			title = 'separated circle'
		elif st == -2:
			title = 'cover circle'
		elif st == 1:
			title = 'tangent circle'
		elif st == 2:
			title = 'intersect circle'
		else:
			title = 'never happen circle'

		if len(pts)	> 0:
			ax.scatter(zip(*pts)[0], zip(*pts)[1],c='r')
		# ax.set_xlabel(r'X', fontsize=20)
		# ax.set_ylabel(r'Y', fontsize=20)
		ax.set_xlim(0, 100)
		ax.set_ylim(0, 100)
		ax.set_title(title)
	
	# ax.grid(True)
	# fig.tight_layout()
	# plt.axis('equal')
	plt.show()


def getTangle(A, B):
	if not isinstance(A, circle) or not isinstance(B, circle):
		raise ValueError, "A or B not class circle"

	if A.r < B.r:
		A, B = B, A
	d2 = Length2(A.c, B.c)
	rdif = A.r - B.r
	rsum = A.r + B.r

	if d2 < rdif**2:
		return []

	base = angle(B.c - A.c)
	if dcmp(d2)==0 and A.r==B.r:
		return []
	if d2 == rdif**2:
		return [A.point(base), B.point(base)]

	ang = acos((A.r-B.r) / sqrt(d2));
	ret = []
	ret.append(A.point(base + ang))
	ret.append(B.point(base + ang))
	ret.append(A.point(base - ang))
	ret.append(B.point(base - ang))

	d = dcmp(d2 - rsum*rsum)
	if d == 0:
		ret.append(A.point(base))
		ret.append(B.point(base+pi))
	elif d > 0:
		ret.append(A.point(base+ang))
		ret.append(B.point(pi+base+ang))
		ret.append(A.point(base-ang))
		ret.append(B.point(pi+base-ang))

	return ret

def test_tangents():
	o1 = np.array([10, 20])
	o2 = o1 + [6.0, 8.0]
	R1 = [4, 3, 13, 8]
	R2 = [4, 7, 3, 7]

	for i in xrange(4):
		r1 = R1[i]
		r2 = R2[i]
		c1 = circle(o1, r1);
		c2 = circle(o2, r2);
		pts = getTangle(c1, c2)

		ax = plt.subplot(2, 2, i+1)
		cir = Circle(xy=tuple(o1), radius=r1, alpha=0.5)
		ax.add_patch(cir)
		cir = Circle(xy=tuple(o2), radius=r2, alpha=0.7)
		ax.add_patch(cir)

		if i == 0:
			title = 'separated circle'
		elif i == 2:
			title = 'cover circle'
		elif i == 1:
			title = 'tangent circle'
		elif i == 3:
			title = 'intersect circle'
		else:
			title = 'never happen circle'

		if len(pts)	> 0:
			X = zip(*pts)[0]
			Y = zip(*pts)[1]
			print pts
			print X
			print Y
			for i in xrange(0, len(X), 2):
				ax.plot(X[i:i+2], Y[i:i+2], 'ro-')
		# ax.set_xlabel(r'X', fontsize=20)
		# ax.set_ylabel(r'Y', fontsize=20)
		# ax.set_xlim(0, 60)
		# ax.set_ylim(0, 60)
		ax.set_title(title)
	
		ax.grid(True)
	plt.tight_layout()
	plt.axis('equal')
	plt.show()


if __name__ == "__main__":
	# arr = rand_data()
	# show_data(arr)
	# arr = rand_circle()
	# show_circle(arr)
	# test_intersect_circle()
	test_tangents()