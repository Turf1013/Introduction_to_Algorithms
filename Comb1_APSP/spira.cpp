/* Spira */
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

typedef struct node_t {
	int u, v, w;
	node_t() {}
	node_t(int u_, int v_, int w_):
		u(u_), v(v_), w(w_) {}
	friend bool operator< (const node_t& a, const node_t& b) {
		return a.w > b.w;
	}
} node_t;

const int INF = 0x1f1f1f1f;
const int maxv = 205;
const int maxe = maxv * maxv + 5;
int dis[maxv], inS[maxv];
int nv, ne;
int V[maxe], W[maxe], nxt[maxe];
int head[maxv], head_[maxv];
node_t ND[maxe];

void addEdge(int u, int v, int w) {
	V[ne] = v;
	W[ne] = w;
	nxt[ne] = head_[u];
	head_[u] = ne++;
}

void forward(priority_queue<node_t>& Q, int u) {
	int& k = head[u];

	if (k != -1) {
		Q.push(node_t(u, V[k], dis[u]+W[k]));
		k = nxt[k];
	}
}

void spira(int s = 1) {
	priority_queue<node_t> Q;
	node_t nd;

	memset(inS, false, sizeof(inS));
	memset(dis, INF, sizeof(dis));
	memcpy(head, head_, sizeof(head));
	inS[s] = true;
	dis[s] = 0;
	forward(Q, s);

	while (!Q.empty()) {
		nd = Q.top();
		Q.pop();
		forward(Q, nd.u);
		if (!inS[nd.v]) {
			inS[nd.v] = true;
			dis[nd.v] = nd.w;
			forward(Q, nd.v);
		}
	}
}

void input() {
	int m;

	scanf("%d %d", &nv, &m);
	rep(i, 0, m)
		scanf("%d %d %d", &ND[i].u, &ND[i].v, &ND[i].w);

	ne = 0;
	memset(head_, -1, sizeof(head_));
	
	// pre sort
	sort(ND, ND+m);
	rep(i, 0, m)
		addEdge(ND[i].u, ND[i].v, ND[i].w);
}

void solve() {
	spira();

	rep(i, 1, nv+1)
		printf("%d: %d\n", i, dis[i]);
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
