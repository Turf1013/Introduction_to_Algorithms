/**
	\author: Trasier
	\date: 2017.05.09
*/
#include <bits/stdc++.h>
using namespace std;

#include "monitor.h"
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

#include "global.h"

int nx, ny;
vector<int> xy, yx;
vector<bool> visit;
vector<worker_t> workers;
vector<task_t> tasks;
int workerN, taskN;
double dw, dr, vw;
int slotN, gridLength, gridWidth;
#ifdef WATCH_MEM
int usedMemory = 0;
#endif

void init_bipartite() {
	workerN = workers.size();
	taskN = tasks.size();
	nx = min(taskN, workerN);
	ny = max(taskN, workerN);

	xy.clear();
	xy.resize(nx, -1);
	yx.clear();
	yx.resize(ny, -1);
	visit.clear();
	visit.resize(ny, false);
}

void init() {
	vector<predictItem_t> predictItems;

	scanf("%d %d %lf %lf %lf %d %d %d", &workerN, &taskN, &dw, &dr, &vw, &slotN, &gridLength, &gridWidth);
	const int itemN = workerN + taskN;
	int typeId;
	worker_t worker;
	task_t task;

	workers.clear();
	tasks.clear();
	for (int i=0; i<itemN; ++i) {
		scanf("%d", &typeId);
		if (typeId == 0) {
			scanf("%d %d", &worker.begTime, &worker.gridId);
			workers.push_back(worker);
		} else {
			scanf("%d %d", &task.begTime, &task.gridId);
			tasks.push_back(task);
		}
	}

	init_bipartite();
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
}

bool dfs0(int x) {
    for (int y=0; y<ny; ++y) {
    	if (!visit[y] && judgeTime2(workers[x], tasks[y])) {
    		visit[y] = true;
    		if (yx[y]==-1 || dfs0(yx[y])) {
    			yx[y] = x;
    			xy[x] = y;
    			return true;
    		}
    	}
    }
    
    return false;
}

bool dfs1(int x) {
    for (int y=0; y<ny; ++y) {
    	if (!visit[y] && judgeTime2(workers[y], tasks[x])) {
    		visit[y] = true;
    		if (yx[y]==-1 || dfs1(yx[y])) {
    			yx[y] = x;
    			xy[x] = y;
    			return true;
    		}
    	}
    }
    
    return false;
}

int MaxMatch() {
	int ret = 0;

	if (workers.size() <= tasks.size()) {
		for (int x=0; x<nx; ++x) {
			fill(visit.begin(), visit.end(), false);
			if (dfs0(x))
				++ret;
		}
	} else {
		for (int x=0; x<nx; ++x) {
			fill(visit.begin(), visit.end(), false);
			if (dfs1(x))
				++ret;
		}
	}
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif

    return ret;
}

int solve() {
	init();
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
	int ret = MaxMatch();
	return ret;
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
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
	printf("OPT %d %.4lf %d\n", nPairs, usedTime, usedMemory/1024);
	#else
	printf("OPT %d %.4lf\n", nPairs, usedTime);
	#endif
	
	return 0;
}