/* splay v2.0 */
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
#define insert			simple_insert
#define remove			simple_remove
#define top_down_access	hard_top_down_access
#define access			top_down_access

// #define fast_rotate

#ifdef fast_rotate
void rotate(Node* , int);
#else
void rotate(Node* &, int);
#endif
void hard_splay(Node* &);
void simple_splay(Node* &);
Node *down_top_access(Node* &, int);
Node *hard_top_down_access(Node* &, int);
Node *simple_top_down_access(Node* &, int);
int Maximum(Node* &);
int Minimum(Node* &);
Node *join(Node* &, Node* &);
void jointo(Node* &, Node* &);
pnn split(Node* &, int);
void hard_insert(Node* &, int);
void simple_insert(Node* &, int);
void hard_remove(Node* &, int);
void simple_remove(Node* &, int);
void Delete(Node *);

// more efficient method to implement splay ?
static void link_left(Node* &, Node* &);
static void link_right(Node* &, Node* &);
static void assemble(Node* &, Node* &, Node* &, Node*, Node*);
void hard_top_down_splay(Node* &);
void simple_top_down_splay(Node* &);


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

Node *down_top_access(Node* &t, int v) {
	if (t == NULL)	return NULL;

	Node *ret = NULL, *x = t, *last = NULL;

	while (x) {
		int d = x->cmp(v);
		if (d == -1) {
			ret = last = x;
			break;
		}
		last = x;
		x = x->ch[d];
	}

	// splay the last nonnull node
	splay(t = last);

	#ifdef DEBUG
	assert(t != NULL);
	#endif
	
	return ret;
}

int Maximum(Node* &t) {
	if (t == NULL)	return -INF;
	
	Node *p = t, *last;

	while (p) {
		last = p;
		p = p->ch[1];
	}

	// splay the last nonnull node
	splay(t = last);

	#ifdef DEBUG
	assert(right(t) == NULL);
	#endif

	return t->v;
}

int Minimum(Node* &t) {
	if (t == NULL)	return INF;

	Node *p = t, *last;

	while (p) {
		last = p;
		p = p->ch[0];
	}

	// splay the last nonnull node
	splay(t = last);

	#ifdef DEBUG
	assert(left(t) == NULL);
	#endif

	return t->v;
}

/*
	Assume that all items in t1 are less than all those in t2,
	and destroy both t1 and t2.
*/
Node *join(Node* &t1, Node* &t2) {
	Node* ret;
	
	if (t1 != NULL)	p(t1) = NULL;
	if (t2 != NULL)	p(t2) = NULL;
	if (t2 == NULL) {
		ret = t1;
		t1 = NULL;
		return ret;
	} else if (t1 == NULL) {
		ret = t2;
		t2 = NULL;
		return ret;
	}

	Maximum(t1);
	right(t1) = t2;
	ret = t1;
	p(t2) = t1;			// maintain father link
	t1 = t2 = NULL;
	
	return ret;
}

/*
	Assume that all items in t1 are less than all those in t2,
	and destroy t2.
*/
void jointo(Node *&t1, Node* &t2) {
	if (t1 != NULL)	p(t1) = NULL;
	if (t2 == NULL)	return ;
	
	p(t2) = NULL;
	if (t1 == NULL)	{
		t1 = t2;
		t2 = NULL;
		return ;
	}

	Maximum(t1);
	right(t1) = t2;
	p(t2) = t1;			// maintain father link
	t2 = NULL;
}

pnn split(Node* &t, int v) {
	if (t == NULL)	return mp((Node*)NULL, (Node*)NULL);

	Node *t1, *t2;
	
	access(t, v);
	int d = t->cmp(v);

	if (d != 0) {
		// break right link
		t1 = t;
		t2 = right(t);
		right(t1) = NULL;	// maintain father link
		if (t2!=NULL)	p(t2) = NULL;
	} else {
		// break left link
		t1 = left(t);
		t2 = t;
		left(t2) = NULL;	// maintain father link
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

	// only root of t1 might be equal to v, and v exists already
	if (t1!=NULL && t1->v==v)	{
		right(t1) = t2;
		if (t2 != NULL)	p(t2) = t1;	// maintain father link
		t = t1;
		return ;
	}

	t = new Node(v);
	left(t) = t1;
	right(t) = t2;
	if (t1!=NULL)	p(t1) = t;		// maintain father link
	if (t2!=NULL)	p(t2) = t;
}

void simple_insert(Node* &t, int v) {
	if (t == NULL) {
		t = new Node(v);
		return ;
	}

	Node *x = t, *y = NULL;
	int d = -1;

	while (x) {
		d = x->cmp(v);
		if (d == -1) {
			splay(t=x);
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
	splay(t=x);
}

void hard_remove(Node* &t, int v) {
	// we can not directly use access, because access with splay at the end
	if (t == NULL)	return ;

	Node *x = NULL, *y = t;

	while (y) {
		int d = y->cmp(v);
		if (d == -1) {
			x = y;
			break;
		}
		y = y->ch[d];
	}

	if (x == NULL)	return ;

	// splay the last nonnull node
	y = join(left(x), right(x));
	if (y != NULL)	p(y) = p(x);
	if (p(x) != NULL) {
		p(x)->ch[right(p(x))==x] = y;
		t = p(x);
	} else {
		t = y;
	}
	delete x;
	splay(t);
}

void simple_remove(Node* &t, int v) {
	if (t == NULL)	return;

	Node *x = t, *y;
	int d;

	while (x) {
		d = x->cmp(v);
		if (d == -1) {
			y = p(x);
			Node *z = join(left(x), right(x));
			if (z != NULL)
				p(z) = y;
			if (y != NULL)
				y->ch[d] = z;
			else
				y = z;
			delete x;
			splay(t=y);
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



// a top-down restructing method to implement access with 2 version.
static void link_left(Node* &t, Node* &l) {
	if (t == NULL)	return ;
	if (l != NULL)
		right(l) = t;
	p(t) = l;
	l = t;
	t = right(t);
	// may no need to maintain this pointer ???
	right(l) = NULL;
	if (t != NULL)	p(t) = NULL;	
}

static void link_right(Node *&t, Node* &r) {
	if (t == NULL)	return ;
	if (r != NULL)
		left(r) = t;
	p(t) = r;
	r = t;
	t = left(t);
	// may no need to maintain this pointer	???
	left(r) = NULL;
	if (t != NULL)	p(t) = NULL;	
}

static void assemble(Node* &t, Node* &l, Node* &r, Node *lt, Node *rt) {
	#ifdef DEBUG
	assert(t != NULL);
	#endif
	
	// current mid pointer may be null, 
	//	Turns out that we had already link last to l or r.
	if (t == l) {
		right(t) = NULL;
		l = p(t);
		if (l == NULL)	lt = NULL;
	} else if (t == r) {
		left(t) = NULL;
		r = p(t);
		if (r == NULL)	rt = NULL;
	}
	
	if (l != NULL)	{
		right(l) = left(t);
		if (left(t) != NULL) {
			p(left(t)) = l;		// maintain father link
			l = left(t);
			// left(l) = right(l) = NULL;	serious wrong
		}
		left(t) = lt;
		p(lt) = t;
	}
	if (r != NULL) {
		left(r) = right(t);
		if (right(t) != NULL) {	
			p(right(t)) = r;	// maintain father link
			r = right(t);
			// left(r) = right(r) = NULL;	serious wrong
		}
		right(t) = rt;
		p(rt) = t;
	}
	
	p(t) = NULL;	// maintain father link
}

Node *hard_top_down_access(Node* &t, int v) {
	if (t == NULL)	return NULL;
	
	Node *lt, *rt, *l, *r;
	Node *ret, *last;
	
	ret = last = lt = rt = l = r = NULL;
	while (t != NULL) {
		int d = t->cmp(v);
		if (d==-1 || t->ch[d]==NULL) {
			if (d == -1)	ret = t;
			last = t;
			break;
		}
		
		int d2 = t->ch[d]->cmp(v);
		if (d == 0) {
			if (d2 == -1) {
				last = t;
				link_right(t, r);
			} else if (d2 == 0) {
				rotate_right(t);
				last = t;
				link_right(t, r);
			} else {
				link_right(t, r);
				last = t;
				link_left(t, l);
			}
		} else {
			if (d2 == -1) {
				last = t;
				link_left(t, l);
			} else if (d2 == 1) {
				rotate_left(t);
				last = t;
				link_left(t, l);
			} else {
				link_left(t, l);
				last = t;
				link_right(t, r);
			}
		}
		
		if (lt==NULL && l!=NULL)	lt = l;
		if (rt==NULL && r!=NULL)	rt = r;
	}
	
	assemble(t = last, l, r, lt, rt);
	
	return ret;
}

Node *simple_top_down_access(Node* &t, int v) {
	if (t == NULL)	return NULL;
	
	Node *lt, *rt, *l, *r;
	Node *ret, *last;
	
	ret = last = lt = rt = l = r = NULL;
	while (t != NULL) {
		int d = t->cmp(v);
		if (d==-1 || t->ch[d]==NULL) {
			if (d == -1)	ret = t;
			last = t;
			break;
		}
		
		int d2 = t->ch[d]->cmp(v);
		if (d == 0) {
			if (d2 == 0)
				rotate_right(t);
			last = t;
			link_right(t, r);
		} else {
			if (d2 == 1)
				rotate_left(t);
			last = t;
			link_left(t, l);
		}
		
		if (lt==NULL && l!=NULL)	lt = l;
		if (rt==NULL && r!=NULL)	rt = r;
	}
	
	assemble(t = last, l, r, lt, rt);
	
	return ret;
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
		freopen("in_e3.in", "r", stdin);
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
