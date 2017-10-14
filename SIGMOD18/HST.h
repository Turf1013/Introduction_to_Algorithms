/**
	\author: 	Trasier
	\date: 		2017.10.13
*/
#ifndef HST_H
#define HST_H

#include <bits/stdc++.h>
using namespace std;

#include "input.h"

struct treeNode_t {
	int dep, sz, id;
	treeNode_t* sons;

	treeNode_t(int dep=0, int sz=0, int id=0, treeNode_t* sons=NULL):
		dep(dep), sz(sz), id(id), sons(sons) {}

	void addSon(treeNode_t *son) {
		treeNode_t* tmp = new treeNode_t[sz];
		memcopy(tmp, sons, sizeof(treeNode_t*)*sz);
		delete[] sons;
		sons = new treeNode_t[sz+1];
		memcopy(sons, tmp, sizeof(treeNode_t*)*sz);
		sons[sz++] = son;
	}

	void setId(int _id) {
		id = _id;
	}
};

void genRandomPermu(int V, int* permu) {
	if (permu == NULL)
		permu = new int[V];
	for (int i=0; i<V; ++i)
		permu[i] = i;
	shuffle(permu, permu+V);
}

double genRandomBeta() {
	double p[205];
	for (int i=100; i<=200; ++i) {
		p[i-100] = 1.0 / (log(2.0, exp(1.0)) * i / 100.0);
	}
	for (int i=101; i<=200)
		p[i-100] += p[i-101];
	int ub = p[100], dice = rand() % ub;
	for (int i=100; i<=200; ++i) {
		if (dice <= p[i-100])
			return i/100.0;
	}

	assert(false);
	return -1.0;
}

double calcDelta(int V, position_t* points) {
	double ret = -1.0;
	for (int i=0; i<V; ++i) {
		for (int j=i+1; j<V; ++j) {
			ret = max(ret, Length(points[i], points[j]));
		}
	}
	return ret;
}

double exp2(int n) {
	double ret = 1.0;
	for (int i=0; i<n; ++i) ret *= 2.0;
	return ret;
}

void HST_Construction(int V, position_t* points, treeNode*& root) {
	int *permu = NULL;
	int delta = ceil(log(calcDelta(V, points), 2.0));
	double beta = genRandomBeta();
	int* vids[2];
	int* cids[2];
	int* bids[2];
	vector<vector<treeNode*> > nodes[2];

	genRandomPermu(V, permu);
	for (int i=0; i<2; ++i) {
		vids[i] = new int[V];
		cids[i] = new int[V];
		bids[i] = new int[V];
		nodes[i].push_back(vector<treeNode*>(NULL, V));
	}
	bids[0][0] = V;
	for (int i=0; i<V; ++i) {
		cids[0][i] = 0；
		vids[0][i] = i;

		cids[1][i] = -1;
		vids[1][i] = -1;
	}
	root = new treeNode(0, 0, NULL);
	nodes[0][0] = root;

	int p = 0, q = 1;
	for (int i=delta-1; i>0; --i) {
		double betai = beta * exp2(i-1);
		int clusterN = 0, idx = 0;
		for (int j=0; j<V; ++j) {
			int oid = permu[j];
			int cid = cids[p][vid];
			int b = (cid==0) ? 0 : bids[p][cid-1];
			int e = bids[p][cid];
			int c = 0;
			for (int k=b; k<e; ++k) {
				int vid = vids[p][k];
				if (cids[q][vid] != -1) continue;

				if (Length(points[oid], points[vid]) <= betai) {
					cids[q][vid] = clusterN;
					vids[q][idx++] = vid;
					++c;
				}
			}

			// add a node, maybe a leaf
			nodes[q][clusterN] = new treeNode(nodes[p][cid].dep+1);
			nodes[p][cid]->addSon(nodes[q][clusterN]);
			nodes[p][cid]->setId(vids[q][idx-1]);
			bids[q][clusterN] = (clusterN == 0) ? idx : (bids[q][clusterN-1]+idx);
			++clusterN;
		}
		swap(p, q);
		for (int j=0; j<V; ++j) {
			cids[q][j] = -1;
			nodes[q][j] = NULL;
		}
	}

	delete[] permu;
	for (int i=0; i<2; ++i) {
		delete[] vids[i];
		delete[] cids[i];
	}
}

void HST_delete(treeNode_t*& root) {
	if (root == NULL) return ;

	for (int i=0; i<root->sz; ++i) {
		HST_delete(root->sons[i]);
	}

	delete root;
}

void HST_traversePrint(treeNode_t* root) {
	if (root == NULL) return ;
	if (root->sz == 0) {
		printf("%d ", root->id);
		return ;
	}

	for (int i=0; i<root->sz; ++i) {
		HST_traversePrint(root->sons[i]);
	}
}

void HST_dump(treeNode_t*& root) {
	queue<treeNode_t*> Q;

	Q.push(root);
	while (!Q.empty()) {
		int szQ = Q.size();
		printf("%d\n", szQ);
		while (szQ--) {
			treeNode_t* node = Q.front();
			Q.pop();
			HST_traversePrint(node);
			putchar('\n');
			for (int i=0; i<node->sz; ++i) {
				Q.push(node->sons[i]);
			}
		}
		fflush(stdout);
	}
}

#endif
