/**
	\author: 	Trasier
	\date: 		2017.7.31
	\note:
*/
#include <bits/stdc++.h>
using namespace std;

#define LOCAL_DEBUG

#include "input.h"

const double eps = 1e-4;
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

const double waitTime = 0;
const double inf = 1e20;
int R, D, M, C, N;
driver_t *drivers;
position_t *rests;
position_t *dists;
order_t *orders;
rider_t *riders;
int *taken;
double ans;

double Length(const position_t& pa, const position_t& pb) {
	return sqrt((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

void initAll() {
	drivers = new driver_t[M];
	rests = new position_t[R];
	dists = new position_t[D];
	orders = new order_t[N];
	riders = new rider_t[N];
	taken = new int[N];
	memset(taken, -1, sizeof(int)*N);
	ans = 0.0;
}

void deleteAll() {
	delete[] drivers;
	delete[] rests;
	delete[] dists;
	delete[] orders;
	delete[] riders;
	delete[] taken;
}

void readNetwork(const string& networkFileName) {
	vector<double> vRest_tmp, vDist_tmp;
	vector<int> vOrder_tmp;

	readInput(networkFileName, R, D, M, C, N, vRest_tmp, vDist_tmp, vOrder_tmp);

	initAll();
	#ifdef LOCAL_DEBUG
	assert(vRest_tmp.size() == R*2);
	assert(vDist_tmp.size() == D*2);
	assert(vOrder_tmp.size() == N*3);
	#endif

	for (int i=0,j=0; i<R; ++i,j+=2) {
		rests[i] = position_t(vRest_tmp[j], vRest_tmp[j+1]);
	}
	for (int i=0,j=0; i<D; ++i,j+=2) {
		dists[i] = position_t(vDist_tmp[j], vDist_tmp[j+1]);
	}
	for (int i=0,j=0; i<N; ++i,j+=3) {
		orders[i] = order_t(vOrder_tmp[j], vOrder_tmp[j+1], vOrder_tmp[j+2]);
	}
}

int findRest(const position_t& a) {
	for (int i=0; i<R; ++i) {
		if (rests[i] == a)
			return i;
	}
	return -1;
}

int findDist(const position_t& a) {
	for (int i=0; i<D; ++i) {
		if (dists[i] == a)
			return i;
	}
	return -1;
}

bool simulateRouteByDriver(ifstream& fin, int driverId, int moveNum) {
	position_t curLoc, nextLoc;
	double simArrive, simLeave = 0.0;
	double stuArrive, stuLeave;
	vector<int> curBucket, nextBucket;
	set<int> curOrderSet, nextOrderSet;
	int orderId, buckNum;

	fin >> curLoc.x >> curLoc.y >> stuArrive >> stuLeave >> buckNum;
	for (int i=0; i<moveNum-1; ++i) {
		fin >> nextLoc.x >> nextLoc.y >> stuArrive >> stuLeave >> buckNum;
		nextBucket.clear();
		for (int j=0; j<buckNum; ++j) {
			fin >> orderId;
			--orderId;
			nextBucket.push_back(orderId);
		}

		// 0. check the capactiy
		if (buckNum > C) {
			printf("driverId = %d, moveId = %d, buckNum = %d out of capacity = %d\n",
					driverId, i, buckNum, C);
			puts("cond 0");
			return false;
		}

		if (i == 0) {
			simArrive = stuArrive;
//		} else if (i == 1) {
//			if (dcmp(stuArrive - Length(curLoc, nextLoc)) < 0)
//				return false;
//			simArrive = stuArrive;
		} else {
			simArrive = simLeave + Length(curLoc, nextLoc);
		}
		simLeave = simArrive;

		// 1. check the arrive time.
		if (dcmp(simArrive - stuArrive) > 0) {
			printf("driverId = %d, moveId = %d, simArrive = %.6lf, stuArrive = %.6lf\n",
					driverId, i, simArrive, stuArrive);
			puts("cond 1");
			return false;
		}
		// 2. check the leave time
		if (dcmp(stuLeave - stuArrive) < 0) {
			puts("cond 2");
			return false;
		}

		nextOrderSet.clear();
		nextOrderSet.insert(nextBucket.begin(), nextBucket.end());
		// 3. \forall order in curOrderSet but not in nextOrderSet, the order must be dropef off
		for (set<int>::iterator iter=curOrderSet.begin(); iter!=curOrderSet.end(); ++iter) {
			if (nextOrderSet.count(*iter) == 0) {
				orderId = *iter;
				// 3.1. position not match
				if (nextLoc != dists[orders[orderId].eid]) {
					puts("cond 3.1");
					return false;
				}
				// 3.2. with no pickup
				if (taken[orderId] != 0) {
					puts("cond 3.2");
					return false;
				}
				taken[orderId] = 1;
				riders[orderId].endTime = stuArrive;
			}
		}
		// 4. \forall order in nextOrderSet but not in curOrderSet, the order must be picked up
		for (set<int>::iterator iter=nextOrderSet.begin(); iter!=nextOrderSet.end(); ++iter) {
			if (curOrderSet.count(*iter) == 0) {
				orderId = *iter;
				// 4.1. position not match
				if (nextLoc != rests[orders[orderId].sid]) {
					printf("driverId = %d, moveId = %d, nextLoc = (%.4lf,%.4lf), rest = (%.4lf, %.4lf)\n",
							driverId, i, nextLoc.x, nextLoc.y, rests[orders[orderId].sid].x, rests[orders[orderId].sid].y);
					puts("cond 4.1");
					return false;
				}
				// 4.2. with no pickup
				if (taken[orderId] != -1) {
					puts("cond 4.2");
					return false;
				}
				taken[orderId] = 0;
				riders[orderId].begTime = max(stuArrive, orders[orderId].tid+waitTime);

				// update the leave time, make sure to pickup the order
				simLeave = max(simLeave, orders[orderId].tid+waitTime);
			}
		}

		// 5. check the leave time
		if (dcmp(stuLeave - simLeave) < 0) {
			puts("cond 5");
			return false;
		}
		simLeave = stuLeave;


		ans += Length(curLoc, nextLoc);

		curLoc = nextLoc;
		curBucket = nextBucket;
		curOrderSet = nextOrderSet;
	}

	// 6. check the final bucket
	if (!curOrderSet.empty()) {
		puts("cond 6");
		return false;
	}

	return true;
}

void simulateRoute(const string& routeFileName) {
	ifstream fin(routeFileName.c_str(), ios::in);

	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", routeFileName.c_str());
		exit(1);
	}

	int driverId, moveNum;

	for (int i=0; i<M; ++i) {
		fin >> driverId >> moveNum;
		//printf("driverId = %d, moveNum = %d\n", driverId, moveNum);
		--driverId;
		if (!simulateRouteByDriver(fin, driverId, moveNum)) {
			printf("route is invalid.\n");
			return ;
		}
	}

	// double simAns = 0;
	bool allDelivered = true;

	for (int i=0; i<N; ++i) {
		if (taken[i] != 1) {// this order hasn't been delivered yet
			if (taken[i] == 0)
				printf("order %d is not delivered\n", i+1);
			else
				printf("order %d is not picked\n", i+1);
			allDelivered = false;
		}
		// simAns = max(simAns, riders[i].endTime-orders[i].tid);
	}
	if (!allDelivered) return ;

	double simAns = ans;

	double stuAns = inf;
	fin >> stuAns;
	if (dcmp(simAns-stuAns) != 0) {
		printf("route is invalid. simAns = %.2lf, stuAns = %.2lf\n", simAns, stuAns);
		return ;
	}

	printf("Right! ans = %.10lf\n", stuAns);
}

void checkRoute(const string& networkFileName, const string& routeFileName) {
	if (networkFileName.empty() || routeFileName.empty()) {
		fprintf(stderr, "srcfileName is missing.\n");
		exit(1);
	}

	/**
		\step1: construct the network
	*/
	readNetwork(networkFileName);

	/**
		\step2: initial riders & drivers
	*/
	//init();

	/**
		\step3: simulate the route
	*/
	simulateRoute(routeFileName);

	/**
		\step4: delete all
	*/
	deleteAll();
}

int main(int argc, char **argv) {
	string networkFileName, routeFileName, outFileName;

	if (argc > 1)
		networkFileName = string(argv[1]);
	if (argc > 2)
		routeFileName = string(argv[2]);
	if (argc > 3)
		freopen(argv[3], "w", stdout);

	checkRoute(networkFileName, routeFileName);

	return 0;
}
