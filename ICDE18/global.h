/**
	1. global
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "input.h"

const double eps = 1e-4;
const double dmax = 5;
typedef pair<int,int> pii;
typedef pair<double,int> pdi;
typedef pair<double,double> pdd;

double hardAccArr[6][24] = {
		{0.88,0.87,0.89,0.89,0.93,0.75,0.83,0.87,0.94,0.85,0.91,0.87,0.78,0.84,0.76,0.75,0.83,0.79,0.81,0.83,0.72,0.81,0.72,0.73},
		{0.89,0.88,0.88,0.88,0.94,0.82,0.74,0.89,0.92,0.81,0.93,0.88,0.72,0.80,0.79,0.81,0.76,0.78,0.81,0.84,0.75,0.72,0.71,0.74},
		{0.88,0.86,0.87,0.87,0.74,0.92,0.83,0.68,0.65,0.70,0.72,0.66,0.77,0.83,0.81,0.73,0.73,0.79,0.80,0.82,0.83,0.75,0.81,0.72},
		{0.87,0.87,0.88,0.88,0.72,0.91,0.72,0.71,0.71,0.62,0.65,0.71,0.75,0.82,0.77,0.78,0.71,0.80,0.82,0.84,0.82,0.84,0.78,0.70},
		{0.76,0.75,0.71,0.65,0.88,0.86,0.85,0.87,0.71,0.92,0.96,0.88,0.72,0.69,0.73,0.71,0.74,0.81,0.71,0.75,0.78,0.80,0.78,0.65},
		{0.64,0.72,0.62,0.71,0.90,0.85,0.87,0.84,0.61,0.92,0.95,0.77,0.83,0.72,0.75,0.75,0.76,0.82,0.81,0.83,0.77,0.79,0.83,0.81}
};

double Length(const location_t& a, const location_t& b) {
	return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

double calcPredictAcc(const task_t& t, const worker_t& w) {
	double l = Length(t.loc, w.loc), p;
	if (l >= dmax)
		p = 0.5 + eps;
	else
		p = w.p * (rand()%2+8) / 10.0;
	if (p <= 0.5) p = 0.5 + eps;
	p = hardAccArr[t.id][w.id];
	return p;
}

double calcUtility(const task_t& t, const worker_t& w) {
	// double p = calcPredictAcc(t, w);
	double p = hardAccArr[t.id][w.id];

	double q = (p+p-1.0)*(p+p-1.0);
	return q;
}

double calcDelta(double epsilon) {
	if (epsilon <= 0) epsilon = eps;
	return 2 * log(1.0 / epsilon);
}

#endif
