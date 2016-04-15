#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include "link_cut.h"
#include "log.h"


#define DEBUG
#define MAXN 		205
#define bpar(x) 	(x)->bparent
#define bleft(x) 	(x)->bleft
#define bright(x)	(x)->bright
#define bhead(x)	(x)->bhead
#define btail(x)	(x)->btail
#define swap(a, b)\
{\
	Ndptr tmp = b;\
	b = a;\
	a = tmp;\
}

Ndptr Stack[maxn];
Ndptr dparent[maxn];

static inline int min(int a, int b) {
	return a<b ? a:b;
}

static inline int max(int a, int b) {
	return a>b ? a:b;
}

static inline void pushdown(Ndptr v) {
#ifdef DEBUG
	assert(v != NULL)
#endif

	if (v->flag == 1) {
		v->flag = 0;
		swap(bleft(x), bright(x));
		swap(bhead(x), bright(x));
	}
}

/*
	\brief 	Return the root of the solid path contains v
*/
Ndptr path(Ndptr v) {
#ifdef DEBUG
	assert(v != NULL);
#endif

	while (bpar(v) != NULL) v = bpar(v);
	return v;
}

/*
	\brief 	Return the root of the solid path v
		Assume x is the root of the solid path v
*/
Ndptr head(Path v) {
#ifdef DEBUG
	assert(bpar(v) == NULL);
#endif

#ifdef EVERT
	return v->flag==1 ? btail(v) : bhead(v);
#else
	return bhead(v);
#endif
}

/*
	\brief 	Return the tail of the solid path v
		Assume x is the root of the solid path v
*/
Ndptr tail(Path v) {
#ifdef DEBUG
	assert(bpar(v) == NULL);
#endif

#ifdef EVERT
	return v->flag==1 ? bhead(v) : btail(v);
#else
	return btail(v);
#endif
}

/*
	\brief 	Return the vertex before v on path(v), 
		if v is the head of the root, return null.
*/
Ndptr before(Ndptr x) {
	Ndptr y = x;
	Ndptr ret = NULL;
	int top = 0;

	do {
		S[top++] = y;
		y = bpar(y);
	} while (y != NULL);

	while (top--) {
		pushdown(S[top]);
		if (top && bright(S[top])==S[top-1])
			y = S[top];
	}
	if (y != NULL) {
		y = bleft(y);
		ret = y->flag < 0 ? y : 
			  y->flag > 0 ? bhead(y) : btail(y);
	}

	return ret;
}

/*
	\brief 	Return the vertex after x on path(x), 
		if x is the tail of the root, return null.
*/
Ndptr after(Ndptr x) {
	Ndptr y = x;
	Ndptr ret = NULL;
	int top = 0;

	do {
		S[top++] = y;
		y = bpar(y);
	} while (y != NULL);

	while (top--) {
		pushdown(S[top]);
		if (top && bleft(S[top])==S[top-1])
			y = S[top];
	}
	if (y != NULL) {
		y = bright(y);
		ret = y->flag < 0 ? y : 
			  y->flag > 0 ? bhead(y) : btail(y);
	}

	return ret;
}

/*
	\brief	Return the cost of the edge(x, after(x)).
*/
int pcost(Ndptr x) {
	Ndptr y = x;
	int ret = 0, delta = 0, mn = 0;
	int top = 0;

	do {
		S[top++] = y;
		y = bpar(y);
	} while (y != NULL);

	while (top--) {
		pushdown(S[top]);
		delta += S[top]->netmin;
		if (top && bleft(S[top])==S[top-1]) {
			y = S[top];
			mn = delta;
		}
	}
	if (y != NULL) {
		ret = mn + y->netcost;
	}

	return ret;
}

/*
	\brief	Return the vertex closes to tail(p) such that (x, after(x)) has the minimum cost among edges on p.
		Assume x is the root of path.
*/
Ndptr pmincost(Path x) {
	Ndptr y = x;
	
#ifdef DEBUG
	assert(bpar(x) == NULL)
#endif
	
	while (1) {
		pushdown(y);
	#ifdef DEBUG
		assert(bpar(y)==NULL || y->netmin==0);
	#endif
	
		
		if (y->netcost==0 && (bright(y)->flag<0 || bright(y)->netmin>0))
			return btail(y);
	#ifdef TARJAN
		if (bright(y)->flag>=0 && bright(y)->netcost==0)
			y = bright(y);
		else if (y->netcost > 0)
			y = left(y);	
		else
			assert(0);
	#else
		/*
			I thought the Pseudo code of Tarjan has some small mistake because:
			\forall v in search-path, grossmin(v) must equal to gorssmin(rt).
			So bright(y)->netcost>0 doesn't mean:
				\forall vv in sub-tree of bright(y), grosscost(vv) != grossmin(rt).
			
			In the content of while-loop:
			we are certain about:
				y->netcost>0 or (bright(y)->flag>=0 && bright(y)->netmin==0)
			(1) bright(y)->flag>=0 && bright(y)->netmin==0
				means grossmin(bright(y)) == grossmin(y), so replace y by bright(y).
			(2) implicit means y->netcost>0
				means 
			
		*/
		if (bright(y)->flag>=0 && bright(y)->netmin==0)
			y = bright(y);
		else
			y = bleft(y);
	#endif
	}
	
#ifdef DEBUG
	/* never goes there */
	assert(0);
#endif
	
	return NULL;
}

/*
	\brief	Add x to the cost of every edge on solid path p.
		Assume x is the root of solid path p
*/
void pupdate(Path x, int delta) {
#ifdef DEBUG
	assert(bpar(x) == NULL);
#endif
	x->netmin += delta;
}

/*
	\brief	Reverse the direction of path x.
		Assume x is the root of solid path p
*/
void reverse(Path x) {
#ifdef DEBUG
	assert(bpar(x) == NULL);
#endif
	/* -1 ^ 1 = -2
	   -2 ^ 1 = -1
	*/
	x->flag ^= 1;
}

/*
	\brief	Given the root x and y of two binary tree and a value w,
		combine the trees into a single tree by constructing a new root node with left son x, right son y, cost w.
*/
Ndptr construct(Ndptr x, Ndptr y, int w) {
#ifdef DEBUG
	assert(bpar(x)==NULL && bpar(y)==NULL);
#endif
	Ndptr rt = (Ndptr) malloc(sizeof(Node));
	rt->flag = 0;
	bpar(rt) = NULL;
	bleft(rt) = x;
	bright(rt) = y;
	/* consider the flag of x & y */
	bhead(rt) = x->flag==1 ? btail(x) : bhead(x);
	btail(rt) = y->flag==1 ? bhead(y) : btail(y);
	rt->netmin = min(min(x->netmin, y->netmin), w);
	rt->netcost = w - rt->netwin;
	
	x->netmin -= w;
	y->netmin -= w;
	bpar(x) = bpar(y) = rt;
}

/*
	\brief	Given the root of nontrival tree x, 
		erase the root u and divide the tree into two sub-trees consists of 
		left son of x, right son of x, and the cost of breaking edge.
*/
void destroy(Ndptr rt, Ndptr *lrt, Ndptr *rrt, int *w) {
	Ndptr x;
#ifdef DEBUG
	assert(bpar(rt) == NULL);
#endif
	/* need to pushdown rt */
	pushdown(rt);
	*w = rt->netmin + rt->netcost;
	
	*lrt = x = bleft(rt);
	bpar(x) = NULL;
	x->netmin += rt->netmin;
	
	*rrt = x = bright(rt);
	bpar(x) = NULL;
	x->netmin += rt->netmin;
	
	free(rt);
}

/*
	\brief	Perform a single left rotation at node x.
		Node x must have an internal right son.
*/
void rotate_left(Ndptr x) {
	Ndptr y = bright(x), z = bleft(y);
	
#ifdef DEBUG
	if (x->flag)	pushdown(x);
	if (y->flag)	pushdown(y);
	assert(x->flag==0 && y->flag==0);
#endif

	bright(x) = z;
	bpar(left(x)) = x;
	z = x;
	bpar(y) = bpar(x);
	bpar(x) = y;
	if (bpar(y) != NULL) {
		if (bright(bpar(y)) == x)
			bright(bpar(y)) = y;
		else
			bleft(bpar(y)) = y;
	}
	
	
}

/*
	\brief	Perform a single right rotation at node x.
		Node x must have an internal left son.
*/
void rotate_right(Ndptr x) {
	Ndptr y = bleft(x), z = bright(y);
	
#ifdef DEBUG
	if (x->flag)	pushdown(x);
	if (y->flag)	pushdown(y);
	assert(x->flag==0 && y->flag==0);
#endif

	bleft(x) = z;
	bpar(left(x)) = x;
	z = x;
	bpar(y) = bpar(x);
	bpar(x) = y;
	if (bpar(y) != NULL) {
		if (bleft(bpar(y)) == x)
			bleft(bpar(y)) = y;
		else
			bright(bpar(y)) = y;
	}
	
	/*
		all the attribute of x, y, z need to maintain
	*/
	
}

/*
	\brief	Combine p and q by adding the edge(tail(p), head(q)) of cost delta, Return the combined path.
		Assume p, q is the root of their solid path
*/
Path concatenate(Path p, Path q, int delta) {
#ifdef DEBUG
	assert(bpar(p)==NULL && bpar(q)==NULL);
#endif

	
}

/*
	\brief 	Extend the solid path by adding the edge from tail(p) to parent(tail(p)),
		if some out-edge from parent(tail(p)) is solid, then turn to dashed instead.
	\prob 	what is path? How to present path? 
		Obviously, we use a BST to present path. 
		So, why don't we just use any vertex of path instead of pathid or something like that.
*/
Ndptr splict(Ndptr p) {
	Ndptr q, r, v;
	int x, y;

	prt = root(p);
	v = dparent[tail(p)];
	split(v, &q, &r, &x, &y);
	if (q != NULL) {
		dparent[tail(q)] = v;
		dcost[tail(q)] = x;
	}
	p = concatenate(p, v, dcost[tail(p)]);

	if (r == NULL)
		return p;
	else
		return concatenate(p, r, y);
}
