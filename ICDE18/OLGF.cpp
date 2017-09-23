/**
	1. online version - Optimzed Largest Gain First
	2. \author: Trasier
	3. \date:   2017.9.14
	4. \compexity: O(nmlogK)
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "global.h"

#define LOCAL_DEBUG

const int inf = 1<<29;
int K;
int* compTime;
task_t* tasks;
worker_t* workers;
int *visit;
int taskN;
int workerN;
double delta, epsilon;

void readInput(istream& fin) {
	fin >> K >> epsilon;
	delta = calcDelta(epsilon);
	readInput_Tasks(fin, taskN, tasks);
	readInput_Workers(fin, workerN, workers);
	compTime = new int[taskN];
	visit = new int[taskN];

	for (int i=0; i<taskN; ++i) {
		compTime[i] = inf;
		visit[i] = 0;
	}
}

void FreeMem() {
	delete[] compTime;
	delete[] tasks;
	delete[] workers;
}

pdd calcValue2() {
	int c = 0;
	double sum = 0, mx = -inf;

	for (int i=0; i<taskN; ++i) {
		if (tasks[i].s == 0)
			continue;
		++c;
		mx = max(mx, tasks[i].s);
		sum += tasks[i].s;
	}

	return (c==0) ? make_pair(0.,0.) : make_pair(sum/c, mx);
}

void calcValue2(double& maxRemain, double& avg) {
	maxRemain = -inf;
	avg = 0;

	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s >= delta)
			continue;
		avg += delta - tasks[j].s;
		maxRemain = max(maxRemain, delta - tasks[j].s);
	}
	avg /= K;
}

void Schedule() {
	int leftNum = taskN, cid = 0;
	double maxRemain, avg;
	priority_queue<pdi, vector<pdi>, greater<pdi> > Q;

	for (int i=0; leftNum>0&&i<workerN; ++i) {
		worker_t& worker = workers[i];
		calcValue2(maxRemain, avg);
		for (int j=0; j<taskN; ++j) {
			if (tasks[j].s >= delta)
				continue;
			if (avg >= maxRemain) {
				double ut = calcUtility(tasks[j], worker);
				Q.push(make_pair(min(delta-tasks[j].s, ut), j));
			} else {
				Q.push(make_pair(delta-tasks[j].s, j));
			}
			if (Q.size() > K) Q.pop();
		}

		while (!Q.empty()) {
			pdi tmp = Q.top();
			Q.pop();
			int taskId = tmp.second;
			double ut = calcUtility(tasks[taskId], worker);
			tasks[taskId].s += ut;
			if (tasks[taskId].s >= delta) {
				compTime[taskId] = i;
				--leftNum;
			}
		}
	}
}

int main(int argc, char **argv) {
	string execName("OLGF");

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
	fprintf(stderr, "finish dumping.\n");
	#endif

	// step4: free memory
	FreeMem();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish free memory.\n");
	#endif

	return 0;
}
