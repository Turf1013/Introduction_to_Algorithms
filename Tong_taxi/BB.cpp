/**
	\author: 	Trasier
	\date: 		2017.6.3
	\source: 	VLDB14 Large Scale Real-time Ridesharing with Service Guarantee on Road Networks
	\note: 		Branch and Bound
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"

#define LOCAL_DEBUG

const double waitTime = 0.0;
int graphLength, graphWidth;
int gridLength, gridWidth;
int R, D, M, C, N;

const double eps = 1e-6;
int dcmp(double x) {
	if (fabs(x) < eps)
		return 0;
	return x<0 ? -1:1;
}

struct position_t {
	double x, y;

	position_t(double x=0., double y=0.):
		x(x), y(y) {}

	bool operator< (const position_t& oth) const {
		if (x == oth.x)
			return y < oth.y;
		else
			return x < oth.x;
	}

	bool operator==(const position_t& oth) const {
		return dcmp(x-oth.x)==0 && dcmp(y-oth.y)==0;
	}

	bool operator!=(const position_t& oth) const {
		return dcmp(x-oth.x)!=0 || dcmp(y-oth.y)!=0;
	}
};

struct order_t {
	int tid, sid, eid;

	order_t(int tid=0, int sid=0, int eid=0):
		tid(tid), sid(sid), eid(eid) {}

	void print() {
		printf("Order: At T%d from R%d to D%d.\n", tid, sid, eid);
	}
};

struct node_t {
	int placeId, orderId;

	node_t(int placeId=0, int orderId=0):
		placeId(placeId), orderId(orderId) {}

	bool operator==(const node_t& oth) const {
		return placeId==oth.placeId && orderId==oth.orderId;
	}
};

struct driver_t {
	position_t pos;
	double curTime;
	vector<node_t> route;

	driver_t(double x=0., double y=0., double curTime=0.) {
		pos.x = x;
		pos.y = y;
		this->curTime = curTime;
	}

	bool isEmpty() const {
		return route.empty();
	}

	bool empty() const {
		return this->isEmpty();
	}

	void push_back(int placeId, int orderId) {
		route.push_back(node_t(placeId, orderId));
	}

	void pop_front() {
		if (!route.empty())
			route.erase(route.begin());
	}

	void clear() {
		route.clear();
	}

	vector<int> getBucket() {
		const int sz = route.size();
		vector<int> ret;

		for (int i=0; i<sz; ++i) {
			if (route[i].placeId >= R)
				ret.push_back(route[i].orderId);
		}
		// sort(ret.begin(), ret.end());
		// ret.erase(unique(ret.begin(), ret.end()), ret.end());

		return ret;
	}
};

struct rider_t {
	double begTime, endTime;

	rider_t(double begTime=0., double endTime=0.):
		begTime(begTime), endTime(endTime) {}
};

const double inf = 1e20;
vector<position_t> vRest, vDist;
vector<order_t> vOrder;
vector<rider_t> riders;
vector<driver_t> drivers;
vector<vector<move_t> > moves;
vector<vector<double> > R2D, R2R, D2D;


inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt((pa.x-pb.y)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
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
		riders.push_back(rider_t());
	}
}

void initDriver() {
	drivers.clear();
	for (int i=0; i<M; ++i) {
		drivers.push_back(driver_t());
	}
}

void initMove() {
	moves.clear();
	for (int i=0; i<M; ++i) {
		moves.push_back(vector<move_t>());
	}
}


int gridNumPerRow, gridNumPerCol;
position_t getGridAnchor(const int gridId) {
	int rid = gridId / gridNumPerRow;
	int cid = gridId % gridNumPerRow;
	double x = (rid + 0.5) * gridWidth;
	double y = (cid + 0.5) * gridLength;

	return position_t(x, y);
}

double Length_grid(const int aGid, const int bGid) {
	position_t ap = getGridAnchor(aGid), bp = getGridAnchor(bGid);
	return Length(ap, bp);
}

int getGridId(const position_t& pos) {
	int rid = pos.x / gridWidth;
	int cid = pos.y / gridLength;
	int gridId = gridNumPerRow * rid + cid;
	return gridId;
}

void initGrid() {
	gridNumPerRow = (graphLength + gridLength - 1) / gridLength;
}

void init() {
	initDriver();
	initRider();
	initMove();
	initGrid();
}

bool checkConstraint(double curTime, const node_t& nd) {
	const int placeId = nd.placeId;
	const int orderId = nd.orderId;

	double l, r;

	if (placeId < R) {// pickup 
		l = vOrder[orderId].tid;
		r = l + waitTime;
	} else {// dropoff
		l = vOrder[orderId].tid;
		r = inf;
	}

	if (l<=curTime && curTime<=r)
		return true;
	else
		return false;
}

void updateMove(const int driverId) {
	driver_t& driver = drivers[driverId];
	if (driver.empty()) return ;
	
	const int placeId = driver.route[0].placeId;
	const int orderId = driver.route[0].orderId;
	query_t Q = orderToQuery(vOrder[orderId]);
	position_t& nextPos = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
	double arriveTime = driver.curTime + Length(driver.pos, nextPos);
	double driverTid = (placeId < R) ? max(arriveTime, vOrder[orderId].tid+waitTime) : arriveTime;

	// update the rider's record to evaluate the global answer
	if (placeId < R) {
		riders[orderId].begTime = driverTid;
	} else {
		riders[orderId].endTime = driverTid;
	}

	move_t move;

	move.x = nextPos.x;
	move.y = nextPos.y;
	move.arrive = arriveTime;
	move.leave = driverTid;
	driver.pop_front();
	move.bucket = driver.getBucket();
	moves[driverId].push_back(move);

	// update the driver: position, time
	driver.pos = nextPos;
	driver.curTime = driverTid;
}

void updateDriverPosition(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.isEmpty())
		return ;

	if (dcmp(driver.curTime-orderTid) == 0)
		return ;

	position_t src = driver.pos;
	const int placeId = driver.route[0].placeId;
	position_t des = (placeId<R) ? vRest[placeId] : vDist[placeId-R];
	if (src == des)
		return ;

	#ifdef LOCAL_DEBUG
	assert(driver.curTime <= orderTid);
	#endif

	double t = Length(src, des);
	double dx = (des.x - src.x) / t;
	double dy = (des.y - src.y) / t;

	// add a new move
	move_t move;

	move.x = src.x + dx * (orderTid - driver.curTime);
	move.y = src.y + dy * (orderTid - driver.curTime);
	move.arrive = move.leave = orderTid;
	if (!moves[driverId].empty())
		move.bucket = moves[driverId].rbegin()->bucket;

	moves[driverId].push_back(move);

	// update the driver's position
	driver.pos.x = move.x;
	driver.pos.y = move.y;
	driver.curTime = orderTid;
}

void updateIndex(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.curTime > orderTid) return ;
	
	while (!driver.isEmpty()) {
		const int placeId = driver.route[0].placeId;
		const int orderId = driver.route[0].orderId;
		position_t& nextPos = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		double arriveTime = driver.curTime + Length(driver.pos, nextPos);
		double driverTid = (placeId < R) ? max(arriveTime, vOrder[orderId].tid+waitTime) : arriveTime;

		if (driverTid > orderTid) {
			break;
		}

		updateMove(driverId);
	}
	updateDriverPosition(driverId, orderTid);
}

double calcUnfinishedCost(const int driverId) {
	driver_t& driver = drivers[driverId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	position_t curLoc = driver.pos, nextLoc;
	double curTime = driver.curTime;
	double ret = -1;

	for (int i=0; i<sz; ++i) {
		const int placeId = route[i].placeId;
		const int orderId = route[i].orderId;
		nextLoc = (placeId < R) ? vRest[orderId] : vDist[orderId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, vOrder[orderId].tid+waitTime);

		// maybe useless even using time as objective function.
		if (placeId < R) {
			riders[orderId].begTime = curTime;
		} else {
			riders[orderId].endTime = curTime;
			ret = max(ret, riders[orderId].endTime-vOrder[orderId].tid);
		}

		curLoc = nextLoc;
	}

	return ret;
}

vector<int> taxiSearching(const int orderId) {
	double bestCost = inf, cost;
	vector<int> ret(1, -1);

	for (int driverId=0; driverId<N; ++driverId) {
		cost = calcUnfinishedCost(driverId);
		if (cost < bestCost) {
			bestCost = cost;
			ret[0] = driverId;
		}
	}

	return ret;
}

vector<node_t> bestRoute;
vector<double> minCost;
double bestVal;
int curOrderId, curDriverId;

void init_minCost(vector<node_t>& src) {
	const int sz = src.size();

	minCost.clear();
	for (int i=0; i<sz; ++i) {
		double mn = inf, tmp;
		position_t& ap = (src[i].placeId < R) ? vRest[src[i].placeId] : vDist[src[i].placeId-R];
		for (int j=0; j<sz; ++j) {
			if (i == j) continue;
			position_t& bp = (src[j].placeId < R) ? vRest[src[i].placeId] : vDist[src[j].placeId-R];
			tmp = Length(ap, bp);
			mn = min(mn, tmp);
		}
		minCost.push_back(mn);
	}
}

void updateRoute(vector<node_t>& newRoute) {
	driver_t& driver = drivers[curDriverId];
	order_t& order = vOrder[curOrderId];
	double curTime = order.tid;
	position_t curLoc = driver.pos, nextLoc;
	const int sz = newRoute.size();
	double val = -1;
	int cap = 0;

	for (int i=0; i<sz; ++i) {
		const int placeId = newRoute[i].placeId;
		const int orderId = newRoute[i].orderId;
		nextLoc = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, vOrder[orderId].tid+waitTime);

		if (placeId < R) {
			riders[orderId].begTime = curTime;
			if (++cap > C) return ;
		} else {
			riders[orderId].endTime = curTime;
			val = max(val, riders[orderId].endTime-vOrder[orderId].tid);
			--cap;
		}
		if (cap > C) return ;

		curLoc = nextLoc;
	}

	if (val < bestVal) {
		bestVal = val;
		bestRoute = newRoute;
	}
}

void dfs(vector<node_t>& des, vector<node_t>& src, int idx, int n, double curTime, double curBound) {
	if (n == 0) {
		updateRoute(des);
		return ;
	}

	double newCurTime, newCurBound;
	position_t curLoc, nextLoc;

	if (idx == 0) {
		curLoc = drivers[curDriverId].pos;
	} else {
		const int placeId = des[idx-1].placeId;
		curLoc = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
	}

	for (int i=0; i<n; ++i) {
		des[idx] = src[i];

		const int placeId = des[idx].placeId;
		const int orderId = des[idx].orderId;
		nextLoc = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		newCurTime = curTime + Length(curLoc, nextLoc);
		if (placeId < R)
			newCurTime = max(newCurTime, vOrder[orderId].tid+waitTime);

		if (!checkConstraint(newCurTime, des[idx]) || newCurTime>=bestVal)
			continue;

		newCurBound = curBound - minCost[i] + newCurTime - curTime;
		if (newCurBound >= bestVal) continue;

		swap(minCost[i], minCost[n-1]);
		swap(src[i], src[n-1]);

		dfs(des, src, idx+1, n-1, newCurTime, newCurBound);

		swap(src[i], src[n-1]);
		swap(minCost[i], minCost[n-1]);
	}
}

vector<node_t> scheduling(const int driverId, const int orderId) {
	driver_t& driver = drivers[driverId];
	order_t& order = vOrder[orderId];
	vector<node_t> src, des;
	
	src = driver.route;
	src.push_back(node_t(order.sid, orderId));
	src.push_back(node_t(order.eid+R, orderId));
	des = src;
	bestVal = inf;
	init_minCost(src);
	curDriverId = driverId;
	curOrderId = orderId;
	double minSum = accumulate(minCost.begin(), minCost.end(), 0.0);

	dfs(des, src, 0, src.size(), order.tid, minSum+order.tid);

	return bestRoute;
}

void responseDriver(const int driverId, const int orderId, vector<node_t>& newRoute) {
	driver_t& driver = drivers[driverId];
	//order_t& order = vOrder[orderId];
	driver.route = newRoute;
}

void branchAndBound() {
	for (int orderId=0; orderId<M; ++orderId) {
		for (int driverId=0; driverId<N; ++driverId) {
			updateIndex(driverId, vOrder[orderId].tid);
		}

		vector<int> canDrivers = taxiSearching(orderId);
		if (canDrivers.empty() || canDrivers[0]<0)
			continue;

		int driverId = canDrivers[0];
		vector<node_t> newRoute = scheduling(driverId, orderId);
		if (bestVal < inf)
			responseDriver(driverId, orderId, newRoute);
	}

	for (int driverId=0; driverId<N; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			updateMove(driverId);
	}
}

void printAns() {
	for (int driverId=0; driverId<N; ++driverId) {
		const int sz = moves[driverId].size();
		printf("%d %d\n", driverId, sz);
		dumpOutput(moves[driverId]);
	}

	double ans = -1;
	for (int orderId=0; orderId<M; ++orderId)
		ans = max(ans, riders[orderId].endTime-vOrder[orderId].tid);

	printf("%.10lf\n", ans);
}

void solve() {
	init();

	branchAndBound();

	printAns();
}

void readNetwork() {
	vector<double> vRest_tmp;
	vector<double> vDist_tmp;
	vector<int> vOrder_tmp;

	readInput(R, D, M, C, N, vRest_tmp, vDist_tmp, vOrder_tmp);

	for (int i=0; i<vRest_tmp.size(); i+=2) {
		vRest.push_back(position_t(vRest_tmp[i], vRest_tmp[i+1]));
	}
	for (int i=0; i<vDist_tmp.size(); i+=2) {
		vDist.push_back(position_t(vDist_tmp[i], vDist_tmp[i+1]));
	}
	for (int i=0; i<vOrder_tmp.size(); i+=3) {
		vOrder.push_back(order_t(vOrder_tmp[i], vOrder_tmp[i+1], vOrder_tmp[i+2]));
	}

	#ifdef LOCAL_DEBUG
	assert(vRest.size() == R);
	assert(vDist.size() == D);
	assert(vOrder.size() == N);
	#endif
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
	readNetwork();

	/**
		\step 2: solve
	*/
	solve();

	return 0;
}
