/**
	1. program name
	2. \author: Trasier
	3. \date:   2017.10.24
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"
#include "output.h"
#include "monitor.h"

// #define LOCAL_DEBUG
// #define WATCH_MEM

int taskN, binN;
double* threshs;
bin_t* bins;
double* thetas;
pdi* ranks;
pdi* ranks_;

void initial() {
	thetas = new double[taskN];
	for (int i=0; i<taskN; ++i) {
		thetas[i] = -log(1 - threshs[i]);
	}
	ranks = new pdi[taskN];
	for (int i=0; i<taskN; ++i) {
		ranks[i] = make_pair(thetas[i], i);
	}
	sort(ranks, ranks+taskN, greater<pdi>());
	ranks_ = new pdi[taskN];
}

void freeMem() {
	delete[] threshs;
	delete[] bins;
	delete[] thetas;
	delete[] ranks;
	delete[] ranks_;
}

void mySort(int c) {
	pdi* p = ranks_, *q = ranks;

	for (int i=0; i<taskN; ++i)
		p[i] = q[i];

	int i = 0, j = c, k = 0;

	while (i<c && j<taskN) {
		if (p[i] >= p[j]) {
			q[k++] = p[i++];
		} else {
			q[k++] = p[j++];
		}
	}
	while (i < c) 		q[k++] = p[i++];
	while (j < taskN)	q[k++] = p[j++];
}

double solve() {
	double ret = 0.0;
	initial();

	while (ranks[0].first > 0) {
		int k = 0, bestIdx = -1;
		double minVal = inf, sumOfTheta = 0;
		for (int i=0; i<binN; ++i) {
			int l = bins[i].l;
			double cl = bins[i].c, rl = bins[i].r;
			while (k<taskN && k<l) {
				sumOfTheta += ranks[k].first;
				++k;
			}
			double tmp = (cl) / min(l*(-log(1.0 - rl)), sumOfTheta);
			if (tmp < minVal) {
				minVal = tmp;
				bestIdx = i;
			}
		}
		ret += bins[bestIdx].c;
		int mid = 0;
		for (int i=0; i<taskN&&i<bins[bestIdx].l; ++i) {
			ranks[i].first -= (-log(1.0 - bins[bestIdx].r));
			if (ranks[i].first < 0) ranks[i].first = 0;
			++mid;
		}
		// sort(ranks, ranks+taskN, greater<pdi>());
		mySort(mid);
	}

	return ret;
}

int main(int argc, char **argv) {
	string execName = "greedyf";
	double result, usedTime = -1;
	int usedMem = -1;

	if (argc > 1)
		freopen(argv[1], "r", stdin);
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	/**
		\step 1: read the input
	*/
	readInput(taskN, threshs, binN, bins);

	/**
		\step 2: solve the problem and return the result
	*/
	clock_t begTime, endTime;
	begTime = clock();
	result = solve();
	endTime = clock();
	usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMem);
	#endif


	/**
		\step 3: print the result
	*/
	dumpResult(execName, result, usedTime, usedMem/1024.0);


	/**
		\step 4: free the memoroy
	*/
	freeMem();

	return 0;
}