/**
	\author: Trasier
	\date: 2017.05.08
*/
#include <bits/stdc.h>
using namespace std;

#include "global.h"
#include "input.h"
#include "output.h"

#define LOCAL_DEBUG

struct worker_t {
	int gridId;
	int begTime;

	worker_t(int gridId=0, int begTime=0):
		gridId(gridId), begTime(begTime) {}
};

struct task_t {
	int gridId;
	int begTime;

	task_t(int gridId=0, int begTime=0):
		gridId(gridId), begTime(begTime) {}
};

const double inf = 1e20;
int workerN, taskN;
int dw, dr, vw;
int slotN, gridLength, gridWidth;
#ifdef WATCH_MEM
int usedMemory = 0;
#endif

void init() {
	scanf("%d %d %d %d %d %d %d %d", &workerN, &taskN, &dw, &dr, &vw, &slotN, &gridLength, &gridWidth);
}

int findBestTask(const worker_t& worker, const vector<task_t>& tasks) {
	const int taskSz = tasks.size();
	double mn = inf, tmp;
	int ret = -1;

	for (int i=0; i<taskSz; ++i) {
		if (judgeTime(worker, tasks[i])) {
			tmp = calcTime(worker, tasks[i]);
			if (tmp < mn) {
				mn = tmp;
				ret = i;
			}
		}
	}

	return ret;
}

int findBestWorker(const task_t& task, const vector<worker_t>& workers) {
	const int workerSz = workers.size();
	double mn = inf, tmp;
	int ret = -1;

	for (int i=0; i<workerSz; ++i) {
		if (judgeTime(workers[i], task)) {
			tmp = calcTime(workers[i], task);
			if (tmp < mn) {
				mn = tmp;
				ret = i;
			}
		}
	}

	return ret;
}

int simpleGreedy() {
	int ans = 0;
	const int itemN = workerN + taskN;
	vector<worker_t> workers;
	vector<task_t> tasks;
	int typeId, gridId, begTime;
	worker_t worker;
	task_t task;
	

	for (int i=0; i<itemN; ++i) {
		scanf("%d %d %d", &typeId, &begTime, &gridId);

		if (typeId == 0) {
			worker.gridId = gridId;
			worker.begTime = begTime;

			const int taskId = findBestTask(worker, tasks);
			if (taskId < 0) {
				workers.push_back(worker);
			} else {
				tasks[taskId] = *tasks.rbegin();
				tasks.pop_back();
				++ans;
			}
		} else {
			task.gridId = gridId;
			task.begTime = begTime;

			const int workerId = findBestWorker(task, workers);
			if (workerId < 0) {
				tasks.push_back(task);
			} else {
				workers[workerId] = *workers.rbegin();
				workers.pop_back();
				++ans;
			}
		}

		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
	}

	return ans;
}

int solve() {
	init();

	int ret = simpleGreedy();

	return ret;
}

int main(int argc, char **argv) {
	program_t begProg, endProg;

	if (argc > 1)
		freopen(argv[1], "r", stdin);
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	save_time(begProg);
	int nPairs = solve();
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("Simple %d %.4lf %d\n", nPairs, usedTime, usedMemory/1024);
	#else
	printf("Simple %d %.4lf\n", nPairs, usedTime);
	#endif

	return 0;
}