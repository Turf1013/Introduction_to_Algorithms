#!/usr/bin/python
from collections import defaultdict
from operator import itemgetter
import numpy as np
import matplotlib.pyplot as plt
import os
import csv
import logging

def show(mape_v0, mape_v1):
	assert len(mape_v0) == len(mape_v1)
	n = len(mape_v0)
	X = range(n)
	
	plt.plot(X, mape_v0, 'ro-', linewidth=2.5, label='v0')
	plt.plot(X, mape_v1, 'gs-', linewidth=2.5, label='v1')
	plt.legend()
	plt.savefig("comp.png", dpi=400)
	plt.show()
	
	
def load(filename):
	ret = []
	with open(filename, "r") as fin:
		line = fin.read()
		ret = map(float, line.split())
	return ret
	
def comp():
	mape_v0 = load("../v0/tot.out")
	mape_v1 = load("../v1/tot.out")
	show(mape_v0, mape_v1)
	
if __name__ == "__main__":
	comp()