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

double hardAccArr[6][20] = {
	0.90,0.91,0.89,0.87,0.83,0.82,0.75,0.83,0.87,0.91,0.84,0.85,0.83,0.87,0.81,0.78,0.75,0.83,0.67,0.61,
	0.91,0.92,0.91,0.89,0.87,0.87,0.82,0.74,0.89,0.92,0.82,0.81,0.78,0.88,0.82,0.72,0.81,0.76,0.68,0.52,
	0.83,0.82,0.85,0.86,0.82,0.65,0.74,0.83,0.68,0.72,0.65,0.70,0.79,0.66,0.71,0.65,0.70,0.77,0.66,0.55,
	0.87,0.82,0.82,0.85,0.81,0.71,0.72,0.72,0.81,0.69,0.71,0.62,0.75,0.71,0.64,0.71,0.72,0.71,0.74,0.64,
	0.76,0.81,0.81,0.85,0.82,0.86,0.88,0.85,0.87,0.83,0.70,0.71,0.78,0.68,0.73,0.72,0.71,0.74,0.61,0.63,
	0.64,0.82,0.85,0.81,0.79,0.85,0.90,0.87,0.84,0.85,0.61,0.62,0.68,0.77,0.75,0.63,0.65,0.66,0.76,0.65
};

double Length(const location_t& a, const location_t& b) {
	return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

double calcUtility(const task_t& t, const worker_t& w) {
	double l = Length(t.loc, w.loc);
	//return w.p * (dmax -l) / dmax;
	return hardAccArr[t.id][w.id];
}

double calcDelta(double epsilon) {
	if (epsilon <= 0) epsilon = eps;
	return 2 * log(1.0 / epsilon);
}

#endif
