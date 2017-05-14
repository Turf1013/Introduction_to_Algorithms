#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <set>
#include <iomanip>
#include <cmath>
#include <vector>
#define MAX_V 40000*144//not real num
#define MAX_n 100005//real num
using namespace std;

#include "monitor.h"

typedef long long LL;
struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};
struct PushRelabel {
	int N;
	vector<vector<Edge> > G;
	vector<LL> excess;
	vector<int> dist, active, count;
	queue<int> Q;
	PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2 * N) {}
	void AddEdge(int from, int to, int cap) {
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to) G[from].back().index++;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	}
	void Enqueue(int v) {
		if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
	}
	void Push(Edge &e) {
		int amt = int(min(excess[e.from], LL(e.cap - e.flow)));
		if (dist[e.from] <= dist[e.to] || amt == 0) return;
		e.flow += amt;
		G[e.to][e.index].flow -= amt;
		excess[e.to] += amt;
		excess[e.from] -= amt;
		Enqueue(e.to);
	}
	void Gap(int k) {
		for (int v = 0; v < N; v++) {
			if (dist[v] < k) continue;
			count[dist[v]]--;
			dist[v] = max(dist[v], N + 1);
			count[dist[v]]++;
			Enqueue(v);
		}
	}
	void Relabel(int v) {
		count[dist[v]]--;
		dist[v] = 2 * N;
		for (int i = 0; i < G[v].size(); i++)
			if (G[v][i].cap - G[v][i].flow > 0)
				dist[v] = min(dist[v], dist[G[v][i].to] + 1);
		count[dist[v]]++;
		Enqueue(v);
	}
	void Discharge(int v) {
		for (int i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
		if (excess[v] > 0) {
			if (count[dist[v]] == 1)
				Gap(dist[v]);
			else
				Relabel(v);
		}
	}
	LL GetMaxFlow(int s, int t) {
		count[0] = N - 1;
		count[N] = 1;
		dist[s] = N;
		active[s] = active[t] = true;
		for (int i = 0; i < G[s].size(); i++) {
			excess[s] += G[s][i].cap;
			Push(G[s][i]);
		}
		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif   
		while (!Q.empty()) {
			int v = Q.front();
			Q.pop();
			active[v] = false;
			Discharge(v);
		}
		LL totflow = 0;
		for (int i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
		return totflow;
	}
};
int W[MAX_V], R[MAX_V],  wlb[MAX_V], rlb[MAX_V];//worker occupied request occupied
int Sw[MAX_n], Lw[MAX_n], Sr[MAX_n], Lr[MAX_n];//real scenario
int SW[MAX_n], LW[MAX_n], SR[MAX_n], LR[MAX_n];//offline guide
int wo[MAX_V], re[MAX_V];
double f[288];
int Lm[MAX_n], Rm[MAX_n];
int t = 96, g = 540;//windownum gridnum
int gridh = 30, gridw = 18;//map height/width in grid(1.708*2.226)
double Dw,Dr,ve = 1;//velocity: grid num per window
bool used[MAX_n];
int main(int argc, char **argv)
{
	int x, y;
	FILE *fp0 = fopen(argv[1], "r");
	FILE *fp2 = fopen(argv[2], "r");
	fscanf(fp0, "%d%d%lf%lf%lf%d%d%d", &x, &y, &Dw, &Dr, &ve, &t, &gridh, &gridw);
	g = gridh*gridw;
	for (int i = 0;i<t;i++)
		f[i] = Dr;//deadline
	//printf("deadline=%f,velocity=%f\n", f[0], ve);
	x = 0, y = 0;//Workerset size Request size
	for (int i = 0;i<t*g;i++)
	{
		int t1, t2, t3, t4;//window grid worker request
		fscanf(fp0, "%d%d%d%d", &t1, &t2, &t3, &t4);
		int p = x, q = y;
		x += t3, y += t4;
		for (int j = p;j<x;j++)SW[j] = t1, LW[j] = t2;
		for (int j = q;j<y;j++)SR[j] = t1, LR[j] = t2;
		int ind = t1*g + t2;
		W[ind] = x;R[ind] = y;
		if (ind != 0)wlb[ind] = W[ind - 1], rlb[ind] = R[ind - 1];
	}
	//printf("%d %d %d\n", x + y, x, y);
	memset(Lm, -1, sizeof(Lm));
	memset(Rm, -1, sizeof(Rm));
	int p, q, n;
	while (fscanf(fp2, "%d%d", &p, &q) == 2)
	{
		Lm[p] = q;Rm[q] = p;
	}
	/*for(int i=0;i<t*g;i++)
	printf("%d %d\n",W[i],R[i]);*/

	struct PushRelabel pr(t*g * 2 + 2);
	int source = t*g * 2, terminal = source + 1;
	for (int i = 0;i<x;i++)
		if (Lm[i] != -1)
		{
			int j = Lm[i];
			pr.AddEdge(SW[i] * g + LW[i], t*g + SR[j] * g + LR[j], 100000);
		}
    #ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif

	program_t begProg, endProg;
	save_time(begProg);

	FILE *fp1 = fopen(argv[3], "r");
	//n records num
	int res = 0;
	fscanf(fp1, "%d%d%lf%lf%lf%d%d%d", &x, &y, &Dw, &Dr, &ve, &t, &gridh, &gridw);
	n = x + y;
	x = y = 0;//x workernum y requestnum
	for (int i = 0;i<n;i++)
	{
		int t1, t2, t3, ind, loc;
		fscanf(fp1, "%d%d%d", &t1, &t2, &t3);//type window grid 
		ind = t2*g + t3;
		if (t1 == 0)//worker
		{
			Sw[x] = t2;Lw[x++] = t3;
			wo[ind]++;
		}
		else//request
		{
			Sr[y] = t2;Lr[y++] = t3;
			re[ind]++;
		}
	}//printf("%d %d\n",x,y);

	for (int i = 0;i<t*g;i++)
		pr.AddEdge(source, i, wo[i]);
	for (int i = 0;i<t*g;i++)
		pr.AddEdge(i + t*g, terminal, re[i]);

	res = pr.GetMaxFlow(source, terminal);
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
	save_time(endProg);

	if (argc > 4)
		freopen(argv[4], "w", stdout);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("OPreTo %d %.4lf %.4lf\n", res, usedTime, usedMemory/1024.0);
	#else
	printf("OPreTo %d %.4lf\n", res, usedTime);
	#endif

	return 0;
}

