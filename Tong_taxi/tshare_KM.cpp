/**
	\author: 	Trasier
	\date:   	2017.8.1
	\source: 	Tshare with KM
	\note:
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "KM.h"
//#include "monitor.h"

#define LOCAL_DEBUG

const double inf = 1e20;
const double waitTime = inf;
int graphLength = 100, graphWidth = 100;
int gridLength = 10, gridWidth = 10;
int R, D, M, CAP, N;
double bound;
Hungarian_t hung;

const double eps = 1e-5;
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
	int status; // -1: working, [1,R]: free & heading to rests nearby, 0: free & staying at rests.

	driver_t(double x=0., double y=0., double curTime=0.) {
		pos.x = x;
		pos.y = y;
		this->curTime = curTime;
		status = 0;
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

position_t *rests;
position_t *dists;
order_t *orders;
rider_t *riders;
driver_t *drivers;
int *taken;
vector<vector<move_t> > moves;
double ans;

double Length(const position_t& pa, const position_t& pb) {
	return sqrt((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

void initRider() {
	riders = new rider_t[N];
}

void initDriver() {
	drivers = new driver_t[M];
}

void initMove() {
	moves.clear();
	for (int i=0; i<M; ++i) {
		moves.push_back(vector<move_t>());
	}
}

void initOrder() {
	orders = new order_t[N];
	taken = new int[N];
	memset(taken, -1, sizeof(int)*N);
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
	bound = 0.0;
	ans = 0.0;
}

void deleteAll() {
	delete[] orders;
	delete[] rests;
	delete[] dists;
	delete[] drivers;
	delete[] riders;
	delete[] taken;
}

void distributeDrivers() {
	for (int i=0; i<M; ++i) {
		int idx = rand() % R;
		drivers[i].status = 0;
		drivers[i].pos = rests[idx];
#ifdef LOCAL_DEBUG
		//drivers[i].pos = position_t(0.0, 0.0);
#endif
		move_t move;
		move.x = rests[idx].x;
		move.y = rests[idx].y;
		move.arrive = move.leave = 0;
		moves[i].push_back(move);
	}
}

void moveForward(const int driverId) {
	driver_t& driver = drivers[driverId];
	if (driver.empty() && driver.status==0)
		return ;

	if (driver.status > 0) {
		#ifdef LOCAL_DEBUG
		assert(driver.empty());
		#endif
		const int placeId = driver.status -1;
		driver.status = 0;
		driver.curTime += Length(driver.pos, rests[placeId]);
		ans += Length(driver.pos, rests[placeId]);
		driver.pos = rests[placeId];
		// add the movement to the driver
		move_t move;
		move.x = rests[placeId].x;
		move.y = rests[placeId].y;
		move.arrive = move.leave = driver.curTime;
		moves[driverId].push_back(move);
		return ;
	}

	// calculate the arriveTime
	const int placeId = driver.route[0].placeId;
	const int orderId = driver.route[0].orderId;
	position_t nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
	double arriveTime = driver.curTime + Length(driver.pos, nextPos);
	ans += Length(driver.pos, nextPos);

	// add the movement to the driver
	move_t move;
	move.x = nextPos.x;
	move.y = nextPos.y;
	move.arrive = arriveTime;
	double& leaveTime = move.leave;
	leaveTime = arriveTime;

	// iterate all possible drop & pickup
	double tmpTime;

	vector<node_t>::iterator iter = driver.route.begin();
	while (iter!=driver.route.end() && iter->placeId==placeId) {
		if (placeId < R) {
			tmpTime = max(arriveTime, (double)orders[iter->orderId].tid);
			riders[iter->orderId].begTime = tmpTime;
			taken[iter->orderId] = 0;
		} else {
			tmpTime = arriveTime;
			riders[iter->orderId].endTime = tmpTime;
			taken[iter->orderId] = 1;
			bound = max(bound, riders[iter->orderId].endTime-orders[iter->orderId].tid);
		}
		leaveTime = max(leaveTime, tmpTime);
		++iter;
	}
	driver.erase(driver.route.begin(), iter);
	move.bucket = driver.getBucket();
	moves[driverId].push_back(move);

	// update the current time & position of driver
	driver.pos = nextPos;
	driver.curTime = leaveTime;

	if (driver.empty() && driver.status<0) {
		int idx = rand() % R;
		driver.status = idx + 1;
	}
}

static position_t orgDriverPos;
static double orgDriverTime;
void updateDriverPosition(const int driverId, const double orderTid, bool toMove=false) {
	driver_t& driver = drivers[driverId];

	orgDriverPos = driver.pos;
	orgDriverTime = driver.curTime;

	if (driver.isEmpty() && driver.status==0) {
		driver.curTime = orderTid;
		return ;
	}

	if (dcmp(driver.curTime - orderTid) == 0)
		return ;

	position_t srcPos = driver.pos;
	const int placeId = (driver.isEmpty()) ? (driver.status-1) : driver.route[0].placeId;
	position_t desPos = (placeId<R) ? rests[placeId] : dists[placeId-R];

	double t = Length(srcPos, desPos);
	double dx = (desPos.x - srcPos.x) / t;
	double dy = (desPos.y - srcPos.y) / t;
	double x = srcPos.x + dx * (orderTid - driver.curTime);
	double y = srcPos.y + dy * (orderTid - driver.curTime);

	if (toMove) {
		ans += (orderTid - driver.curTime);
		// add a new move
		move_t move;
		move.x = x;
		move.y = y;
		move.arrive = move.leave = orderTid;
		if (!moves[driverId].empty())
			move.bucket = moves[driverId].rbegin()->bucket;
		moves[driverId].push_back(move);
	}

	// update the current position & time of driver
	driver.pos.x = x;
	driver.pos.y = y;
	driver.curTime = orderTid;
}

void restoreDriverPosition(const int driverId) {
	driver_t& driver = drivers[driverId];

	driver.pos = orgDriverPos;
	driver.curTime = orgDriverTime;
}

void updateIndex(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];

	while (!driver.isEmpty()) {
		const int placeId = driver.route[0].placeId;
		const int orderId = driver.route[0].orderId;
		position_t& nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		double arriveTime = driver.curTime + Length(driver.pos, nextPos);
		double tmpTime = (placeId<R) ? max(arriveTime, (double)orders[orderId].tid) : arriveTime;

		if (tmpTime > orderTid) break;

		moveForward(driverId);
	}
	if (driver.isEmpty()) {
		if (driver.status < 0) {
			driver.status = 1;
		}
		if (driver.status > 0) {
			const int placeId =	driver.status - 1;
			position_t nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
			double arriveTime = driver.curTime + Length(driver.pos, nextPos);
			if (arriveTime <= orderTid) {
				moveForward(driverId);
				#ifdef LOCAL_DEBUG
				assert(driver.status == 0);
				#endif
			}
		}
		#ifdef LOCAL_DEBUG
			assert(driver.status >= 0);
		#endif
	}
}

vector<int> taxiSearching(const int orderId) {
	vector<int> ret;

	for (int i=0; i<M; ++i)
		ret.push_back(i);

	return ret;
}

int calcInitCap(const int driverId) {
	driver_t& driver = drivers[driverId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	int ret = 0;

	for (int i=0; i<sz; ++i) {
		if (route[i].placeId>=R && taken[route[i].orderId]==0)
			++ret;
	}

	return ret;
}

double calcDetour(int driverId, int orderId, int pickLoc, int dropLoc) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	double ret = 0.0;
	int placeId;
	position_t curPos, nextPos, midPos;

	if (pickLoc == dropLoc) {
		if (pickLoc == 0) {
			curPos = driver.pos;
		} else {
			placeId = route[pickLoc-1].placeId;
			curPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		}
		ret += Length(curPos, rests[order.sid]);
		ret += Length(rests[order.sid], dists[order.eid]);

		if (pickLoc < sz) {
			placeId = route[pickLoc].placeId;
			nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
			ret += Length(dists[order.eid], nextPos) - Length(curPos, nextPos);
		}

	} else {
		if (pickLoc == 0) {
			curPos = driver.pos;
		} else {
			placeId = route[pickLoc-1].placeId;
			curPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		}
		midPos = rests[order.sid];
		{
			#ifdef LOCAL_DEBUG
			assert(pickLoc != sz);
			#endif
			placeId = route[pickLoc].placeId;
			nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		}
		ret += Length(curPos, midPos) + Length(midPos, nextPos) - Length(curPos, nextPos);

		{
			#ifdef LOCAL_DEBUG
			assert(dropLoc != 0);
			#endif
			placeId = route[dropLoc-1].placeId;
			curPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		}
		midPos = dists[order.eid];

		if (dropLoc < sz) {
			placeId = route[dropLoc].placeId;
			nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
			ret += Length(curPos, midPos) + Length(midPos, nextPos) - Length(curPos, nextPos);
		} else {
			ret += Length(curPos, midPos);
		}
	}

	return ret;
}

bool judgeRoute(int driverId, int orderId, int pickLoc, int dropLoc) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	int cap = calcInitCap(driverId);
	double curTime = driver.curTime;
	position_t curPos = driver.pos, nextPos;

	#ifdef LOCAL_DEBUG
	assert(cap <= CAP);
	#endif

	for (int i=0; i<=sz; ++i) {
		if (pickLoc == i) {
			if (++cap > CAP) return false;
			nextPos = rests[order.sid];
			curTime += Length(curPos, nextPos);
			if (curTime > order.tid+waitTime) return false;
			curPos = nextPos;
		}
		if (dropLoc == i) {
			--cap;
			nextPos = dists[order.eid];
			curTime += Length(curPos, nextPos);
			curPos = nextPos;
		}
		if (i < sz) {
			const int placeId = route[i].placeId;
			const int orderId = route[i].orderId;
			nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
			curTime += Length(curPos, nextPos);
			if (placeId < R) {
				if (++cap > CAP) return false;
				if (curTime > orders[orderId].tid+waitTime) return false;
			} else {
				--cap;
			}
			curPos = nextPos;
		}
	}

	return true;
}

double calcCost(int driverId, int orderId, int pickLoc, int dropLoc) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	double curTime = driver.curTime;
	position_t curPos = driver.pos, nextPos;


	for (int i=0; i<=sz; ++i) {
		if (pickLoc == i) {
			nextPos = rests[order.sid];
			curTime += Length(curPos, nextPos);
			curPos = nextPos;
		}
		if (dropLoc == i) {
			nextPos = dists[order.eid];
			curTime += Length(curPos, nextPos);
			curPos = nextPos;
		}
		if (i < sz) {
			const int placeId = route[i].placeId;
			const int orderId = route[i].orderId;
			nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
			curTime += Length(curPos, nextPos);
			curPos = nextPos;
		}
	}

	return curTime;
}

double calcCost(int driverId) {
	driver_t& driver = drivers[driverId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	double curTime = driver.curTime;
	position_t curPos = driver.pos, nextPos;


	for (int i=0; i<sz; ++i) {
		const int placeId = route[i].placeId;
		const int orderId = route[i].orderId;
		nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		curTime += Length(curPos, nextPos);
		curPos = nextPos;
	}

	return curTime;
}

void updateResult(double& bestCost, int& bestPick, int& bestDrop, double tmpCost, int pickLoc, int dropLoc) {
	if (tmpCost < bestCost) {
		bestCost = tmpCost;
		bestPick = pickLoc;
		bestDrop = dropLoc;
	}
}

void getBestPosition(int driverId, int orderId, int& bestPick, int& bestDrop, double& bestCost) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	double tmpCost;

	bestCost = inf;
	for (int pickLoc=0; pickLoc<=sz; ++pickLoc) {
		for (int dropLoc=pickLoc; dropLoc<=sz; ++dropLoc) {
			if (!judgeRoute(driverId, orderId, pickLoc, dropLoc)) continue;
			tmpCost = calcCost(driverId, orderId, pickLoc, dropLoc) - calcCost(driverId);
			//tmpCost = calcCost(driverId, orderId, pickLoc, dropLoc) - calcCost(driverId);
			updateResult(bestCost, bestPick, bestDrop, tmpCost, pickLoc, dropLoc);
		}
	}
}


pair<int,pair<int,int> > scheduling(const vector<int>& canDrivers, const int orderId) {
	order_t& order = orders[orderId];
	const int sz = canDrivers.size();
	double bestDelta = inf, delta;
	int bestDriver=-1, bestPick, bestDrop;
	int pick, drop, driverId;

	for (int i=0; i<sz; ++i) {
		driverId = canDrivers[i];

		updateDriverPosition(driverId, order.tid);

		getBestPosition(driverId, orderId, pick, drop, delta);

		restoreDriverPosition(driverId);

		if (delta < bestDelta) {
			bestDelta = delta;
			bestDriver = driverId;
			bestPick = pick;
			bestDrop = drop;
		}
	}

	return make_pair(bestDriver, make_pair(bestPick, bestDrop));
}

void responseDriver(const int driverId, const int orderId, int pickLoc, int dropLoc) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];

	updateDriverPosition(driverId, order.tid, true);

	vector<node_t> route = driver.route;
	int routeNum = route.size();

	driver.curTime = order.tid;
	driver.route.clear();
	for (int i=0; i<=routeNum; ++i) {
		if (pickLoc == i) driver.route.push_back(node_t(order.sid, orderId));
		if (dropLoc == i) driver.route.push_back(node_t(order.eid+R, orderId));
		if (i < routeNum)
			driver.route.push_back(route[i]);
	}
	driver.status = -1;
}

void updateBound(const int driverId, const int orderId) {
	driver_t& driver = drivers[driverId];
	if (driver.isEmpty()) return ;

	vector<node_t>& route = driver.route;
	const int sz = route.size();
	double curTime = driver.curTime;
	position_t curPos = driver.pos, nextPos;

	for (int i=0; i<sz; ++i) {
		const int placeId = route[i].placeId;
		const int orderId = route[i].orderId;
		nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		curTime += Length(curPos, nextPos);
		if (placeId < R) {
			curTime = max(curTime, (double)orders[orderId].tid);
		} else {
			bound = max(bound, curTime-orders[orderId].tid);
		}
		curPos = nextPos;
	}
}

void Tshare_Dist() {
	for (int orderId=0; orderId<N; ++orderId) {
		for (int driverId=0; driverId<M; ++driverId) {
			updateIndex(driverId, orders[orderId].tid);
		}
		vector<int> canDrivers = taxiSearching(orderId);
		pair<int,pair<int,int> > tmp = scheduling(canDrivers, orderId);
		int driverId = tmp.first;
		int pickLoc = tmp.second.first, dropLoc = tmp.second.second;
		#ifdef LOCAL_DEBUG
		assert(driverId>=0 && pickLoc>=0 && dropLoc>=0 && pickLoc<=dropLoc);
		// printf("orderId = %d, driverId = %d\n", orderId, driverId);
		#endif
		responseDriver(driverId, orderId, pickLoc, dropLoc);
		//updateBound(driverId, orderId);
	}

	for (int driverId=0; driverId<M; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			moveForward(driverId);
	}
}

void scheduleAndMatch(vector<int>& driverIds, vector<int>& orderIds, double curTime) {
	int pickLoc, dropLoc;
	double delta;

	while (!orderIds.empty()) {
		const int driverSz = driverIds.size();
		const int orderSz = orderIds.size();
		if (driverSz < orderSz) {
			hung.init(driverSz, orderSz);
		} else {
			hung.init(orderSz, driverSz);
		}

		for (int i=0; i<driverSz; ++i) {
			const int driverId = driverIds[i];
			for (int j=0; j<orderSz; ++j) {
				const int orderId = orderIds[j];

				updateDriverPosition(driverId, curTime);
				getBestPosition(driverId, orderId, pickLoc, dropLoc, delta);
				restoreDriverPosition(driverId);

				if (driverSz < orderSz)
					hung.addEdge(i, j, -delta);
				else
					hung.addEdge(j, i, -delta);
			}
		}

		hung.match();

		if (driverSz < orderSz) {
			for (int x=0; x<driverSz; ++x) {
				int y = hung.xy[x];
				const int driverId = driverIds[x];
				const int orderId = orderIds[y];

				updateDriverPosition(driverId, curTime, true);
				getBestPosition(driverId, orderId, pickLoc, dropLoc, delta);
				responseDriver(driverId, orderId, pickLoc, dropLoc);

				orderIds[y] = -1;
			}

			for (int y=orderSz-1; y>=0; --y) {
				if (orderIds[y] == -1) {
					orderIds[y] = *orderIds.rbegin();
					orderIds.pop_back();
				}
			}
		} else {
			for (int y=0; y<driverSz; ++y) {
				int x = hung.xy[y];
				const int driverId = driverIds[x];
				const int orderId = orderIds[y];

				updateDriverPosition(driverId, curTime, true);
				getBestPosition(driverId, orderId, pickLoc, dropLoc, delta);
				responseDriver(driverId, orderId, pickLoc, dropLoc);
			}
			orderIds.clear();
		}

		hung.clear();
	}
}

void Tshare_Dist_KM(const double timeWindowSize = 100) {
	double preTime = 0, curTime;
	int orderId = 0;
	vector<int> orderIds, driverIds;

	while (orderId < N) {
		orderIds.clear();
		while (orderId<N && orders[orderId].tid<preTime+timeWindowSize) {
			orderIds.push_back(orderId);
			curTime = orders[orderId].tid;
			++orderId;
		}
		if (orderIds.empty()) {
			preTime = orders[orderId].tid;
			printf("orderId = %d, tid = %d, preTime = %.0lf\n", orderId, orders[orderId].tid, preTime);
			fflush(stdout);
			continue;
		}

		driverIds.clear();
		for (int driverId=0; driverId<M; ++driverId) {
			updateIndex(driverId, curTime);
			// updateDriverPosition(driverId, curTime, true);
			driverIds.push_back(driverId);
		}

		scheduleAndMatch(driverIds, orderIds, curTime);

		preTime += timeWindowSize;
		printf("orderId = %d, tid = %d, preTime = %.0lf\n", orderId, orders[orderId-1].tid, preTime);
		fflush(stdout);
	}

	for (int driverId=0; driverId<M; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			moveForward(driverId);
	}
}

void printAns() {
	for (int driverId=0; driverId<M; ++driverId) {
		const int sz = moves[driverId].size();
		printf("%d %d\n", driverId, sz);
		dumpOutput(moves[driverId]);
	}

	printf("%.10lf\n", ans);
	fflush(stdout);
}

void solve() {
	Tshare_Dist();
	printAns();
	deleteAll();
}

void readNetwork() {
	vector<double> rests_tmp;
	vector<double> dists_tmp;
	vector<int> orders_tmp;

	readInput(R, D, M, CAP, N, rests_tmp, dists_tmp, orders_tmp);

	initAll();

	for (int i=0,j=0; j<R; i+=2,++j) {
		rests[j] = position_t(rests_tmp[i], rests_tmp[i+1]);
	}
	for (int i=0,j=0; j<D; i+=2,++j) {
		dists[j] = position_t(dists_tmp[i], dists_tmp[i+1]);
	}
	for (int i=0,j=0; j<N; i+=3,++j) {
		orders[j] = order_t(orders_tmp[i], orders_tmp[i+1], orders_tmp[i+2]);
	}

 	distributeDrivers();
}


int main(int argc, char **argv) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	else {
		freopen("data.in", "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}
	else {
		freopen("data.out", "w", stdout);
	}

	readNetwork();
	solve();

	return 0;
}
/**
9433
orderId=94,driverId=16,val=124.13518788,delta=156.05131737,pick=1,drop=3
orderId=94,driverId=16,val=124.13518788,delta=152.82675504,pick=1,drop=2
time = 23ms.
*/
