/**
	\author:	Trasier
	\date:		2017.10.27
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

#define LOCAL_DEBUG

typedef long long LL;
vector<double> chargerPrices;

int calc_demand_vid(const int vid) {
	if (vecSumDemands.size() == nV)
		return vecSumDemands[vid];

	int ret = 0;

	for (int i=0; i<points.size(); ++i) {
		if (calc_distance(i, vid) <= rmax) {
			ret += points[i].d;
		}
	}

	return ret;
}

void init_chargerPrice() {
	chargerPrices.resize(K+1, 0.0);
	for (int i=1; i<=K; ++i) {
		chargerPrices[i] = chargerPrices[i-1] + chargers[0].f;
	}
}

void init() {
	init_global(vecSumDemands, yIndicator, points);
	init_chargerPrice();
	#ifdef LOCAL_DEBUG
	assert(chargerN = 1);
	#endif
}

double bestu = -inf, tmpu;
int cc[105];

plan_t genPlan() {
	station_t station;
	plan_t ret;
#ifdef LOCAL_DEBUG
	double tmp = 0;
#endif

	for (int i=0; i<nV; ++i) {
		if (cc[i] == 0)
			continue;
		station.id = i;
		station.x[0] = cc[i];
		ret.push_back(station);
#ifdef LOCAL_DEBUG
		tmp += calc_fs(station, points);
#endif
	}

#ifdef LOCAL_DEBUG
	assert(tmp <= B+5);
#endif

	return ret;
}

void updateBestPlan(plan_t& bestPlan) {
	plan_t plan = genPlan();
	update_yIndicator(plan, points);
	tmpu = calc_social(plan, points);
	if (tmpu > bestu) {
		bestu = tmpu;
		bestPlan = plan;
	}
}

void dfs(double budget, plan_t& bestPlan, int dep) {
	if (budget < 0) return ;
	if (dep == nV) {
		updateBestPlan(bestPlan);
		return ;
	}
	
	double budget_;
	for (int k=0; k<=K; ++k) {
		budget_ = budget - chargerPrices[k];
		if (k > 0) {
			budget_ -= points[dep].ep;
			int d = calc_demand_vid(dep);
			if (chargers[k].p*k < d)
				continue;
		}
		if (budget_ < 0)
			continue;
		cc[dep] = k;
		dfs(budget_, bestPlan, dep+1);
	}
}

double solve() {
	init();

	double ret = 0.0;
	plan_t bestPlan;
	double budget = B;
	
	memset(cc, 0, sizeof(cc));
	dfs(budget, bestPlan, 0);
	update_yIndicator(bestPlan, points);
	ret = calc_social(bestPlan, points);
	dumpResult(bestPlan, points);

#ifdef LOCAL_DEBUG
	for (int i=0; i<bestPlan.size(); ++i) {
		station_t sta = bestPlan[i];
		printf("station at %d with %d charger.\n", sta.id, sta.x[0]);
	}
#endif

	return ret;
}

int main(int argc, char **argv) {
	string execName("OPT"), priceFileName("./prices.txt");

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}
	if (argc > 3) {
		priceFileName = string(argv[3]);
	}
	
	clock_t begTime, endTime;
	begTime = clock();
	
	read_all(cin, priceFileName);
	//nV = 20;

	double ans = solve();

	endTime = clock();
	usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;

	dumpResult(execName, ans);

	fflush(stdout);

	return 0;
}
