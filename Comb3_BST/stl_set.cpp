/* set */
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <deque>
#include <bitset>
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
#define INF				0x3f3f3f3f
#define mset(a, val)	memset(a, (val), sizeof(a))

set<int> st;

void Delete(int x) {
	st.erase(x);
}

void Insert(int x) {
	st.insert(x);
}

bool Member(int x) {
	return st.count(x) > 0;
}

int Maximum() {
	return st.empty() ? -INF : *st.rbegin();
}

int Minimum() {
	return st.empty() ? INF : *st.begin();
}

int Predecessor(int x) {
	sti::iterator iter = st.lower_bound(x);
	return iter==st.begin() ? -INF : *(--iter);
}

int Successor(int x) {
	sti::iterator iter = st.upper_bound(x);
	return iter==st.end() ? INF : *iter;
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("in_e3.txt", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	int t;
	int n, m, x;
	char op[12];

	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		st.clr();
		rep(i, 0, m) {
			scanf("%s", op);
			if (op[0] == 'M') {
				if (op[1] == 'a') {
					int mx = Maximum();
					printf("%d\n", mx==-INF ? -1:mx);
				} else if (op[1] == 'i') {
					int mn = Minimum();
					printf("%d\n", mn==INF ? -1:mn);
				} else {
					scanf("%d", &x);
					puts(Member(x) ? "Yes" : "No");
				}
			} else if (op[0] == 'P') {
				scanf("%d", &x);
				printf("%d\n", Predecessor(x));
			} else if (op[0] == 'S') {
				scanf("%d", &x);
				printf("%d\n", Successor(x));
			} else if (op[0] == 'I') {
				scanf("%d", &x);
				if (Member(x))
					puts("No");
				else {
					puts("Yes");
					Insert(x);
				}
			} else {
				scanf("%d", &x);
				if (Member(x)) {
					puts("Yes");
					Delete(x);
				} else {
					puts("No");
				}
			}
		}
	}

	#ifndef ONLINE_JUDGE
		printf("time = %ldms.\n", clock());
	#endif

	return 0;
}


/* treap */
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <deque>
#include <bitset>
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
#define INF				0x3f3f3f3f
#define mset(a, val)	memset(a, (val), sizeof(a))

typedef struct node {
	node *ch[2];
	int r, v;

	node() {
		ch[0] = ch[1] = NULL;
		r = rand();
	}

	node(int _v) {
		v = _v;
		ch[0] = ch[1] = NULL;
		r = rand();
	}

	int cmp(int _v) {
		if (v == _v)	return -1;
		return _v < v ? 0:1;
	}

} node;

void Rotate(node* &o, int d) {
	node *k = o->ch[d^1];
	o->ch[d^1] = k->ch[d];
	k->ch[d] = o;
	o = k;
}

void Insert(node* &o, int v) {
	if (o == NULL) {
		o = new node(v);
	} else {
		int d = o->cmp(v);
		if (d == -1)
			return ;

		Insert(o->ch[d], v);
		if (o->ch[d]->r > o->r)
			Rotate(o, d^1);
	}
}

void Erase(node* &o, int v) {
	int d = o->cmp(v);

	if (d == -1) {
		if (o->ch[0] == NULL)
			o = o->ch[1];
		else if (o->ch[1] == NULL)
			o = o->ch[0];
		else {
			int d2 =  (o->ch[0]->r > o->ch[1]->r) ? 1:0;
			Rotate(o, d2);
			Erase(o->ch[d2], v);
		}
	} else {
		Erase(o->ch[d], v);
	}
}

bool Find(node *o, int v) {
	while (o != NULL) {
		int d = o->cmp(v);
		if (d == -1)
			return true;
		o = o->ch[d];
	}
	return false;
}

void Delete(node *rt) {
	if (rt->ch[0])	Delete(rt->ch[0]);
	if (rt->ch[1])	Delete(rt->ch[1]);
	delete rt;
}

node *rt = NULL;

void Insert(int x) {
	Insert(rt, x);
}

int Maximum() {
	node *o = rt;
	int ret = -INF;

	while (o != NULL) {
		ret = o->v;
		o = o->ch[1];
	}
	return ret;
}

int Minimum() {
	node *o = rt;
	int ret = INF;

	while (o != NULL) {
		ret = o->v;
		o = o->ch[0];
	}
	return ret;
}

bool Member(int x) {
	return Find(rt, x);
}

int Predecessor(node *o, int x) {
	if (o == NULL)	return -INF;

	int d = o->cmp(x);
	if (d <= 0) {
		return Predecessor(o->ch[0], x);
	} else {
		int tmp = Predecessor(o->ch[1], x);
		if (x-tmp < x-o->v)
			return tmp;
		else
			return o->v;
	}
}

int Predecessor(int x) {
	return Predecessor(rt, x);
}

int Successor(node *o, int x) {
	if (o == NULL)	return INF;

	int d = o->cmp(x);
	if (d) {
		return Successor(o->ch[1], x);
	} else {
		int tmp = Successor(o->ch[0], x);
		if (tmp-x < o->v-x)
			return tmp;
		else
			return o->v;
	}
}

int Successor(int x) {
	return Successor(rt, x);
}

void Erase(int x) {
	Erase(rt, x);
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("in_e7.txt", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	int t;
	int n, m, x;
	char op[12];

	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		if (rt)	{
			Delete(rt);
			rt = NULL;
		}
		rep(i, 0, m) {
			scanf("%s", op);
			if (op[0] == 'M') {
				if (op[1] == 'a') {
					int mx = Maximum();
					printf("%d\n", mx==-INF ? -1:mx);
				} else if (op[1] == 'i') {
					int mn = Minimum();
					printf("%d\n", mn==INF ? -1:mn);
				} else {
					scanf("%d", &x);
					puts(Member(x) ? "Yes" : "No");
				}
			} else if (op[0] == 'P') {
				scanf("%d", &x);
				printf("%d\n", Predecessor(x));
			} else if (op[0] == 'S') {
				scanf("%d", &x);
				printf("%d\n", Successor(x));
			} else if (op[0] == 'I') {
				scanf("%d", &x);
				if (Member(x))
					puts("No");
				else {
					puts("Yes");
					Insert(x);
				}
			} else {
				scanf("%d", &x);
				if (Member(x)) {
					puts("Yes");
					Erase(x);
				} else {
					puts("No");
				}
			}
		}
	}

	#ifndef ONLINE_JUDGE
		printf("time = %ldms.\n", clock());
	#endif

	return 0;
}