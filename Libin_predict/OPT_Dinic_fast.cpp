/**
	\author: Trasier
	\date: 2017.05.08
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

struct edge_t {
	int v, f, nxt;

	edge_t(int v=0, int f=0, int nxt=0):
		v(v), f(f), nxt(nxt) {}
};

vector<int> head, head_;
vector<int> dis;
vector<edge_t> E;
vector<worker_t> workers;
vector<task_t> tasks;
vector<int> workerCap, taskCap;
int workerN, taskN;
double dw, dr, vw;
int slotN, gridLength, gridWidth;
int st, ed;
#ifdef WATCH_MEM
int usedMemory = 0;
#endif

inline void addEdge(int u, int v, int c) {
	E.push_back(edge_t(v, c, head[u]));
	head[u] = E.size() - 1;

	E.push_back(edge_t(u, 0, head[v]));
	head[v] = E.size() - 1;
}

void init_network() {
	workerN = workers.size();
	taskN = tasks.size();
	st = workerN + taskN;
	ed = workerN + taskN + 1;
	int vertexN = workerN + taskN + 2;

	dis.clear();
	dis.resize(vertexN, 0);
	head.clear();
	head.resize(vertexN, -1);
	head_.clear();
	head_.resize(vertexN, -1);
	E.clear();

	for (int i=0; i<workerN; ++i) {
		if (workerCap[i])
			addEdge(st, i, workerCap[i]);
	}
	for (int j=0; j<taskN; ++j) {
		if (taskCap[j])
			addEdge(j+workerN, ed, taskCap[j]);
	}
	for (int i=0; i<workerN; ++i) {
		if (workerCap[i] == 0) continue;
		for (int j=0; j<taskN; ++j) {
			if (taskCap[j] == 0) continue;

			if (judgeTime2(workers[i], tasks[j])) {
				addEdge(i, j+workerN, min(workerCap[i], taskCap[j]));
			}
		}
	}
		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
}

void init() {
	vector<predictItem_t> predictItems;

	scanf("%d %d %lf %lf %lf %d %d %d", &workerN, &taskN, &dw, &dr, &vw, &slotN, &gridLength, &gridWidth);
	const int itemN = workerN + taskN;
	const int gridN = gridLength * gridWidth;
	const int spatialN = slotN * gridN;
	int typeId, slotId, gridId;
	
	workerCap.clear();
	taskCap.clear();
	workerCap.resize(spatialN, 0);
	taskCap.resize(spatialN, 0);
	for (int i=0; i<itemN; ++i) {
		scanf("%d %d %d", &typeId, &slotId, &gridId);
		const int spatialId = slotId * gridN + gridId;
		if (typeId == 0) {
			++workerCap[spatialId];
		} else {
			++taskCap[spatialId];
		}
	}

	worker_t worker;
	task_t task;

	workers.clear();
	tasks.clear();
	for (slotId=0; slotId<slotN; ++slotId) {
		worker.begTime = task.begTime = slotId;
		for (gridId=0; gridId<gridN; ++gridId) {
			worker.gridId = task.gridId = gridId;
			workers.push_back(worker);
			tasks.push_back(task);
		}
	}

		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
	init_network();
}

bool bfs() {
    int u, v, k;
    queue<int> Q;
    
    Q.push(st);
    fill(dis.begin(), dis.end(), 0);
    dis[st] = 1;
    
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        if (u == ed) return true;
        for (k=head[u]; k!=-1; k=E[k].nxt) {
        	v = E[k].v;
        	if (dis[v]==0 && E[k].f) {
        		dis[v] = dis[u] + 1;
        		Q.push(v);
        	}
        }
    }
    
    return false;
}

int dfs(int u, int val) {
	if (u==ed || val==0)
		return val;

	int ret = 0, tmp;
	int v;

	for (int& k=head_[u]; k!=-1; k=E[k].nxt) {
		v = E[k].v;
		if (dis[v]==dis[u]+1 && E[k].f && (tmp=dfs(v, min(val, E[k].f)))>0) {
			E[k].f -= tmp;
			E[k^1].f += tmp;
			ret += tmp;
			val -= tmp;
			if (val == 0)
				break;
		}
	}

	return ret;
}

int Dinic() {
	const int vertexN = head.size();
	int maxFlow = 0, tmp;

	while (bfs()) {
		for (int i=0; i<vertexN; ++i)
			head_[i] = head[i];

        while (true) {
        	tmp = dfs(st, 1<<28);
        	if (tmp == 0)
        		break;
        	maxFlow += tmp;
        }

		//#ifdef WATCH_MEM
		//watchSolutionOnce(getpid(), usedMemory);
		//#endif
    }

		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
    return maxFlow;
}

int solve() {
	init();
	int maxFlow = Dinic();
	return maxFlow;
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
