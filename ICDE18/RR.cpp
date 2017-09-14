/**
	1. online version
	2. \author: Trasier
	3. \date:   2017.9.14
	4. \complexity: O(nm)
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "globa.h"

const int inf = 1<<30;
int K;
int* compTime;
task_t* tasks;
worker_t* workers;
int taskN;
int workerN;

void readInput(ifstream& fin) {
	fin >> K;
	readInput_tasks(fin, taskN, tasks);
	readInput_workers(fin, workerN, workers);
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
			while (tasks[cid].s == 0) {
				if (++cid == taskN) cid =0;
			}
			double u = calcUtility(tasks[cid], workers[i]);
			if (tasks[cid].s <= u) {
				compTime[cid] = i;
				tasks[cid].s = 0;
				--leftNum;
			} else {
				tasks[cid].s -= u;
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
			fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
			exit(1);
		}	
		
		readInput(fin);
		fin.close();
	}
	
	// step2: online execute
	Schedule();
	
	// step3: output result
	int ans = calcResult(taskN, compTime);
	dumpResult(execName, ans);
	
	// step4: free memory
	FreeMem();
	
	return 0;
}