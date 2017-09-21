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

const int inf = 1<<29;
int Umax;
int K, t0;
int* compTime;
task_t* tasks;
worker_t* workers;
int taskN;
int workerN;
double delta;

void Schedule();
void del_Graph();
pair<double,int> solve_Graph();

void readInput(istream& fin) {
	fin >> K >> delta >> Umax;
	readInput_Tasks(fin, taskN, tasks);
	readInput_Workers(fin, workerN, workers);
	compTime = new int[taskN];
	for (int i=0; i<taskN; ++i)
		compTime[i] = inf;
}

void FreeMem() {
	delete[] compTime;
	delete[] tasks;
	delete[] workers;
}

int main(int argc, char **argv) {
	string execName("offline2");
	
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
			fprintf(stderr, "FILE %s is invalid.", srcFileName.c_str());
			exit(1);
		}	
		
		readInput(fin);
		fin.close();
	}
	
	// step2: online execute
	Schedule();
	
	// step3: output result
	int ans = calcResult(taskN, compTime);
	dumpResult(execName, ans);
	
	// step4: free memory
	FreeMem();
	
	return 0;
}

struct edge_t {
	int v, f, w;
	int nxt;
};

int st, ed;
int edgeN, vertexN, l;
int *head;
edge_t *E;
bool *visit;
double *dis;
int *pre, *ID;

void init_Graph() {
	int uN = 0, vN = 0;
	
	t0 = (int)ceil(taskN * floor(delta*1.0/Umax) / K);
	uN = t0;
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s == 0)
			continue;
		++vN;
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
}

void del_Graph() {
	delete[] head;
	delete[] E;
	delete[] visit;
	delete[] dis;
	delete[] pre;
	delete[] ID;
}

void add_Edge(int u, int v, int f, int w) {
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

void build_Graph(int leftNum, int rid) {
	int uN = min(t0, workerN-t0*rid), vN = leftNum;
	l = 0;
	
	for (int i=t0*rid,j=0; j<uN; ++j,++i) {
		add_Edge(st, j, K, 0);
	}
	for (int i=0; i<taskN; ++i) {
		if (tasks[i].s == 0)
			continue;
		int c = (int)ceil(tasks[i].s / Umax);
		add_Edge(uN+i, ed, c, 0);
		
		for (int j=0,k=t0*rid; j<uN; ++j,++k) {
			double u = calcUtility(tasks[i], workers[k]);
			double r = min(u, tasks[i].s);
			add_Edge(j, uN+i, 1, -r);
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

void make_Assign(int& leftNum, int rid) {
	double ut;
	int workerId, taskId;
	int uN = min(t0, workerN-t0*rid), vN = leftNum;
	priority_queue<pair<double,pii>, vector<pair<double,pii> >, greater<pair<double,pii> > > Q;
	
	for (int u=0,j=t0*rid; u<uN; ++u,++j) {
		for (int k=head[u]; k!=-1; k=E[k].f) {
			if (k & 1) continue;
			if (E[k].f) continue;
			int v = E[k].v - uN;
			ut = calcUtility(tasks[v], workers[j]);
			Q.push(make_pair(ut, make_pair(v, j)));
			// if (tasks[v].s <= ut) {
				// tasks[v].s = 0;
				// compTime[v] = j;
			// } else {
				// tasks[v].s -= ut;
			// }
		}
	}
	
	set<pdi,greater<pdi> > *st = new set<pdi,greater<pdi> >[uN];
	int* cnt = new int[uN];
	for (int i=0; i<uN; ++i) {
		st[i] = set<pdi,greater<pdi> >();
		cnt[i] = K;
	}
	
	for (int u=0,j=t0*rid; u<uN; ++u,++j) {
		for (int i=0; i<taskN; ++i) {
			if (tasks[i].s == 0)
				continue;
			double ut = calcUtility(tasks[i], workers[j]);
			st[u].insert(make_pair(ut, i));
		}
	}
	
	while (!Q.empty()) {
		pair<double,pair<int,int> > p = Q.top();
		Q.pop();
		ut = p.first;
		taskId = p.second.first, workerId = p.second.second - rid*t0;
		if (st[workerId].begin()->first <= ut) {
			st[workerId].erase(make_pair(ut, taskId));
		} else {
			ut = st[workerId].begin()->first;
			taskId = st[workerId].begin()->second;
			st[workerId].erase(st[workerId].begin());
		}
		while (!st[workerId].empty() && tasks[taskId].s==0) {
			ut = st[workerId].begin()->first;
			taskId = st[workerId].begin()->second;
			st[workerId].erase(st[workerId].begin());
		}
		if (tasks[taskId].s == 0) continue;
		
		if (tasks[taskId].s <= ut) {
			tasks[taskId].s = 0;
			compTime[taskId] = workerId + t0*rid;
		} else {
			tasks[taskId].s -= ut;
		}
		--cnt[workerId];
	}
	
	for (int u=0,j=t0*rid; u<uN; ++u,++j) {
		workerId = u;
		while (cnt[workerId]>0 && !st[workerId].empty()) {
			ut = st[workerId].begin()->first;
			taskId = st[workerId].begin()->second;
			st[workerId].erase(st[workerId].begin());
			if (tasks[taskId].s != 0) {			
				if (tasks[taskId].s <= ut) {
					tasks[taskId].s = 0;
					compTime[taskId] = workerId + t0*rid;
				} else {
					tasks[taskId].s -= ut;
				}
				--cnt[workerId];
			}
		}
	}
	
	leftNum = 0;
	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s == 0)
			continue;
		++leftNum;
	}
}

void Schedule() {
	int leftNum = taskN, flow;
	double cost;
	
	init_Graph();
	
	for (int rid=0; rid*t0<workerN; ++rid) {
		build_Graph(leftNum, rid);
		solve_Graph(flow, cost);
		make_Assign(leftNum, rid);
	}
	
	del_Graph();
}
