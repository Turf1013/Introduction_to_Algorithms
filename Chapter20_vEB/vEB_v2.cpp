/* vEB */
#include <iostream>
#include <sstream>
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

#define INF	0x3f3f3f3f

typedef struct vEB {

	#define DEBUG

	typedef struct node {
		int u;
		int mn, mx;
		node *summary;
		vector<node*> cluster;
	} node;

	static const int maxn = 1e7+5;
	static const int maxnode = maxn * 4;
	node nd[maxnode];
	vi base2;
	int l;

	vEB() {
		for (int i=0; i<=18; ++i) {
			base2.pb(1<<i);
		}
	}

	void init() {
		l = 0;
	}

	node *newNode(int u) {
		#ifdef DEBUG
			assert(l < maxnode);
		#endif
		nd[l].u = u;
		nd[l].mn = INF;
		nd[l].mx = -INF;
		nd[l].summary = NULL;
		nd[l].cluster.clr();
		++l;
		return nd + (l - 1);
	}

	node *Build(int u) {
		node* ret = newNode(u);

		if (u == 2)
			return ret;

		int ncluster = ceil(sqrt((double) u));
		node *p;

		ret->summary = Build(ncluster);
		rep(i, 0, ncluster) {
			p = Build(ncluster);
			ret->cluster.pb(p);
		}

		return ret;
	}

	bool Member(node *rt, int x) {
		if (x==rt->mn || x==rt->mx)
			return true;

		if (rt->u == 2)
			return false;

		int ncluster = SZ(rt->cluster);

		return Member(rt->cluster[x/ncluster], x%ncluster);
	}

	int Minimum(node* rt) {
		return rt->mn;
	}

	int Maximum(node* rt) {
		return rt->mx;
	}

	int Successor(node* rt, int x) {
		if (rt->u == 2) {
			if (x==0 && rt->mx==1)
				return 1;
			return -1;
		}

		if (rt->mn!=INF && x<rt->mn)
			return rt->mn;

		int ncluster = SZ(rt->cluster);
		int highx = x/ncluster;
		int lowx = x%ncluster;

		int mx_low = Maximum(rt->cluster[highx]);

		if (mx_low!=-INF && lowx<mx_low) {
			int offset = Successor(rt->cluster[highx], lowx);
			return (x - lowx) + offset;
		}

		int succ_cluster = Successor(rt->summary, highx);

		if (succ_cluster < 0)
			return -1;

		int offset = Minimum(rt->cluster[succ_cluster]);

		return offset<0 ? -1 : succ_cluster*ncluster + offset;
	}

	int Predecessor(node* rt, int x) {
		if (rt->u == 2) {
			if (x==1 && rt->mn==0)
				return 0;
			return -1;
		}

		if (rt->mx!=-INF && x>rt->mx)
			return rt->mx;

		int ncluster = SZ(rt->cluster);
		int highx = x/ncluster;
		int lowx = x%ncluster;

		int mn_low = Minimum(rt->cluster[highx]);

		if (mn_low!=INF && lowx>mn_low) {
			int offset = Predecessor(rt->cluster[highx], lowx);
			return (x - lowx) + offset;
		}

		int pred_cluster = Predecessor(rt->summary, highx);

		if (pred_cluster < 0) {
			/* Introduction to Algorithms */
			/*
			* need to consider mn, different from mx.
			*/
			if (rt->mn!=INF && x>rt->mn)
				return rt->mn;
			return -1;
		}

		int offset = Maximum(rt->cluster[pred_cluster]);

		return offset<0 ? -1 : pred_cluster*ncluster + offset;
	}

	void Empty_Insert(node* rt, int x) {
		rt->mn = rt->mx = x;
	}

	void Insert(node* rt, int x) {
		if (rt->mn == INF) {
			Empty_Insert(rt, x);
			return ;
		}

		if (x < rt->mn)
			swap(x, rt->mn);

		int ncluster = SZ(rt->cluster);

		if (rt->u > 2) {
			int highx = x / ncluster;
			int lowx = x % ncluster;
			if (Minimum(rt->cluster[highx]) == INF) {
				Insert(rt->summary, highx);
				Empty_Insert(rt->cluster[highx], lowx);
			} else {
				Insert(rt->cluster[highx], lowx);
			}
		}

		rt->mx = max(rt->mx, x);
	}

	void Delete(node* rt, int x) {
		if (rt->mn == rt->mx) {
			rt->mn = INF;
			rt->mx = -INF;
			return ;
		}

		if (rt->u == 2) {
			if (x == 0)
				rt->mn = 1;
			else
				rt->mn = 0;	// may useless
			rt->mx = rt->mn;
			return ;
		}

		int ncluster = SZ(rt->cluster);

		if (x == rt->mn) {
			int fir_cluster = Minimum(rt->summary);
			x = fir_cluster * ncluster + Minimum(rt->cluster[fir_cluster]);
			rt->mn = x;
		}

		int highx = x / ncluster;
		int lowx = x % ncluster;
		Delete(rt->cluster[highx], lowx);

		if (Minimum(rt->cluster[highx]) == INF) {
			Delete(rt->summary, highx);
			if (x == rt->mx) {
				int summary_mx = Maximum(rt->summary);
				if (summary_mx == -INF) {
					rt->mx = rt->mn;
				} else {
					rt->mx = summary_mx*ncluster + Maximum(rt->cluster[summary_mx]);
				}
			}
		} else if (x == rt->mx) {
			rt->mx = (x - lowx) + Maximum(rt->cluster[highx]);
		}
	}

} vEB;

vEB veb;
int n, m;
int tot = 0;

void solve() {
	int x;
	char op[12];
	vEB::node *rt;

	veb.init();
	rt = veb.Build(n);

	while (m--) {
		scanf("%s", op);
		#ifdef DEBUG
		 if (++ tot == 50) {
			 puts(op);
			 fflush(stdout);
		 }
		#endif
		if (op[0] == 'M') {
			if (op[1] == 'a') {
				int mx = veb.Maximum(rt);
				printf("%d\n", mx==-INF ? -1:mx);
			} else if (op[1] == 'i') {
				int mn = veb.Minimum(rt);
				printf("%d\n", mn==INF ? -1:mn);
			} else {
				scanf("%d", &x);
				puts(veb.Member(rt, x) ? "Yes" : "No");
			}
		} else if (op[0] == 'P') {
			scanf("%d", &x);
			printf("%d\n", veb.Predecessor(rt, x));
		} else if (op[0] == 'S') {
			scanf("%d", &x);
			printf("%d\n", veb.Successor(rt, x));
		} else if (op[0] == 'I') {
			scanf("%d", &x);
			if (veb.Member(rt, x))
				puts("No");
			else {
				puts("Yes");
				veb.Insert(rt, x);
			}
		} else {
			scanf("%d", &x);
			if (veb.Member(rt, x)) {
				puts("Yes");
				veb.Delete(rt, x);
			} else {
				puts("No");
			}
		}

		fflush(stdout);
	}
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	int t;

	scanf("%d", &t);
	rep(tt, 1, t+1) {
		scanf("%d %d", &n, &m);
		printf("Case #%d:\n", tt);
		solve();
	}

	#ifndef ONLINE_JUDGE
		printf("time = %d.\n", (int)clock());
	#endif

	return 0;
}

