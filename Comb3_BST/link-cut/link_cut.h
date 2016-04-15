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
typedef struct Node {
	int netmin, netcost;
	Ndptr bparent;
	Ndptr bhead, bleft, bright, btail;
	int flag;	// -1: external, 0: not reverse, 1: reversed
} Node;

void link();
void cut();
void evert();

void parent();
void root();
void cost();
void mincost();
void update();

Ndptr path(Ndptr);
Ndptr head(Ndptr);
Ndptr tail(Ndptr);
Ndptr before(Ndptr);
Ndptr after(Ndptr);
int pcost(Ndptr);
int pmincost(Ndptr);
void pupdate(Ndptr, int);
void reverse(Ndptr);
Ndptr concatenate(Ndptr, Ndptr, int);
void split(Ndptr, Ndptr*, Ndptr*, int*, int *y);

/*
	Naive Partitioning
*/
void expose();
void splice();


#endif  /* LINK_CUT_H */