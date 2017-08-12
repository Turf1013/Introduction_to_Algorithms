/**
	\author: Trasier
	\date: 2017.05.08
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
//#include "monitor.h"
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

int *head, *head_;
int *dis;
edge_t *E;
worker_t *workers;
task_t *tasks;
bool *visit;
int** g;
int** neighbour;
int workerN, taskN, gridN, vertexN;
double dw, dr, vw;
int slotN, gridLength, gridWidth;
int st, ed;
int l = 0;
#ifdef WATCH_MEM
int usedMemory = 0;
#endif

void init_ptr(int workerC, int taskC) {
	workerN = workerC;
	taskN = taskC;
	int n = workerN + taskN + 2;
	
	workers = new worker_t[workerN];
	tasks = new task_t[taskN];
	head = new int[n];
	head_ = new int[n];
	dis = new int[n];
}

void init_eptr(int edgeN) {
	E = new edge_t[edgeN];
	l = 0;
}

void del_ptr() {
	delete[] head;
	delete[] head_;
	delete[] dis;
	delete[] E;
	delete[] workers;
	delete[] tasks;
}

inline void addEdge(int u, int v, int c) {
	E[l] = edge_t(v, c, head[u]);
	head[u] = l++;

	E[l] = edge_t(u, 0, head[v]);
	head[v] = l++;
}

void init_network() {
	//workerN = workers.size();
	//taskN = tasks.size();
	st = workerN + taskN;
	ed = workerN + taskN + 1;
	vertexN = workerN + taskN + 2;

	memset(dis, 0, sizeof(int)*vertexN);
	memset(head, -1, sizeof(int)*vertexN);
	memset(head_, -1, sizeof(int)*vertexN);

	for (int i=0; i<workerN; ++i) {
		addEdge(st, i, 2);				// !!! update capacity
	}
	for (int j=0; j<taskN; ++j) {
		addEdge(j+workerN, ed, 2);		// !!! update capacity
	}
	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			if (judgeTime2(workers[i], tasks[j])) {
				addEdge(i, j+workerN, 1);
			}
		}
	}
}

void init_EdgeN(int& edgeN) {
	edgeN = workerN + taskN;
	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			if (judgeTime2(workers[i], tasks[j])) {
				++edgeN;
			}
		}
	}
	edgeN *= 2;
}

void readInput_predict(int& workerN, int& taskN, double& dw, double& dr,
						double& vw, int& slotN, int& gridLength, int& gridWidth, predictItem_t*& items) {
	
	cin >> workerN >> taskN >> dw >> dr >> vw >> slotN >> gridLength >> gridWidth;

	gridN = gridLength * gridWidth;
	int slotId, gridId;
	predictItem_t item;
	
	items = new predictItem_t[slotN*gridN];
	for (int i=0; i<slotN; ++i) {
		for (int j=0; j<gridN; ++j) {
			cin >> slotId >> gridId >> item.workerN >> item.taskN;
			items[slotId*gridN+gridId] = item;
		}
	}
}

void init_Cap(int& workerCap, int& taskCap, predictItem_t* predictItems) {
	int itemId;
	
	workerCap = taskCap = itemId = 0;
	for (int begTime=0; begTime<slotN; ++begTime) {
		for (int gridId=0; gridId<gridN; ++gridId) {
			if (predictItems[itemId].workerN > 0) {
				worker_t worker(gridId, begTime);
				int cap = predictItems[itemId].workerN;
				workerCap += cap;
			}
			if (predictItems[itemId].taskN > 0) {
				task_t task(gridId, begTime);
				int cap = predictItems[itemId].taskN;
				taskCap += cap;
			}
			++itemId;
		}
	}
}

void init() {
	predictItem_t *predictItems;

	readInput_predict(workerN, taskN, dw, dr, vw, slotN, gridLength, gridWidth, predictItems);
	const int gridN = gridLength * gridWidth;
	int itemId = 0;
	int workerCap = 0, taskCap = 0;
	
	init_Cap(workerCap, taskCap, predictItems);
	init_ptr(workerCap, taskCap);
	
	int workerIdx = 0, taskIdx = 0;
	for (int begTime=0; begTime<slotN; ++begTime) {
		for (int gridId=0; gridId<gridN; ++gridId) {
			if (predictItems[itemId].workerN > 0) {
				worker_t worker(gridId, begTime);
				int cap = predictItems[itemId].workerN;
				while (cap--)
					workers[workerIdx++] = worker;
			}
			if (predictItems[itemId].taskN > 0) {
				task_t task(gridId, begTime);
				int cap = predictItems[itemId].taskN;
				while (cap--)
					tasks[taskIdx++] = task;
			}
			++itemId;
		}
	}
	
	delete[] predictItems;
	
	int edgeN = 0;
	init_EdgeN(edgeN);
	init_eptr(edgeN);
	
	init_network();
}

bool bfs() {
    int u, v, k;
    queue<int> Q;
    
    Q.push(st);
    //fill(dis.begin(), dis.end(), 0);
	for (int i=0; i<vertexN; ++i) dis[i] = 0;
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
	const int vertexN = workerN + taskN + 2;
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

void init_subgraph() {
	g = new int*[workerN+taskN];
	neighbour = new int*[workerN+taskN];
	visit = new bool[workerN+taskN];
	for (int i=0; i<workerN+taskN; ++i) {
		g[i] = new int[2];
		g[i][0] = g[i][1] = -1;
		neighbour[i] = new int[2];
		neighbour[i][0] = neighbour[i][1] = -1;
		visit[i] = false;
	}
}

void del_subgraph() {
	for (int i=0; i<workerN+taskN; ++i) {
		delete[] g[i];
		delete[] neighbour[i];
	}
	delete[] g;
	delete[] neighbour;
}

void addLink(int u, int v) {
	#ifdef LOCAL_DEBUG
	assert(g[u][1] == -1);
	assert(g[v][1] == -1);
	#endif
	
	if (g[u][0] == -1) {
		g[u][0] = v;
	} else {
		g[u][1] = v;
	}
	
	if (g[v][0] == -1) {
		g[v][0] = u;
	} else {
		g[v][1] = u;
	}
}

void add_neighbour(int u, int v, int col) {
#ifdef LOCAL_DEBUG
//	if (neighbour[u][col] != -1 || neighbour[v][col] != -1) {
//		printf("u = %d, v = %d, col = %d\n", u, v, col);
//	}
//	assert(neighbour[u][col] == -1);
//	assert(neighbour[v][col] == -1);
#endif
	neighbour[u][col] = v;
	neighbour[v][col] = u;
}

void dfs_bipartite(int u, int fa, int col) {
	int v, c = col;
	
	visit[u] = true;
	for (int i=0; i<2; ++i) {
		v = g[u][i];
		if (v==-1 || v==fa) continue;
		add_neighbour(u, v, c);
		if (visit[v]) continue;
		dfs_bipartite(v, u, c^1);
		c ^= 1;
	}
}

void output_neighbour() {
	int c[2], u, v;
	
	c[0] = c[1] = 0;
	for (int i=0; i<workerN+taskN; ++i) {
		if (neighbour[i][0] != -1) ++c[0];
		if (neighbour[i][1] != -1) ++c[1];
	}
	//printf("|neighbour| = %d\n", (c[0]+c[1])/2);
	
	int idx = (c[0] >= c[1]) ? 0 : 1;
	for (u=0; u<workerN+taskN; ++u) {
		//if (neighbour[u][0]==-1 && neighbour[u][1]==-1) continue;
//		printf("%d %d %d\n", u, neighbour[u][idx], neighbour[u][idx^1]);
//		continue;
		
		if (u < workerN)
			printf("%d", u);
		else
			printf("%d", u-workerN);
		
		v = neighbour[u][idx];
		if (v < workerN)
			printf(" %d", v);
		else
			printf(" %d", v-workerN);
		
		//if (neighbour[u][idx^1] != -1) {
			v = neighbour[u][idx^1];
			if (v < workerN)
				printf(" %d", v);
			else
				printf(" %d", v-workerN);
		//}
		
		putchar('\n');
	}	
}

void output_network(int maxFlow) {
	int u, v, k;

	init_subgraph();
	for (u=0; u<workerN; ++u) {
		for (k=head[u]; k!=-1; k=E[k].nxt) {
			if (k & 1) continue;
			v = E[k].v;
			if (E[k].f == 0) {
				/**
					
				*/
				//printf("%d %d\n", u, v-workerN);
				addLink(u, v);
			}
		}
	}
	
	for (u=0; u<workerN; ++u) {
		if (!visit[u])
			dfs_bipartite(u, -1, 0);
	}
	for (v=workerN; v<workerN+taskN; ++v) {
		if (g[v][0] == -1) continue;
		assert(visit[v]);
	}
	output_neighbour();
	del_subgraph();
}

void solve() {
	init();
	int maxFlow = Dinic();
	//printf("maxFlow = %d\n", maxFlow);
	output_network(maxFlow);
	//fprintf(stderr, "maxFlow = %d\n", maxFlow);
	del_ptr();
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
