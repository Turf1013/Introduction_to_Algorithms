/**
	1. program name
	2. \author: Trasier
	3. \date:   2017.10.5
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"
#include "output.h"
#include "monitor.h"

#define LOCAL_DEBUG
// #define WATCH_MEM

int taskN, binN;
double* threshs;
bin_t* bins;

void initial() {
	
}

void freeMem() {
	delete[] threshs;
	delete[] bins;
}

double solve() {
	double ret = 0.0;
	initial();
	
	return ret;
}

int main(int argc, char **argv) {
	string execName = "";
	double result, usedTime = -1, usedMem = -1;
	
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
	usedMem /= 1024.0;
	#endif
	
	
	/**
		\step 3: print the result
	*/
	dumpResult(execName, result, usedTime, usedMem);
	
	
	/**
		\step 4: free the memoroy
	*/
	freeMem();
	
	
	return 0;
}
	
