/**
	\author:	Trasier
	\date:		2017.10.27
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

#define LOCAL_DEBUG

double calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points);
double calc_ubgv(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points);
double calc_deltaBenefit(const station_t& station, const vector<point_t>& points);
double calc_deltaCost(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points);

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

double solve() {
	double ret = 0.0;

	plan_t plan = bndAndOpt();
	ret = calc_benefit(plan, points);

	return ret;
}

int main(int argc, char **argv) {
	string execName("bao");

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}
	
	read_all(cin);

	clock_t begTime, endTime;
	begTime = clock();

	double ans = solve();

	endTime = clock();
	usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;

	dumpResult(execName, ans);

	return 0;
}

int calc_I1starS(const station_t& station, const vector<point_t>& points) {
	int ret = 0;

	for (int i=0; i<points.size(); ++i) {
		if (calc_distance(station.p, points[i]) <= rmax)
			++ret;
	}

	return ret;
}

double calc_deltaBenefit(const station_t& station, const vector<point_t>& points) {
	double ret;
	int I1starS = calc_I1starS(station, points);
	int I2S = calc_I2S(station);
	double ws = calc_ws(station, points);

	ret = 2.0 / (1.0 + exp(-ws * (I1starS - I2S))) - 1.0;
	return ret;
}

double calc_deltaCost(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points) {
	double ret = 0.0;
	plan_t newPlan = plan;
	newPlan.push_back(station);
	vector<int> yvs = stationSeeking(newPlan, points);

	for (int i=0; i<newPlan.size(); ++i) {
		for (int j=0; j<yvs.size(); ++j) {
			if (yvs[j] == newPlan[i].id) {
				ret += points[j].d * calc_costa(j, newPlan[i], points);
			}
		}
	}

	return ret;
}

double calc_ubgv(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points) {
	double ret;
	double deltaBenefit = calc_deltaBenefit(station, points);
	double deltaCost = calc_deltaCost(v, plan, station, points);
	double estatePrice = calc_estatePrice(station, points);

	ret = (lambda*deltaBenefit - (1.0-lambda)*deltaCost) / estatePrice;
	return ret;
}

double calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points) {
	plan.push_back(station);
	double social_ps = calc_social(plan, points);
	plan.pop_back();
	double social_p = calc_social(plan, points);
	double estatePrice = calc_estatePrice(station, points);

	return (social_ps - social_p) / estatePrice;
}
