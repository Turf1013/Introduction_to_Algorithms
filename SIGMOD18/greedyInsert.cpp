/**
	\author: 	Trasier
	\date: 		2017.10.13
*/
/**
	\author: 	Trasier
	\date:   	2017.6.1
	\source: 	ICDE13 T-share: A Large-Scale Dynamic Taxi Ridesharing Service
	\note: 		1) 2017.6.5 updateMove is not fixed yet.
				2) 2017.6.6 There could be some bugs in updateMove, since at one place(aRest or aDist), more than one riders can be pickedup or delivered.
				3) 2017.6.7 Because of previous bugs, leaveTime of each movement should also be updated, the begTime/endTime for all the places are not the same.
								But the maximum value is the leaveTime.
*/
#include "global.h"



#define LOCAL_DEBUG


int V, N, C, M;
position_t* points = NULL;
order_t* orders = NULL;
double *pickTime;
double *deliverTime;
int *mark;

void init() {
	mark = new int[M];
	mark_ = new int[M];
	pickTime = new double[M];
	delvierTime = new double[M];
	for (int i=0; i<M; ++i) {
		pickTime[i] = deliverTime[i] = inf;
		mark[i] = -1;
	}
}

void FreeMem() {
	delete[] points;
	delete[] orders;
	delete[] pickTime;
	delete[] deliverTime;
	delete[] mark;
}

void updateMove(const int driverId) {
	driver_t& driver = drivers[driverId];
	if (driver.empty()) return ;
	
	const int placeId = driver.route[0].placeId;
	const int orderId = driver.route[0].orderId;
	position_t& nextPos = points[placeId];
	double arriveTime = driver.curTime + Length(driver.pos, nextPos);
	
	// update the pickup time or delivery time
	vector<node_t>::iterator iter = driver.route.begin();
	while (iter!=driver.route.end() && iter->placeId==placeId) {
		/** 
			update the rider's record to evaluate the global answer
				-- 2017.6.7 more than once.
		*/
		const int orderId = iter->orderId;
		if (mark[orderId] == -1) {
			#ifdef LOCAL_DEBUG
			assert(orders[orderId].sid == placeId);
			#endif
			pickTime[orderId] = arriveTime;
			mark[orderId] = 0;
		} else {
			#ifdef LOCAL_DEBUG
			assert(mark[orderId] == 0);
			assert(orders[orderId].eid == placeId);
			#endif
			deliverTime[orderId] = arriveTime;
			mark[orderId] = 1;
		}
		++iter;
	}
	driver.erase(driver.route.begin(), iter);
	
	driver.pos = nextPos;
	driver.curTime = arriveTime;
}

void updateDriverPosition(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.isEmpty())
		return ;

	if (dcmp(driver.curTime-orderTid) == 0)
		return ;

	position_t src = driver.pos;
	const int placeId = driver.route[0].placeId;
	position_t des = points[placeId];
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

	driver.pos.x = src.x + dx * (orderTid - driver.curTime);
	driver.pos.y = src.y + dy * (orderTid - driver.curTime);
	move.arrive = move.leave = orderTid;
	driver.curTime = orderTid;
}

void updateDriverPosition(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	#ifdef LOCAL_DEBUG
	assert(driver.curTime <= orderTid);
	#endif
	
	while (!driver.isEmpty()) {
		const int placeId = driver.route[0].placeId;
		const int orderId = driver.route[0].orderId;
		position_t& nextPos = points[placeId];
		double driverTid = driver.curTime + Length(driver.pos, nextPos);

		if (driverTid > orderTid) {
			break;
		}

		updateMove(driverId);
	}

	updateDriverPosition(driverId, orderTid);
}

int calcCurCap(const int driverId) {
	driver_t& driver = drivers[driverId];
	vector<node_t>& route = driver.route;
	const int sz = route.size();
	int ret = 0;

	for (int i=0; i<sz; ++i) {
		if (mark[route[i].orderId]==0)
			++ret;
	}

	return ret;
}

pair<double,double> insertFeasibilityCheck(const int driverId, const int orderId, int pick, int deliver, const int initCap) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	int sz = route.size();
	double flowTime = inf;

	// check the complete path
	position_t curLoc = driver.pos, nextLoc;
	double arriveTime = order.tid;
	int cap = initCap;
	double ret = -1;

	for (int i=0; i<=sz; ++i) {
		if (i == pick) {
			nextLoc = points[order.sid];
			arriveTime += Length(curLoc, nextLoc);
			if (++cap > C) {
				flowTime = inf;
				break;
			}

			curLoc = nextLoc;
		}
		if (i == deliver) {
			nextLoc = points[order.eid];
			arriveTime += Length(curLoc, nextLoc);
			--cap;
			ret = max(ret, arriveTime-order.tid);

			curLoc = nextLoc;
		}
		if (i == sz) continue;

		const int placeId_ = route[i].placeId;
		const int orderId_ = route[i].orderId;
		nextLoc = points[placeId_];
		arriveTime += Length(curLoc, nextLoc);
		
		if (mark[orderId_]==1 || pickTime[orderId_]<inf) {
			flowTime = max(flowTime, arriveTime-orders[orderId_].tid);
			--cap;
		} else {
			pickTime[orderId_] = arriveTime;
			if (++cap > C) {
				flowTime = inf;
				break;
			}
		}
		
		curLoc = nextLoc;
	}

	for (int i=0; i<sz; ++i) {
		const int placeId_ = route[i].placeId;
		const int orderId_ = route[i].orderId;
		if (mark[orderId_] == -1) {
			pickTime[orderId_] = inf;
		}
	}

	return make_pair(flowTime, arriveTime-order.tid);
}

void getBestPosition(const int driverId, const int orderId, int& pick, int& deliver, double& flowTime, double& distance) {
	driver_t& driver = drivers[driverId];
	int sz = driver.route.size();
	double tmp;
	int iniCap = calcCap(driverId);

	pick = deliver = -1;
	flowTime = distance = inf;
	for (int i=0; i<=sz; ++i) {
		for (int j=i; j<=sz; ++j) {
			pair<double,double> tmp = insertFeasibilityCheck(driverId, orderId, i, j, iniCap);
			if (tmp.first<flowTime || (tmp.fist==flowTime && tmp.second<distance)) {
				flowTime = tmp.first;
				distance = tmp.second;
			}
		}
	}
}

void scheduling(const int orderId, int& bestDriver, int& bestPick, int& bestDeliver) {
	double bestFlow = inf, bestDistance = inf;
	double tmpFlow, tmpDistance;
	int pickLoc, deliverLoc;
	
	bestPick = bestDeliver = bestDriver = -1;
	for (int driverId=0; driverId<N; ++driverId) {
		getBesPosition(driverId, orderId, pickLoc, deliverLoc, tmpFlow, tmpDistance);
		if (tmpFlow<bestFlow || (tmpFlow==bestFlow && tmpDistance<bestDistance)) {
			bestDriver = driverId;
			bestPick = pickLoc;
			bestDeliver = deliverLoc;
			bestFlow = tmpFlow;
			bestDistance = tmpDistance;
		}
	}
}

void responseDriver(int orderId, int driverId, int pickLoc, int deliverLoc) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t> route = driver.route;
	int routeSz = route.size();

	driver.curTime = order.tid;
	driver.clear();
	for (int i=0; i<=routeSz; ++i) {
		if (i == pickLoc) 
			driver.route.push_back(node_t(order.sid, orderId));
		if (i == deliverLoc)
			driver.route.push_back(node_t(order.eid, orderId));
		if (i < routeSz)
			driver.route.push_back(route[i]);
	}
}

void greedyInsert() {
	int driverId, orderId, pickLoc, deliverLoc;
	
	for (orderId=0; orderId<M; ++orderId) {
		for (driverId=0; driverId<N; ++driverId) {
			updateIndex(driverId, orders[orderId].tid);
		}
		scheduling(orderId, driverId, pickLoc, deliverLoc);
		#ifdef LOCAL_DEBUG
		assert(driverId>=0 && pickLoc>=0 && deliverLoc>=0);
		#endif
		responseDriver(orderId, driverId, pickLoc, deliverLoc);
	}

	for (driverId=0; driverId<N; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			updateMove(driverId);
	}
}

double calcResult() {
	double ans = -1;
	
	for (int orderId=0; orderId<M; ++orderId) {
		#ifdef LOCAL_DEBUG
		assert(mark[orderId] == 2);
		#endif
		ans = max(ans, deliverTime[orderId]-orders[orderId].tid);
	}
	
	return ans;
}

double solve() {
	init();

	greedyInsert();
	
	double ret = calcResult();
	return ret;
}

int main(int argc, char **argv) {
	string execName("LAF");

	string srcFileName;
	if (argc > 1) {
		srcFileName = string(argv[1]);
	}
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	// step1: read Input
	if (srcFileName.empty()) {
		readInput(cin);
	} else {
		ifstream fin(srcFileName.c_str(), ios::in);
		if (!fin.is_open()) {
			fprintf(stderr, "FILE %s is invalid.\n", srcFileName.c_str());
			exit(1);
		}

		readInput(fin);
		fin.close();
	}

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish reading input.\n");
	#endif

	// step2: online execute
	clock_t begTime, endTime;
	begTime = clock();
	double ans = solve();
	endTime = clock();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish solving.\n");
	#endif

	// step3: output result
	double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	#ifdef WATCH_MEM
	dumpResult(execName, ans, usedTime, usedMemory/1024.0);
	#else
	dumpResult(execName, ans, usedTime);
	#endif

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish dumping.\n");
	#endif

	// step4: free memory
	FreeMem();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish free memory.\n");
	#endif

	fflush(stdout);

	return 0;
}