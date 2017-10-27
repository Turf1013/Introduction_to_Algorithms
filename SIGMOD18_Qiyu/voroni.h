/**
	\author: 	Trasier
	\date:		2017.10.27
*/
#ifndef VORONI_H
#define VORONI_H

#include "global.h"

vector<vector<int> > voroniSplit(const vector<point_t>& points, const vector<point_t>& center);

vector<vector<int> > voroniSplit(const vector<point_t>& points, const vector<point_t>& center) {
	vector<vector<int> > ret(vector<int>(), center.size());

	for (int i=0; i<points.size(); ++i) {
		double mnVal = inf, tmp;
		int v = -1;
		for (int j=0; j<center.size(); ++j) {
			tmp = calc_distance(points[i], center[j]);
			if (tmp < mnVal) {
				mnVal = tmp;
				v = j;
			}
		}
		ret[v].push_back(i);
	}

	return ret;
}

#endif
