/*  */
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <climits>
#include <cctype>
#include <cassert>
#include <functional>
#include <iterator>
#include <iomanip>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,1024000")

#define sti				set<int>
#define stpii			set<pair<int, int> >
#define mpii			map<int,int>
#define vi				vector<int>
#define pii				pair<int,int>
#define vpii			vector<pair<int,int> >
#define rep(i, a, n) 	for (int i=a;i<n;++i)
#define per(i, a, n) 	for (int i=n-1;i>=a;--i)
#define clr				clear
#define pb 				push_back
#define mp 				make_pair
#define fir				first
#define sec				second
#define all(x) 			(x).begin(),(x).end()
#define SZ(x) 			((int)(x).size())
#define lson			l, mid, rt<<1
#define rson			mid+1, r, rt<<1|1

const int INF = 0x1f1f1f1f;
const int maxv = 205;
const int maxe = maxv * maxv + 5;
int V[maxe], W[maxe], nxt[maxe];
int head[maxv];
int dis[maxv];
bool visit[maxv];
int nv, ne = 0;

void addEdge(int u, int v, int w) {
	V[ne] = v;
	W[ne] = w;
	nxt[ne] = head[u];
	head[u] = ne++;
}

void spfa(int s = 1) {
	queue<int> Q;
	int u, v, k;

	memset(visit, false, sizeof(visit));
	memset(dis, INF, sizeof(dis));
	visit[s] = true;
	dis[s] = 0;
	Q.push(s);

	while (!Q.empty()) {
		u = Q.front();
		Q.pop();
		visit[u] = false;
		for (k=head[u]; k!=-1; k=nxt[k]) {
			v = V[k];
			if (dis[v] > dis[u]+W[k]) {
				dis[v] = dis[u] + W[k];
				if (!visit[v]) {
					visit[v] = true;
					Q.push(v);
				}
			}
		}
	}
}

void input() {
	int n, m;
	int u, v, w;

	scanf("%d %d", &n, &m);

	nv = n;
	ne = 0;
	memset(head, -1, sizeof(head));

	rep(i, 0, m) {
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
}

void solve() {
	spfa();

	rep(i, 1, nv+1) {
		printf("%d: %d\n", i, dis[i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	input();
	solve();

	#ifndef ONLINE_JUDGE
		printf("time = %d.\n", (int)clock());
	#endif

	return 0;
}
