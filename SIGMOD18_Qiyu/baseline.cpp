/**
	\author:	Trasier
	\date:		2017.10.27
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

#define LOCAL_DEBUG
#define RANDOM_SELECT

void planCharger(station_t& station, double budget) {
	int i, j, k, c=K;

	budget -= calc_estatePrice(station, points);
	for (j=0; j<chargerN; ++j) {
		k = min(c, (int)(budget/chargers[j].f));
		budget -= chargers[j].f * k;
		c -= k;
		station.x[j] = k;
		if (c==0 || budget<=0)
			break;
	}

	if (calc_rho(station, points) > 1)
		station.reset();
}

bool cmpCharger(const charger_t& a, const charger_t& b) {
	//return (a.p*b.f) > (b.p*a.f);
	return a.p > b.p;
}

bool cmpDemand(const int& a, const int& b) {
	return points[a].d > points[b].d;
}

vector<int> permu;
double solve() {
	sort(chargers.begin(), chargers.end(), cmpCharger);

	double ret = 0.0;
	plan_t plan;
	double budget = B;
	station_t station;

	for (int i=0; i<nV; ++i) {
		permu.push_back(i);
	}
	#ifdef RANDOM_SELECT
	random_shuffle(permu.begin(), permu.end());
	#else
	sort(permu.begin(), permu.end(), cmpDemand);
	#endif

	for (int i=0; budget>0&&i<nV; ++i) {
		station.reset();
		station.id = i;
		if (budget < calc_estatePrice(station, points))
			continue;
		planCharger(station, budget);
		if (station.hasCharger()) {
			station.p = points[i];
			budget -= calc_fs(station, points);
			plan.push_back(station);
		}
	}

	ret = calc_benefit(plan, points);

	return ret;
}

int main(int argc, char **argv) {
	string execName("base");

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
	#ifdef RANDOM_SELECT
	for (int i=0; i<permu.size(); ++i) {
		printf("%d ", permu[i]);
	}
	putchar('\n');
	#endif
	fflush(stdout);

	return 0;
}
