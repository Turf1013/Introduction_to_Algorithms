/**
	\author: 	Trasier
	\date:   	2017.6.19
	\source: 	optimized TShare using DP
	\note: 		
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
//#include "monitor.h"

#define LOCAL_DEBUG

const double waitTime = 0.0;
const double inf = 1e20;
int graphLength = 100, graphWidth = 100;
int gridLength = 10, gridWidth = 10;
int R, D, M, C, N;
double bound;

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
		drivers[i].status = idx + 1;
		drivers[i].pos = rests[idx];
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
		driver.pos = rests[placeId];
		return ;
	}

	// calculate the arriveTime
	const int placeId = driver.route[0].placeId;
	const int orderId = driver.route[0].orderId;
	position_t nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
	double arriveTime = driver.curTime + Length(driver.pos, nextPos);

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
			tmpTime = max(arriveTime, orders[iter->orderId].tid+waitTime);
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
	const int placeId = driver.route[0].placeId;
	position_t desPos = (placeId<R) ? rests[placeId] : dists[placeId-R];

	double t = Length(srcPos, desPos);
	double dx = (desPos.x - srcPos.x) / t;
	double dy = (desPos.y - srcPos.y) / t;
	double x = srcPos.x + dx * (orderTid - driver.curTime);
	double y = srcPos.y + dy * (orderTid - driver.curTime);

	if (toMove) {
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
		double tmpTime = (placeId<R) ? max(arriveTime, orderTid+waitTime) : arriveTime;

		if (tmpTime > orderTid) break;

		moveForward(driverId);
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
		if (route[i].placeId>=R && taken[route[i].placeId-R]==0)
			++ret;
	}

	return ret;
}

void getBestPosition(int driverId, int orderId, int& bestPick, int& bestDrop, double& bestVal, double& bestCost) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	int pickLoc, dropLoc;
	double val, cost, delta;
	
	if (sz == 0) {
		bestPick = bestDrop = 0;
		bestVal = max(Length(driver.pos,rests[order.sid]), order.tid+waitTime) + Length(rests[order.sid], dists[order.eid]) - order.tid;
		bestCost = 0.0;
		return ;
	}
	
	bestVal = inf;
	bestCost = inf;
	
	bool* F = new bool[sz+1];
	int* C = new int[sz+1];
	double* T = new double[sz+1];
	double* slack = new double[sz+1];
	position_t curPos = driver.pos, nextPos;
	
	C[0] = calcInitCap(driverId);
	T[0] = order.tid;
	F[0] = false;
	for (int i=1; i<=sz; ++i) {
		const int placeId = route[i-1].placeId;
		const int orderId = route[i-1].orderId;
		nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
		T[i] = T[i-1] + Length(curPos, nextPos);
		if (placeId < R)
			T[i] = max(T[i], orders[orderId].tid+waitTime);
		
		if (placeId < R)
			C[i] = C[i-1] + 1;
		else
			C[i] = C[i-1] - 1;
		
		if (placeId < R)
			F[i] = false;
		else
			F[i] = true;
	}
	#ifdef LOCAL_DEBUG
	assert(F[sz]);
	#endif
	
	for (int i=sz; i>=0; --i) {
		if (F[i]) {
			const int orderId = route[i-1].orderId;
			slack[i] = min(slack[i+1], orders[orderId].tid+bound-T[i]);
		} else {
			slack[i] = slack[i+1];
		}
	}
	
	double* Ddelta = new double[sz+1];
	double* Dval = new double[sz+1];
	int* Dpos = new int[sz+1];
	position_t dropPos = dists[order.eid], pickPos = rests[order.sid];
	
	for (int i=sz; i>=0; --i) {
		if (i == 0) {
			position_t apos = driver.pos, bpos = (route[i].placeId < R) ? rests[route[i].placeId] : dists[route[i].placeId];
			Ddelta[i] = Length(apos, dropPos) + Length(dropPos, bpos) - Length(apos, bpos);
		} else if (i == sz) {
			Ddelta[i] = 0;
		} else {
			position_t apos = (route[i].placeId < R) ? rests[route[i].placeId] : dists[route[i].placeId];
			position_t bpos = (route[i+1].placeId < R) ? rests[route[i+1].placeId] : dists[route[i+1].placeId];
			Ddelta[i] = Length(apos, dropPos) + Length(dropPos, bpos) - Length(apos, bpos);
		}
		
		if (Ddelta[i] <= slack[i]) {
			Dval[i] = bound;
		} else {
			Dval[i] = bound + Ddelta[i] - slack[i];
		}
		Dpos[i] = i;
		
		if (i < sz) {
			if (Dval[i] > Dval[i+1]) {
				Dval[i] = Dval[i+1];
				Dpos[i] = Dpos[i+1];
			} else if (Dval[i]==Dval[i+1] && Ddelta[i]>Ddelta[Dpos[i+1]]) {
				Dval[i] = Dval[i+1];
				Dpos[i] = Dpos[i+1];
			}
		}
	}
	
	double l0 = Length(pickPos, dropPos);
	
	for (int i=0; i<=sz; ++i) {
		/**
			two case needs to be considered, 1)[i,sz); 2) after sz.
			The frist case is calculated by DP.
			The second case is calculated directly.
		*/
		pickLoc = i;
		double tmpVal, tmpDelta, tmpCost;
		
		{// case2:
			dropLoc = i;
			if (i == 0) {
				position_t apos = driver.pos, bpos = (route[i].placeId < R) ? rests[route[i].placeId] : dists[route[i].placeId-R];
				delta = Length(apos, pickPos) + l0 + Length(dropPos, bpos) - Length(apos, bpos);
				tmpVal = bound + max(0.0, delta-slack[i]);
				tmpVal = max(tmpVal, T[i]+Length(apos, pickPos)+l0-order.tid);
				tmpCost = delta;
			} else if (i == sz) {
				position_t apos = (route[i-1].placeId < R) ? rests[route[i-1].placeId] : dists[route[i-1].placeId-R];
				tmpVal = max(bound, T[i]+Length(apos, pickPos)+l0-order.tid);
				tmpCost = Length(apos, pickPos)+l0;
			} else {
				position_t apos = (route[i-1].placeId < R) ? rests[route[i-1].placeId] : dists[route[i-1].placeId-R];
				position_t bpos = (route[i].placeId < R) ? rests[route[i].placeId] : dists[route[i].placeId-R];
				delta = Length(apos, pickPos) + l0 + Length(dropPos, bpos) - Length(apos,bpos);
				tmpVal = bound + max(0.0, delta-slack[i]);
				tmpVal = max(tmpVal, T[i]+Length(apos, pickPos)+l0-order.tid);
				tmpCost = delta;
			}
		}
		val = tmpVal;
		cost = tmpCost;
		
		if (i < sz) {// case1:
			if (i == 0) {
				position_t apos = driver.pos, bpos = (route[i].placeId < R) ? rests[route[i].placeId] : dists[route[i].placeId-R];
				delta = Length(apos, dropPos) + Length(dropPos, bpos) - Length(apos, bpos);
			} else {
				position_t apos = (route[i-1].placeId < R) ? rests[route[i-1].placeId] : dists[route[i-1].placeId-R];
				position_t bpos = (route[i].placeId < R) ? rests[route[i].placeId] : dists[route[i].placeId-R];
				delta = Length(apos, dropPos) + Length(dropPos, bpos) - Length(apos, bpos);
			}
			tmpVal = bound + max(0.0, delta - slack[i]);
			tmpVal += Dval[i+1] - bound;
			tmpCost = delta + Ddelta[i+1];
			
			if (tmpVal < val) {
				val = tmpVal;
				cost = tmpCost;
				pickLoc = Dpos[i+1];
			} else if (tmpVal==val && tmpCost<cost) {
				val = tmpVal;
				cost = tmpCost;
				pickLoc = Dpos[i+1];
			}
		}
		
		if (val < bestVal) {
			bestVal = val;
			bestCost = cost;
			bestPick = pickLoc;
			bestDrop = dropLoc;
		} else if (val==bestVal && cost<bestCost) {
			bestVal = val;
			bestCost = cost;
			bestPick = pickLoc;
			bestDrop = dropLoc;
		}
	}
	
	delete[] Dval;
	delete[] Dpos;
	delete[] Ddelta;
	
	delete[] F;
	delete[] C;
	delete[] T;
	delete[] D;
	delete[] slack;
	delete[] delta;
}

pair<int,pair<int,int> > scheduling(const vector<int>& canDrivers, const int orderId) {
	order_t& order = orders[orderId];
	const int sz = canDrivers.size();
	double bestVal = inf, bestDelta = inf, val, delta;
	int bestDriver=-1, bestPick, bestDrop;
	int pick, drop, driverId;

	for (int i=0; i<sz; ++i) {
		driverId = canDrivers[i];
		
		updateDriverPosition(driverId, order.tid);
		getBestPosition(driverId, orderId, pick, drop, val, delta);
		restoreDriverPosition(driverId);
		
		val = max(val, bound);
		
		if (val < bestVal) {
			bestVal = val;
			bestDriver = driverId;
			bestPick = pick;
			bestDrop = drop;
			bestDelta = delta;
		} else if (dcmp(val-bestVal)==0 && delta<bestDelta) {
			bestVal = val;
			bestDriver = driverId;
			bestPick = pick;
			bestDrop = drop;
			bestDelta = delta;
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
		driver.route.push_back(route[i]);
	}
	driver.status = -1;
}

void ZShare() {
	for (int orderId=0; orderId<N; ++orderId) {
		for (int driverId=0; driverId<M; ++driverId) {
			updateIndex(driverId, orders[orderId].tid);
		}
		vector<int> canDrivers = taxiSearching(orderId);
		pair<int,pair<int,int> > tmp = scheduling(canDrivers, orderId);
		int driverId = tmp.first;
		int pickLoc = tmp.second.first, dropLoc = tmp.second.second;
		#ifdef LOCAL_DEBUG
		assert(driverId>=0 && pickLoc>=0 && dropLoc>=0);
		#endif		
		responseDriver(driverId, orderId, pickLoc, dropLoc);
	}
}

void solve() {
	ZShare();
	printAns();
	deleteAll();
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

void readNetwork() {
	vector<double> rests_tmp;
	vector<double> dists_tmp;
	vector<int> orders_tmp;

	readInput(R, D, M, C, N, rests_tmp, dists_tmp, orders_tmp);

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
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}

	readNetwork();
	solve();

	return 0;
}