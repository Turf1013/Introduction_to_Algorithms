/* foward-backward spira */
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
node_t ND[maxe];
int dis[maxv];
bool inS[maxv], active[maxv], out[maxv];
int U[maxe], V[maxe], W[maxe];
int RV[maxe], RW[maxe];
int inxt[maxe], onxt[maxe], rnxt[maxe];
int ihead[maxv], ohead[maxv], rhead[maxv];
int nv, ne = 0, rne = 0, MID;


void addEdge(int u, int v, int w) {
	U[ne] = u;
	V[ne] = v;
	W[ne] = w;
	
	onxt[ne] = ohead[u];
	ohead[u] = ne;
	
	inxt[ne] = ihead[v];
	ihead[v] = ne;
	++ne;
}

void addReqEdge(int u, int v, int w) {
	RV[rne] = v;
	RW[rne] = w;
	rnxt[rne] = rhead[u];
	rhead[u] = rne++;
}

void forward(priority_queue<node_t>& Q, int u) {
	int v, w;
	
	if (out[u]) {
		int& k = ohead[u];
		
		if (k == -1) {
			out[u] = false;
		} else {
			v = V[k];
			w = W[k];
			if (w > 2*(MID - dis[u]))
				out[u] = false;
			k = onxt[k];
			active[u] = true;
		}
	}
	
	if (!out[u]) {
		int& k = rhead[u];
		
		if (k == -1) {
			active[u] = false;
		} else {
			v = RV[k];
			w = RW[k];
			k = rnxt[k];
			active[u] = true;
		}
	}
	
	if (active[u]) {
		Q.push(node_t(u, v, dis[u]+w));
	}
}

void backward(priority_queue<node_t>& Q, int v) {
	int& k = ihead[v];
	
	if (k != -1) {
		Q.push(node_t(k, v, W[k]));
		k = inxt[k];
	}
}

void request(priority_queue<node_t>& Q, int k) {
	int u = U[k], v = V[k], w = W[k];
	
	if (w <= 2*(MID - dis[u]))
		return ;
	
	// append(Req[u], v)
	addReqEdge(u, v, w);
	
	if (inS[u] && !active[u]) {
		forward(Q, u);
	}
}

void sssp(int s = 1) {
	priority_queue<node_t> P, Q;
	node_t nd;
	int u, v, k, n = 1;
	int mnp, mnq;
	int nth = (nv+1) >> 1;
	
	MID = INF;
	memset(dis, INF, sizeof(dis));
	memset(inS, false, sizeof(inS));
	memset(out, true, sizeof(out));
	dis[s] = 0;
	inS[s] = true;
	forward(P, s);
	
	while (n<nv && !P.empty()) {
		nd = P.top();
		P.pop();
		forward(P, nd.u);
		if (!inS[nd.v]) {
			++n;
			inS[nd.v] = true;
			dis[nd.v] = nd.w;
			forward(P, nd.v);
			if (n == nth) {
				MID = nd.w;
				rep(i, 1, nv+1)
					if (!inS[i])
						backward(Q, i);
			}
		}
		
		while (!Q.empty()) {
			mnp = P.empty() ? INF:P.top().w;
			mnq = Q.top().w;
			if (mnq >= 2*(mnp - MID))
				break;
			nd = Q.top();
			k = nd.u;
			Q.pop();
			if (!inS[nd.v]) {
				backward(Q, nd.v);
				request(P, k);
			}
		}
	}
}

void input() {
	int m;
	
	scanf("%d %d", &nv, &m);
	rep(i, 0, m)
		scanf("%d %d %d", &ND[i].u, &ND[i].v, &ND[i].w);
		
	// init
	ne = rne = 0;
	memset(ihead, -1, sizeof(ihead));
	memset(ohead, -1, sizeof(ohead));
	memset(rhead, -1, sizeof(rhead));
	sort(ND, ND+m);
	rep(i, 0, m)
		addEdge(ND[i].u, ND[i].v, ND[i].w);
}

void solve() {
	sssp();
	
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
