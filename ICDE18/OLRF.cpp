/**
	1. online version
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"

const int inf = 1<<30;
int K;
int* compTime;
task_t* tasks;
worker_t* workers;
int *visit;
int taskN;
int workerN;

void readInput(ifstream& fin) {
	fin >> K;
	readInput_tasks(fin, taskN, tasks);
	readInput_workers(fin, workerN, workers);
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
	
	return (c==0) ? mp(0.,0.) : mp(sum/c, mx); 
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
	priority_queu<pdi, vector<pdi>, greater<pdi> > rQ;
	double sum = 0.0, mx = -inf;
	int c = 0;
	
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s == 0)
			continue;
		double u = calcUtility(tasks[j], worker);
		double r = min(u, tasks[j].s);
		rQ.push(make_pair(r, j));
		if (rQ.size() > K) {
			int taskId = rQ.top().second;
			rQ.pop();
			mx = max(mx, tasks[taskId].s);
		}
		
		++c;
		sum += tasks[j].s;
	}
	while (!rQ.empty()) {
		pdi tmp = rQ.top();
		rQ.pop();
		int taskId = tmp.second;
		double r = tmp.first;
		visit[taskId] |= 1;
		sum -= r;
		if (tasks[taskId].s <= r) {
			--c;
		} else {
			mx = max(mx, tasks[taskId].s-r);
		}
	}
	
	return (c==0) ? 0. : max(sum/c, mx);
}

double tryMax(worker_t& worker) {
	priority_queu<pdi, vector<pdi>, greater<pdi> > sQ;
	int c = 0;
	double sum = 0., mx = 0.;
	
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s <= 0)
			continue;
		sQ.push(make_pair(tasks[j].s, j));
		if (sQ.size() > K) {
			int taskId = sQ.top().second;
			sQ.pop();
			mx = max(mx, tasks[taskId].s);
		}
		
		++c;
		sum += tasks[j].s;
	}
	
	while (!sQ.empty()) {
		pdi tmp = sQ.top();
		sQ.pop();
		int taskId = tmp.second;
		double u = calcUtility(tasks[taskId], worker);
		double r = min(u, tasks[taskId].s);
		visit[taskId] |= 2;
		sum -= r;
		if (tasks[taskId].s <= r) {
			--c;
		} else {
			mx = max(mx, tasks[taskId].s-r);
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
				double u = calcUtility(tasks[j], worker);
				if (tasks[j].s <= u) {
					tasks[j].s = 0;
					compTime[j] = i;
					--leftNum;
				} else {
					tasks[j].s -= u;
				}
			}
			visit[j] = 0;
		}
	}
}

int main(int argc, char **argv) {
	string execName("OLRF");
	
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