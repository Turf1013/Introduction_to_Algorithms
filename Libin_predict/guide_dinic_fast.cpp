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

vector<int> head, head_;
vector<int> dis;
vector<edge_t> E;
vector<worker_t> workers;
vector<task_t> tasks;
vector<int> workerCnt, taskCnt;
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
		addEdge(st, i, workers[i].cap);
	}
	for (int j=0; j<taskN; ++j) {
		addEdge(j+workerN, ed, tasks[j].cap);
	}
	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			if (judgeTime2(workers[i], tasks[j])) {
				addEdge(i, j+workerN, min(workers[i].cap, tasks[j].cap));
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
			if (predictItems[itemId].workerN > 0) {
				workers.push_back(worker_t(gridId, begTime, predictItems[itemId].workerN));
			}
			if (predictItems[itemId].taskN > 0) {
				tasks.push_back(task_t(gridId, begTime, predictItems[itemId].taskN));
			}
			++itemId;
		}
	}

	init_network();

	workerCnt.clear();
	taskCnt.clear();
	workerCnt.resize(workers.size()+1, 0);
	taskCnt.resize(tasks.size()+1, 0);
	for (int i=0; i<workers.size(); ++i) {
		workerCnt[i+1] = workerCnt[i] + workers[i].cap;
	}
	for (int j=0; j<tasks.size(); ++j) {
		taskCnt[j+1] = taskCnt[j] + tasks[j].cap;
	}
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
	int k, u, v;
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

void output_network(int maxFlow) {
	int u, v, k, f;
	vector<int> workerIdx = workerCnt;
	vector<int> taskIdx = taskCnt;

	#ifdef LOCAL_DEBUG
	//fprintf(stderr, "workerIdxSize = %d, taskIdxSize = %d\n", workerIdx.size(), taskIdx.size());
	int curFlow = 0;
	#endif
	
	//fprintf(stderr, "maxFlow = %d\n", maxFlow);
	for (u=0; u<workerN; ++u) {
		for (k=head[u]; k!=-1; k=E[k].nxt) {
			if (k & 1) continue;
			v = E[k].v - workerN;
			f = min(workers[u].cap, tasks[v].cap) - E[k].f;
			if (E[k].f>=0 && f>0) {
				#ifdef LOCAL_DEBUG
				curFlow += f;
				#endif
				for (int i=0; i<f; ++i) {
					fprintf(stdout, "%d %d\n", workerIdx[u], taskIdx[v]);
					#ifdef LOCAL_DEBUG
					assert(workerIdx[u] < workerCnt[u+1]);
					assert(taskIdx[v] < taskCnt[v+1]);
					#endif
					++workerIdx[u];
					++taskIdx[v];
				}
			}
		}
	}

	#ifdef LOCAL_DEBUG
	assert(curFlow == maxFlow);
	#endif
}

int solve() {
	// #ifdef LOCAL_DEBUG
	// puts("begin init");
	// #endif
	init();
	// #ifdef LOCAL_DEBUG
	// puts("end init");
	// #endif

	// #ifdef LOCAL_DEBUG
	// puts("begin Dinic");
	// #endif
	int maxFlow = Dinic();
	// #ifdef LOCAL_DEBUG
	// puts("end Dinic");
	// #endif

	// #ifdef LOCAL_DEBUG
	// puts("begin output");
	// #endif
	output_network(maxFlow);
	// #ifdef LOCAL_DEBUG
	// puts("end output");
	// #endif

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
	int ans = solve();
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	fprintf(stderr, "Guide: %d %.4lf %d\n", ans, usedTime, usedMemory/1024);
	#else
	fprintf(stderr, "Guide: %d %.4lf\n", ans, usedTime);
	#endif
	
	return 0;
}
