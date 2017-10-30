/**
	\author: 	Trasier
	\date:		2017.10.27
*/
#ifndef VORONI_H
#define VORONI_H

#include <bits/stdc++.h>
using namespace std;

struct point_t {
	double x, y;
	
	point_t(double x=0., double y=0.):
		x(x), y(y) {}
};

double calc_distance(point_t& a, point_t& b);
vector<vector<int> > voroniSplit(const vector<point_t>& points, const vector<point_t>& center);


#endif
