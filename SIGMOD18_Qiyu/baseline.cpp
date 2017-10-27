/**
	\author:	Trasier
	\date:		2017.10.27
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

#define LOCAL_DEBUG

void planCharger(station_t& station, double budget) {
	int i, j, k, c=K;
	
	budget -= calc_estatePrice(station, points);
	for (j=0; j<chargerN; ++j) {
		k = min(c, budget/chargers[j].f);
		budget -= chargers[j].f * k;
		c -= k;
		station[j] = k;
		if (c==0 || budget<=0)
			break;
	}
}

bool cmpCharger(const charger_t& a, const charger_t& b) {
	return (a.p*b.f) > (b.p*a.f);
} 

double solve() {
	sort(chargers.begin(), chargers.end(), cmpCharger);
	
	double ret = 0.0;
	vector<int> permu;
	plan_t plan;
	double budget = B;
	station_t station;
	
	for (int i=0; i<nV; ++i) {
		permu.push_back(i);
	}
	random_shuffle(perm.begin(), permu.end());
	
	for (int i=0; budget>0&&i<nV; ++i) {
		station.reset();
		station.id = i;
		if (budget < calc_estatePrice(station, budget))
			continue;
		planCharger(station, budget);
		if (station.hasCharger()) {
			budget -= calc_fs(station, points);
			plan.push_back(station);
		}
	}
	
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
