/**
	\author:	Trasier
	\date:		2017.10.28
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

// #define LOCAL_DEBUG
// #define RANDOM_SELECT

clock_t begTime, endTime;
vector<double> bs;
vector<int> permu;
vector<bool> visit;

void planCharger(station_t& station, double budget) {
	#ifdef LOCAL_DEBUG
	printf("id = %d, budget = %.2lf, estatPrice = %.2lf\n", station.id, budget, calc_estatePrice(station, points));
	//fflush(stdout);
	#endif
	int i, j, k, c=K;

	station.reset();
	budget -= calc_estatePrice(station, points);
	if (budget <= 0) 
		return ;
	for (j=0; j<chargerN; ++j) {
		k = min(c, (int)(budget/chargers[j].f));
		budget -= chargers[j].f * k;
		c -= k;
	#ifdef LOCAL_DEBUG
		assert(k>=0 && budget>=0);
	#endif
		station.x[j] = k;
		if (c==0 || budget<=0)
			break;
	}
	#ifdef LOCAL_DEBUG
	if(station.id >= 18268)
		printf("%d %.2lf\n", station.cs(), budget);
	#endif

	if (calc_rho(station, points) > 1) {
		
		#ifdef LOCAL_DEBUG
		printf("budget or charger is not enough for node %d: need %d, have %d\n", 
				station.id, calc_demands(station, points), station.cs());
		#endif
		station.reset();
	}
	
	#ifdef LOCAL_DEBUG
	printf("station for %d: ", station.id);
	station.print();
	#endif
}

bool cmpCharger(const charger_t& a, const charger_t& b) {
	//return (a.p*b.f) > (b.p*a.f);
	return a.p > b.p;
}

bool cmpDemand(const int& a, const int& b) {
	return points[a].d > points[b].d;
}

void init() {
	init_global(vecSumDemands, yIndicator, points);

	for (int i=0; i<nV; ++i) {
		permu.push_back(i);
		visit.push_back(false);
	}

	sort(chargers.begin(), chargers.end(), cmpCharger);
	sort(permu.begin(), permu.end(), cmpDemand);
}

plan_t planOnce(double budget) {
	plan_t plan;
	station_t station;

	for (int i=0; budget>0&&i<nV; ++i) {
		if (visit[i])
			continue;
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
		#ifdef LOCAL_DEBUG
		printf("%d: plan.size() = %d, plan.cs()= %d\n", i, plan.size(), plan.cs());
		fflush(stdout);
		#endif
	}

	return plan;
}

double solve() {
	string execName("ibase");
	init();

	double ret = 0.0;
	plan_t plan;
	double budget;

	for (int i=0; i<bs.size(); ++i) {
		budget = bs[i];
		plan_t tmpPlan = planOnce(budget);
		mergeTwoPlan(plan, tmpPlan);
		for (int j=0; j<tmpPlan.size(); ++j) {
			visit[tmpPlan[j].id] = true;
		}

		update_yIndicator(plan, points);
		ret = calc_social(plan, points);

		dumpResult(plan, points);

		endTime = clock();
		usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;

		dumpResult(execName, ret);
	}

	return ret;
}

int main(int argc, char **argv) {
	string execName("ibase"), priceFileName("./prices.txt");

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}
	if (argc > 3) {
		priceFileName = string(argv[3]);
	}
	
	begTime = clock();

	read_incremental(cin, priceFileName, bs);

	double ans = solve();

	// endTime = clock();
	// usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;

	// dumpResult(execName, ans);

	fflush(stdout);

	return 0;
}
