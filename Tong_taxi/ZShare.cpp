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
int R, D, M, CAP, N;
double bound;

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
		drivers[i].status = 0;
		drivers[i].pos = rests[0];
#ifdef LOCAL_DEBUG
		//drivers[i].pos = position_t(0.0, 0.0);
#endif
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
		driver.status = 1;
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
		double tmpTime = (placeId<R) ? max(arriveTime, orders[orderId].tid+waitTime) : arriveTime;

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

bool judgeRoute(int driverId, int orderId, int pickLoc, int dropLoc, double& val, double& cost) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	int cap = calcInitCap(driverId);
	double curTime = order.tid;
	position_t curPos = driver.pos, nextPos;

	#ifdef LOCAL_DEBUG
	assert(cap <= CAP);
	#endif
	val = 0.0;
	for (int i=0; i<=sz; ++i) {
		if (pickLoc == i) {
			nextPos = rests[order.sid];
			curTime += Length(curPos, nextPos);
			curTime = max(curTime, order.tid+waitTime);
			curPos = nextPos;
			if (++cap > CAP) return false;
		}
		if (dropLoc == i) {
			nextPos = dists[order.eid];
			curTime += Length(curPos, nextPos);
			val = max(val, curTime-order.tid);
			curPos = nextPos;
			--cap;
		}
		if (i < sz) {
			const int placeId = route[i].placeId;
			const int orderId = route[i].orderId;
			nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
			curTime += Length(curPos, nextPos);
			if (placeId < R) {
				curTime = max(curTime, orders[orderId].tid+waitTime);
				if (++cap > CAP) return false;
			} else {
				val = max(val, curTime-orders[orderId].tid);
				--cap;
			}
			curPos = nextPos;
		}
	}
	cost = curTime;

	return true;
}

void updateResult(double& bestVal, double& bestCost, int& bestPick, int& bestDrop, double tmpVal, double tmpCost, int pickLoc, int dropLoc) {
	if (dcmp(tmpVal-bestVal) < 0) {
		bestVal = tmpVal;
		bestCost = tmpCost;
		bestPick = pickLoc;
		bestDrop = dropLoc;
	} else if (dcmp(tmpVal-bestVal)==0 && dcmp(tmpCost-bestCost)<0) {
		bestVal = tmpVal;
		bestCost = tmpCost;
		bestPick = pickLoc;
		bestDrop = dropLoc;
	} else if (dcmp(tmpVal-bestVal)==0 && dcmp(tmpCost-bestCost)==0 && bestPick+bestDrop<pickLoc+dropLoc) {
		bestVal = tmpVal;
		bestCost = tmpCost;
		bestPick = pickLoc;
		bestDrop = dropLoc;
	}
}

void getBestPosition2(int driverId, int orderId, int& bestPick, int& bestDrop, double& bestVal, double& bestCost) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	double tmpVal, tmpCost;

	bestVal = bestCost = inf;
	for (int pickLoc=0; pickLoc<=sz; ++pickLoc) {
		for (int dropLoc=pickLoc; dropLoc<=sz; ++dropLoc) {
			if (!judgeRoute(driverId, orderId, pickLoc, dropLoc, tmpVal, tmpCost)) continue;
			updateResult(bestVal, bestCost, bestPick, bestDrop, tmpVal, tmpCost, pickLoc, dropLoc);
		}
	}
}

void getBestPosition(int driverId, int orderId, int& bestPick, int& bestDrop, double& bestVal, double& bestCost) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	
	if (sz == 0) {
		bestPick = bestDrop = 0;
		bestCost = max(order.tid+Length(driver.pos,rests[order.sid]), order.tid+waitTime) + Length(rests[order.sid], dists[order.eid]);
		bestVal = bestCost - order.tid;
		return ;
	}
	
	bestVal = bestCost = inf;
	bestPick = bestDrop = -1;
	int* C = new int[sz+1];
	int* F = new int[sz+1];
	double* Tid = new double[sz+1];
	double* T = new double[sz+1];
	double* Br = new double[sz+1];
	double* Bl = new double[sz+1];
	position_t curPos = driver.pos, nextPos;

	C[0] = calcInitCap(driverId);
	T[0] = order.tid;
	F[0] = 0;
	Tid[0] = order.tid;
	for (int i=1; i<=sz; ++i) {
		const int placeId = route[i-1].placeId;
		const int orderId = route[i-1].orderId;
		Tid[i] = orders[orderId].tid;
		nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
		T[i] = T[i-1] + Length(curPos, nextPos);
		if (placeId < R)
			T[i] = max(T[i], orders[orderId].tid+waitTime);
		C[i] = (placeId<R) ? (C[i-1]+1) : (C[i-1]-1);
		F[i] = (placeId<R) ? 0 : 1;
		curPos = nextPos;
	}

	for (int i=sz; i>=0; --i) {
		// if (F[i]) {
			// Br[i] = T[i] - Tid[i];
			// if (i < sz)
				// Br[i] = max(Br[i], Br[i+1]);
		// } else {
			// Br[i] = Br[i+1];
		// }
		if (i == sz) {
			Br[i] = F[i] * (T[i] - Tid[i]);
		} else {
			Br[i] = max(Br[i+1], F[i]*(T[i] - Tid[i]));
		}
	}
	for (int i=0; i<=sz; ++i) {
		if (i == 0) {
			Bl[i] = F[i] * (T[i] - Tid[i]);
		} else {
			Bl[i] = max(Bl[i-1], F[i]*(T[i] - Tid[i]));
		}
		// if (i == 0) {
			// Bl[i] = 0.0;
		// } else {
			// B[i] = Bl[i-1];
			// if (F[i]) {
				// Bl[i] = max(Bl[i], T[i]-Tid[i]);
			// }
		// }
	}

	double* dcost = new double[sz+1];
	double* dval = new double[sz+1];
	int* dpos = new int[sz+1];
	position_t pickPos = rests[order.sid], dropPos = dists[order.eid];
	position_t endPos = (route[sz-1].placeId<R) ? rests[route[sz-1].placeId] : dists[route[sz-1].placeId-R];
	double l0 = Length(pickPos, dropPos), t0 = order.tid;
	double delta, tmp;
	int pickLoc, dropLoc;

	for (int i=sz; i>=0; --i) {
		if (i>0 && C[i]==CAP) {
			dval[i] = dcost[i] = inf;
			dpos[i] = i;
			continue;
		}

		if (i == sz) {
			delta = Length(endPos, dropPos);
			dval[i] = T[sz] + delta - t0;
			dcost[i] = delta;
			dpos[i] = i;
		} else {
			if (i == 0) {
				curPos = driver.pos;
			} else {
				curPos = (route[i-1].placeId<R) ? rests[route[i-1].placeId] : dists[route[i-1].placeId-R];
			}
			nextPos = (route[i].placeId<R) ? rests[route[i].placeId] : dists[route[i].placeId-R];
			delta = Length(curPos, dropPos) + Length(dropPos, nextPos) - Length(curPos, nextPos);
			dval[i] = max(Br[i+1]+delta, T[i]+delta-t0);
			dcost[i] = delta;
			dpos[i] = i;
		}
		if (i < sz) {
			tmp = max(Br[i+1], dval[i+1]);
			if (tmp<dval[i] || (tmp==dval[i] && dcost[i+1]<=dcost[i])) {
				dval[i] = tmp;
				dcost[i] = dcost[i+1];
				dpos[i] = dpos[i+1];
			}
		}
	}

	for (int i=0; i<=sz; ++i) {
		if (C[i] >= CAP) continue;

		pickLoc = i;
		double tmpVal, tmpDelta, tmpCost, arriveTime;

		{// case1: i==j
			dropLoc = i;
			if (i == sz) {
				delta = Length(endPos, pickPos) + Length(pickPos, dropPos);
				tmpVal = max(Br[0], T[sz]+delta-t0);
				tmpCost = T[sz] + delta;
			} else {
				if (i == 0) {
					curPos = driver.pos;
				} else {
					curPos = (route[i-1].placeId<R) ? rests[route[i-1].placeId] : dists[route[i-1].placeId-R];
				}
				nextPos = (route[i].placeId<R) ? rests[route[i].placeId] : dists[route[i].placeId-R];
				delta = Length(curPos, pickPos) + Length(pickPos, dropPos) + Length(dropPos, nextPos) - Length(curPos, nextPos);
				tmp = max(Br[0], Br[i+1]+delta);
				tmpVal = max(tmp, T[i]+Length(curPos, pickPos)+Length(pickPos, dropPos)-t0);
				tmpCost = T[sz] + delta;
			}
			updateResult(bestVal, bestCost, bestPick, bestDrop, tmpVal, tmpCost, pickLoc, dropLoc);
		}
		if (i < sz) {// case2:
			if (i == 0) {
				curPos = driver.pos;
			} else {
				curPos = (route[i-1].placeId<R) ? rests[route[i-1].placeId] : dists[route[i-1].placeId-R];
			}
			nextPos = (route[i].placeId<R) ? rests[route[i].placeId] : dists[route[i].placeId-R];
			double delta_d = Length(curPos, pickPos) + Length(pickPos, nextPos) - Length(curPos, nextPos);
			tmp = delta_d + max(Br[i+1], dval[i+1]);
			tmpVal = max(Bl[i], tmp);
			tmpCost = T[sz] + delta_d + dcost[i+1];
			dropLoc = dpos[i+1];
			updateResult(bestVal, bestCost, bestPick, bestDrop, tmpVal, tmpCost, pickLoc, dropLoc);
		}
	}

	delete[] dcost;
	delete[] dval;
	delete[] dpos;
	delete[] C;
	delete[] F;
	delete[] T;
	delete[] Tid;
	delete[] Br;
	delete[] Bl;
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
		#ifdef LOCAL_DEBUG
		printf("orderId=%d,driverId=%d,val=%.8lf,delta=%.8lf,pick=%d,drop=%d\n",
				orderId, driverId, val, delta, pick, drop);
		#endif
		getBestPosition2(driverId, orderId, pick, drop, val, delta);
		#ifdef LOCAL_DEBUG
		printf("orderId=%d,driverId=%d,val=%.8lf,delta=%.8lf,pick=%d,drop=%d\n",
				orderId, driverId, val, delta, pick, drop);
		#endif

		restoreDriverPosition(driverId);
		
		val = max(val, bound);
		
		if (val < bestVal) {
			bestVal = val;
			bestDriver = driverId;
			bestPick = pick;
			bestDrop = drop;
			bestDelta = delta;
		} else if (val==bestVal && delta<bestDelta) {
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
	// #ifdef LOCAL_DEBUG
	// if (driverId==40 && orderId==452)
		// printf("driver at (%.4lf,%.4lf), time = %.2lf, initCap = %d\n", driver.pos.x, driver.pos.y, driver.curTime, calcInitCap(driverId));
	// #endif
	
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
	// #ifdef LOCAL_DEBUG
	// if (driverId==40 && orderId==452)
		// printf("driver at (%.4lf,%.4lf), time = %.2lf, initCap = %d\n", driver.pos.x, driver.pos.y, driver.curTime, calcInitCap(driverId));
	// #endif
	// #ifdef LOCAL_DEBUG
	// int cap = calcInitCap(driverId);
	// vector<int> vcap(1, cap);
	// if (driverId==40 && orderId==452)
		// printf("cap = %d\n", cap);
	// #endif

	for (int i=0; i<sz; ++i) {
		const int placeId = route[i].placeId;
		const int orderId = route[i].orderId;
		nextPos = (placeId<R) ? rests[placeId] : dists[placeId-R];
		curTime += Length(curPos, nextPos);
		if (placeId < R) {
			curTime = max(curTime, orders[orderId].tid+waitTime);
			// #ifdef LOCAL_DEBUG
			// ++cap;
			// vcap.push_back(cap);
			// if (cap > CAP) {
				// for (int j=0; j<vcap.size(); ++j)
					// printf("%2d ", vcap[j]);
				// putchar('\n');
				// printf("NOCAP:driverId=%d,orderId=%d,cap=%d\n", driverId, orderId, cap);
				// fflush(stdout);
			// }
			// assert(cap <= CAP);
			// #endif
		} else {
			bound = max(bound, curTime-orders[orderId].tid);
			// #ifdef LOCAL_DEBUG
			// --cap;
			// vcap.push_back(cap);
			// #endif
		}
		curPos = nextPos;
	}
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
		assert(driverId>=0 && pickLoc>=0 && dropLoc>=0 && pickLoc<=dropLoc);
		#endif		
		responseDriver(driverId, orderId, pickLoc, dropLoc);
		updateBound(driverId, orderId);
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

	double ans = -1;
	for (int orderId=0; orderId<N; ++orderId)
		ans = max(ans, riders[orderId].endTime-orders[orderId].tid);

	printf("%.10lf\n", ans);
	fflush(stdout);
}

void solve() {
	ZShare();
	//printAns();
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