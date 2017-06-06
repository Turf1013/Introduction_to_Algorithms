/**
	\author: 	Trasier
	\date:   	2017.6.1
	\source: 	ICDE13 T-share: A Large-Scale Dynamic Taxi Ridesharing Service
	\note: 		1) 2016.6.5 updateMove is not fixed yet.
				2) 2016.6.6 There could be some bugs in updateMove, since at one place(aRest or aDist), more than one riders can be pickedup or delivered.
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"

#define LOCAL_DEBUG

const double waitTime = 0.0;
int graphLength = 20, graphWidth = 20;
int gridLength = 7, gridWidth = 7;
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

	bool operator!=(const node_t& oth) const {
		return placeId!=oth.placeId || orderId!=oth.orderId;
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

	void erase(vector<node_t>::iterator biter, vector<node_t>::iterator eiter) {
		route.erase(biter, eiter);
	}

	void clear() {
		route.clear();
	}

	vector<int> getBucket() {
		const int sz = route.size();
		vector<int> ret;
		set<int> unpicked;

		for (int i=0; i<sz; ++i) {
			if (route[i].placeId < R)
				unpicked.insert(route[i].orderId);
			if (route[i].placeId>=R && unpicked.count(route[i].orderId)==0)
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

const double inf = 1e20;
position_t *rests;
position_t *dists;
order_t *orders;
rider_t *riders;
driver_t *drivers;
// vector<position_t> rests, dists;
// vector<order_t> orders;
// vector<rider_t> riders;
// vector<driver_t> drivers;
vector<vector<move_t> > moves;
vector<vector<double> > R2D, R2R, D2D;
vector<grid_t> grids;

inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

void init_Dist() {
	{// R2R: Restaurant to Restaurant
		R2R.clear();
		vector<double> vtmp(R, 0.0);

		for (int i=0; i<R; ++i) {
			for (int j=0; j<R; ++j) {
				vtmp[j] = Length(rests[i], rests[j]);
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
				vtmp[j] = Length(dists[i], dists[j]);
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
				vtmp[j] = Length(rests[i], dists[j]);
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
	// riders.clear();
	// for (int i=0; i<N; ++i) {
		// riders.push_back(rider_t());
	// }
	riders = new rider_t[N];
}

void initDriver() {
	// drivers.clear();
	// for (int i=0; i<M; ++i) {
		// drivers.push_back(driver_t());
	// }
	drivers = new driver_t[M];
}

void initMove() {
	moves.clear();
	for (int i=0; i<M; ++i) {
		moves.push_back(vector<move_t>());
	}
}

// anchor should inside the graph, so consider the boundary.
int gridNumPerRow, gridNumPerCol;
position_t getGridAnchor(const int gridId) {
	int rid = gridId / gridNumPerRow;
	int cid = gridId % gridNumPerRow;
	double lx = rid * gridWidth, rx = min((double)graphWidth, lx+gridWidth);
	double ly = cid * gridLength, ry = min((double)graphLength, ly+gridLength);
	double x = (lx + rx) * 0.5;
	double y = (ly + ry) * 0.5;

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
		drivers[i].pos = rests[placeId];
		drivers[i].curTime = 0;
#ifdef LOCAL_DEBUG
		printf("Driver%d is located in (%.2lf, %.2lf) at first.\n", i, drivers[i].pos.x, drivers[i].pos.y);
#endif
		// update the initial move
//		move_t move;
//
//		move.x = drivers[i].pos.x;
//		move.y = drivers[i].pos.y;
//		move.arrive = move.leave = 0;
//		moves[i].push_back(move);
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

void initOrder() {
	orders = new order_t[N];
}

void initRest() {
	rests = new position_t[R];
}

void initDist() {
	dists = new position_t[D];
}

void initAll() {
	initOrder();
	initRest();
	initDist();
	initDriver();
	initRider();
	initMove();
	//initGrid();
}

void deleteAll() {
	delete[] orders;
	delete[] rests;
	delete[] dists;
	delete[] drivers;
	delete[] riders;
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

#ifdef LOCAL_DEBUG
void printGridLv() {
	for (int i=0; i<grids.size(); ++i) {
		int gx = i / gridNumPerRow;
		int gy = i % gridNumPerRow;
		printf("(%d,%d):", gx, gy);
		for (int j=0; j<grids[i].lv.size(); ++j)
			printf(" %d", grids[i].lv[j]);
		putchar('\n');
	}
}
#endif

void updateMove(const int driverId) {
	driver_t& driver = drivers[driverId];
	if (driver.empty()) return ;
	
	const int placeId = driver.route[0].placeId;
	const int orderId = driver.route[0].orderId;
	query_t Q = orderToQuery(orders[orderId]);
	position_t& nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
	double arriveTime = driver.curTime + Length(driver.pos, nextPos);
	double driverTid = (placeId < R) ? max(arriveTime, Q.wp.e) : max(arriveTime, Q.wd.e);

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
#ifdef LOCAL_DEBUG
	{
		if (placeId < R) {
			printf("At %.4lf Arrive %d -> R%d. PICK:", arriveTime, driverId, placeId);
		} else {
			printf("At %.4lf Arrive %d -> D%d. DROP:", arriveTime, driverId, placeId-R);
		}
		const int sz = driver.route.size();
		for (int i=0; i<sz; ++i) {
			if (driver.route[i].placeId == placeId)
				printf(" %d", driver.route[i].orderId);
			else
				break;
		}
		putchar('\n');
	}
#endif
	//!!!! THIS BLOCK IS IMPORTANT TO UPDATE THE BUCKET.
	vector<node_t>::iterator iter = driver.route.begin();
	while (iter!=driver.route.end() && iter->placeId==placeId)
		++iter;
	driver.erase(driver.route.begin(), iter);
	//----
	move.bucket = driver.getBucket();
	moves[driverId].push_back(move);
#ifdef LOCAL_DEBUG
	printf("\tBucket:");
	for (int i=0; i<move.bucket.size(); ++i)
		printf(" %d", move.bucket[i]);
	putchar('\n');
#endif

	// update the driver: position, time, oldGrid -> newGrid
	int oldGridId = getGridId(driver.pos);
	int newGridId = getGridId(nextPos);
	driver.pos = nextPos;
	driver.curTime = driverTid;

	removeFromGrid(oldGridId, driverId);
	insertIntoGrid(newGridId, driverId);

#ifdef LOCAL_DEBUG
	printGridLv();
#endif
}

void updateDriverPosition(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.isEmpty())
		return ;

	if (dcmp(driver.curTime-orderTid) == 0)
		return ;

	position_t src = driver.pos;
	const int placeId = driver.route[0].placeId;
	position_t des = (placeId<R) ? rests[placeId] : dists[placeId-R];
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

#ifdef LOCAL_DEBUG
	printf("At %.4lf Middle %d, (%.4lf, %.4lf) -> (%.4lf, %.4lf).\n",
			move.arrive, driverId, src.x, src.y, move.x, move.y);
#endif

	// update the driver's position, time, oldGrid -> newGrid
	int oldGridId = getGridId(driver.pos);
	int newGridId = getGridId(position_t(move.x, move.y));
	driver.pos.x = move.x;
	driver.pos.y = move.y;
	driver.curTime = orderTid;

	removeFromGrid(oldGridId, driverId);
	insertIntoGrid(newGridId, driverId);

#ifdef LOCAL_DEBUG
	printGridLv();
#endif
}

void updateIndex(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.curTime > orderTid) return ;
	
	while (!driver.isEmpty()) {
		const int placeId = driver.route[0].placeId;
		const int orderId = driver.route[0].orderId;
		position_t& nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
		double arriveTime = driver.curTime + Length(driver.pos, nextPos);
		double driverTid = (placeId < R) ? max(arriveTime, orders[orderId].tid+waitTime) : arriveTime;

		if (driverTid > orderTid) {
			break;
		}

		updateMove(driverId);
	}
	updateDriverPosition(driverId, orderTid);
}

vector<int> searchByPick(const int orderId) {
	const order_t& order = orders[orderId];
	const query_t Q = orderToQuery(order);
	int pickGridId = getGridId(rests[order.sid]);
	vector<int> ret;

	ret.push_back(pickGridId);
	vector<int>& tlg = grids[pickGridId].tlg;
	const int tlgSz = tlg.size();
	for (int i=0; i<tlgSz; ++i) {
		double t = Length_grid(pickGridId, tlg[i]);
		if (t+order.tid > Q.wp.l)
			break;	

		ret.push_back(tlg[i]);
	}

	return ret;
}

vector<int> searchByDeliver(const int orderId) {
	const order_t& order = orders[orderId];
	const query_t Q = orderToQuery(order);
	int deliverGridId = getGridId(dists[order.eid]);
	vector<int> ret;

	ret.push_back(deliverGridId);
	vector<int>& tlg = grids[deliverGridId].tlg;
	const int tlgSz = tlg.size();
	for (int i=0; i<tlgSz; ++i) {
		double t = Length_grid(deliverGridId, tlg[i]);
		if (t+order.tid > Q.wd.l)
			break;	

		ret.push_back(tlg[i]);
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
//	const order_t& order = orders[orderId];
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

		// find the intersection set of So & Sd
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

#define USE_SINGLE_SEARCH
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
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	int sz = route.size();

	{// prune1: using triangle inequality
		query_t Q = orderToQuery(order);
		position_t driverLoc;
		if (pick == 0) {
			driverLoc = driver.pos;
		} else {
			const int placeId = route[pick-1].placeId;
			driverLoc = (placeId < R) ? rests[placeId] : dists[placeId-R];
		}
		if (order.tid+Length(driverLoc, rests[order.sid]) > Q.wp.l)
			return inf;
	}

	// check the complete path
	position_t curLoc = driver.pos, nextLoc;
	double curTime = order.tid;
	int cap = 0;
	double ret = -1;

	for (int i=0; i<=sz; ++i) {
		if (i == pick) {
			query_t Q = orderToQuery(order);

			nextLoc = rests[order.sid];
			curTime = max(curTime+Length(curLoc, nextLoc), Q.wp.e);
			if (curTime > Q.wp.l) return inf;
			if (++cap > C) return inf;
			riders[orderId].begTime = curTime;

			curLoc = nextLoc;
		}
		if (i == deliver) {
			query_t Q = orderToQuery(order);

			nextLoc = dists[order.eid];
			curTime = max(curTime+Length(curLoc, nextLoc), Q.wd.e);
			if (curTime > Q.wd.l) return inf;
			--cap;
			riders[orderId].endTime = curTime;
			ret = max(ret, riders[orderId].endTime-order.tid);

			curLoc = nextLoc;
		}
		if (i == sz) continue;

		const int placeId_ = route[i].placeId;
		const int orderId_ = route[i].orderId;
		nextLoc = (placeId_ < R) ? rests[placeId_] : dists[placeId_-R];
		curTime += Length(curLoc, nextLoc);
		query_t Q = orderToQuery(orders[orderId_]);

		if (placeId_ < R) {
			curTime = max(curTime, Q.wp.e);
			if (curTime > Q.wp.l) return inf;
			if (++cap > C) return inf;

			riders[orderId_].begTime = curTime;
		} else {
			curTime = max(curTime, Q.wd.e);
			if (curTime > Q.wd.l) return inf;
			--cap;

			riders[orderId_].endTime = curTime;
			ret = max(ret, riders[orderId_].endTime-orders[orderId_].tid);
		}

		curLoc = nextLoc;
	}

	#ifdef LOCAL_DEBUG
	assert(ret >= 0);
	#endif

	return ret;
}

/*
double insertFeasibilityCheck(const int driverId, const int orderId, int pick, int deliver) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	query_t Q = orderToQuery(order);
	int sz = route.size();

	position_t driverLoc;
	if (pick == 0) {
		driverLoc = driver.pos;
	} else {
		const int placeId = route[pick-1].placeId;
		driverLoc = (placeId < R) ? rests[placeId] : dists[placeId-R];
	}
	if (order.tid+Length(driverLoc, rests[order.sid]) > Q.wp.l)
		return inf;

	// check the subschedule after pickup point
	double arrive, ret = inf;

	if (pick == sz) {
		// append in the end of the route, no detour, no need for checking capacity
		double arrive = max(Q.wp.e, order.tid+Length(driverLoc, rests[order.sid]));
		arrive += Length(rests[order.sid], dists[order.eid]);
		double ret = arrive - order.tid;
		
		return ret;
	}

	position_t curLoc, nextLoc;

	curLoc = driver.pos;
	arrive = driver.curTime;
	for (int i=0; i<pick; ++i) {
		const int orderId = route[i].orderId;
		const int placeId = route[i].placeId;
		position_t nextLoc = (placeId < R) ? rests[placeId] : dists[placeId-R];
		arrive += Length(curLoc, nextLoc);
		if (placeId<R && arrive<orders[orderId].tid)
			arrive = orders[orderId].tid;

		if (placeId < R)
			riders[orderId].begTime = arrive;
		curLoc = nextLoc;
	}
	arrive = max(Q.wp.e, arrive+Length(curLoc, rests[order.sid]));
	if (arrive > Q.wp.l)
		return inf;
	riders[orderId].begTime = arrive;
	curLoc = rests[order.sid];


	for (int i=pick; i<sz; ++i) {
		if (i == deliver) {
			arrive += Length(curLoc, dists[order.eid]);
			ret = min(ret, arrive-riders[orderId].begTime);
			curLoc = dists[order.eid];
			if (arrive > Q.wd.l) return inf;
		}
		const int orderId = route[i].orderId;
		const int placeId = route[i].placeId;
		position_t nextLoc = (placeId < R) ? rests[placeId] : dists[placeId-R];
		arrive += Length(curLoc, nextLoc);
		if (placeId<R && arrive<orders[orderId].tid)
			arrive = orders[orderId].tid;

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
*/

void getBestPosition(const int driverId, const int orderId, int& pick, int& deliver, double& cost) {
	driver_t& driver = drivers[driverId];
	//order_t& order = orders[orderId];
	int sz = driver.route.size();
	double tmp;

	pick = deliver = -1;
	cost = inf - 1.0;
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
	order_t& order = orders[orderId];
	vector<node_t> route = driver.route;
	int routeSz = route.size();
	int pickLoc, deliverLoc;
	double cost;

	getBestPosition(driverId, orderId, pickLoc, deliverLoc, cost);
	driver.curTime = order.tid;
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
	for (int orderId=0; orderId<N; ++orderId) {
#ifdef LOCAL_DEBUG
		printf("order%d:\n", orderId);
#endif
		for (int driverId=0; driverId<M; ++driverId) {
			updateIndex(driverId, orders[orderId].tid);
		}
		vector<int> canDrivers = taxiSearching(orderId);
		int driverId = scheduling(canDrivers, orderId);
		if (driverId >= 0)
			responseDriver(driverId, orderId);

#ifdef LOCAL_DEBUG
		printf("ORDER %d -> DRIVER %d.\n\n\n", orderId, driverId);
		fflush(stdout);
#endif
	}

	for (int driverId=0; driverId<M; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			updateMove(driverId);
	}
}

void printAns() {
	for (int driverId=0; driverId<M; ++driverId) {
		const int sz = moves[driverId].size();
		printf("%d %d\n", driverId, sz);
		dumpOutput(moves[driverId]);
	}

	double ans = -1;
	for (int orderId=0; orderId<N; ++orderId)
		ans = max(ans, riders[orderId].endTime-orders[orderId].tid);

	printf("%.10lf\n", ans);
}

void solve() {
	//init();

	TShare();

	printAns();

	deleteAll();
}

void readNetwork() {
	vector<double> rests_tmp;
	vector<double> dists_tmp;
	vector<int> orders_tmp;

	readInput(R, D, M, C, N, rests_tmp, dists_tmp, orders_tmp);

	initAll();
	// for (int i=0; i<rests_tmp.size(); i+=2) {
		// rests.push_back(position_t(rests_tmp[i], rests_tmp[i+1]));
	// }
	// for (int i=0; i<dists_tmp.size(); i+=2) {
		// dists.push_back(position_t(dists_tmp[i], dists_tmp[i+1]));
	// }
	// for (int i=0; i<orders_tmp.size(); i+=3) {
		// orders.push_back(order_t(orders_tmp[i], orders_tmp[i+1], orders_tmp[i+2]));
	// }

	// #ifdef LOCAL_DEBUG
	// assert(rests.size() == R);
	// assert(dists.size() == D);
	// assert(orders.size() == N);
	// #endif

	for (int i=0,j=0; j<R; i+=2,++j) {
		rests[j] = position_t(rests_tmp[i], rests_tmp[i+1]);
	}
	for (int i=0,j=0; j<D; i+=2,++j) {
		dists[j] = position_t(dists_tmp[i], dists_tmp[i+1]);
	}
	for (int i=0,j=0; j<N; i+=3,++j) {
		orders[j] = order_t(orders_tmp[i], orders_tmp[i+1], orders_tmp[i+2]);
	}

	initGrid();
//	for (int i=0; i<M; ++i) {
//		int placeId = rand() % R;
//		drivers[i].pos = rests[placeId];
//#ifdef LOCAL_DEBUG
//		printf("Driver%d is located in (%.2lf, %.2lf) at first.\n", i, drivers[i].pos.x, drivers[i].pos.y);
//#endif
//	}
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
