/**
	1. online version - Pure Random
	2. \author: Trasier
	3. \date:   2017.9.14
	4. \complexity: O(nm)
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "global.h"

const int inf = 1<<30;
int K;
int* compTime;
task_t* tasks;
worker_t* workers;
int taskN;
int workerN;

void readInput(istream& fin) {
	fin >> K;
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
	int* tid = new int[taskN];
	
	for (int j=0; j<taskN; ++j) tid[j] = j;
	for (int i=0; leftNum>0&&i<workerN; ++i) {
		random_shuffle(tid, tid+leftNum);
		for (int j=min(K,leftNum); j>0; --j) {
			int taskId = tid[j];
			double ut = calcUtility(tasks[taskId], workers[i]);
			if (tasks[taskId].s <= ut) {
				compTime[taskId] = i;
				tasks[taskId].s = 0;
				--leftNum;
				tid[j] = tid[leftNum];
			} else {
				tasks[taskId].s -= ut;
			}
		}
	}
	
	delete[] tid;
}

int main(int argc, char **argv) {
	string execName("PR");
	
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
			fprintf(stderr, "FILE %s is invalid.", srcFileName.c_str());
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
