/**
	1. global
	2. \author: Trasier
	3. \date:   2017.10.5
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "input.h"
#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
const int maxBinNum = 5000;
const double inf = 1LL<<50;
typedef pair<double,int> pdi;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

LL __lcm(LL a, LL b);
double log2(double x);
double exp2(int x);

LL __lcm(LL a, LL b) {
	LL g = __gcd(a, b);
	return a/g*b;
}

double log2(double x) {
	return log(x) / log(2.0);
}

double exp2(int x) {
	if (x <= 0) return 1.0;
	double ret = 1.0;
	for (int i=1; i<=x; ++i) ret *= 2.0;
	return ret;
}

item_t calcItem(int* itemS, bin_t* bins, int n) {
	item_t ret(1, 0.0);
	int i = 0, j, k;
	LL lcm;

	while (i < n) {
		j = i, k = itemS[j];
		while (i<n && itemS[i]==itemS[j]) ++i;
		ret.lcm = __lcm(ret.lcm, 1LL*bins[k].l);
		ret.uc += (i-j) * bins[k].c / bins[k].l;
	}

	return ret;
}

#endif
