/**
	\author:	Trasier
	\date:		2017.10.27
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

double calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points);

plan_t bndAndOpt() {
	plan_t P;
	double B = ::B;
	
	while (B > 0) {
		for (int i=0; i<points.size(); ++i) {
			// calc_ubgv(points[i], );
		}
	}
	
	return P;
}

int main(int argc, char **argv) {
	
	return 0;
}

double calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points) {
	plan.push_back(station);
	double social_ps = calc_social(plan, points);
	plan.pop_back();
	double social_p = calc_social(plan, pointds);
	double fs = station.fs();
	
	return (social_ps - social_p) / fs;
}