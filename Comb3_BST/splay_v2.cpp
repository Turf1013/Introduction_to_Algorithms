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

#define DEBUG

typedef struct Node {
	int v;
	Node *p, *ch[2];

	Node() {}
	Node(int v, Node *p=NULL):v(v),p(p) {
		ch[0] = ch[1] = NULL;
	}

	int cmp(int _v) {
		return 	v==_v ? -1 :
				v <_v ?  0 : 1;
	}

} Node;

typedef pair<Node*, Node*>	pnn;

#define g(x) 			(x)->p->p
#define p(x) 			(x)->p
#define left(x)			(x)->ch[0]
#define right(x)		(x)->ch[1]
#define rotate_left(x)	rotate(x, 0)
#define rotate_right(x)	rotate(x, 1)
#define top_down_access	hard_top_down_access
#define splay			hard_splay
#define insert			hard_insert
#define remove			hard_remove
#define access			down_top_access

static void rotate(Node* &, int);
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
static void rotate(Node* &x, int d) {
	Node *y = x->ch[d^1];
	x->ch[d^1] = y->ch[d];
	p(y->ch[d]) = x;	// maintain father link
	y->ch[d] = x;
	p(y) = p(x);		// maintain father link
	p(x) = y;			// maintain father link
	x = y;
}

void hard_splay(Node* &x) {
	if (x == NULL)	return ;

	while (p(x) != NULL) {
		if (x == left(p(x))) {
			if (g(x) == NULL) {
				// zig
				rotate_right(x);
			} else if (p(x) == left(g(x))) {
				// zig-zig
				rotate_right(p(x));
				rotate_right(x);
			} else {
				// zig-zag
				rotate_right(x);
				rotate_left(x);
			}
		} else {
			if (g(x) == NULL) {
				// zig
				rotate_left(x);
			} else if (p(x) == right(g(x))) {
				// zig-zig
				rotate_left(p(x));
				rotate_left(x);
			} else {
				// zig-zag
				rotate_left(x);
				rotate_right(x);
			}
		}
	}
}

void simple_splay(Node* &x) {
	if (x == NULL)	return ;

	while (p(x) != NULL) {
		if (x == left(p(x))) {
			if (g(x) && p(x) == left(g(x))) {
				// zig-zig
				rotate_right(p(x));
			}
			rotate_right(x);
		} else {
			if (g(x) && p(x) == right(g(x))) {
				// zig-zig
				rotate_left(p(x));
			}
			rotate_left(x);
		}
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
	
	#ifdef DEBUG
	assert(last != NULL);
	#endif

	// splay the last nonnull node
	splay(last);
	t = last;	// make root point to last

	return ret;
}

int Maximum(Node* &t) {
	if (t == NULL)	return -INF;
	
	// access the INF value
	access(t, INF);
	
	#ifdef DEBUG
	assert(right(t) == NULL);
	#endif

	return t->v;
}

int Minimum(Node* &t) {
	if (t == NULL)	return INF;

	// access the -INF value
	access(t, -INF);

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
	Node* ret = t1;

	if (t2 == NULL) {
		t1 = NULL;
		return ret;
	} else if (t1 == NULL) {
		ret = t2;
		t2 = NULL;
		return ret;
	}

	Maximum(t1);
	right(t1) = t2;
	p(t2) = t1;			// maintain father link
	t1 = t2 = NULL;

	return ret;
}

/*
	Assume that all items in t1 are less than all those in t2,
	and destroy t2.
*/
void jointo(Node *&t1, Node* &t2) {

	if (t2 == NULL)	return ;
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

	Node *x = access(t, v), *t1, *t2;
	int d = x->cmp(v);

	if (d <= 0) {
		// break right link
		t1 = t;
		t2 = right(t);
		right(t1) = NULL;	// maintain father link
		p(t2) = NULL;
	} else {
		// break left link
		t1 = left(t);
		t2 = t;
		left(t2) = NULL;	// maintain father link
		p(t1) = NULL;
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
	if (t1 && t1->v==v)	{
		right(t1) = t2;
		p(t2) = t1;			// maintain father link
		t = t1;
		return ;
	}

	t = new Node(v);
	left(t) = t1;
	right(t) = t2;
	p(t1) = t;				// maintain father link
	p(t2) = t;
}

void simple_insert(Node* &t, int v) {
	if (t == NULL) {
		t = new Node(v);
		return ;
	}

	Node *x = t, *y = NULL;
	int d;

	while (x) {
		d = t->cmp(v);
		if (d == -1)	return ;

		y = x;
		x = x->ch[d];
	}

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
	if (y != NULL)
		p(y) = p(x);
	t = p(x);
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
	p(t) = NULL;
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
	p(t) = NULL;
}

static void assemble(Node* &t, Node* &l, Node* &r, Node *lt, Node *rt) {
	#ifdef DEBUG
	assert(t != NULL);
	#endif
	if (l != NULL)	{
		right(l) = left(t);
		if (left(t) != NULL) {
			p(left(t)) = l;		// maintain father link
			l = left(t);
			left(l) = right(l) = NULL;
		}
	}
	if (r != NULL) {
		left(r) = right(t);
		if (right(t) != NULL) {	
			p(right(t)) = r;	// maintain father link
			r = right(t);
			left(r) = right(r) = NULL;
		}
	}
	
	left(t) = lt;
	right(t) = rt;
	p(t) = NULL;	// maintain father link
	if (lt != NULL)	p(lt) = t;
	if (rt != NULL) p(rt) = t;
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
	
	assemble(last, l, r, lt, rt);
	t = last;
	
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
			if (d2 == 0) {
				rotate_right(t);
			}
			last = t;
			link_right(t, r);
		} else {
			if (d2 == 1) {
				rotate_left(t);
			}
			last = t;
			link_left(t, l);
		}
		
		if (lt==NULL && l!=NULL)	lt = l;
		if (rt==NULL && r!=NULL)	rt = r;
	}
	
	assemble(last, l, r, lt, rt);
	t = last;
	
	return ret;
}

//-------------------------------------------------
Node *rt = NULL;

bool Member(int v) {
	return access(rt, v) != NULL;
}

int Maximum() {
	return Maximum(rt);
}

int Minimum() {
	return Minimum(rt);
}

void Insert(int v) {
	insert(rt, v);
}

void Erase(int v) {
	remove(rt, v);
}

int Predecessor(int v) {
	Node *x = access(rt, v);
	if (x != NULL) {
		return Maximum(left(x));
	} else {
		return x->v;
	}
}

int Successor(int v) {
	Node *x = access(rt, v);
	return Minimum(right(x));
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("data.in", "r", stdin);
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
		printf("time = %d.\n", (int)clock());
	#endif

	return 0;
}