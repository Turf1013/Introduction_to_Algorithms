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

static inline void maintain(Ndptr v) {
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
*/
Ndptr head(Ndptr v) {
#ifdef EVERT
	return v->flag==1 ? btail(v) : bhead(v);
#else
	return bhead(v);
#endif
}

/*
	\brief 	Return the tail of the solid path v
*/
Ndptr tail(Ndptr v) {
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
		maintain(S[top]);
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
		maintain(S[top]);
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
		maintain(S[top]);
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
*/
Ndptr pmincost(Ndptr x) {

}

/*
	\brief	Add x to the cost of every edge on p.
*/
void pupdate(Ndptr x, int delta) {

}

/*
	\brief Reverse the direction of path x.
*/
void update(Ndptr x) {

}

/*
	\brief	Combine p and q by adding the edge(tail(p), head(q)) of cost delta, Return the combined path.
*/
Ndptr concatenate(Ndptr p, Ndptr q, int delta) {

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
