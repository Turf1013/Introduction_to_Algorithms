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

int taskN, binN;
double* threshs;
bin_t* bins;
item_t* itemS;

void enumerate(int bidx, item_t prevS, double q, double logt, priQueue& Q);

void initial() {
	itemS = new item_t[maxBinNum+5];
}

void freeMem() {
	delete[] threshs;
	delete[] bins;
	delete[] itemS;
}

void initial_PQ(priQueue& Q) {
	double logt = log(1.0 - threshs[0]);
	Q.clear();
	enumerate(0, 0, 0, threshs[0], Q);
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
		if (vitems[i].uc < minUc) {
			minUc = vitems[i].uc;
			Q.insert(vitems[i]);
		}
	}
}

void enumerate(int bidx, item_t prevS, double q, double logt, priQueue& Q) {
	item_t curS;
	for (int k=bidx; k<binN; ++k) {
		curS.lcm = __lcm(prevS.lcm, bins[k].l);
		LL na = curS.lcm / prevS.lcm, nb = curS.lcm / bins[k].l;
		curS.uc = prevS.lcm * na + bins[k].c/bins[k].l * nb;

		bool flag = false;
		for (priQueueIter iter=Q.begin(); !flag&&iter!=Q.end(); ++iter) {
			if (curS.lcm<iter->lcm || curS.uc<iter->uc) {
				flag = true;
				break;
			}
		}

		if (flag) {
			double tmp = q-log(1.0 - bins[k].r);
			if (tmp >= -logt) {
				Q.insert(curS);
				priQueueIter citer = Q.upper_bound(curS), eiter;
				while (citer!=Q.end() && citer->lcm==curS.lcm) {
					eiter = citer++;
					if (eiter->uc > curS.uc) {
						Q.erase(eiter);
					}
				}
			} else {
				enumerate(k, curS, tmp, logt, Q);
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
	double prevCost = 0.0;
	item_t prevItem, curItem(1LL<<50, 0.0);

	#ifdef LOCAL_DEBUG
	assert(Q.size() > 0);
	#endif
	while (n > 0) {
		if (iter == Q.end()) {
			cost += prevItem.lcm * prevItem.uc;
			n = 0;
			break;
		}
		while (iter != Q.end()) {
			curItem = *iter;
			iter++;
		}
		LL k = (int)floor(n / curItem.lcm);
		if (k*curItem.lcm*curItem.uc > prevCost) {
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
