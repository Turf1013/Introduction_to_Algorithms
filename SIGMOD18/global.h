/**
	\author: 	Trasier
	\date: 		2017.10.13
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"

const double inf = 1e20;
int usedMemory = -1;

double Length(const position_t& a, const position_t& b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

const double eps = 1e-6;
int dcmp(double x) {
	if (fabs(x) < eps)
		return 0;
	return x<0 ? -1:1;
}

#endif