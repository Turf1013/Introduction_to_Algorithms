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
		addEdge(st, i, 1);
	}
	for (int j=0; j<taskN; ++j) {
		addEdge(j+workerN, ed, 1);
	}
	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			if (judgeTime2(workers[i], tasks[j])) {
				addEdge(i, j+workerN, 1);
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

		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
    }

    return maxFlow;
}

void output_network(int maxFlow) {
	int u, v, k;

	#ifdef LOCAL_DEBUG
	int curFlow = 0;
	#endif
	for (u=0; u<workerN; ++u) {
		for (k=head[u]; k!=-1; k=E[k].nxt) {
			if (k & 1) continue;
			v = E[k].v;
			if (E[k].f == 0) {
				fprintf(stderr, "%d %d\n", u, v);
				#ifdef LOCAL_DEBUG
				++curFlow;
				#endif
			}
		}
	}
	printf("maxFlow = %d\n", maxFlow);

	#ifdef LOCAL_DEBUG
	assert(curFlow == maxFlow);
	#endif
}

void solve() {
	init();
	int maxFlow = Dinic();
	output_network(maxFlow);
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