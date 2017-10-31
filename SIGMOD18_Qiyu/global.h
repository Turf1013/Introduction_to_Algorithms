/**
	\author:	Trasier
	\date:		2017.10.26
*/
#ifndef GLOBAL_H
#define GLOBAL_H

// #define GLOBAL_DEBUG

#define MAXN 21005

// #define USE_MAP
#define USE_ARRAY

typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef pair<int,double> pid;
typedef pair<double,int> pdi;

#ifdef	USE_ARRAY
	// extern vector<vector<double> > dists;
	extern double dists[MAXN][MAXN];
#else
	#ifdef USE_MAP
	extern map<pii,double> dists;
	#endif
#endif
extern const double eps;
extern const double inf;
extern const double infw;
extern int chargerN;
extern double rmax;
extern double alpha;
extern double lambda;
extern double B;
extern int K;
extern int nV, nE;
extern double usedTime;
extern int usedMemory;
extern vector<int> vecSumDemands;
extern vector<int> yIndicator;

struct point_t {
	double x, y;
	int id;
	double w;
	int d;
	double ep;

	point_t(double x=0., double y=0., int id=0, double w=0., int d=0., double ep=0.):
		x(x), y(y),id(id),w(w),d(d),ep(ep) {}

	bool operator< (const point_t& oth) const {
		if (x != oth.x)
			return x < oth.x;
		else if (y != oth.y)
			return y < oth.y;
		else
			return id < oth.id;
	}
};
extern vector<point_t> points;

struct charger_t {
	double f;
	int p;

	charger_t(double f=0., int p=0.):
		f(f), p(p) {}
};
extern vector<charger_t> chargers;

struct station_t {
	int id;
	point_t p;
	vector<int> x;

	station_t(int id=0, point_t p_=point_t(0.,0.)):id(id),p(p_) {
		x.resize(chargerN, 0);
	}

	bool hasCharger() const {
		for (int i=0; i<x.size(); ++i) {
			if (x[i] > 0)
				return true;
		}
		return false;
	}

	int cs() const {
		int ret = 0;
		for (int i=0; i<chargerN; ++i) {
			ret += x[i] * chargers[i].p;
		}
		return ret;
	}

	int getChargerNum() const {
		int ret = 0;
		for (int i=0; i<chargerN; ++i) {
			ret += x[i];
		}
		return ret;
	}

	void reset() {
		for (int i=0; i<chargerN; ++i)
			x[i] = 0;
	}

	double fs() const {
		double ret = 0;
		for (int i=0; i<chargerN; ++i) {
			ret += x[i] * chargers[i].f;
		}
		return ret;
	}

	void print() const {
		putchar('[');
		for (int i=0; i<chargerN; ++i) {
			if (i == 0) {
				printf("%d", x[i]);
			} else {
				printf(", %d", x[i]);
			}
		}
		putchar(']');
		putchar('\n');
	}
};

struct plan_t {
	vector<station_t> stations;

	int size() const {
		return stations.size();
	}

	station_t operator[](int idx) const {
		return stations[idx];
	}

	void pop_back() {
		stations.pop_back();
	}

	void push_back(const station_t& station) {
		stations.push_back(station);
	}

	void print() const {
		printf("plan with %d stations\n", (int)stations.size());
		for (int i=0; i<stations.size(); ++i) {
			printf("station_%d: ", i);
			stations[i].print();
		}
	}

	int cs() const {
		int ret = 0;
		for (int i=0; i<stations.size(); ++i)
			ret += stations[i].cs();
		return ret;
	}
};

extern vector<set<int> > covered;

int dcmp(double x);
double calc_distance(const point_t& a, const point_t& b);
double calc_rs(const station_t& station);
double calc_social(const plan_t& plan, const vector<point_t>& points);
double calc_benefit(const plan_t& plan, const vector<point_t>& points);
double calc_cost(const plan_t& plan, const vector<point_t>& points);
double calc_ds(const station_t& station, const vector<point_t>& points, const vector<int>& y);
double calc_rho(const station_t& station, const vector<point_t>& points);
double calc_ws(const station_t& station, const vector<point_t>& points);
double calc_costt(const plan_t& plan, const vector<point_t>& points);
double calc_costb(const plan_t& plan, const vector<point_t>& points);
double calc_costa(int v, const station_t& station, const vector<point_t>& points);
double calc_estatePrice(const station_t& station, const vector<point_t>& points);
double calc_fs(const station_t& station, const vector<point_t>& points);
int calc_demands(const station_t& station, const vector<point_t>& points);
vector<int> stationSeeking(const plan_t& plan, const vector<point_t>& points);

vector<int> calc_yvs(const plan_t& plan, const vector<point_t>& points);
double calc_distance(int a, int b);
int calc_I1S(const station_t& station, const vector<point_t>& points);
int calc_I2S(const station_t& station, const vector<point_t>& points);
void update_covered(const plan_t& plan, const vector<point_t>& points);
void update_covered(const station_t& station, const vector<point_t>& points);
double calc_benefit(const station_t& station, const vector<point_t>& points);

void init_global(vector<int>& vecSumDemands, vector<int>& yIndicator, const vector<point_t>& points);
void init_global_sumDemands(vector<int>& vecSumDemands, const vector<point_t>& points);
void init_global_yIndicator(vector<int>& yIndicator, const vector<point_t>& points);
void update_yIndicator(plan_t& plan, const station_t& station, const vector<point_t>& points);
void restore_yIndicator(plan_t& plan, const station_t& station, const vector<point_t>& points);
void update_yIndicator(plan_t& plan, const vector<point_t>& points);
void restore_yIndicator(plan_t& plan, const vector<point_t>& points);
void mergeTwoPlan(plan_t& des, plan_t& src);

void dumpResult(string execName, double result);
void dumpResult(const plan_t& plan, const vector<point_t>& points);
#endif
