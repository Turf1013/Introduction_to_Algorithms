/**
	1. global
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "input.h"

const double eps = 1e-4;
const double dmax = 100 * 1.4122;
typedef pair<int,int> pii;
typedef pair<double,int> pdi;
typedef pair<double,double> pdd;

double Length(const location_t& a, const location_t& b) {
	return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

double calcUtility(const task_t& t, const worker_t& w) {
	double l = Length(t.loc, w.loc);
	return w.p * (dmax -l) / dmax;
}

double calcDelta(double epsilon) {
	if (epsilon <= 0) epsilon = eps;
	return 2 * log(1.0 / epsilon);
}

#endif
