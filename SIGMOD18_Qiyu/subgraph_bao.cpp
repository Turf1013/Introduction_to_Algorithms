/**
	\author:	Trasier
	\date:		2017.10.27
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"

#define LOCAL_DEBUG

vector<bool> visit;
vector<int> vecI1starS;
vector<vector<int> > clusters;
int ksub;
int maxp;
double minf;

double calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points);
double calc_ubgv(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points);
double calc_deltaBenefit(const station_t& station, const vector<point_t>& points);
double calc_deltaCost(int v, const plan_t& plan, const station_t& station, const vector<point_t>& points);
bool planStation(plan_t& plan, station_t& station, double budget);
plan_t bndAndOpt(double& budget);
plan_t bndAndOpt(int clusterId, double& budget);

plan_t bndAndOpt(double& budget) {
	plan_t plan;
	station_t station;

	while (budget > 0) {
		double mxVal = -inf, tmp;
		int v = -1;
		station.reset();
		for (int i=0; i<points.size(); ++i) {
			if (visit[i])
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

		station.id = v;
		station.p = points[v];
		if (planStation(plan, station, budget)) {
			visit[v] = true;
			plan.push_back(station);
			budget -= calc_fs(station, points);
			#ifdef LOCAL_DEBUG
			assert(budget >= 0);
			#endif
		}
	}

	return plan;
}

plan_t bndAndOpt(int clusterId, double& budget) {
	plan_t plan;
	station_t station;
	vector<int>& pointIds = clusters[clusterId];
	
	while (budget > 0) {
		double mxVal = -inf, tmp;
		int v = -1;
		station.reset();
		for (int i=0; i<pointIds.size(); ++i) {
			int pointId = pointIds[i];
			station.id = pointId;
			tmp = calc_ubgv(pointId, plan, station, points);
			if (tmp > mxVal) {
				mxVal = tmp;
				v = pointId;
			}
		}
		if (v < 0)
			break;

		station.id = v;
		station.p = points[v];
		if (planStation(plan, station, budget)) {
			plan.push_back(station);
			budget -= calc_fs(station, points);
			visit[v] = true;
			#ifdef LOCAL_DEBUG
			assert(budget >= 0);
			#endif
		}
	}

	return plan;
}

void init_subgraph() {
	int n;
	
	cin >> ksub;
	for (int i=0; i<ksub; ++i) {
		cin >> n;
		vector<int> vtmp(n, -1);
		for (int j=0; j<n; ++j) {
			cin >> vtmp[j];
		}
		clusters.push_back(vtmp);
	}
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
			if (calc_distance(j, points[i]) <= rmax)
				++sum;
		}
	}
	
	init_subgraph();
}

void mergeTwoPlan(plan_t& des, plan_t& src) {
	for (int i=0; i<src.size(); ++i)
		des.push_back(src[i]);
}

double solve() {
	double budget = 0.0, budget_ = B / ksub, tmp;
	plan_t plan;
	init();

	for (int i=0; i<ksub; ++i) {
		tmp = budget_;
		plan_t tmpPlan = bndAndOpt(tmp);
		mergeTwoPlan(plan, tmpPlan);
		budget += tmp;
	}
	if (budget > 0) {
		plan_t tmpPlan = bndAndOpt(budget);
		mergeTwoPlan(plan, tmpPlan);
	}
	
	double ret = calc_benefit(plan, points);
		
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

	return sumDemands*1.0 / _calc_cs();
}

double _calc_ws(const station_t& station, const vector<point_t>& points) {
	double rho = _calc_rho(station, points);
	double tau = 1.0 / _calc_cs();
	return rho * tau / (2.0 * (1.0 - rho));
}

double calc_deltaBenefit(const station_t& station, const vector<point_t>& points) {
	double ret;
	int I1starS = calc_I1starS(station, points);
	int I2S = calc_I2S(station, points);
	double ws = _calc_ws(station, points);

	ret = 2.0 / (1.0 + exp(-ws * (I1starS - I2S))) - 1.0;
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
	vector<int> yvs = stationSeeking(newPlan, points);

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

double calc_gs(plan_t& plan, const station_t& station, const vector<point_t>& points) {
	plan.push_back(station);
	double social_ps = calc_social(plan, points);
	plan.pop_back();
	double social_p = calc_social(plan, points);
	double fs = calc_fs(station, points);

	return (social_ps - social_p) / fs;
}

double KnapsackBasedOpt(station_t& station) {
	int sumDemands = calc_demands(station, points);
	int bound = sumDemands + maxp;
	vector<double> dp(bound+5, inf);
	vector<int> dps(bound+5, -1);

	dp[0] = 0.0;
	for (int i=0; i<chargers.size(); ++i) {
		for (int j=chargers[i].p; j<=bound; ++j) {
			if (dp[j-chargers[i].p] >= inf)
				continue;
			double tmp = dp[j-chargers[i].p]+chargers[i].f;
			if (tmp < dp[j]) {
				dp[j] = tmp;
				dps[j] = i;
			}
		}
	}

	double mnVal = inf;
	int w = -1, v;
	for (int i=sumDemands; i<=bound; ++i) {
		if (dp[i] < mnVal) {
			mnVal = dp[i];
			w = i;
		}
	}
	if (w == -1) return inf;

	station.reset();
	while (w > 0) {
		v = dps[w];
		station.x[v]++;
		w -= chargers[v].p;
		#ifdef LOCAL_DEBUG
		assert(w>=0 && w<=bound);
		#endif
	}
	#ifdef LOCAL_DEBUG
	assert(w == 0);
	assert(dcmp(station.fs() - mnVal) == 0);
	#endif

	return mnVal;
}

bool planStation(plan_t& plan, station_t& station, double budget) {
	double price = KnapsackBasedOpt(station);

	if (price > budget)
		return false;

	int c = station.cs();
	budget -= price;
	while (c <= K) {
		double gs0 = calc_gs(plan, station, points), mxVal = 0, tmp;
		int v = -1;
		for (int j=0; j<chargers.size(); ++j) {
			if (budget < chargers[j].f)
				continue;
			station.x[j]++;
			tmp = calc_gs(plan, station, points) - gs0;
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
	string execName("sbao");

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
