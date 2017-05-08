#ifndef GLOBAL_H
#define GLOBAL_H

struct worker_t;
struct task_t;

const double eps = 1e-6;
int dcmp(double x) {
	if (fabs(x) < eps) return 0;
	return x>0 ? 1:-1;
}

double calcTime(const worker_t& worker, const task_t& task) {
	return 1.0 * fabs(worker.gridId - task.gridId) / vw;
}

inline bool judgeTime(const worker_t& worker, const task_t& task) {
	double d = calcTime(worker, task);
	if (worker.begTime <= task.begTime)
		return dcmp(task.begTime - (worker.begTime + dw))<0 && dcmp(dr - d)>=0;
	else
		return dcmp(dr - (worker.begTime-task.begTIme) - d) >= 0;
}

#endif