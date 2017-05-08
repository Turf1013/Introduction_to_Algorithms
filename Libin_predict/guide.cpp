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
int dw, dr, vw;
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
			if (judgeTime(workers[i], tasks[j])) {
				addEdge(i, j+workerN, tasks[j].cap);
			}
		}
	}
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
			if (predictItems[itemId].workerN > 0)
				workers.push_back(worker_t(gridId, begTime, predictItems[itemId].workerN));
			if (predictItems[itemId].taskN > 0)
				tasks.push_back(task_t(gridId, begTime, predictItems[itemId].taskN));
			++itemId;
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
    pre[st] = -1;
    
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
        for (u=ed,v=pre[u]; u!=-1; u=v,v=pre[u]) {
        	k = eid[v];
        	E[k].f -= mnf[ed];
        	E[k^1].f += mnf[ed];
        }
        maxFlow += mnf[ed];
    }

    return maxFlow;
}

void output_network() {
	int u, v, k, f;
	int edgeN = 0;

	for (u=0; u<workerN; ++u) {
		for (k=head[u]; k!=-1; k=E[k].nxt) {
			v = E[k].v;
			f = tasks[v-workerN].cap - E[k].f;
			if (f > 0) {
				++edgeN;
			}
		}
	}

	printf("%d %d %d %d %d %d %d %d", workerN, taskN, dw, dr, vw, slotN, gridLength, gridWidth);
	for (u=0; u<workerN; ++u)
		printf("%d %d\n", workers[u].begTime, workers[u].gridId);
	for (v=0; v<taskN; ++v)
		printf("%d %d\n", tasks[v].begTime, tasks[v].gridId);

	printf("%d\n", edgeN);
	for (u=0; u<workerN; ++u) {
		for (k=head[u]; k!=-1; k=E[k].nxt) {
			if (k & 1) continue;
			v = E[k].v;
			f = tasks[v-workerN].cap - E[k].f;
			if (E[k].f>=0 && f>0) {
				printf("%d %d %d\n", u, v-workerN, f);
			}
		}
	}
}

void solve() {
	init();
	int maxFlow = Ford_Fulkerson();
	output_network();
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	// program_t begProg, endProg;

	if (argc > 1)
		freopen(argv[1], "r", stdin);
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	// save_time(begProg);
	solve();
	// save_time(endProg);

	// double usedTime = calc_time(begProg, endProg);
	
	return 0;
}