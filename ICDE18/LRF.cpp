/**
	1. online version - Largest Remain First
	2. \author: Trasier
	3. \date:   2017.9.14
	4. \compexity: O(nmlogK)
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
double delta, epsilon;

void readInput(istream& fin) {
	fin >> K >> epsilon;
	delta = calcDelta(epsilon);
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
	priority_queue<pdi, vector<pdi>, greater<pdi> > rQ;
	
	for (int i=0; leftNum>0&&i<workerN; ++i) {
		worker_t& worker = workers[i];
		for (int j=0; j<taskN; ++j) {
			if (tasks[j].s >= delta)
				continue;
			rQ.push(make_pair(tasks[j].s, j));
			if (rQ.size() > K) rQ.pop();
		}
		while (!rQ.empty()) {
			pdi tmp = rQ.top();
			rQ.pop();
			int taskId = tmp.second;
			double ut = calcUtility(tasks[taskId], workers[i]);
			tasks[taskId].s += ut;
			if (tasks[taskId].s >= delta) {
				compTime[taskId] = i;
				--leftNum;
			}
		}
	}
}

int main(int argc, char **argv) {
	string execName("LRF");
	
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
