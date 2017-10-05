/**
	1. input data
	2. \author: Trasier
	3. \date:   2017.10.5
*/
#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

struct item_t {
	LL lcm;
	double uc;

	item_t(LL lcm=0, double uc=0.0):
		lcm(lcm), uc(uc) {}

	bool operator<(const item_t& i) const {
		if (lcm != i.lcm)
			return lcm > i.lcm;
		else
			return uc < i.uc;
	}
};

typedef set<item_t> priQueue;
typedef set<item_t>::iterator priQueueIter;

struct bin_t {
	int l;
	double c, r;
	
	friend istream& operator>>(istream& fin, bin_t& b) {
		fin >> b.l >> b.c >> b.r;
		return fin;
	}
};

void readInput(int& taskN, double*& threshs, int& binN, bin_t*& bins);
void readInput(const string& fileName, int& taskN, double*& threshs, int& binN, bin_t*& bins);
void readInput(istream& fin, int& taskN, double*& threshs, int& binN, bin_t*& bins);

void readInput(const string& fileName, int& taskN, double*& threshs, int& binN, bin_t*& bins) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	readInput(fin, taskN, threshs, binN, bins);
	fin.close();
}

void readInput(istream& fin, int& taskN, double*& threshs, int& binN, bin_t*& bins) {
	fin >> taskN;
	if (threshs == NULL)
		threshs = new double[taskN];
	for (int i=0; i<taskN; ++i)
		fin >> threshs[i];
	fin >> binN;
	if (bins == NULL)
		bins = new bin_t[binN];
	for (int i=0; i<binN; ++i)
		fin >> bins[i];
}

void readInput(int& taskN, double*& threshs, int& binN, bin_t*& bins) {
	readInput(cin, taskN, threshs, binN, bins);
}

#endif
