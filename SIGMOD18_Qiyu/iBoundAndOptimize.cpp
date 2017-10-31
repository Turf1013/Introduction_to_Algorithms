/**
	\author:	Trasier
	\date:		2017.10.31
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

#define LOCAL_DEBUG

clock_t begTime, endTime;
vector<bool> visit;
vector<int> vecI1starS;
vector<double> bs;
int maxp;
double minf, minEstate;

double calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points);
double calc_ubgv(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points);
double calc_deltaBenefit(const station_t& station, const vector<point_t>& points);
double calc_deltaCost(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points);
bool planStation(plan_t& plan, station_t& station, double budget);

plan_t bndAndOpt(double& budget) {
	plan_t plan;
	station_t station;

	while (budget >= minEstate) {
		double mxVal = -inf, tmp;
		int v = -1;
		station.reset();
		for (int i=0; i<points.size(); ++i) {
			if (visit[i] || budget<points[i].ep)
				continue;
			station.id = i;
			tmp = calc_ubgv(i, plan, station, points);
			if (tmp > mxVal) {
				mxVal = tmp;
				v = i;
			}
		}
		if (v < 0)
			break;

		visit[v] = true;
		station.id = v;
		station.p = points[v];
		station.reset();
		if (planStation(plan, station, budget) && station.hasCharger()) {
			plan.push_back(station);
			budget -= calc_fs(station, points);
			#ifdef LOCAL_DEBUG
			assert(budget >= 0);
			#endif
			update_yIndicator(plan, points);
		}
	}

	return plan;
}


void init() {
	init_global(vecSumDemands, yIndicator, points);

	maxp = INT_MIN;
	minf = inf;
	for (int i=0; i<chargers.size(); ++i) {
		maxp = max(maxp, chargers[i].p);
		minf = min(minf, chargers[i].f);
	}
	visit.resize(points.size(), false);

	vecI1starS.resize(points.size(), 0);
	for (int j=0; j<points.size(); ++j) {
		int& sum = vecI1starS[j];
		for (int i=0; i<points.size(); ++i) {
			if (calc_distance(i, j) <= rmax)
				++sum;
		}
	}

	minEstate = inf;
	for (int i=0; i<points.size(); ++i)
		minEstate = min(minEstate, points[i].ep);
}

double solve() {
	string execName("ibao");
	init();

	double ret = 0.0;
	plan_t plan;
	double budget;

	for (int i=0; i<bs.size(); ++i) {
		budget = bs[i];
		plan_t tmp = bndAndOpt(budget);
		mergeTwoPlan(plan, tmp);
		fill(visit.begin(), visit.end(), false);
		for (int j=0; j<plan.size(); ++j) {
			visit[plan[j].id] = true;
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

int calc_I1starS(const station_t& station, const vector<point_t>& points) {
	if (vecI1starS.size() == points.size())
		return vecI1starS[station.id];

	int ret = 0;

	for (int i=0; i<points.size(); ++i) {
		if (calc_distance(station.p, points[i]) <= rmax)
			++ret;
	}

	return ret;
}

inline double _calc_fs() {
	return K * minf;
}

inline double _calc_cs() {
	return K * maxp;
}

double _calc_rho(const station_t& station, const vector<point_t>& points) {
	int sumDemands = calc_demands(station, points);

	double ret = sumDemands*1.0 / _calc_cs();
	if (ret >= 1.0)
		ret = 0.999999;
	#ifdef LOCAL_DEBUG
	assert(ret < 1.0);
	#endif
	return ret;
}

double _calc_ws(const station_t& station, const vector<point_t>& points) {
	double rho = _calc_rho(station, points);
	double tau = 1.0 / _calc_cs();
	return rho * tau / (2.0 * (1.0 - rho));
}

double calc_deltaBenefit(const station_t& station, const vector<point_t>& points) {
	double ret;
	int I1starS = calc_I1starS(station, points);
	// int I2S = calc_I2S(station, points);
	double ws = _calc_ws(station, points);

	ret = 2.0 / (1.0 + exp(-ws * I1starS)) - 1.0;
	return ret;
}

double calc_costb_bound(const station_t& station) {
	return 0.0;
	double ret;
	ret = _calc_ws(station, points) + 1.0 / _calc_cs();
	return ret;
}

double calc_deltaCost(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points) {
	return 0.0;

	double ret = 0.0;
	plan_t newPlan = plan;
	newPlan.push_back(station);
	vector<int>& yvs = yIndicator;

	for (int i=0; i<newPlan.size(); ++i) {
		for (int j=0; j<yvs.size(); ++j) {
			if (yvs[j] == newPlan[i].id) {
				double costt = calc_distance(j, plan[i].id);
				double costb = calc_costb_bound(station);
				ret += points[j].d * (alpha*costt + (1.0-alpha)*costb);
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

pdd calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points, double social_p) {
	if (station.hasCharger())
		plan.push_back(station);

	update_yIndicator(plan, points);
	double social_ps = calc_social(plan, points);
	double fs = calc_fs(station, points);
	if (station.hasCharger())
		plan.pop_back();
	// double social_p = calc_social(plan, points);

	double ret = (social_ps - social_p) / fs;

	restore_yIndicator(plan, points);

	return make_pair(ret, social_ps);
}

/**
	dp[i][j][k] = min{dp[i][j-chargers[i].p][k-1]}
*/
double KnapsackBasedOpt(station_t& station) {
	int sumDemands = calc_demands(station, points);
	int bound = sumDemands + maxp;
	vector<vector<double> > dp(K+1, vector<double>(bound+5, inf));
	vector<vector<int> > dps(K+1, vector<int>(bound+5, -1));

	dp[0][0] = 0.0;
	for (int i=0; i<chargers.size(); ++i) {
		for (int k=K; k>=1; --k) {
			for (int j=chargers[i].p; j<=bound; ++j) {
				if (dp[k-1][j-chargers[i].p] >= inf)
					continue;
				double tmp = dp[k-1][j-chargers[i].p]+chargers[i].f;
				if (tmp < dp[k][j]) {
					dp[k][j] = tmp;
					dps[k][j] = i;
				}
			}
		}
	}

	double mnVal = inf;
	int ii = -1, kk = -1;
	for (int k=1; k<=K; ++k) {
		for (int i=sumDemands; i<=bound; ++i) {
			if (dp[k][i] < mnVal) {
				mnVal = dp[k][i];
				ii = i;
				kk = k;
			}
		}
	}
	if (ii==-1 || kk==-1) return inf;

	int v;

	station.reset();
	while (ii > 0) {
		v = dps[kk][ii];
		station.x[v]++;
		ii -= chargers[v].p;
		--kk;
		#ifdef LOCAL_DEBUG
		assert(ii>=0 && ii<=bound);
		#endif
	}
	#ifdef LOCAL_DEBUG
	assert(ii == 0);
	assert(dcmp(station.fs() - mnVal) == 0);
	#endif

	return mnVal + calc_estatePrice(station, points);
}

bool planStation(plan_t& plan, station_t& station, double budget) {
	double price = KnapsackBasedOpt(station);

	if (price > budget) {
		station.reset();
		return false;
	}

	int c = station.getChargerNum();
	budget -= price;
	while (c<=K && budget>=0) {
		double social0 = calc_social(plan, points);
		pdd dtmp = calc_gs(plan, station, points, social0);
		double gs0 = dtmp.first, mxVal = 0, tmp;

		int v = -1;
		for (int j=0; j<chargers.size(); ++j) {
			if (budget < chargers[j].f)
				continue;
			station.x[j]++;
			dtmp = calc_gs(plan, station, points, social0);
			tmp = dtmp.first - gs0;
			if (tmp > mxVal) {
				mxVal = tmp;
				v =j;
			}
			station.x[j]--;
		}
		if (v < 0) break;
		budget -= chargers[v].f;
		station.x[v]++;
		++c;
	}

	return true;
}

int main(int argc, char **argv) {
	string execName("ibao");
	string priceFileName("./prices.txt");

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
