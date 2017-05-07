#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
using namespace std;

struct predictItem_t {
	// int slotId;
	// int gridId;
	int workerN;
	int taskN;

	predictItem_t(int workerN=0, int taskN=0):
		workerN(workerN), taskN(taskN) {}
};

struct networkEdge_t {
	int u, v, f;

	networkEdge_t(int u=0, int v=0, int f=0):
		u(u), v(v), f(f) {}
};

void readInput_predict(const string& fileName, int& workerN, int& taskN, int& dw, int& dr,
						int& vw, int& slotN, int& gridLength, int& gridWidth, vector<predictItem_t>& items);
void readInput_predict(const ifstream& fin, int& workerN, int& taskN, int& dw, int& dr,
						int& vw, int& slotN, int& gridLength, int& gridWidth, vector<predictItem_t>& items);
void readInput_network(const ifstream& fin, int& vertexN, int& edgeN, vector<networkEdge_t>& edges);
void readInput_network(const string& fileName, int& vertexN, int& edgeN, vector<networkEdge_t>& edges);


void readInput_predict(const string& fileName, int& workerN, int& taskN, int& dw, int& dr,
						int& vw, int& slotN, int& gridLength, int& gridWidth, vector<predictItem_t>& items) {
	ifstream fin(fileName.c_str(), ios::in);

	readInput_predict(fin, workerN, taskN, dw, dr, vw, slotN, gridLength, gridWidth, items);

	fin.close();
}

void readInput_predict(const ifstream& fin, int& workerN, int& taskN, int& dw, int& dr,
						int& vw, int& slotN, int& gridLength, int& gridWidth, vector<predictItem_t>& items) {
	
	fin >> workerN >> taskN >> dw >> dr >> vw >> slotN >> gridLength >> gridWidth;

	const int gridN = gridLength * gridWidth;
	int slotId, gridId;
	predictItem_t item;
	items.clear();
	items.resize(slotN*gridN, item)

	for (int i=0; i<slotN; ++i) {
		for (int j=0; j<gridN; ++j) {
			fin >> slotId >> gridId >> item.workerN >> item.taskN;
			items[slotId*gridN+gridId] = item;
		}
	}
}

void readInput_network(const ifstream& fin, int& vertexN, int& edgeN, vector<networkEdge_t>& edges) {
	fin >> vertexN >> edgeN;

	edges.clear();
	edges.resize(edgeN, networkEdge_t());
	for (int i=0; i<edgeN; ++i) {
		fin >> edges[i].u >> edges[i].v >> edges[i].f;
	}
}

void readInput_network(const string& fileName, int& vertexN, int& edgeN, vector<networkEdge_t>& edges) {
	ifstream fin(fileName.c_str(), ios::in);

	readInput_network(fin, vertexN, edgeN, edges);

	fin.close();
}

#endif