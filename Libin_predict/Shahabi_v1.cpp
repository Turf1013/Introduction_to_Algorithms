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
int workerN, taskN;
double dw, dr, vw;
int slotN, gridLength, gridWidth;
int st, ed;
int timeBound;
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
	int workerN = workers.size();
	int taskN = tasks.size();
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
	#ifdef LOCAL_DEBUG
	vector<bool> workerVisit(workers.size(), false);
	vector<bool> taskVisit(tasks.size(), false);
	#endif
	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			if (judgeTime1(workers[i], tasks[j])) {
				addEdge(i, j+workerN, tasks[j].cap);
				#ifdef LOCAL_DEBUG
				workerVisit[i] = taskVisit[j] = true;
				#endif
			}
		}
	}
	#ifdef LOCAL_DEBUG
		int workerVisitCnt = 0, taskVisitCnt = 0;
		for (int i=0; i<workerN; ++i) workerVisitCnt += workerVisit[i];
		for (int j=0; j<taskN; ++j) taskVisitCnt += taskVisit[j];
		printf("workerVisitCnt = %d, taskVisitCnt = %d\n", workerVisitCnt, taskVisitCnt);
	#endif

	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
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

		// #ifdef WATCH_MEM
		// watchSolutionOnce(getpid(), usedMemory);
		// #endif
    }

    #ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif

    return maxFlow;
}

struct triple_t {
	int typeId, begTime, gridId;

	bool operator< (const triple_t& o) const {
		return begTime < o.begTime;
	}
};

char desFileName[505];
void reSort(const char *srcFileName) {
	int len = strlen(srcFileName);
	const char *label = "Data30/";
	const int labelN = strlen(label);

	desFileName[0] = '\0';
	for (int i=0; i<len; ++i) {
		if (strncmp(srcFileName+i, label, labelN) == 0) {
			strcpy(desFileName, srcFileName+i+labelN);
			break;
		}
	}

	len = strlen(desFileName);
	if (len == 1) {
		perror("invalid srcFilePath");
		exit(1);
	}

	for (int i=0; i<len; ++i) {
		if (desFileName[i]=='/')
			desFileName[i] = '_';
	}
	for (int i=len-1; i>=0; --i) {
		if (desFileName[i] == '.') {
			desFileName[i+1] = 't';
			desFileName[i+2] = 'm';
			desFileName[i+3] = 'p';
			desFileName[i+4] = '\0';
			break;
		}
	}

	FILE* fp = fopen(desFileName, "w");
	scanf("%d %d %lf %lf %lf %d %d %d", &workerN, &taskN, &dw, &dr, &vw, &slotN, &gridLength, &gridWidth);
	fprintf(fp, "%d %d %.4lf %.4lf %.4lf %d %d %d\n", workerN, taskN, dw, dr, vw, slotN, gridLength, gridWidth);
	const int itemN = workerN + taskN;
	triple_t t;
	vector<triple_t> triples;

	for (int i=0; i<itemN; ++i) {
		scanf("%d %d %d", &t.typeId, &t.begTime, &t.gridId);
		triples.push_back(t);
	}

	sort(triples.begin(), triples.end());

	for (int i=0; i<itemN; ++i) {
		fprintf(fp, "%d %d %d\n", triples[i].typeId, triples[i].begTime, triples[i].gridId);
	}

	fclose(fp);

	freopen(desFileName, "r", stdin);
}

int solve() {
	//const int timeBound = 3;
	scanf("%d %d %lf %lf %lf %d %d %d", &workerN, &taskN, &dw, &dr, &vw, &slotN, &gridLength, &gridWidth);
	const int itemN = workerN + taskN;
	int typeId, begTime, gridId;
	int preBegTime;
	int maxFlow = 0, tmpFlow;
	int i = 0;
	#ifdef LOCAL_DEBUG
	int workerCnt = workerN, taskCnt = taskN;
	#endif

	workers.clear();
	tasks.clear();
	while (i < itemN) {
		if (i == 0) {
			scanf("%d %d %d", &typeId, &begTime, &gridId);
			preBegTime = begTime;
			if (typeId == 0) {
				workers.push_back(worker_t(gridId, begTime, 1));
			} else {
				tasks.push_back(task_t(gridId, begTime, 1));
			}
			if (++i >= itemN) break;
		}
		while (i < itemN) {
			scanf("%d %d %d", &typeId, &begTime, &gridId);
			if (begTime > preBegTime+timeBound) {
				++i;
				break;
			}

			if (typeId == 0) {
				workers.push_back(worker_t(gridId, begTime, 1));
			} else {
				tasks.push_back(task_t(gridId, begTime, 1));
			}
			++i;
		}

		// calculate this network
		init_network();
		tmpFlow = Dinic();
		maxFlow += tmpFlow;

		#ifdef LOCAL_DEBUG
		printf("%d: workerN = %d, taskN = %d, E.size() = %d, tmpFlow = %d\n", preBegTime, workers.size(), tasks.size(), E.size(), tmpFlow);
		workerCnt -= workers.size();
		taskCnt -= tasks.size();
		#endif

		// clear current workers & tasks
		workers.clear();
		tasks.clear();
		if (typeId == 0) {
			workers.push_back(worker_t(gridId, begTime, 1));
		} else {
			tasks.push_back(task_t(gridId, begTime, 1));
		}
		preBegTime = begTime;
	}
	#ifdef LOCAL_DEBUG
	printf("workerCnt = %d, taskCnt = %d\n", workerCnt, taskCnt);
	assert(workerCnt == 0);
	assert(taskCnt == 0);
	#endif
	
	return maxFlow;
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	program_t begProg, endProg;

	if (argc > 1)
		freopen(argv[1], "r", stdin);
	if (argc > 2)
		sscanf(argv[2], "%d", &timeBound);
	else
		timeBound = 1;
	timeBound = max(0, timeBound-1);
	if (argc > 3)
		freopen(argv[3], "w", stdout);

	reSort(argv[1]);

	save_time(begProg);
	int nPairs = solve();
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("Sha %d %.4lf %d\n", nPairs, usedTime, usedMemory/1024);
	#else
	printf("Sha %d %.4lf\n", nPairs, usedTime);
	#endif
	
	return 0;
}