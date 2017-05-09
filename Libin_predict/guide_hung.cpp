/**
	\author: Trasier
	\date: 2017.05.08
*/
#include <bits/stdc++.h>
using namespace std;

#include "monitor.h"
#include "input.h"
#include "output.h"

//#define LOCAL_DEBUG

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

	readInput_predict(workerN, taskN, dw, dr, vw, slotN, gridLength, gridWidth, predictItems);
	const int gridN = gridLength * gridWidth;
	int itemId = 0;

	workers.clear();
	tasks.clear();
	for (int begTime=0; begTime<slotN; ++begTime) {
		for (int gridId=0; gridId<gridN; ++gridId) {
			if (predictItems[itemId].workerN > 0) {
				worker_t worker(gridId, begTime);
				int cap = predictItems[itemId].workerN;
				while (cap--)
					workers.push_back(worker);
			}
			if (predictItems[itemId].taskN > 0) {
				task_t task(gridId, begTime);
				int cap = predictItems[itemId].taskN;
				while (cap--)
					tasks.push_back(task);
			}
			++itemId;
		}
	}

	init_bipartite();
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

void output_bipartite(int maxFlow) {
	if (workers.size() <= tasks.size()) {
		for (int x=0; x<nx; ++x) {
			if (xy[x] != -1) {
				fprintf(stderr, "%d %d\n", x, xy[x]);
			}
		}
	} else {
		for (int x=0; x<nx; ++x) {
			if (xy[x] != -1) {
				fprintf(stderr, "%d %d\n", xy[x], x);
			}	
		}
	}
	printf("maxFlow %d\n", maxFlow);

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "maxFlow = %d\n", maxFlow);
	#endif
}

void solve() {
	init();
	int maxFlow = MaxMatch();
	output_bipartite(maxFlow);
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	// program_t begProg, endProg;

	if (argc > 1)
		freopen(argv[1], "r", stdin);
	if (argc > 2)
		freopen(argv[2], "w", stderr);

	// save_time(begProg);
	solve();
	// save_time(endProg);

	// double usedTime = calc_time(begProg, endProg);
	
	return 0;
}
