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

const int inf = 1<<30;
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

double calcValue() {
	int c = 0;
	double sum = 0, mx = -inf;
	
	for (int i=0; i<taskN; ++i) {
		if (tasks[i].s == 0)
			continue;
		++c;
		mx = max(mx, tasks[i].s);
		sum += tasks[i].s;
	}
	
	return (c==0) ? 0 : max(sum/c, mx);
}

double tryRemain(worker_t& worker) {
	priority_queue<pdi, vector<pdi>, greater<pdi> > rQ;
	double sum = 0.0, mx = -inf;
	int c = 0;
	
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s >= delta)
			continue;
		double u = calcUtility(tasks[j], worker);
		double r = min(u, delta-tasks[j].s);
		rQ.push(make_pair(r, j));
		if (rQ.size() > K) {
			int taskId = rQ.top().second;
			rQ.pop();
			mx = max(mx, delta - tasks[taskId].s);
			sum += delta - tasks[j].s;
		}
		++c;
	}
	while (!rQ.empty()) {
		pdi tmp = rQ.top();
		rQ.pop();
		int taskId = tmp.second;
		double r = tmp.first;
		visit[taskId] |= 1;
		
		if(tasks[taskId].s+r >= delta) {
			--c;
		} else {
			sum += delta - (tasks[taskId].s+r);
			mx = max(mx, delta - (tasks[taskId].s+r));
		}
	}
	
	return (c==0) ? 0. : max(sum/K, mx);
}

double tryMax(worker_t& worker) {
	priority_queue<pdi, vector<pdi>, greater<pdi> > sQ;
	int c = 0;
	double sum = 0., mx = 0.;
	
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s >= delta)
			continue;
		sQ.push(make_pair(delta-tasks[j].s, j));
		if (sQ.size() > K) {
			int taskId = sQ.top().second;
			sQ.pop();
			mx = max(mx, delta - tasks[taskId].s);
			sum += delta - tasks[j].s;
		}
		
		++c;
	}
	
	while (!sQ.empty()) {
		pdi tmp = sQ.top();
		sQ.pop();
		int taskId = tmp.second;
		double r = calcUtility(tasks[taskId], worker);
		visit[taskId] |= 2;
		
		if(tasks[taskId].s+r >= delta) {
			--c;
		} else {
			sum += delta - (tasks[taskId].s+r);
			mx = max(mx, delta - (tasks[taskId].s+r));
		}
	}
	
	return (c==0) ? 0. : max(sum/c, mx);
}

void Schedule() {
	int leftNum = taskN, cid = 0;
	
	for (int i=0; leftNum>0&&i<workerN; ++i) {
		worker_t& worker = workers[i];
		double v1 = tryRemain(worker);
		double v2 = tryMax(worker);
		int mask = (v1 <= v2) ? 1:2;
		for (int j=0; j<taskN; ++j) {
			if (visit[j] & mask) {
				double ut = calcUtility(tasks[j], worker);
				tasks[j].s += ut;
				if (tasks[j].s >= delta) {
					compTime[j] = i;
					--leftNum;
				}
			}
			visit[j] = 0;
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
	
	// step2: online execute
	Schedule();
	
	// step3: output result
	int ans = calcResult(taskN, compTime);
	dumpResult(execName, ans);
	
	// step4: free memory
	FreeMem();
	
	return 0;
}
