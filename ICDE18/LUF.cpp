/**
	1. online version - Largest Utility First
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
	priority_queu<pdi, vector<pdi>, greater<pdi> > uQ;
	
	for (int i=0; leftNum>0&&i<workerN; ++i) {
		worker_t& worker = workers[i];
		for (int j=0; j<taskN; ++j) {
			if (tasks[j].s == 0)
				continue;
			double u = calcUtility(tasks[j], worker);
			uQ.push(make_pair(u, j));
			if (uQ.size() > K) uQ.pop();
		}
		while (!uQ.empty()) {
			pdi tmp = uQ.top();
			uQ.pop();
			int taskId = tmp.second;
			double u = tmp.first;
			if (tasks[taskId].s <= u) {
				compTime[taskId] = i;
				tasks[taskId].s = 0;
				--leftNum;
			} else{
				tasks[taskId].s -= u;
			}
		}
	}
}

int main(int argc, char **argv) {
	string execName("LUF");
	
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