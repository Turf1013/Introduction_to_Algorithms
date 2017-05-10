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
#define MAX_V 40000*144//not real num
#define MAX_n 100000//real num
using namespace std;
typedef vector<double> VD;
typedef vector<VD> VVD;
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
		if (from == to) { printf("%d", from);G[from].back().index++; }
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
int Sw[MAX_n], Lw[MAX_n], Sr[MAX_n], Lr[MAX_n];//real scenario
double f[288];
int t = 96, g = 540;//windownum gridnum
int gridh = 30, gridw = 18;//map height/width in grid(1.708*2.226)
double ve = 1,Dw,Dr;//velocity: grid num per window
int main()
{
	FILE *fp1 = fopen("rscenario.txt", "r");
	//n records num
	int res = 0,n,x,y;
	fscanf(fp1, "%d%d%lf%lf%lf%d%d%d", &x, &y, &Dw, &Dr, &ve, &t, &gridh, &gridw);
	g = gridh*gridw;
	for (int i = 0;i < t;i++)
	{
		f[i] = Dr;
	}
	n = x + y;
	x = y = 0;//x workernum y requestnum
	for (int i = 0;i<n;i++)
	{
		int t1, t2, t3, ind, loc;
		fscanf(fp1, "%d%d%d", &t1, &t2, &t3);//type window grid 
		if (t1 == 0)//worker
		{
			Sw[x] = t2;Lw[x++] = t3;
		}
		else//request
		{
			Sr[y] = t2;Lr[y++] = t3;
		}
	}
	//opt
	int a = clock();
	struct PushRelabel pr(x + y + 2);
	int source = x + y, terminal = source + 1;
	for (int i = 0;i<x;i++)
		pr.AddEdge(source, i, 1);
	for (int i = 0;i<y;i++)
		pr.AddEdge(i + x, terminal, 1);
	for (int i = 0;i<x;i++)
		for (int j = 0;j<y;j++)
		{
			int sw = Sw[i], sr = Sr[j], lw = Lw[i], lr = Lr[j];double dr = f[sr];//dr:function of sr
			int xw = lw%gridh, yw = lw / gridh, xr = lr%gridh, yr = lr / gridh;
			double s1 = sqrt((double)((xw - xr)*(xw - xr) + (yw - yr)*(yw - yr)));
			if (dr - s1 / ve - (sw - sr) >= 0 && sr - sw <= Dw)
				pr.AddEdge(i, x + j, 1);
		}
	res=pr.GetMaxFlow(source, terminal);
	int b = clock();


	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
	float memoryCost = pmc.PeakWorkingSetSize / 1024.0f / 1024.0f;
	FILE *fp4 = fopen("..//..//result.txt", "a");
	fprintf(fp4, "opt:%d %f %f\n", res, (double)(b - a) / 1000, memoryCost);
	return 0;
}

