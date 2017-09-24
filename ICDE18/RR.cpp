/**
	1. online version - Round Robin
	2. \author: Trasier
	3. \date:   2017.9.14
	4. \complexity: O(nm)
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "global.h"

#define LOCAL_DEBUG

const int inf = 1<<30;
int K;
int* compTime;
task_t* tasks;
worker_t* workers;
int taskN;
int workerN;
double delta, epsilon;

void readInput(istream& fin) {
	fin >> K >> epsilon;
	delta = calcDelta(epsilon);
	#ifdef LOCAL_DEBUG
	fprintf(stderr, "epsilon = %.3lf, delta = %.3lf\n", epsilon, delta);
	#endif
	taskN = workerN = 0;
	readInput_Tasks(fin, taskN, tasks);
	readInput_Workers(fin, workerN, workers);
	compTime = new int[taskN];
	for (int i=0; i<taskN; ++i)
		compTime[i] = inf;
}

void FreeMem() {
	delete[] compTime;
	delete[] tasks;
	delete[] workers;
}

void Schedule() {
	int leftNum = taskN, cid = 0;

	for (int i=0; leftNum>0&&i<workerN; ++i) {
		for (int j=0; leftNum>0&&j<K; ++j) {
			while (tasks[cid].s >= delta) {
				if (++cid == taskN) cid =0;
			}
			double ut = calcUtility(tasks[cid], workers[i]);
			tasks[cid].s += ut;
			if (tasks[cid].s >= delta) {
				compTime[cid] = i;
				--leftNum;
			}
			if (++cid == taskN) cid = 0;
		}
	}
}

int main(int argc, char **argv) {
	string execName("RR");

	string srcFileName;
	if (argc > 1) {
		srcFileName = string(argv[1]);
	}
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	// step1: read Input
	if (srcFileName.empty()) {
		readInput(cin);
	} else {
		ifstream fin(srcFileName.c_str(), ios::in);
		if (!fin.is_open()) {
			fprintf(stderr, "FILE %s is invalid.\n", srcFileName.c_str());
			exit(1);
		}

		readInput(fin);
		fin.close();
	}

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish reading input.\n");
	#endif

	// step2: online execute
	Schedule();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish scheduling.\n");
	#endif

	// step3: output result
	int ans = calcResult(taskN, compTime);
	dumpResult(execName, ans);

	#ifdef LOCAL_DEBUG
	calcResult(taskN, compTime, tasks);
	fprintf(stderr, "finish dumping.\n");
	#endif

	// step4: free memory
	FreeMem();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish free memory.\n");
	#endif

	return 0;
}
