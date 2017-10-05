/**
	1. program name
	2. \author: OPQ
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

const int maxBin = 30;
int taskN, binN;
double* threshs;
bin_t* bins;
int* itemS;

void enumerate(int bidx, double q, double logt, priQueue& Q, int dep=0);

void initial() {
	itemS = new int[maxBin];
	for (int i=0; i<maxBin; ++i)
		itemS[i] = 0;
}

void freeMem() {
	delete[] threshs;
	delete[] bins;
	delete[] itemS;
}

void initial_PQ(priQueue& Q) {
	double logt = log(1.0 - threshs[0]);
	Q.clear();
	enumerate(0, 0, logt, Q, 0);
	if (Q.empty()) return;

	const int szQ = Q.size();
	vector<item_t> vitems(szQ);
	priQueueIter iter = Q.begin();
	for (int i=0; i<szQ; ++i,++iter) {
		vitems[i] = *iter;
	}
	Q.clear();

	double minUc = inf;
	for (int i=szQ-1; i>=0; --i) {
		if (vitems[i].uc <= minUc) {
			minUc = vitems[i].uc;
			Q.insert(vitems[i]);
		}
	}
}

void enumerate(int bidx, double q, double logt, priQueue& Q, int dep) {
	if (dep >= maxBinNum) return ;
	item_t curS;
	for (int k=bidx; k<binN; ++k) {
		itemS[dep] = k;
		curS = calcItem(itemS, bins, dep+1);

		bool flag = true;
		for (priQueueIter iter=Q.begin(); !flag&&iter!=Q.end(); ++iter) {
			if (!(curS.lcm<iter->lcm || curS.uc<iter->uc)) {
				flag = false;
				break;
			}
		}

		if (flag) {
			double tmp = q-log(1.0 - bins[k].r);
			if (tmp >= -logt) {
				Q.insert(curS);
				priQueueIter citer = Q.find(curS), eiter;
				#ifdef LOCAL_DEBUG
				assert(citer != Q.end());
				#endif
				++citer;
				while (citer!=Q.end() && citer->lcm==curS.lcm) {
					eiter = citer++;
					#ifdef LOCAL_DEBUG
					assert(eiter->uc > curS.uc);
					#endif
					if (eiter->uc > curS.uc) {
						Q.erase(eiter);
					}
				}
// #ifdef LOCAL_DEBUG
				// printf("add curS with (%lld, %.3lf)\n", curS.lcm, curS.uc);
				// for (priQueueIter iter=Q.begin(); iter!=Q.end(); ++iter)
					// printf("(%lld, %.3lf)  ", iter->lcm, iter->uc);
				// putchar('\n');
				// fflush(stdout);
// #endif
			} else {
				enumerate(k, tmp, logt, Q, dep+1);
			}
		}
	}
}

double solve() {
	double cost = 0.0;
	priQueue Q;
	priQueueIter iter;

	initial();
	initial_PQ(Q);

	int n = taskN;
	double prevCost = inf;
	item_t prevItem, curItem(1LL<<50, 0.0);

	#ifdef LOCAL_DEBUG
	assert(Q.size() > 0);
	#endif
	iter = Q.begin();
	while (n > 0) {
		if (iter == Q.end()) {
			cost += prevItem.lcm * prevItem.uc;
			n = 0;
			break;
		}
		while (iter != Q.end()) {
			curItem = *iter;
			iter++;
			if (curItem.lcm <= n)
				break;
		}
		LL k = (int)floor(n / curItem.lcm);
		if (curItem.lcm*curItem.uc*k > prevCost) {
			cost += prevItem.lcm * prevItem.uc;
			n -= prevItem.lcm;
		} else {
			cost += curItem.lcm * curItem.uc * k;
			n = n % curItem.lcm;
			prevItem = curItem;
			prevCost = curItem.lcm * curItem.uc;
		}
	}

	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMem);
	#endif

	return cost;
}

int main(int argc, char **argv) {
	string execName = "opq";
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
