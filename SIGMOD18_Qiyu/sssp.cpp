/**
	\author: 	Trasier
	\date: 		2017.10.22
*/
#include <bits/stdc++.h>
using namespace std;

//#define LOCAL_DEBUG

const int maxn = 8e4;
struct edge_t {
	int v;
	double w;

	edge_t(int v=0., double w=0.):
		v(v), w(w) {}
};


const double inf = 1e25;
int nV, nE, st = 1;
double dis[maxn];
bool visit[maxn];
vector<edge_t> E[maxn];

void readInput() {
	double x, y;

	scanf("%d %d", &nV, &nE);
	for (int i=1; i<=nV; ++i) {
		scanf("%lf %lf", &x, &y);
	}

	int u, v, w;
	edge_t e;
	for (int i=1; i<=nE; ++i) {
		scanf("%d %d %lf", &u, &e.v, &e.w);
		E[u].push_back(e);
	}
}

void init() {
	for (int i=1; i<=nV; ++i) {
		dis[i] = inf;
		visit[i] = false;
	}
	for (int i=0; i<E[st].size(); ++i) {
		edge_t& e = E[st][i];
		dis[e.v] = min(dis[e.v], e.w);
	}
	dis[st] = 0;
	visit[st] = true;
}

void dijkstra() {
	double mn;
	set<pair<double,int> > st;
	int v;
	
	for (int j=1; j<=nV; ++j) {
		if (!visit[j])
			st.insert(make_pair(dis[j], j));
	}
	for (int i=1; i<nV; ++i) {
		mn = st.begin()->first;
		v = st.begin()->second;
		st.erase(st.begin());
		if (mn >= inf) break;
		
		visit[v] = true;
		
		int sz = E[v].size();
		for (int j=0; j<sz; ++j) {
			int k = E[v][j].v;
			double w = E[v][j].w;
			if (!visit[k] && dis[k]>mn+w) {
				st.erase(make_pair(dis[k], k));
				dis[k] = mn + w;
				st.insert(make_pair(dis[k], k));
			}
		}
	}
}

void dump() {
	for (int i=1; i<=nV; ++i)
		printf("%.6lf\n", dis[i]);
	putchar('\n');
	fflush(stdout);
}

void solve() {
	init();

	dijkstra();

	dump();
}

int main(int argc, char **argv) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}
	if (argc > 3) {
		sscanf(argv[3], "%d", &st);
	}
	
	#ifdef LOCAL_DEBUG
	clock_t begTime, endTime;
	begTime = clock();
	#endif
	
	readInput();
	solve();
	
	#ifdef LOCAL_DEBUG
	endTime = clock();
	double usedTime = (endTime - begTime) * 1000.0 / CLOCKS_PER_SEC ;
	fprintf(stdout, "time = %.2lfms.\n", usedTime);
	#endif

	return 0;
}
