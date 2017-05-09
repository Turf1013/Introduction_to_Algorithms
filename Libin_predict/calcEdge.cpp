/**
	\author: Trasier
	\date: 2017.05.09
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"

#define LOCAL_DEBUG

struct worker_t {
	int gridId;
	int begTime;
	int cap;

	worker_t(int gridId=0, int begTime=0, int cap=0):
		gridId(gridId), begTime(begTime), cap(cap) {}
};

struct task_t {
	int gridId;
	int begTime;
	int cap;

	task_t(int gridId=0, int begTime=0, int cap=0):
		gridId(gridId), begTime(begTime), cap(cap) {}
};

#include "global.h"

typedef long long LL;
vector<worker_t> workers;
vector<task_t> tasks;
int workerN, taskN;
double dw, dr, vw;
int slotN, gridLength, gridWidth;

LL init_network() {
	workerN = workers.size();
	taskN = tasks.size();
	LL ret = workerN + taskN;

	printf("workerN = %d, taskN = %d\n", workerN, taskN);

	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			if (judgeTime2(workers[i], tasks[j])) {
				++ret;
			}
		}
	}

	return ret * 2;
}

LL calcEdge() {
	vector<predictItem_t> predictItems;

	readInput_predict(workerN, taskN, dw, dr, vw, slotN, gridLength, gridWidth, predictItems);
	const int gridN = gridLength * gridWidth;
	int itemId = 0;

	workers.clear();
	tasks.clear();
	for (int begTime=0; begTime<slotN; ++begTime) {
		for (int gridId=0; gridId<gridN; ++gridId) {
			if (predictItems[itemId].workerN > 0)
				workers.push_back(worker_t(gridId, begTime, predictItems[itemId].workerN));
			if (predictItems[itemId].taskN > 0)
				tasks.push_back(task_t(gridId, begTime, predictItems[itemId].taskN));
			++itemId;
		}
	}

	return init_network();
}

void solve() {
	LL edgeN = calcEdge();
	printf("edgeN = %lld\n", edgeN);
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	if (argc > 1)
		freopen(argv[1], "r", stdin);

	solve();
	
	return 0;
}