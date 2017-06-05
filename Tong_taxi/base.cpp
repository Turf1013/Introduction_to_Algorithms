/**
	\author: 	Trasier
	\date: 		2017.6.5 
	\describe: 	base is a simple solution. Every driver can only take a rider once. 
			Everytime, a nearest driver is selected from candinates to match with the rider.
*/

#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"

#define LOCAL_DEBUG

const double eps = 1e-7;
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
vector<vector<move_t> > moves;
int *tasks;
vector<int> orderQ;
vector<int> driverQ;
priority_queue<pair<double,int>,vector<pair<double,int> >, greater<pair<double,int> > > taskQ;
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
	// moves = new move_t[M];
	tasks = new int[M];

	for (int i=0; i<M; ++i)
		orderQ.push_back(i);

	for (int i=0; i<M; ++i) {
		int placeId = rand() % R;
		drivers[i].pos = rests[placeId];
		moves.push_back(vector<move_t>());
	}

	ans = inf;
}

void deleteAll() {
	delete[] drivers;
	delete[] rests;
	delete[] dists;
	delete[] orders;
	delete[] riders;
	// delete[] moves;
	delete[] tasks;
}

void readNetwork() {
	vector<double> vRest_tmp, vDist_tmp;
	vector<int> vOrder_tmp;

	readInput(R, D, M, C, N, vRest_tmp, vDist_tmp, vOrder_tmp);

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

void updateTask(const double curTime) {
	while (!taskQ.empty()) {
		if (dcmp(taskQ.top().first - curTime) > 0)
			break;
		const int driverId = taskQ.top().second;
		driverQ.push_back(driverId);
		drivers[driverId].pos = dists[orders[tasks[driverId]].eid];
		tasks[driverId] = -1;
		taskQ.pop();
	}
}

double finishTask(int taskNum) {
	double ret = -1.0;

	while (!taskQ.empty() && taskNum>0) {
		driverQ.push_back(taskQ.top().second);
		ret = taskQ.top().first;
		taskQ.pop();
		--taskNum;	
	}

	return ret;
}

void executeTask(const int driverId, const int orderId, double curTime) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	double pickTime = max(curTime + Length(driver.pos, rests[order.sid]), order.tid+waitTime);
	double dropTime = pickTime + Length(rests[order.sid], dists[order.eid]);

	tasks[driverId] = orderId;
	taskQ.push(make_pair(dropTime, driverId));
	ans = min(ans, dropTime-order.tid);

	move_t move;

	// pickup
	move.x = rests[order.sid].x;
	move.y = rests[order.sid].y;
	move.arrive = move.leave = pickTime;
	move.bucket.clear();
	move.bucket.push_back(orderId);
	moves[driverId].push_back(move);


	// dropoff
	move.x = dists[order.eid].x;
	move.y = dists[order.eid].y;
	move.arrive = move.leave = dropTime;
	move.bucket.clear();
	moves[driverId].push_back(move);
}

void assignTask(double curTime) {
	vector<pair<double,int> > waitTimes;

	for (int i=0; i<orderQ.size(); ++i) {
		order_t& order = orders[orderQ[i]];
		double wait = max(curTime, (double)order.tid) + Length(rests[order.sid], dists[order.eid]) - order.tid;
		waitTimes.push_back(make_pair(wait, i));
	}
	sort(waitTimes.begin(), waitTimes.end(), greater<pair<double,int> >() );

	for (int i=0; i<orderQ.size()&&!driverQ.empty(); ++i) {
		order_t& order = orders[orderQ[i]];
		int v = -1;
		double bestVal = inf, val;
		for (int j=0; j<driverQ.size(); ++j) {
			driver_t& driver = drivers[driverQ[j]];
			double pickTime = max(curTime+Length(driver.pos, rests[order.sid]), (double)order.tid);
			val = pickTime + Length(rests[order.sid], dists[order.eid]);
			if (val < bestVal) {
				bestVal = val;
				v = j;
			}
		}

		#ifdef LOCAL_DEBUG
		assert(v != -1);
		#endif
		const int driverId = driverQ[v];
		driverQ[v] = *driverQ.rbegin();
		driverQ.pop_back();

		executeTask(driverId, orderQ[i], curTime);
		orderQ[i] = -1;
	}
}

void printAns() {
	for (int driverId=0; driverId<N; ++driverId) {
		const int sz = moves[driverId].size();
		printf("%d %d\n", driverId, sz);
		dumpOutput(moves[driverId]);
	}
}

void solve() {
	int orderId, driverId;
	initAll();
	double curTime = 0.0;

	for (orderId=0; orderId<M; ++orderId) {
		updateTask(orders[orderId].tid);
		orderQ.push_back(orderId);
		if (!driverQ.empty()) {
			assignTask(orders[orderId].tid);
		}
	}
	while (!taskQ.empty()) {
		curTime = finishTask(1);
		assignTask(curTime);
	}

	printAns();

	deleteAll();
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

