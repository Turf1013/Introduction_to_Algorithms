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

const int maxBinNum = 6;
const double inf = 1LL<<50;
typedef pair<double,int> pdi;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

LL __lcm(LL a, LL b);

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

#endif
