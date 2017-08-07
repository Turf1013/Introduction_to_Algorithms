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
//	treeNode_t* parent=NULL; 
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
/* 
template <class T>
void setParent(treeNode_t<T>* child){
	treeNode_t<T>* parent=child->parent;
	
	for(int i=0;i<parent->size();i++){
		printf("1\n");
		if((parent->children[i]-child)==0){
			printf("2\n");
			if(child==NULL){
				printf("set wrong3\n");
			} 
			parent->children[i]=NULL;
			printf("3\n");
			if(child==NULL){
				printf("set wrong1\n");
			} 
			break;
		}
	}
}
*/

 
//   delete里面要注意在父节点中将子节点设置为NULL 
template <class T>
void deleteTree(treeNode_t<T>*& rt) {
	if (rt == NULL) return ;
	const int sz = rt->size();
//	printf("size: %d\n",sz); 
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
	//	child->parent=des; 
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



// 通过递归更新slackTime 怎么避免重复计算其他分支呢？？ 
/*
double updateInfo(treeNode*&rt){
	if(rt->children.size()==0){
		int placeId=rt->val.placeId;
		int orderId=rt->val.orderId;
		if(placeId<R){
			rt->val.slackTime=orders[orderId].tid+waittime-rt->val.time;
		}
		else{
			rt->val.slackTime=(1+detour)*Length(rests[orders[orderId].sid],dists[placeId-R])-
			(orders[orderId].droptime-orders[orderId].takentime);
		}
		return rt->val.slackTime;
	}
	
	vector<double> timelist;
	double temp;
	double max;
	double d;
	int placeId=rt->val.placeId;
	for(int i=0;i<rt->children.size();i++){
		treeNode*& subtree=rt->children[i];
		if(subtree->val.placeId>R) {
			orders[subtree->val.orderId].takentime=subtree->val.time;
		}
		else {
			orders[subtree->val.orderId].droptime=subtree->val.time;
		}
		temp=updateInfo(subtree);
		timelist.push_back(temp);
	}
	max=countMax(timelist);
	
	if(placeId<R){
		rt->val.slackTime=orders[orderId].tid+waittime-rt->val.time;
	}
	else{
		rt->val.slackTime=(1+detour)*Length(rests[orders[orderId].sid],dists[placeId-R])-
		(orders[orderId].droptime-orders[orderId].takentime);
	}
	rt->val.slackTime=min(rt->val.slackTime,max);
}
*/
