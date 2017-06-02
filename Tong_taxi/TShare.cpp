/**
	\author: Trasier
	\date: 2017.6.1
	\source: ICDE13 T-share: A Large-Scale Dynamic Taxi Ridesharing Service
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"

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
		return route.size() == 0;
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
			ret.push_back(route[i].orderId);
		}
		sort(ret.begin(), ret.end());
		ret.erase(unique(ret.begin(), ret.end()), ret.end());

		return ret;
	}
};

struct rider_t {
	double begTime, endTime;

	rider_t(double begTime=0., double endTime=0.):
		begTime(begTime), endTime(endTime) {}
};

struct grid_t {
	vector<int> lv;
	vector<int> tlg;
	vector<int> dlg;
};

struct query_t {
	int t;
	int o, d;
	struct {
		double e, l;
	} wp;
	struct {
		double e, l;
	} wd;
};

int graphLength, graphWidth;
int gridLength, gridWidth;
const double inf = 1e20;
vector<position_t> vRest, vDist;
vector<order_t> vOrder;
vector<rider_t> riders;
vector<driver_t> drivers;
vector<vector<move_t> > moves;
vector<bool> visit;
vector<vector<double> > R2D, R2R, D2D;
vector<grid_t> grids;
int R, D, M, C, N;

vector<int> driverPosIds;

inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt(1.0*(pa.x-pb.y)*(pa.x-pb.x) + 1.0*(pa.y-pb.y)*(pa.y-pb.y));
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

int gridNumPerRow, gridNumPerCol;
position_t getGridAnchor(const int gridId) {
	int rid = gridId / gridNumPerRow;
	int cid = gridId % gridNumPerRow;
	double x = (rid + 0.5) * gridWidth;
	double y = (cid + 0.5) * gridLength;

	return position_t(x, y);
}

double Length_grid(const int ag, const int bg) {
	position_t ap = getGridAnchor(ag), bp = getGridAnchor(bg);
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

	for (int i=0; i<M; ++i) {
		// random initialize the poisition of driver at the rid
		int placeId = rand() % R;
		drivers[i].pos = vRest[placeId];
		drivers[i].curTime = 0;

		// update the initial move
		move_t move;

		move.x = drivers[i].pos.x;
		move.y = drivers[i].pos.y;
		move.arrive = move.leave = 0;
		moves[i].push_back(move);
	}

	for (int i=0; i<graphWidth; i+=gridWidth) {
		for (int j=0; j<graphLength; j+=gridLength) {
			grids.push_back(grid_t());
		}
	}

	// initialize the lv of grid
	for (int driverId=0; driverId<M; ++driverId) {
		int gridId = getGridId(drivers[driverId].pos);
		grids[gridId].lv.push_back(driverId);
	}

	// initialize the tlg of grid, dlg is the same as tlg here.
	const int gridSz = grids.size();
	vector<pair<double,int> > vtmp(gridSz-1, pair<double,int>(0.,0));
	for (int curId=0; curId<gridSz; ++curId) {
		position_t curAnchor = getGridAnchor(curId);
		for (int othId=0,k=0; othId<gridSz; ++othId) {
			if (curId == othId) continue;

			position_t othAnchor = getGridAnchor(othId);
			double l = Length(curAnchor, othAnchor);
			vtmp[k++] = make_pair(l, othId);
		}

		sort(vtmp.begin(), vtmp.end());
		for (int k=0; k<gridSz-1; ++k) {
			grids[curId].tlg.push_back(vtmp[k].second);
		}
	}
}

void init() {
	initDriver();
	initRider();
	initMove();
	initVisit();
	initGrid();
}

void removeFromGrid(const int gridId, const int driverId) {
	vector<int>& lv = grids[gridId].lv;
	const int sz = lv.size();

	for (int i=0; i<sz; ++i) {
		if (lv[i] == driverId) {
			lv[i] = lv[sz-1];
			lv.pop_back();
			break;
		}
	}
}

void insertIntoGrid(const int gridId, const int driverId) {
	vector<int>& lv = grids[gridId].lv;
	lv.push_back(driverId);
}

const double waitTime = 5;
query_t orderToQuery(const order_t& order) {
	query_t ret;

	ret.t = order.tid;
	ret.o = order.sid;
	ret.d = order.eid;
	ret.wp.e = ret.t + waitTime;
	ret.wp.l = inf;
	ret.wd.e = ret.t;
	ret.wd.l = inf;

	return ret;
}

void updateMove(const int driverId) {
	driver_t& driver = drivers[driverId];
	const int placeId = driver.route.begin()->placeId;
	const int orderId = driver.route.begin()->orderId;
	position_t& nextPos = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
	double t = Length(driver.pos, nextPos);
	double driverTid = (placeId < R) ? max(driver.curTime+t, vOrder[orderId].tid+waitTime) : (driver.curTime + t);

	// update the rider's record to evaluate the global answer
	if (placeId < R) {
		riders[orderId].begTime = driverTid;
	} else {
		riders[orderId].endTime = driverTid;
	}


	vector<move_t>& schedule = moves[driverId];
	move_t move;

	move.x = nextPos.x;
	move.y = nextPos.y;
	move.arrive = driver.curTime + t;
	move.leave = move.arrive;
	driver.pop_front();
	move.bucket = driver.getBucket();
	schedule.push_back(move);

	// update the driver: position, time, oldGrid -> newGrid
	int oldGridId = getGridId(driver.pos);
	int newGridId = getGridId(nextPos);
	driver.pos = nextPos;
	driver.curTime = driverTid;

	removeFromGrid(oldGridId, driverId);
	insertIntoGrid(newGridId, driverId);
}

void updateIndex(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	while (!driver.isEmpty()) {
		const int placeId = driver.route.begin()->placeId;
		const int orderId = driver.route.begin()->orderId;
		position_t& nextPos = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		double t = Length(driver.pos, nextPos);
		double driverTid = (placeId < R) ? max(driver.curTime+t, vOrder[orderId].tid+waitTime) : (driver.curTime+t);

		if (driverTid > orderTid) {
			break;
		}

		updateMove(driverId);
	}

}
vector<int> searchByPick(const int orderId) {
	const order_t& order = vOrder[orderId];
	const query_t Q = orderToQuery(order);
	int pickGridId = getGridId(vRest[order.sid]);
	vector<int> ret;

	ret.push_back(pickGridId);
	vector<int> tlg = grids[pickGridId].tlg;
	const int tlgSz = tlg.size();
	for (int i=0; i<tlgSz; ++i) {
		double t = Length_grid(pickGridId, tlg[i]);
		if (t+order.tid > Q.wp.l)
			break;	

		const int sid = tlg[i];
		ret.push_back(sid);
	}

	return ret;
}

vector<int> searchByDeliver(const int orderId) {
	const order_t& order = vOrder[orderId];
	const query_t Q = orderToQuery(order);
	int deliverGridId = getGridId(vDist[order.eid]);
	vector<int> ret;

	ret.push_back(deliverGridId);
	vector<int> tlg = grids[deliverGridId].tlg;
	const int tlgSz = tlg.size();
	for (int i=0; i<tlgSz; ++i) {
		double t = Length_grid(deliverGridId, tlg[i]);
		if (t+order.tid > Q.wd.l)
			break;	

		const int sid = tlg[i];
		ret.push_back(sid);
	}

	return ret;
}

vector<int> singleSearching(const int orderId) {
	vector<int> gridIds = searchByPick(orderId);
	const int gridIdsSz = gridIds.size();
	set<int> driverSet;

	for (int i=0; i<gridIdsSz; ++i) {
		int sid = gridIds[i];
		driverSet.insert(grids[sid].lv.begin(), grids[sid].lv.end());
	}

	return vector<int>(driverSet.begin(), driverSet.end());	
}

vector<int> dualSearching(const int orderId) {
//	const order_t& order = vOrder[orderId];
	set<int> S, So, Sd;
	//int go = order.sid;
	vector<int> lo = searchByPick(orderId);
	//int gd = order.eid;
	vector<int> ld = searchByDeliver(orderId);
	vector<int>::iterator oiter = lo.begin(), diter = ld.begin();
	bool stopo = false, stopd = false;

	while (S.empty() && (stopo==false || stopd==false)) {
		if (oiter != lo.end()) {
			int gi = *oiter;
			So.insert(grids[gi].lv.begin(), grids[gi].lv.end());
		} else {
			stopo = true;
		}
		if (diter != ld.end()) {
			int gj = *diter;
			Sd.insert(grids[gj].lv.begin(), grids[gj].lv.end());
		} else {
			stopd = true;
		}

		set<int>::iterator so_iter = So.begin();
		set<int>::iterator sd_iter = Sd.begin();
		while (so_iter!=So.end() && sd_iter!=Sd.end()) {
			if (*so_iter < *sd_iter) {
				++so_iter;
			} else if (*so_iter > *sd_iter) {
				++sd_iter;
			} else {
				S.insert(*so_iter);
				++so_iter;
				++sd_iter;
			}
		}
	}

	return vector<int>(S.begin(), S.end());
}

vector<int> taxiSearching(const int orderId) {
	vector<int> ret;

#ifdef USE_SINGLE_SEARCH
	ret = singleSearching(orderId);
#else
	ret = dualSearching(orderId);
#endif

	return ret;
}

double insertFeasibilityCheck(const int driverId, const int orderId, int pick, int deliver) {
	driver_t& driver = drivers[driverId];
	order_t& order = vOrder[orderId];
	vector<node_t>& route = driver.route;
	query_t Q = orderToQuery(order);
	int sz = route.size();

	position_t driverLoc;
	if (pick == 0) {
		driverLoc = driver.pos;
	} else {
		const int placeId = route[pick-1].placeId;
		driverLoc = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
	}
	if (order.tid+Length(driverLoc, vRest[order.sid]) > Q.wp.l) 
		return inf;

	// check the subschedule after pickup point
	double arrive, ret = inf;

	if (pick == sz) {
		// append in the end of the route, no detour, no need for checking capacity
		double arrive = max(Q.wp.e, Length(driverLoc, vRest[order.sid]));
		arrive += Length(vRest[order.sid], vRest[order.eid]);
		return arrive;
	}

	position_t curLoc, nextLoc;

	curLoc = driver.pos;
	arrive = driver.curTime;
	for (int i=0; i<pick; ++i) {
		const int orderId = route[i].orderId;
		const int placeId = route[i].placeId;
		position_t nextLoc = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		arrive += Length(curLoc, nextLoc);
		if (placeId<R && arrive<vOrder[orderId].tid)
			arrive = vOrder[orderId].tid;

		if (placeId < R)
			riders[orderId].begTime = arrive;
		curLoc = nextLoc;
	}
	arrive = max(Q.wp.e, arrive+Length(curLoc, vRest[order.sid]));
	if (arrive > Q.wp.l)
		return inf;
	riders[orderId].begTime = arrive;
	curLoc = vRest[order.sid];


	for (int i=pick; i<sz; ++i) {
		if (i == deliver) {
			arrive += Length(curLoc, vDist[order.eid]);
			ret = min(ret, arrive-riders[orderId].begTime);
			curLoc = vDist[order.eid];
			if (arrive > Q.wd.l) return inf;
		}
		const int orderId = route[i].orderId;
		const int placeId = route[i].placeId;
		position_t nextLoc = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		arrive += Length(curLoc, nextLoc);
		if (placeId<R && arrive<vOrder[orderId].tid)
			arrive = vOrder[orderId].tid;

		if (placeId < R) {
			riders[orderId].begTime = arrive;
			if (arrive > Q.wp.l) return inf;
		} else {
			ret = min(ret, arrive-riders[orderId].begTime);
			if (arrive > Q.wd.l) return inf;
		}
		curLoc = nextLoc;
	}

	return ret;
}

void getBestPosition(const int driverId, const int orderId, int& pick, int& deliver, double& cost) {
	driver_t& driver = drivers[driverId];
	//order_t& order = vOrder[orderId];
	int sz = driver.route.size();
	double tmp;

	pick = deliver = -1;
	cost = inf;
	for (int i=0; i<=sz; ++i) {
		for (int j=i; j<=sz; ++j) {
			tmp = insertFeasibilityCheck(driverId, orderId, i, j);
			if (tmp <= cost) {
				cost = tmp;
				pick = i;
				deliver = j;
			}
		}
	}
}

int scheduling(const vector<int>& canDrivers, const int orderId) {
	const int sz = canDrivers.size();
	double bstVal = inf, cost;
	int pickLoc, deliverLoc;
	int ret = -1;

	for (int i=0; i<sz; ++i) {
		const int driverId = canDrivers[i];

		getBestPosition(driverId, orderId, pickLoc, deliverLoc, cost);
		if (cost < bstVal) {
			bstVal = cost;
			ret = driverId;
		}
	}

	return ret;
}

void responseDriver(const int driverId, const int orderId) {
	driver_t& driver = drivers[driverId];
	order_t& order = vOrder[orderId];
	vector<node_t> route = driver.route;
	int routeSz = route.size();
	int pickLoc, deliverLoc;
	double cost;

	getBestPosition(driverId, orderId, pickLoc, deliverLoc, cost);
	driver.clear();
	for (int i=0; i<=routeSz; ++i) {
		if (i == pickLoc) 
			driver.route.push_back(node_t(order.sid, orderId));
		if (i == deliverLoc)
			driver.route.push_back(node_t(order.eid+R, orderId));
		if (i < routeSz)
			driver.route.push_back(route[i]);
	}
}

void TShare() {
	for (int orderId=0; orderId<M; ++orderId) {
		for (int driverId=0; driverId<N; ++driverId) {
			updateIndex(driverId, vOrder[orderId].tid);
		}

		vector<int> canDrivers = taxiSearching(orderId);
		int driverId = scheduling(canDrivers, orderId);
		if (driverId >= 0)
			responseDriver(driverId, orderId);
	}

	for (int driverId=0; driverId<N; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			updateMove(driverId);
	}
}

void printAns() {
	double ans = inf;
	for (int orderId=0; orderId<M; ++orderId)
		ans = min(ans, riders[orderId].endTime-riders[orderId].begTime);

	printf("tshare %.4lf\n", ans);
}

void solve() {
	init();

	TShare();
	printAns();
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

	/**
		\step 2: solve
	*/
	solve();

	return 0;
}
