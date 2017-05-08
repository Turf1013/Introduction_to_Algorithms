/**
	\author: Trasier
	\date: 2017.05.07
*/
#ifndef OUTPUT_H
#define OUTPUT_H

#include <bits/stdc++.h>
using namespace std;

struct graphEdge_t {
	int u, v, f;

	graphEdge_t(int u=0, int v=0, int f=0):
		u(u), v(v), f(f) {}

	void print() {
		printf("%d %d %d\n", u, v, f);
	}
};

void output_network(const int vertexN, const vector<graphEdge_t>& edges);

void output_network(const int vertexN, const vector<graphEdge_t>& edges) {
	const int sz = edges.size();
	int edgeN = 0;

	for (int i=0; i<sz; ++i) {
		if (edges[i].f > 0)
			++edgeN;
	}

	printf("%d %d\n", vertexN, edgeN);
	for (int i=0; i<sz; ++i) {
		if (edges[i].f > 0) {
			printf("%d %d %d\n", edges[i].u, edges[i].v, edges[i].f);
		}
	}
}

#endif