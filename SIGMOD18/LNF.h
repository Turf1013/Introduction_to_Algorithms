/**
	\author:	Trasier
	\date:		2017.10.28
*/
#ifndef LNF_H
#define LNF_H

#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "HST.h"

struct myTreeNode_t : public treeNode_t {
	int dep, sz, id;
	treeNode_t *fa;
	vector<treeNode_t*> sons;
	int c;

	myTreeNode_t(int dep=0, int sz=0, int id=0, treeNode_t* fa=NULL):
		treeNode_t(dep, sz, id, fa) {
			c = 0;
	}

	bool operator<(const myTreeNode_t& oth) {
		return dep < oth.dep;
	}
};

#endif
