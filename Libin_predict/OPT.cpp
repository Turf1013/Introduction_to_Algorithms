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
	int cap;

	worker_t(int gridId=0, int begTime=0, int cap=0):
		gridId(gridId), begTime(begTime), cap(cap) {}
};

struct task_t {
	int gridId;
	int begTime;
	int cap;

	task_t(int gridId=0, int begTime=0, int cap=0):
		gridId(gridId), begTime(begTime), cap(cap) {}
};

#include "global.h"

struct edge_t {
	int v, f, nxt;

	edge_t(int v=0, int f=0, int nxt=0):
		v(v), f(f), nxt(nxt) {}
};

vector<int> head;
vector<int> pre, mnf, eid;
vector<edge_t> E;
vector<worker_t> workers;
vector<task_t> tasks;
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

	pre.clear();
	pre.resize(vertexN, -1);
	mnf.clear();
	mnf.resize(vertexN, 0);
	eid.clear();
	eid.resize(vertexN, 0);
	head.clear();
	head.resize(vertexN, -1);
	E.clear();

	for (int i=0; i<workerN; ++i) {
		addEdge(st, i, workers[i].cap);
	}
	for (int j=0; j<taskN; ++j) {
		addEdge(j+workerN, ed, tasks[j].cap);
	}
	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			if (judgeTime2(workers[i], tasks[j])) {
				addEdge(i, j+workerN, tasks[j].cap);
			}
		}
	}
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
	worker.cap = task.cap = 1;
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

	init_network();
}

bool bfs() {
    int u, v, k;
    queue<int> Q;
    
    fill(mnf.begin(), mnf.end(), 0);
    Q.push(st);
    mnf[st] = INT_MAX;
    pre[st] = st;
    
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        if (u == ed) return true;
        for (k=head[u]; k!=-1; k=E[k].nxt) {
        	v = E[k].v;
        	if (E[k].f && !mnf[v]) {
        		eid[v] = k;
        		pre[v] = u;
        		mnf[v] = min(mnf[u], E[k].f);
        		Q.push(v);
        	}
        }
    }
    
    return false;
}

int Ford_Fulkerson() {
	int k, u, v;
	int maxFlow = 0;

	while (bfs()) {
        for (v=ed,u=pre[v]; v!=st; v=u,u=pre[v]) {
        	k = eid[v];
        	E[k].f -= mnf[ed];
        	E[k^1].f += mnf[ed];
        }
        maxFlow += mnf[ed];

		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
    }

    return maxFlow;
}

int solve() {
	init();
	int maxFlow = Ford_Fulkerson();
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