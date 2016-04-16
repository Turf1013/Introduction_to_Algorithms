#ifndef LINK_CUT_H
#define LINK_CUT_H

#define EVERT

/*
	`Author`: 	Traiser
	`Date`:		04.15.2016
	`Refer`:	A Data Structure for Dynamic Trees, Daniel D. Sleator and Robert Endre Tarjan.
				Self-Adjusting Binary Search Trees, Daniel D. Sleator and Robert Endre Tarjan.
*/
typedef struct Node* Ndptr;
typedef struct Node* Path;
typedef struct Node {
	int netmin, netcost;	// assert(netmin>=0 && netcost>=0)
	Ndptr bparent;
	Ndptr bhead, bleft, bright, btail;
	int flag;	// -1: external, 0: not reverse, 1: reversed
} Node;

Path link(Ndptr, Ndptr, int);
void cut();
void evert();

void parent(Ndptr);
void root(Ndptr);
int cost(Ndptr);
int mincost(Ndptr);
void update(Ndptr, int);

Ndptr path(Ndptr);
Ndptr head(Path);
Ndptr tail(Path);
Ndptr before(Ndptr);
Ndptr after(Ndptr);
int pcost(Ndptr);
int pmincost(Path);
void pupdate(Path, int);
void reverse(Path);
Path concatenate(Path, Path, int);
void split(Ndptr, Ndptr*, Ndptr*, int*, int *y);

Ndptr construct(Path, Path, int);
void destroy(Ndptr);
void rotate_left(Ndptr);
void rotate_right(Ndptr);

/*
	Naive Partitioning
*/
void splice(Path);
void expose(Ndptr);


#endif  /* LINK_CUT_H */