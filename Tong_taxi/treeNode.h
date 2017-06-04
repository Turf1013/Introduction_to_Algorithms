/**
	\author: 	Trasier
	\date: 		2017.6.4
	\source: 	VLDB14 Large Scale Real-time Ridesharing with Service Guarantee on Road Networks
	\note: 		Kinetic Tree
*/
#include <bits/stdc++.h>
using namespace std;


template <class T>
struct treeNode_t {
	T val;
	vector<treeNode_t*> children;

	treeNode_t(T val):
		val(val) {}

	void push_back(treeNode_t* nxt) {
		children.push_back(nxt);
	}

	size_t size() const {
		return children.size();
	}

	bool isEmpty() const {
		return children.empty();
	}

	bool empty() const {
		return children.empty();
	}

	friend ostream& operator<< (ostream& out, const treeNode_t& node) {
		out << node.val;
		return out;
	}
};

template <class T>
void traverseTree(treeNode_t<T>* rt, int dep) {
	if (rt == NULL) return;

	for (int i=0; i<dep; ++i)
		cout << '\t';
	cout << *rt << '\n';
	const int sz = rt->size();
	for (int i=0; i<sz; ++i)
		traverseTree(rt->children[i], dep+1);
}

template <class T>
void deleteTree(treeNode_t<T>*& rt) {
	if (rt == NULL) return ;

	const int sz = rt->size();
	for (int i=0; i<sz; ++i)
		deleteTree(rt->children[i]);
	delete rt;
	rt = NULL;
}

template <class T>
void dfsCopyTree(treeNode_t<T>*& des, treeNode_t<T>* src) {
	des = new treeNode_t<T>(src->val);
	const int sz = src->size();
	for (int i=0; i<sz; ++i) {
		treeNode_t<T>* child;
		dfsCopyTree(child, src->children[i]);
		des->push_back(child);
	}
}

template <class T>
void copyTree(treeNode_t<T>*& des, treeNode_t<T>* src) {
	if (src == NULL) {
		des = NULL;
	} else {
		dfsCopyTree(des, src);
	}
}