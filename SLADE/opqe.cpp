/**
	1. program name
	2. \author: OPQE
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
double* thetas;
bin_t* bins;
int* itemS;
priQueue* Qs;
int* Ns;

double OPQ(int n, priQueue& Q);
void enumerate(int bidx, double q, double logt, priQueue& Q, int dep);

void initial() {
	itemS = new int[maxBinNum+5];
	thetas = new double[taskN];

	for (int i=0; i<taskN; ++i) {
		thetas[i] = -log(1.0 - threshs[i]);
	}
}

void freeMem() {
	delete[] threshs;
	delete[] bins;
	delete[] itemS;
	delete[] Qs;
	delete[] thetas;
}

void initial_PQ(priQueue& Q, double theta) {
	double logt = -theta;
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
			} else {
				enumerate(k, tmp, logt, Q, dep+1);
			}
		}
	}
}

int calcK(int alpha, double theta) {
	int ret = 0, i = 0;

	while (exp2(alpha+i) <= theta) {
		++i;
	}

	return i;
}

void initial_Qs() {
	double theta_min = inf, theta_max = -inf;

	for (int i=0; i<taskN; ++i) {
		theta_min = min(theta_min, thetas[i]);
		theta_max = max(theta_max, thetas[i]);
	}

	int alpha = (int)floor(log2(theta_min-eps)), i = 0;
	int K = calcK(alpha, theta_max);
	double tau;

	Qs = new priQueue[K];
	Ns = new int[K];
	memset(Ns, 0, sizeof(int)*K);
	while (exp2(alpha+i) < theta_max) {
		if (exp2(alpha+i+1) > theta_max) {
			tau = theta_max;
		} else {
			tau = exp2(alpha+i+1);
		}
		#ifdef LOCAL_DEBUG
		assert(i>=0 && i<K);
		#endif
		initial_PQ(Qs[i], tau);
		++i;
	}
}

double solve() {
	double cost = 0.0;

	initial();
	initial_Qs();

	double theta_max = -inf, theta_min = inf;

	for (int i=0; i<taskN; ++i) {
		theta_max = max(theta_max, thetas[i]);
		theta_min = min(theta_min, thetas[i]);
	}
	int alpha = (int)floor(log2(theta_min-eps)), beta = (int)ceil(log2(theta_max)), K = calcK(alpha, theta_max);

	for (int i=0; i<taskN; ++i) {
		int j = (int)ceil(log2(thetas[i]));
		#ifdef LOCAL_DEBUG
		assert((j-alpha-1) >= 0);
		assert((j-alpha-1) < K);
		#endif
		++Ns[j-alpha-1];
	}

	for (int i=0; i<K; ++i) {
		if (Ns[i] == 0) continue;

		cost += OPQ(Ns[i], Qs[i]);
	}

// #ifdef LOCAL_DEBUG
	// for (int i=0; i<K; ++i) {
		// double thresh = (i==K-1) ? (*max_element(threshs, threshs+taskN)) : (1.0 - exp(-exp2(alpha + i + 1)));
		// double tmp = OPQ(Ns[i], Qs[i]);
		// printf("%d %.3lf %.3lf\n", Ns[i], thresh, tmp);
		// for (priQueueIter iter=Qs[i].begin(); iter!=Qs[i].end(); ++iter)
			// printf("(%lld,%.3lf) ", iter->lcm, iter->uc);
		// putchar('\n');
		// fflush(stdout);
	// }
// #endif

#ifdef WATCH_MEM
watchSolutionOnce(getpid(), usedMem);
#endif

	return cost;
}

double OPQ(int n, priQueue& Q) {
	double cost = 0.0, prevCost = inf;
	item_t prevItem, curItem(1LL<<50, 0.0);

	#ifdef LOCAL_DEBUG
	assert(Q.size() > 0);
	printf("Q.size() = %d\n", Q.size());
	#endif
	priQueueIter iter = Q.begin();
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

	return cost;
}

int main(int argc, char **argv) {
	string execName = "opqe";
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
