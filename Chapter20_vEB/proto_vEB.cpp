/* proto_vEB */
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

typedef struct proto_vEB {
	
	#define DEBUG
	
	typedef struct node {
		int u;
		int A[2];
		int n;
		node *summary;
		vector<node*> cluster;
	} node;
	
	static const int maxn = 1<<18;
	static const int maxnode = maxn;
	node nd[maxnode];
	node* rt;
	int l;
	map<int,int> sq2;
	map<int,int> Bit2;
	
	proto_vEB() {
		Init();
	}
	
	void Init() {
		int i, j;
		
		for (i=1,j=i*i; j<=maxn; i<<=1,j<<=2) {
			sq2[j] = i;
		}
		
		for (i=1,j=1<<i; j<=maxn; ++i,j<<=1) {
			Bit2[j] = i;
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
		nd[l].n = 0;
		nd[l].A[0] = nd[l].A[1] = 0;
		nd[l].summary = NULL;
		nd[l].cluster.clr();
		++l;
		return nd + (l - 1);
	}
	
	node *Build(int u) {
		node* ret = newNode(u);
		
		if (u == 2) 
			return ret;
		
		#ifdef DEBUG
			assert(sq2.find(u) != sq2.end());
		#endif
		int ncluster = sq2[u];
		node *p;
		
		ret->summary = Build(ncluster);
		rep(i, 0, ncluster) {
			p = Build(ncluster);
			ret->cluster.pb(p);
		}
		
		return ret;
	}
	
	bool Member(node *rt, int x) {
		if (rt->u == 2) {
			return rt->A[x];
		}
		
		int ncluster = sq2[rt->u];
		int l = Bit2[ncluster];
		int mask = (1<<l) - 1;
		
		#ifdef DEBUG
			assert(x>>l < ncluster);
		#endif
		
		return Member(rt->cluster[x>>l], x&mask);
	}
	
	int Minimum(node* rt) {
		if (rt->u == 2) {
			if (rt->A[0] == 1)
				return 0;
			else if (rt->A[1] == 1)
				return 1;
			else
				return -1;
		}
		
		int mn_cluster = Minimum(rt->summary);
		if (mn_cluster < 0)
			return -1;
		
		int ncluster = sq2[rt->u];
		int l = Bit2[ncluster];
		int offset = Minimum(rt->cluster[mn_cluster]);
		
		return (mn_cluster<<l) | offset;
	}
	
	int Maximum(node* rt) {
		if (rt->u == 2) {
			if (rt->A[1] == 1)
				return 1;
			else if (rt->A[0] == 1)
				return 0;
			else
				return -1;
		}
		
		int mx_cluster = Maximum(rt->summary);
		if (mx_cluster < 0)
			return -1;
		
		int ncluster = sq2[rt->u];
		int l = Bit2[ncluster];
		int offset = Maximum(rt->cluster[mx_cluster]);
		
		return (mx_cluster<<l) | offset;
	}
	
	int Successor(node* rt, int x) {
		if (rt->u == 2) {
			if (x==0 && rt->A[1])
				return 1;
			return -1;
		}
		
		int ncluster = sq2[rt->u];
		int l = Bit2[ncluster];
		int mask = (1<<l) - 1;
		
		#ifdef DEBUG
			assert(x>>l < ncluster);
		#endif
		
		int offset = Successor(rt->cluster[x>>l], x&mask);
		
		if (offset >= 0)
			return (x ^ (x&mask)) | offset;
		
		int succ_cluster = Successor(rt->summary, x>>l);
		
		if (succ_cluster < 0)
			return -1;
		
		offset = Minimum(rt->cluster[succ_cluster]);
		
		return offset<0 ? -1 : (succ_cluster<<l) | offset;
	}
	
	int Predecessor(node* rt, int x) {
		if (rt->u == 2) {
			if (x==1 && rt->A[0])
				return 0;
			return -1;
		}
		
		int ncluster = sq2[rt->u];
		int l = Bit2[ncluster];
		int mask = (1<<l) - 1;
		
		#ifdef DEBUG
			assert(x>>l < ncluster);
		#endif
		
		int offset = Predecessor(rt->cluster[x>>l], x&mask);
		
		if (offset >= 0)
			return (x ^ (x&mask)) | offset;
		
		int pred_cluster = Predecessor(rt->summary, x>>l);
		
		if (pred_cluster < 0)
			return -1;
		
		offset = Maximum(rt->cluster[pred_cluster]);
		
		return offset<0 ? -1 : (pred_cluster<<l) | offset;
	}
	
	void Insert(node* rt, int x) {
		if (rt->u == 2) {
			rt->A[x] = 1;
			return ;
		}
		
		int ncluster = sq2[rt->u];
		int l = Bit2[ncluster];
		int mask = (1<<l) - 1;
		
		Insert(rt->cluster[x>>l], x&mask);
		Insert(rt->summary, x>>l);
	}
	
	void Delete(node* rt, int x) {
		if (rt->u == 2) {
			if (rt->A[x]) {
				--rt->n;
				rt->A[x] = 0;
			}
			return ;
		}
		
		int ncluster = sq2[rt->u];
		int l = Bit2[ncluster];
		int mask = (1<<l) - 1;
		
		Delete(rt->cluster[x>>l], x&mask);
		if (rt->cluster[x>>l]->n == 0)
			Delete(rt->summary, x>>l);
	}
	
} proto_vEB;

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif
	

	
	#ifndef ONLINE_JUDGE
		printf("time = %d.\n", (int)clock());
	#endif
	
	return 0;
}
