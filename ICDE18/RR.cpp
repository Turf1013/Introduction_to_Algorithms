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

//#define LOCAL_DEBUG
//#define LOG_ALLOCATE

#ifdef WATCH_MEM
#include "monitor.h"
int usedMemory = 0;
#endif

const int inf = 1<<30;
int K;
int* compTime;
task_t* tasks;
worker_t* workers;
int taskN = 0;
int workerN = 0;
double delta, epsilon;

void dumpPredictAcc() {
	for (int j=0; j<taskN; ++j) {
		for (int i=0; i<workerN; ++i) {
			double p = calcUtility(tasks[j], workers[i]);
			printf("%.3lf ", p);
		}
		putchar('\n');
	}
}

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
	#ifdef LOCAL_DEBUG
	dumpPredictAcc();
	#endif
}

void FreeMem() {
	delete[] compTime;
	delete[] tasks;
	delete[] workers;
}

void Schedule() {
	int leftNum = taskN, cid = 0;

	for (int i=0; leftNum>0&&i<workerN; ++i) {
		#ifdef LOG_ALLOCATE
		printf("w%d:", i+1);
		#endif
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

			#ifdef LOG_ALLOCATE
			printf(" t%d", cid+1);
			#endif
		}
		#ifdef LOG_ALLOCATE
		putchar('\n');
		#endif
	}

	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
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
	clock_t begTime, endTime;
	begTime = clock();
	Schedule();
	endTime = clock();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish scheduling.\n");
	#endif

	// step3: output result
	int ans = calcResult(taskN, compTime);
	double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	#ifdef WATCH_MEM
	dumpResult(execName, ans, usedTime, usedMemory/1024.0);
	#else
	dumpResult(execName, ans, usedTime);
	#endif

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
