#ifndef GLOBAL_H
#define GLOBAL_H

#include <bits/stdc++.h>
using namespace std;

extern int dr, dw, vw;
extern int gridLength, gridWidth;
struct worker_t;
struct task_t;

const double eps = 1e-6;
int dcmp(double x) {
	if (fabs(x) < eps) return 0;
	return x>0 ? 1:-1;
}

double calcTime(const worker_t& worker, const task_t& task) {
	int workerX = worker.gridId / gridLength, workerY = worker.gridId % gridLength;
	int taskX = task.gridId / gridLength, taskY = task.gridId % gridLength;
	double dist = sqrt(1.0 * (workerX-taskX) * (workerX-taskX) + 1.0 * (workerY-taskY) * (workerY - taskY));
	return dist / vw;
}

inline bool judgeTime(const worker_t& worker, const task_t& task) {
	double d = calcTime(worker, task);
	if (worker.begTime <= task.begTime)
		return dcmp(task.begTime - (worker.begTime + dw))<0 && dcmp(dr - d)>=0;
	else
		return dcmp(dr - (worker.begTime-task.begTime) - d) >= 0;
}

#endif