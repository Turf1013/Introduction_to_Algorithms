/**
	\author: 	Trasier
	\date: 		2017.10.13
*/
#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
using namespace std;

struct position_t {
	double x, y;
	
	position_t(double x=0., double y=0.):
		x(x), y(y) {}
		
	bool operator<(const position_t& o) const {
		if (x == o.x)
			return y < o.y;
		else
			return x < o.x;
	}
	
	bool operator==(const position_t& oth) const {
		return dcmp(x-oth.x)==0 && dcmp(y-oth.y)==0;
	}

	bool operator!=(const position_t& oth) const {
		return dcmp(x-oth.x)!=0 || dcmp(y-oth.y)!=0;
	}
};

struct order_t {
	int tid, sid, eid;
	
	order_t(int tid=0, int sid=0, int eid=0):
		tid(tid), sid(sid), eid(eid) {}
		
	bool operator<(const order_t& o) const {
		return tid < o.tid;
	}
};

struct node_t {
	int placeId, orderId;

	node_t(int placeId=0, int orderId=0):
		placeId(placeId), orderId(orderId) {}

	bool operator==(const node_t& oth) const {
		return placeId==oth.placeId && orderId==oth.orderId;
	}

	bool operator!=(const node_t& oth) const {
		return placeId!=oth.placeId || orderId!=oth.orderId;
	}
};

struct driver_t {
	position_t pos;
	double curTime;
	vector<node_t> route;

	driver_t(double x=0., double y=0., double curTime=0.) {
		pos.x = x;
		pos.y = y;
		this->curTime = curTime;
	}

	bool isEmpty() const {
		return route.empty();
	}

	bool empty() const {
		return this->isEmpty();
	}

	void push_back(int placeId, int orderId) {
		route.push_back(node_t(placeId, orderId));
	}

	void pop_front() {
		if (!route.empty())
			route.erase(route.begin());
	}

	void erase(vector<node_t>::iterator biter, vector<node_t>::iterator eiter) {
		route.erase(biter, eiter);
	}

	void clear() {
		route.clear();
	}

	vector<int> getBucket() {
		const int sz = route.size();
		vector<int> ret;
		set<int> unpicked;

		for (int i=0; i<sz; ++i) {
			if (route[i].placeId < R)
				unpicked.insert(route[i].orderId);
			if (route[i].placeId>=R && unpicked.count(route[i].orderId)==0)
				ret.push_back(route[i].orderId);
		}

		return ret;
	}
};

void readInput(const string& fileName, int& V, int& N, int& C, int& M, position_t*& points, order_t*& orders);
void readInput(istream& fin, int& V, int& N, int& C, int& M, position_t*& points, order_t*& orders);

void readInput(const string& fileName, int& V, int& N, int& C, int& M, position_t*& points, order_t*& orders) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	readInput(fin, V, N, C, M, points, orders);
	fin.close();
}

void readInput(istream& fin, int& V, int& N, int& C, int& M, position_t*& points, order_t*& orders) {
	fin >> V >> N >> C >> M;
	if (points == NULL)
		points = new position_t[V];
	if (orders == NULL)
		orders = new order_t[M];
	
	for (int i=0; i<V; ++i) {
		fin >> points[i].x >> points[i].y;
	}
	for (int i=0; i<M; ++i) {
		fin >> orders[i].tid >> orders[i].sid >> orders[i].eid;
		--orders[i].sid;
		--orders[i].eid;
	}
}


#endif