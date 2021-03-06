/* splay v1.0 */
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
#define INF				0x3f3f3f3f

// #define DEBUG

typedef struct Node {
	int v;
	Node *p, *ch[2];

	Node() {}
	Node(int v, Node *p=NULL):v(v),p(p) {
		ch[0] = ch[1] = NULL;
	}

	int cmp(int _v) {
		return 	_v==v ? -1 :
				_v <v ?  0 : 1;
	}

} Node;

typedef pair<Node*, Node*>	pnn;

#define g(x) 			(x)->p->p
#define p(x) 			(x)->p
#define left(x)			(x)->ch[0]
#define right(x)		(x)->ch[1]
#define rotate_left(x)	rotate(x, 0)
#define rotate_right(x)	rotate(x, 1)
#define splay			hard_splay
#define insert			hard_insert
#define remove			simple_remove

// #define fast_rotate

#ifdef fast_rotate
void rotate(Node* , int);
#else
void rotate(Node* &, int);
#endif
void hard_splay(Node* &);
void simple_splay(Node* &);
Node *access(Node* &, int);
int Maximum(Node* &);
Node *join(Node* , Node* );
void jointo(Node* &, Node* &);
pnn split(Node* &, int);
void hard_insert(Node* &, int);
void simple_insert(Node* &, int);
void hard_remove(Node* &, int);
void simple_remove(Node* &, int);
void Delete(Node *);

// pay attention to update of node.p
#ifdef fast_rotate
void rotate(Node* x, int d) {
	#ifdef DEBUG
	assert(x != NULL);
	#endif

	Node *y = x->ch[d^1];
	x->ch[d^1] = y->ch[d];
	if (y->ch[d] != NULL) p(y->ch[d]) = x;	// maintain father link
	y->ch[d] = x;
	p(y) = p(x);		// maintain father link
	p(x) = y;			// maintain father link
	if (p(y) != NULL)
		p(y)->ch[right(p(y)) == x] = y;
}

void hard_splay(Node* &x) {
	if (x == NULL)	return ;

	while (p(x) != NULL) {
		if (x == left(p(x))) {
			if (g(x) == NULL) {
				// zig
				rotate_right(p(x));
			} else if (p(x) == left(g(x))) {
				// zig-zig
				rotate_right(g(x));
				rotate_right(p(x));
			} else {
				// zig-zag
				rotate_right(p(x));
				rotate_left(p(x));
			}
		} else {
			if (g(x) == NULL) {
				// zig
				rotate_left(p(x));
			} else if (p(x) == right(g(x))) {
				// zig-zig
				rotate_left(g(x));
				rotate_left(p(x));
			} else {
				// zig-zag
				rotate_left(p(x));
				rotate_right(p(x));
			}
		}
	}
}

#else

void rotate(Node* &x, int d) {
	#ifdef DEBUG
	assert(x != NULL);
	#endif

	Node *y = x->ch[d^1];
	x->ch[d^1] = y->ch[d];
	if (y->ch[d] != NULL) p(y->ch[d]) = x;	// maintain father link
	y->ch[d] = x;
	p(y) = p(x);		// maintain father link
	p(x) = y;			// maintain father link
	if (p(y) != NULL)
		p(y)->ch[right(p(y)) == x] = y;
	x = y;
}

void hard_splay(Node* &x) {
	if (x == NULL)	return ;
	Node *y;

	while (p(x) != NULL) {
		if (x == left(p(x))) {
			if (g(x) == NULL) {
				// zig
				rotate_right(y=p(x));
			} else if (p(x) == left(g(x))) {
				// zig-zig
				rotate_right(y=g(x));
				rotate_right(y);
			} else {
				// zig-zag
				rotate_right(y=p(x));
				rotate_left(y=p(x));
			}
		} else {
			if (g(x) == NULL) {
				// zig
				rotate_left(y=p(x));
			} else if (p(x) == right(g(x))) {
				// zig-zig
				rotate_left(y=g(x));
				rotate_left(y);
			} else {
				// zig-zag
				rotate_left(y=p(x));
				rotate_right(y=p(x));
			}
		}
		x = y;
	}
}
#endif

void simple_splay(Node* &x) {
	if (x == NULL)	return ;

	Node *y;

	while (p(x) != NULL) {
		if (x == left(p(x))) {
			if (g(x)!=NULL && p(x) == left(g(x))) {
				// zig-zig
				rotate_right(y=g(x));
			} else {
				y = p(x);
			}
			rotate_right(y);
		} else {
			if (g(x)!=NULL && p(x) == right(g(x))) {
				// zig-zig
				rotate_left(y=g(x));
			} else {
				y = p(x);
			}
			rotate_left(y);
		}
		x = y;
	}
}

Node *access(Node* &t, int v) {
	if (t == NULL)	return NULL;

	Node *ret = NULL, *x = t, *last;

	while (x != NULL) {
		int d = x->cmp(v);
		if (d == -1) {
			ret = last = x;
			break;
		}
		last = x;
		x = x->ch[d];
	}

	splay(t = last);

	#ifdef DEBUG
	assert(t != NULL);
	#endif

	return ret;
}

int Maximum(Node* &t) {
	if (t == NULL)	return -INF;
	while (right(t) != NULL) t = right(t);
	splay(t);
	return t->v;
}

Node *join(Node* t1, Node* t2) {
	if (t2 == NULL)	return t1;
	if (t1 == NULL)	return t2;
	
	// make p(t1) to NIL is necessary to make Maximum.splay stop at t1.
	p(t1) = NULL;	
	Maximum(t1);
	right(t1) = t2;
	p(t2) = t1;	

	return t1;
}

pnn split(Node* &t, int v) {
	if (t == NULL)	return mp((Node*)NULL, (Node*)NULL);

	Node *t1, *t2;

	access(t, v);
	int d = t->cmp(v);

	if (d != 0) {
		t1 = t;
		t2 = right(t);
		right(t1) = NULL;	
		if (t2!=NULL)	p(t2) = NULL;
	} else {
		t1 = left(t);
		t2 = t;
		left(t2) = NULL;	
		if (t1!=NULL)	p(t1) = NULL;
	}

	return mp(t1, t2);
}

void hard_insert(Node* &t, int v) {
	if (t == NULL) {
		t = new Node(v);
		return ;
	}

	pnn pr = split(t, v);
	Node* &t1 = pr.fir;
	Node* &t2 = pr.sec;

	if (t1!=NULL && t1->v==v)	{
		right(t1) = t2;
		if (t2 != NULL)	p(t2) = t1;
		t = t1;
		return ;
	}

	t = new Node(v);
	left(t) = t1;
	right(t) = t2;
	if (t1!=NULL)	p(t1) = t;
	if (t2!=NULL)	p(t2) = t;
}

void simple_insert(Node* &t, int v) {
	if (t == NULL) {
		t = new Node(v);
		return ;
	}

	Node *x = t, *y = NULL;
	int d = -1;

	while (x != NULL) {
		d = x->cmp(v);
		if (d == -1) {
			splay(t = x);
			return ;
		}
		y = x;
		x = x->ch[d];
	}

	#ifdef DEBUG
	assert(y!=NULL && d>=0);
	#endif
	x = new Node(v, y);
	y->ch[d] = x;
	splay(t = x);
}

void hard_remove(Node* &t, int v) {
	Node *x = access(t, v);
	if (x != NULL) {
		t = join(left(x), right(x));
		p(t) = NULL;
		delete x;
	}
}

void simple_remove(Node* &t, int v) {
	Node *x = t;

	while (x) {
		int d = x->cmp(v);
		if (d < 0) {
			t = p(x);
			Node *z = join(left(x), right(x));
			if (z != NULL)	p(z) = t;
			if (t != NULL)
				t->ch[right(t)==x] = z;
			else
				t = z;
			delete x;
			splay(t);
			break;
		}
		x = x->ch[d];
	}
}

void Delete(Node *t) {
	if (t->ch[0])	Delete(t->ch[0]);
	if (t->ch[1])	Delete(t->ch[1]);
	delete t;
}



//-------------------------------------------------
Node *rt = NULL;

static int getMin(const Node *x) {
	int ret = INF;

	while (x) {
		ret = x->v;
		x = x->ch[0];
	}
	return ret;
}

static int getMax(const Node *x) {
	int ret = -INF;

	while (x) {
		ret = x->v;
		x = x->ch[1];
	}
	return ret;
}

bool Member(int v) {
	return access(rt, v) != NULL;
}

inline int Maximum() {
	return getMax(rt);
}

inline int Minimum() {
	return getMin(rt);
}

void Insert(int v) {
	insert(rt, v);
}

void Erase(int v) {
	remove(rt, v);
}

int Predecessor(int v) {
	if (rt == NULL)	return -INF;

	access(rt, v);

	int d = rt->cmp(v);
	if (d <= 0)
		return getMax(left(rt));

	#ifdef DEBUG
	assert(getMin(right(rt)) > v);
	#endif
	return rt->v;
}

int Successor(int v) {
	if (rt == NULL)	return INF;

	access(rt, v);

	int d = rt->cmp(v);
	if (d != 0)
		return getMin(right(rt));

	#ifdef DEBUG
	assert(getMax(left(rt)) < v);
	#endif
	return rt->v;
}

#ifdef DEBUG
vi vc;

bool check_splay(const Node *rt) {
	if (rt == NULL)	return true;

	if (left(rt) != NULL) {
		if (p(left(rt))!=rt || !check_splay(left(rt)))
			return false;
	}

	vc.pb(rt->v);

	if (right(rt) != NULL) {
		if (p(right(rt))!=rt || !check_splay(right(rt)))
			return false;
	}

	return true;
}

bool judge() {
	vc.clr();

	if (rt == NULL)	return true;
	if (p(rt) != NULL)	return false;

	if (!check_splay(rt))	return false;

	int sz = SZ(vc);
	rep(i, 1, sz)
		if (vc[i] <= vc[i-1])
			return false;
	return true;
}

void print() {
	int sz = SZ(vc);

	rep(i, 0, sz)
		printf("%d ", vc[i]);
	putchar('\n');
}
#endif


int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("in_e7.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	int t;
	int n, m, x;
	char op[12];
	#ifdef DEBUG
	int nline = 1;
	#endif

	scanf("%d", &t);
	rep(tt, 1, t+1) {
		scanf("%d%d", &n, &m);
		if (rt)	{
			Delete(rt);
			rt = NULL;
		}
		#ifdef DEBUG
		++nline;
		printf("Case #%d:\n", tt);
		#endif
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
			#ifdef DEBUG
			++nline;
			if (!judge()) {
				printf("%d: wa\n", nline);
				abort();
			}
			print();
			fflush(stdout);
			#endif
		}
		#ifdef DEBUG
		putchar('\n');
		#endif
	}

	#ifndef ONLINE_JUDGE
		printf("time = %ldms.\n", clock());
	#endif

	return 0;
}
