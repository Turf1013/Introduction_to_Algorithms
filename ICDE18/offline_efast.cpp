/**
	1. offline version - Minimum Cost Maximum Flow
	2. \author: Trasier
	3. \date:   2017.9.14
	4. \complexity: O(n^3 U_max)
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "global.h"

#define LOCAL_DEBUG
#define LOG_ALLOCATE

#ifdef WATCH_MEM
#include "monitor.h"
int usedMemory = 0;
#endif

extern const double eps;
const int inf = 1<<30;
int K, t0;
int* compTime;
task_t* tasks;
worker_t* workers;
int *vlabels, *wcap;
int taskN = 0;
int workerN = 0;
double delta, epsilon;

void Schedule();
void del_Graph();
pair<double,int> solve_Graph();

void readInput(istream& fin) {
	fin >> K >> epsilon;
	delta = calcDelta(epsilon);
	readInput_Tasks(fin, taskN, tasks);
	readInput_Workers(fin, workerN, workers);
	compTime = new int[taskN];
	for (int i=0; i<taskN; ++i)
		compTime[i] = inf;
	vlabels = new int[taskN];
	double m = taskN * ceil(delta) / K;
	wcap = new int[(int)floor(m) + 5];
}

void FreeMem() {
	delete[] compTime;
	delete[] tasks;
	delete[] workers;
	delete[] vlabels;
}

int main(int argc, char **argv) {
	string execName("MCF");

	string srcFileName;
	if (argc > 1) {
		srcFileName = string(argv[1]);
	}
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	// step1: read Input
	if (srcFileName.empty()) {
		readInput(cin);
	} else {
		ifstream fin(srcFileName.c_str(), ios::in);
		if (!fin.is_open()) {
			fprintf(stderr, "FILE %s is invalid.\n", srcFileName.c_str());
			exit(1);
		}

		readInput(fin);
		fin.close();
	}

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish reading input.\n");
	#endif

	// step2: online execute
	clock_t begTime, endTime;
	begTime = clock();
	Schedule();
	endTime = clock();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish scheduling.\n");
	#endif

	// step3: output result
	int ans = calcResult(taskN, compTime);
	double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	#ifdef WATCH_MEM
	dumpResult(execName, ans, usedTime, usedMemory/1024.0);
	#else
	dumpResult(execName, ans, usedTime);
	#endif

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish dumping.\n");
	#endif

	// step4: free memory
	FreeMem();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish free memory.\n");
	#endif

	fflush(stdout);

	return 0;
}

struct edge_t {
	int v, f;
	double w;
	int nxt;
};

int st, ed;
int edgeN, vertexN, l;
int *head;
edge_t *E;
bool *visit;
double *dis;
int *pre, *ID;
double m;

void init_Graph(int bid, int eid) {
	int uN = 0, vN = 0;

	uN = eid - bid;
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s >= delta)
			continue;
		vlabels[vN++] = j;
	}

	edgeN = 2 * (uN*vN + uN + vN);
	vertexN = uN + vN + 2;
	st = vertexN - 2;
	ed = vertexN - 1;

	head = new int[vertexN];
	E = new edge_t[edgeN];
	visit = new bool[vertexN];
	dis = new double[vertexN];
	pre = new int[vertexN];
	ID = new int[vertexN];

	l = 0;
	for (int i=0; i<vertexN; ++i)
		head[i] = -1;
}

void del_Graph() {
	delete[] head;
	delete[] E;
	delete[] visit;
	delete[] dis;
	delete[] pre;
	delete[] ID;
}

void add_Edge(int u, int v, int f, double w) {
	E[l].v = v;
	E[l].f = f;
	E[l].w = w;
	E[l].nxt = head[u];
	head[u] = l++;

	E[l].v = u;
	E[l].f = 0;
	E[l].w = -w;
	E[l].nxt = head[v];
	head[v] = l++;
}

void build_Graph(int leftNum, int bid, int eid) {
	int uN = eid - bid, vN = leftNum;

	for (int j=0; j<uN; ++j) {
		add_Edge(st, j, K, 0);
	}
	for (int i=0; i<vN; ++i) {
		int taskId = vlabels[i];
		int c = (int)ceil(delta - tasks[taskId].s);
		add_Edge(uN+i, ed, c, 0);

		for (int j=0; j<uN; ++j) {
			double ut = calcUtility(tasks[taskId], workers[bid+j]);
			ut = min(ut, delta-tasks[taskId].s);
			add_Edge(j, uN+i, 1, -ut);
		}
	}
}

bool bfs() {
    queue<int> Q;
    int u, v, k;

	for (int i=0; i<vertexN; ++i) {
		dis[i] = inf;
		visit[i] = false;
	}
	visit[st] = true;
	dis[st] = 0;
	Q.push(st);

    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        visit[u] = false;
        for (k=head[u]; k!=-1; k=E[k].nxt) {
            v = E[k].v;
            if (E[k].f && dis[v]>dis[u]+E[k].w) {
                dis[v] = dis[u] + E[k].w;
                ID[v] = k;
                pre[v] = u;
                if (!visit[v]) {
                    visit[v] = true;
                    Q.push(v);
                }
            }
        }
    }

    return dis[ed] >= inf;
}

pair<double,int> solve_Graph(int& flow, double& cost) {
	int tmp;
    int u, v, k;

	flow = 0;
	cost = 0.0;
    while (true) {
        if (bfs())
            break;

        tmp = inf;
        for (v=ed, u=pre[v]; v!=st; v=u, u=pre[v]) {
            k = ID[v];
            tmp = min(E[k].f, tmp);
        }

        for (v=ed, u=pre[v]; v!=st; v=u, u=pre[v]) {
            k = ID[v];
            E[k].f -= tmp;
            E[k^1].f += tmp;
        }

		flow += tmp;
        cost += dis[ed] * tmp;
    }

    return make_pair(cost, flow);
}

void make_Assign(int& leftNum, int bid, int eid) {
	int uN = eid - bid, vN = leftNum;
	int *leftK = new int[uN];

	for (int i=0; i<uN; ++i) leftK[i] = K;

	#ifdef LOG_ALLOCATE
	vector<vector<int> > allocList;
	for (int i=0; i<uN; ++i)
		allocList.push_back(vector<int>());
	#endif
	for (int u=0; u<uN; ++u) {
		int workerId = bid + u;
		for (int k=head[u]; k!=-1; k=E[k].nxt) {
			if (k & 1) continue;
			if (E[k].f) continue;
			int taskId = vlabels[E[k].v - uN];
			double ut = calcUtility(tasks[taskId], workers[workerId]);
			tasks[taskId].s += ut;
			if (tasks[taskId].s >= delta) {
				compTime[taskId] = workerId;
			}
			--leftK[u];
			#ifdef LOG_ALLOCATE
			allocList[u].push_back(taskId);
			#endif
		}
	}
	#ifdef LOG_ALLOCATE
	printf("ALLOCATE FROM FLOW:\n");
	for (int i=0; i<uN; ++i) {
		vector<int>& vtask = allocList[i];
		printf("w%d:", bid+i);
		sort(vtask.begin(), vtask.end());
		assert(vtask.size() <= K);
		for (int j=0; j<vtask.size(); ++j) {
			printf(" t%d", vtask[j]+1);
		}
		putchar('\n');
		vtask.clear();
	}
	#endif

	#ifdef LOCAL_DEBUG
	for (int i=0; i<taskN; ++i)
		printf("%d: %.3lf\n", i, tasks[i].s);
	fflush(stdout);
	#endif

	priority_queue<pdi, vector<pdi>, greater<pdi> > Q;

	for (int u=0, workerId = bid+u; u<uN; ++u,++workerId) {
		if (leftK[u] == 0) continue;
		int szQ = leftK[u];
#ifdef LOCAL_DEBUG
		assert(szQ <= K && szQ >= 0);
#endif
		#ifdef LOG_ALLOCATE
		printf("w%d:", workerId);
		vector<int> vtask;
		#endif
		for (int k=head[u]; k!=-1; k=E[k].nxt) {
			if (k & 1) continue;
			if (E[k].f == 0) continue;
			int taskId = vlabels[E[k].v - uN];
			if (tasks[taskId].s >= delta)
				continue;
			double ut = calcUtility(tasks[taskId], workers[workerId]);
			// ut = min(ut, tasks[v].s);
			Q.push(make_pair(ut, taskId));
			if (Q.size() > szQ) Q.pop();
		}

		while (!Q.empty()) {
			pdi p = Q.top();
			Q.pop();
			int taskId = p.second;
			double ut = p.first;
			tasks[taskId].s += ut;
			if (tasks[taskId].s >= delta) {
				compTime[taskId] = workerId;
			}
			#ifdef LOG_ALLOCATE
			vtask.push_back(taskId);
			#endif
		}

		#ifdef LOG_ALLOCATE
		for (int j=vtask.size()-1; j>=0; --j)
			printf(" t%d", vtask[j]+1);
		putchar('\n');
		#endif
	}

	leftNum = 0;
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s >= delta)
			continue;
		++leftNum;
	}
}

void greedy_Assign(int& leftNum, int bid, int eid) {
	for (int j=bid; j<eid; ++j)
		wcap[j-bid] = K;

	typedef pair<pdi, int> pdii;
	priority_queue<pdii, vector<pdii>, greater<pdii> > Q;
	for (int i=0; i<taskN; ++i) {
		if (tasks[i].s >= delta)
			continue;
		for (int j=bid; j<eid; ++j) {
			double ut = calcUtility(tasks[i], workers[j]);
			if (ut > eps) {
				pdi p = make_pair(ut, j);
				Q.push(make_pair(p, i));
			}
		}
	}
	while (!Q.empty()) {
		pdii p = Q.top();
		Q.pop();
		int taskId = p.second, workerId = p.first.second;
		if (tasks[taskId].s>=delta || wcap[workerId]<=0)
			continue;
		double ut = p.first.first;
		tasks[taskId].s += ut;
		if (tasks[taskId].s >= delta) {
			compTime[taskId] = workerId;
			--leftNum;
		}
	}
}

void Schedule() {
	double m = taskN * ceil(delta) / K;
	int leftNum = taskN, flow;
	double cost;

	if (workerN <= floor(2*m)) {
		int bid = 0, eid = workerN;

		init_Graph(bid, eid);
		build_Graph(leftNum, bid, eid);
		solve_Graph(flow, cost);
		make_Assign(leftNum, bid, eid);
		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif

		del_Graph();
		return ;
	}
	{// first round MinCostFlow
		int bid = 0, eid = floor(2*m);
		init_Graph(bid, eid);
		build_Graph(leftNum, bid, eid);
		solve_Graph(flow, cost);
		make_Assign(leftNum, bid, eid);
		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif

		del_Graph();
	}
	{// batch greedy
		int batchSize = floor(m);
		for (int bid=floor(2*m),eid; leftNum>0&&bid<workerN; bid=eid) {
			eid = min(workerN, bid+batchSize);

			greedy_Assign(leftNum, bid, eid);
		}
	}
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
}
