/**
	\author: 	Trasier
	\date: 		2017.5.1 
	\describe: 	base_v0 is a baseline method to solve the problem of taxi sharing. 
		The core idea of this method is to force all the workers fill with their package and then send them out ASAP.
		Basically, the less time the workers return to restaurants, the more time they will save. 
		Therefore, the package should be delivered as early as possible.
*/

#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"

#define LOCAL_DEBUG
// #define WATCH_MEM

struct order_t {
	int id;
	int tid, sid, eid;

	order_t(int id=0, int tid=0, int sid=0, int eid=0):
		id(id), tid(tid), sid(sid), eid(eid) {}

	void print() {
		printf("Order%d: At T%d from R%d to D%d.\n", id, tid, sid, eid);
	}
};

struct driver_t {
	double x, y;
	double curTime;
	vector<int> route;

	driver_t(double x=0., double y=0., double curTime=0.):
		x(x), y(y), curTime(curTime) {}

	bool isFull(const int c) const {
		return route.size() >= c + c;
	}

	bool isEmpty() const {
		return route.size() == 0;
	}

	void push_back(int posId) {
		route.push_back(posId);
	}

	void pop_front() {
		if (!route.empty())
			route.erase(route.begin());
	}

	int getBucketSize() const {
		return taxi.size();
	}
};

struct rider_t {
	double begTime, endTime;

	rider_t(double begTime=0.):
		begTime(begTime), endTime(begTime) {}

	rider_t(double begTime=0., double endTime=0.):
		begTime(begTime), endTime(endTime) {}
};

const double inf = 1e20;
typedef pair<int,int> position_t;
vector<position_t> vRest, vDist;
vector<order_t> vOrder;
vector<rider_t> riders;
vector<driver_t> drivers;
vector<vector<move_t> > moves;
vector<bool> visit;
vector<vector<double> > R2D, R2R, D2D;
int R, D, M, C, N;

vector<int> driverPosIds;

inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt(1.0*(pa.first-pb.first)*(pa.first-pb.first) + 1.0*(pa.second-pb.second)*(pa.second-pb.second));
}

void init_Dist() {
	{// R2R: Restaurant to Restaurant
		R2R.clear();
		vector<double> vtmp(R, 0.0);

		for (int i=0; i<R; ++i) {
			for (int j=0; j<R; ++j) {
				vtmp[j] = Length(vRest[i], vRest[j]);
			}
			vtmp[i] = 0.0;
			R2R.push_back(vtmp);
		}
	}

	{// D2D: District to District
		D2D.clear();
		vector<double> vtmp(D, 0.0);

		for (int i=0; i<D; ++i) {
			for (int j=0; j<D; ++j) {
				vtmp[j] = Length(vDist[i], vDist[j]);
			}
			vtmp[i] = 0.0;
			D2D.push_back(vtmp);
		}
	}

	{// R2D: Restaurant to District
		R2D.clear();
		vector<double> vtmp(D, 0.0);

		for (int i=0; i<R; ++i) {
			for (int j=0; j<D; ++j) {
				vtmp[j] = Length(vRest[i], vDist[j]);
			}
			R2D.push_back(vtmp);
		}
	}
}

inline double dist_R2D(const int rid, const int did) {
	#ifdef LOCAL_DEBUG
	assert(rid>=0 && rid<R2D.size());
	assert(did>=0 && did<R2D[rid].size());
	#endif
	return R2D[rid][did];
}

inline double dist_D2R(const int did, const int rid) {
	return dist_R2D(rid, did);
}

inline double dist_D2D(const int did1, const int did2) {
	#ifdef LOCAL_DEBUG
	assert(did1>=0 && did1<=D2D.size());
	assert(did2>=0 && did2<=D2D[did1].size());
	#endif
	return D2D[did1][did2];
}

inline double dist_R2R(const int rid1, const int rid2) {
	#ifdef LOCAL_DEBUG
	assert(rid1>=0 && rid1<=R2R.size());
	assert(rid2>=0 && rid2<=R2R[rid1].size());
	#endif
	return R2R[rid1][rid2];	
}

void initRider() {
	riders.clear();
	for (int i=0; i<N; ++i) {
		riders.push_back(receiver_t(vOrder[i].tid));
	}
}

void initDriver() {
	drivers.clear();
	for (int i=0; i<M; ++i) {
		drivers.push_back(sender());
	}
	driverPosIds.clear();
	driverPosIds.resize(M, -1);
}

void initMove() {
	moves.clear();
	for (int i=0; i<M; ++i) {
		moves.push_back(vector<move_t>());
	}
}

void initVisit() {
	visit.clear();
	visit.resize(N, false);
}

void addMove(const int driverId, const move_t& move) {
	#ifdef LOCAL_DEBUG
	assert(driverId>=0 && driverId<drivers.size());
	#endif
	drivers[driverId].push_back(move);
}

void moveDriver(const int driverId, const double curOrderTime) {
	driver& driver = drivers[driverId];
	
	while (!driver.isEmpty()) {
		int placeId = *driver.route.begin();
		double t;

		if (placeId < R) {
			t = Length(position_t(driver.x, driver.y), vRest[placeId]);
		} else {
			t = Length(position_t(driver.x, driver.y), vDist[placeId-R]);
		}

		if (driver.curTime+t <= curOrderTime) {
			move_t move;

			if (placeId < R) {
				move.x = vRest[placeId].first;
				move.y = vRest[placeId].second;
			} else {
				move.x = vDist[placeId-R].first;
				move.y = vDist[placeId-R].second;
			}
			move.arrive = driver.curTime + t;
			move.leave = move.arrive;

			moves[driverId].push_back(move);

			// update driver
			driver.x = move.x;
			driver.y = move.y;
			driver.curTime = move.leave;
			driver.pop_front();
		}
	}
}

double calcDist(const int driverId, order_t& order) {
	driver_t driver = drivers[driverId];
	const int orderTid = order.tid;
	const int orderSid = order.sid;
	const int orderEid = order.eid;
	const int sz = 
	double ret = inf, tmp;



}

double findNearestNeighbour(const int orderId) {
	order_t& order = vOrder[orderId];
	const int orderTid = order.tid;
	const int orderSid = order.sid;
	const int orderEid = order.eid;
	double mn = inf, tmp;
	int bestDriver = -1;

	/**
		In fact, we can always find a valid schedule for any taxi.
		e.g. Insert the order at the end of the move.
	*/
	for (int i=0; i<M; ++i) {
		moveDriver(i, orderTid);
		tmp = calcDist(i, order);
		if (tmp < mn) {
			mn = tmp;
			bestDriver = i;
		}
	}

	if (bestDriver != -1)
		pickUp(bestDriver, orderId);

	return mn;
}

double NN() {
	double ret = 0.0, tmp;
	init_calc();

	for (int i=0; i<N; ++i) {
		tmp = findNearestNeightbour(i);
		ret = max(ret, tmp);
	}	

	return ret;
}

double fastSolve() {
	#ifdef LOCAL_DEBUG
	assert(M >= N);
	#endif

	double ret = 0.0;
	move_t move;

	for (int i=0; i<N; ++i) {
		const int tid = vOrder[i].tid;
		const int sid = vOrder[i].sid;
		const int eid = vOrder[i].eid;
		move.x = vRest[sid].first;
		move.y = vRest[sid].second;
		move.arrive = 0;
		move.leave = tid;
		move.bucket.clear();
		move.bucket.push_back(i);
		moves[i].push_back(move);

		move.x = vDist[eid].first;
		move.y = vDist[eid].second;
		move.arrive += dist_R2D(sid, eid);
		move.leave = move.arrive;
		move.bucket.clear();
		moves[i].push_back(move);
		
		ret = max(ret, dist_R2D(sid, eid));
	}

	return ret;
}

void printAns(double ans) {
	dumpOutput(senders());
	printf("%.4lf\n", ans);
}

void init() {
	initDriver();
	initRider();
	initMove();
	initVisit();
}

void solve() {
	init();

	if (M >= N) {
		double ans = fastSolve();
		printAns(ans);
		return ;
	}
	
	double ans = NN();
	printAns(ans);
}

int main(int argc, char **argv) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}

	/**
		\step 1: read input
	*/
	readInput(R, D, M, C, N, vRest, vDist, vOrder);

	/**
		\step 2: solve
	*/
	solve();

	return 0;
}

 