#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
using namespace std;

void readInput(const string& fileName, int& R, int& D, int& M, int& C, int& N, 
			vector<int>& vRest, vector<int>& vDist, vector<int>& vOrder);
void readInput(const ifstream& fin, int& R, int& D, int& M, int& C, int& N, 
			vector<int>& vRest, vector<int>& vDist, vector<int>& vOrder);
void readInput(int& R, int& D, int& M, int& C, int& N, 
			vector<int>& vRest, vector<int>& vDist, vector<int>& vOrder);

void readInput(const string& fileName, int& R, int& D, int& M, int& C, int& N, 
			vector<double>& vRest, vector<double>& vDist, vector<int>& vOrder);
void readInput(const ifstream& fin, int& R, int& D, int& M, int& C, int& N, 
			vector<double>& vRest, vector<double>& vDist, vector<int>& vOrder);
void readInput(int& R, int& D, int& M, int& C, int& N, 
			vector<double>& vRest, vector<double>& vDist, vector<int>& vOrder);

void readInput(int& R, int& D, int& M, int& C, int& N, 
			vector<int>& vRest, vector<int>& vDist, vector<int>& vOrder) {
	
	vRest.clear();
	vDist.clear();
	vOrder.clear();
	scanf("%d %d %d %d %d", &R, &D, &M, &C, &N);

	int x, y;
	for (int i=0; i<R; ++i) {
		scanf("%d %d", &x, &y);
		vRest.push_back(x);
		vRest.push_back(y);
	}

	for (int i=0; i<D; ++i) {
		scanf("%d %d", &x, &y);
		vDist.push_back(x);
		vDist.push_back(y);
	}

	int tid, rid, did;
	for (int i=0; i<N; ++i) {
		scanf("%d %d %d", &tid, &rid, &did);
		vOrder.push_back(tid);
		vOrder.push_back(rid);
		vOrder.push_back(did);
	}	
}

void readInput(const ifstream& fin, int& R, int& D, int& M, int& C, int& N, 
			vector<int>& vRest, vector<int>& vDist, vector<int>& vOrder) {

	vRest.clear();
	vDist.clear();
	vOrder.clear();
	fin >> R >> D >> M >> C >> N;

	int x, y;
	for (int i=0; i<R; ++i) {
		fin >> x >> y;
		vRest.push_back(x);
		vRest.push_back(y);
	}

	for (int i=0; i<D; ++i) {
		fin >> x >> y;
		vDist.push_back(x);
		vDist.push_back(y);
	}

	int tid, rid, did;
	for (int i=0; i<N; ++i) {
		fin >> tid >> rid >> did;
		vOrder.push_back(tid);
		vOrder.push_back(rid);
		vOrder.push_back(did);
	}
}

void readInput(int& R, int& D, int& M, int& C, int& N, 
			vector<double>& vRest, vector<double>& vDist, vector<int>& vOrder) {
	
	vRest.clear();
	vDist.clear();
	vOrder.clear();
	scanf("%d %d %d %d %d", &R, &D, &M, &C, &N);

	double x, y;
	for (int i=0; i<R; ++i) {
		scanf("%d %d", &x, &y);
		vRest.push_back(x);
		vRest.push_back(y);
	}

	for (int i=0; i<D; ++i) {
		scanf("%d %d", &x, &y);
		vDist.push_back(x);
		vDist.push_back(y);
	}

	int tid, rid, did;
	for (int i=0; i<N; ++i) {
		scanf("%d %d %d", &tid, &rid, &did);
		vOrder.push_back(tid);
		vOrder.push_back(rid);
		vOrder.push_back(did);
	}	
}

void readInput(const ifstream& fin, int& R, int& D, int& M, int& C, int& N, 
			vector<double>& vRest, vector<double>& vDist, vector<int>& vOrder) {

	vRest.clear();
	vDist.clear();
	vOrder.clear();
	fin >> R >> D >> M >> C >> N;

	double x, y;
	for (int i=0; i<R; ++i) {
		fin >> x >> y;
		vRest.push_back(x);
		vRest.push_back(y);
	}

	for (int i=0; i<D; ++i) {
		fin >> x >> y;
		vDist.push_back(x);
		vDist.push_back(y);
	}

	int tid, rid, did;
	for (int i=0; i<N; ++i) {
		fin >> tid >> rid >> did;
		vOrder.push_back(tid);
		vOrder.push_back(rid);
		vOrder.push_back(did);
	}
}

void readInput(const string& fileName, int& R, int& D, int& M, int& C, int& N, 
			vector<int>& vRest, vector<int>& vDist, vector<int>& vOrder) {
	ifstream fin(fileName.c_str(), ios::in);

	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	readInput(fin, R, D, M, C, N, vRest, vDist, vOrder);

	fin.close();
}

void readInput(const string& fileName, int& R, int& D, int& M, int& C, int& N, 
			vector<double>& vRest, vector<double>& vDist, vector<int>& vOrder) {
	ifstream fin(fileName.c_str(), ios::in);

	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	readInput(fin, R, D, M, C, N, vRest, vDist, vOrder);

	fin.close();
}

#endif