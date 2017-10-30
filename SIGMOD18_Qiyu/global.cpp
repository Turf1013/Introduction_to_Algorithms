/**
	\author:	Trasier
	\date:		2017.10.26
*/
#include <bits/stdc++.h>
using namespace std;

#include "global.h"



const double eps = 1e-6;
const double inf = 1e30;
int chargerN;
double rmax;
double alpha;
double lambda;
double B;
int K;
int nV, nE;
double usedTime = -1;
int usedMemory = -1;
vector<charger_t> chargers;
vector<set<int> > covered;
#ifdef	USE_ARRAY
	// vector<vector<double> > dists;
	double dists[MAXN][MAXN];
#else
	#ifndef USE_SQL
	map<pii,double> dists;
	#endif
#endif
vector<point_t> points;
vector<int> vecSumDemands;
vector<int> yIndicator;

void init_global_sumDemands(vector<int>& vecSumDemands, const vector<point_t>& points) {
	vecSumDemands.resize(nV, 0);
	for (int j=0; j<nV; ++j) {
		int& sum = vecSumDemands[j];
		for (int i=0; i<points.size(); ++i) {
			if (calc_distance(i, j) <= rmax) {
				sum += points[i].d;
			}
		}
	}
}

static vector<int> yIndicator_bk;
void init_global_yIndicator(vector<int>& yIndicator, const vector<point_t>& points) {
	yIndicator.resize(nV, -1);
	yIndicator_bk.resize(nV, -1);
}

void init_global(vector<int>& vecSumDemands, vector<int>& yIndicator, const vector<point_t>& points) {
	init_global_sumDemands(vecSumDemands, points);
	init_global_yIndicator(yIndicator, points);
}

int dcmp(double x) {
	if (fabs(x) < eps)
		return 0;
	return x > 0 ? 1 : -1;
}

double calc_distance(const point_t& a, const point_t& b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

double calc_rs(const station_t& station) {
	double cs = station.cs();
	return rmax * (2.0 / (1.0 + exp(-cs)) - 1.0);
}

void update_covered(const station_t& station, const vector<point_t>& points) {
	double rs = calc_rs(station);

	for (int i=0; i<points.size(); ++i) {
		if (calc_distance(station.id, i) <= rs)
			covered[i].insert(station.id);
	}
}

void update_covered(const plan_t& plan, const vector<point_t>& points) {
	return ;
	for (int i=0; i<covered.size(); ++i)
		covered[i].clear();
	for (int i=0; i<plan.size(); ++i) {
		update_covered(plan[i], points);
	}
}

int calc_I1S(const station_t& station, const vector<point_t>& points) {
	int ret = 0;
	double rs = calc_rs(station);

	for (int i=0; i<points.size(); ++i) {
		if (calc_distance(station.id, i) <= rs)
			++ret;
	}

	return ret;
}

int calc_I2S(const station_t& station, const vector<point_t>& points) {
	return 0;
	int ret = 0;

	for (int i=0; i<points.size(); ++i) {
		if (covered[i].count(station.id)>0 && covered[i].size()>1)
			++ret;
	}

	return ret;
}

double calc_benefit(const station_t& station, const vector<point_t>& points) {
	// double i1s = calc_I1S(station, points), i2s = calc_I2S(station, points);
	double i1s = calc_I1S(station, points);
	const point_t& p = points[station.id];
	printf("rs = %.12lf, i1s = %.0lf, p.w = %.12lf\n", calc_rs(station), i1s, p.w);
	return 2.0 / (1.0 + exp(-p.w * i1s)) - 1.0;
}

double calc_benefit(const plan_t& plan, const vector<point_t>& points) {
	double ret = 0.0, tmp;

	// update_covered(plan, points);
	for (int i=0; i<plan.size(); ++i) {
		tmp = calc_benefit(plan[i], points);
		ret += tmp;
		printf("calc_benefit %d: tmp = %.12lf\n", plan[i].id, tmp);
	}

	return ret;
}

double calc_distance(int a, int b) {
	#ifdef USE_ARRAY
		return dists[a][b];
	#else
		#ifndef USE_SQL
		pii p = make_pair(a, b);
		if (dists.count(p) > 0)
			return dists[p];
		else
			return 130000.0;
		#endif
	#endif
}

double calc_costt(const plan_t& plan, const vector<point_t>& points) {
	double ret = 0.0;
	vector<int>& y = yIndicator;

	y = calc_yvs(plan, points);
	for (int i=0; i<plan.size(); ++i) {
		for (int j=0; j<y.size(); ++j) {
			if (y[j] == i) {
				ret += points[j].d * calc_distance(j, plan[i].id);
			}
		}
	}

	return ret;
}

vector<int> calc_yvs(const plan_t& plan, const vector<point_t>& points) {
	return stationSeeking(plan, points);
}

double calc_ds(const station_t& station, const vector<point_t>& points, const vector<int>& y) {
	double ret = 0.0;

	for (int i=0; i<y.size(); ++i) {
		if (y[i] == station.id) {
			ret += points[i].d / calc_distance(i, station.id);
		}
	}

	return ret;
}

int calc_demands(const station_t& station, const vector<point_t>& points) {
	if (vecSumDemands.size() == nV)
		return vecSumDemands[station.id];

	int ret = 0;

	for (int i=0; i<points.size(); ++i) {
		if (calc_distance(i, station.id) <= rmax) {
			ret += points[i].d;
		}
	}

	return ret;
}

double calc_rho(const station_t& station, const vector<point_t>& points) {
	int cs = station.cs();
	if (cs == 0) return 2.0;
	int sumDemands = calc_demands(station, points);

	return sumDemands*1.0 / station.cs();
}

double calc_ws(const station_t& station, const vector<point_t>& points) {
	double rho = calc_rho(station, points);
	double tau = 1.0 / station.cs();
	return rho * tau / (2.0 * (1.0 - rho));
}

double calc_costb(const plan_t& plan, const vector<point_t>& points) {
	double ret = 0.0;
	vector<int>& y = yIndicator;

	for (int i=0; i<plan.size(); ++i) {
		station_t station = plan[i];
		double ds = calc_ds(station, points, y);
		double ws = calc_ws(station, points);
		double cs = station.cs();
		ret += ds * (ws + 1.0 / cs);
	}

	return ret;
}

double calc_cost(const plan_t& plan, const vector<point_t>& points) {
	double ret;
	double costt = calc_costt(plan, points);
	double costb = calc_costb(plan, points);

	ret = alpha * costt + (1.0 - alpha) * costb;

	return ret;
}

double calc_social(const plan_t& plan, const vector<point_t>& points) {
	double ret;
	double benefit = calc_benefit(plan, points);
	double cost = calc_cost(plan, points);

	// if (plan.size() >= 180) {
		// plan.print();
		printf("calc_social: benefit = %.8lf, cost = %.8lf\n", benefit, cost);
	// }

	ret = lambda * benefit - (1.0 - lambda) * cost;

	return ret;
}

double calc_costa(int v, const station_t& station, const vector<point_t>& points) {
	double ret;
	double dist_vs = calc_distance(v, station.id);
	double ws = calc_ws(station, points);
	double cs = station.cs();
	double dv = points[v].d;

	ret = dv * (alpha * dist_vs + (1.0-alpha) * (ws + 1.0/cs));

	return ret;
}

vector<int> stationSeeking(const plan_t& plan, const vector<point_t>& points) {
	vector<int> ret(points.size(), -1);

	for (int v=0; v<points.size(); ++v) {
		double mnVal = inf;
		int& sid = ret[v];
		for (int j=0; j<plan.size(); ++j) {
			double costa = calc_costa(v, plan[j], points);
			if (costa < mnVal) {
				mnVal = costa;
				sid = j;
			}
		}
	}

	return ret;
}

void dumpResult(string execName, double result) {
	printf("%s %.6lf", execName.c_str(), result);
	if (usedTime >= 0)
		printf(" %.3lf", usedTime);
	if (usedMemory >= 0)
		printf(" %.3lf", usedMemory/1024.0);
	putchar('\n');
	fflush(stdout);
}

double calc_estatePrice(const station_t& station, const vector<point_t>& points) {
	return points[station.id].ep;
}

double calc_fs(const station_t& station, const vector<point_t>& points) {
	return station.fs() + calc_estatePrice(station, points);
}

void update_yIndicator(plan_t& plan, const station_t& station, const vector<point_t>& points) {
	int sid = station.id;

	yIndicator_bk = yIndicator;
	for (int v=0; v<points.size(); ++v) {
		if (yIndicator[v] == -1) {
			yIndicator[v] = sid;
			continue;
		}
		double mnVal = calc_costa(v, plan[yIndicator[v]], points);
		double curVal = calc_costa(v, station, points);
		if (curVal < mnVal) {
			yIndicator[v] = plan.size();
		}
	}
}

void restore_yIndicator(plan_t& plan, const station_t& station, const vector<point_t>& points) {
	yIndicator = yIndicator_bk;
}

void update_yIndicator(plan_t& plan, const vector<point_t>& points) {
	yIndicator_bk = yIndicator;
	yIndicator = stationSeeking(plan, points);
}
