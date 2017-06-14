/**
	\author: 	Trasier
	\date: 		2017.6.13
	\source: 	VLDB14 Large Scale Real-time Ridesharing with Service Guarantee on Road Networks
	\describ: 	Kinetic Tree with hotspot
				
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
//#include "monitor.h"
#include "treeNode.h"

#define LOCAL_DEBUG

const double waitTime = 0.0;
int graphLength = 100, graphWidth = 100;
int gridLength = 10, gridWidth = 10;
int theta = 50;
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

	void print() const {
		printf("%.2lf %.2lf\n", x, y);
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

struct hotspot_t {
	int spotId;
	node_t node;
	
	hotspot_t(int spotId = -1) {
		this->spotId = spotId;
	}
	hotspot_t(const node_t& a, int spotId = -1) {
		this->spotId = spotId;
		node = a;
	}
	
	bool operator==(const hotspot_t& oth) const {
		return spotId==oth.spotId && node==oth.node;
	}
	
	bool operator!=(const hotspot_t& oth) const {
		return spotId!=oth.spotId || node!=oth.node;
	}
};

typedef treeNode_t<hotspot_t> treeNode;

struct driver_t {
	position_t pos;
	double curTime;
	vector<treeNode*> route;

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

	// void push_back(int placeId, int orderId) {
		// route.push_back(node_t(placeId, orderId));
	// }

	void push_back(treeNode* p) {
		route.push_back(p);
	}

	void pop_front() {
		if (!route.empty())
			route.erase(route.begin());
	}

	void erase(vector<treeNode*>::iterator biter, vector<treeNode*>::iterator eiter) {
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
			node_t& node = route[i]->val.node;
			if (node.placeId < R)
				unpicked.insert(node.orderId);
			if (node.placeId>=R && unpicked.count(node.orderId)==0)
				ret.push_back(node.orderId);
		}

		return ret;
	}
};

struct rider_t {
	double begTime, endTime;

	rider_t(double begTime=0., double endTime=0.):
		begTime(begTime), endTime(endTime) {}
};


const double inf = 1e20;
position_t *rests;
position_t *dists;
order_t *orders;
rider_t *riders;
driver_t *drivers;
treeNode** kineticRoots;
int *taken;
vector<vector<move_t> > moves;

inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

void initRider() {
	// riders.clear();
	// for (int i=0; i<N; ++i) {
		// riders.push_back(rider_t());
	// }
	riders = new rider_t[N];
}

void initRoot() {
	kineticRoots = new treeNode*[M];
	hotspot_t hotspot(node_t(-1,-1), -1);
	for (int i=0; i<M; ++i) {
		kineticRoots[i] = new treeNode(hotspot);
	}
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
#ifdef LOCAL_DEBUG
		drivers[i].pos = position_t(10.0, 10.0);
#endif
		drivers[i].curTime = 0;
// #ifdef LOCAL_DEBUG
// 		printf("Driver%d is located in (%.2lf, %.2lf) at first.\n", i, drivers[i].pos.x, drivers[i].pos.y);
// #endif
		// update the initial move
//		move_t move;
//
//		move.x = drivers[i].pos.x;
//		move.y = drivers[i].pos.y;
//		move.arrive = move.leave = 0;
//		moves[i].push_back(move);
	}
}

void initAll() {
	initOrder();
	initRest();
	initDist();
	initDriver();
	initRider();
	initMove();
	initRoot();
}

void deleteAll() {
	delete[] orders;
	delete[] rests;
	delete[] dists;
	delete[] drivers;
	delete[] riders;
	for (int i=0; i<M; ++i) {
		deleteTree(kineticRoots[i]);
	}
	delete[] kineticRoots;
	delete[] taken;
}

void deleteSubtree(const int driverId, const treeNode* node) {
	// update the kinetic tree
	treeNode *rt = kineticRoots[driverId], *nrt = NULL;
	const int childSz = rt->size();

	for (int i=0; i<childSz; ++i) {
		if (rt->children[i] == node) {
			#ifdef LOCAL_DEBUG
			assert(nrt == NULL);
			#endif
			nrt = rt->children[i];
		} else {
			deleteTree(rt->children[i]);
		}
	}
	#ifdef LOCAL_DEBUG
	assert(nrt != NULL);
	#endif

	rt->children = nrt->children;
	delete nrt;
}

void updateMove(const int driverId) {
	driver_t& driver = drivers[driverId];
	if (driver.empty()) return ;
	
	const int placeId = driver.route[0]->val.node.placeId;
	//const int orderId = driver.route[0]->val.node.orderId;
	position_t& nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
	double arriveTime = driver.curTime + Length(driver.pos, nextPos);

	// add the movement of the driver
	move_t move;

	move.x = nextPos.x;
	move.y = nextPos.y;
	move.arrive = arriveTime;
	double& leaveTime = move.leave;
	leaveTime = arriveTime;
// #ifdef LOCAL_DEBUG
// 	{
// 		if (placeId < R) {
// 			printf("At %.4lf Arrive %d -> R%d. PICK:", arriveTime, driverId, placeId);
// 		} else {
// 			printf("At %.4lf Arrive %d -> D%d. DROP:", arriveTime, driverId, placeId-R);
// 		}
// 		const int sz = driver.route.size();
// 		for (int i=0; i<sz; ++i) {
// 			if (driver.route[i].placeId == placeId)
// 				printf(" %d", driver.route[i].orderId);
// 			else
// 				break;
// 		}
// 		putchar('\n');
// 	}
// #endif
	//!!!! THIS BLOCK IS IMPORTANT TO UPDATE THE BUCKET.
	vector<treeNode*>::iterator iter = driver.route.begin();
	double driverTid;
	while (iter!=driver.route.end()) {
		node_t node = (*iter)->val.node;
		if (node.placeId != placeId) break;
		if (placeId < R) {
			driverTid = max(arriveTime, orders[node.orderId].tid+waitTime);
			riders[node.orderId].begTime = driverTid;
			taken[node.orderId] = 0;
		} else {
			driverTid = arriveTime;
			riders[node.orderId].endTime = driverTid;
			taken[node.orderId] = 1;
		}
		leaveTime = max(leaveTime, driverTid);
		deleteSubtree(driverId, *iter);
		++iter;
	}
	driver.erase(driver.route.begin(), iter);
	//----
	move.bucket = driver.getBucket();
	moves[driverId].push_back(move);
// #ifdef LOCAL_DEBUG
// 	printf("\tBucket:");
// 	for (int i=0; i<move.bucket.size(); ++i)
// 		printf(" %d", move.bucket[i]);
// 	putchar('\n');
// #endif

	// update the driver: position, time
	driver.pos = nextPos;
	driver.curTime = leaveTime;
}

void updateDriverPosition(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.isEmpty())
		return ;

	if (dcmp(driver.curTime-orderTid) == 0)
		return ;

	position_t src = driver.pos;
	const int placeId = driver.route[0]->val.node.placeId;
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

	// update the driver's position
	driver.pos.x = move.x;
	driver.pos.y = move.y;
	driver.curTime = orderTid;
}


void updateIndex(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.curTime > orderTid) return ;
	
	while (!driver.isEmpty()) {
		const int placeId = driver.route[0]->val.node.placeId;
		const int orderId = driver.route[0]->val.node.orderId;
		position_t& nextPos = (placeId < R) ? rests[placeId] : dists[placeId-R];
		double arriveTime = driver.curTime + Length(driver.pos, nextPos);
		double driverTid = (placeId < R) ? max(arriveTime, orders[orderId].tid+waitTime) : arriveTime;

		if (driverTid > orderTid) {
			break;
		}

		updateMove(driverId);
	}
	//updateDriverPosition(driverId, orderTid);
}

void driverUseCurTime(const int driverId, double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.isEmpty())
		return ;

	if (dcmp(driver.curTime-orderTid) == 0)
		return ;

	position_t src = driver.pos;
	const int placeId = driver.route[0]->val.node.placeId;
	position_t des = (placeId<R) ? rests[placeId] : dists[placeId-R];
	if (src == des)
		return ;

	#ifdef LOCAL_DEBUG
	assert(driver.curTime <= orderTid);
	#endif

	double t = Length(src, des);
	double dx = (des.x - src.x) / t;
	double dy = (des.y - src.y) / t;

	// update the driver's position
	driver.pos.x = src.x + dx * (orderTid - driver.curTime);
	driver.pos.y = src.y + dy * (orderTid - driver.curTime);
	driver.curTime = orderTid;
}

double calcUnfinishedCost(const int driverId, double orderTid) {
	// update the status of driver to now
	driver_t& driver = drivers[driverId];
	position_t preLoc = driver.pos;
	double preTime = driver.curTime;
	driverUseCurTime(driverId, orderTid);

	vector<treeNode*>& route = driver.route;
	const int sz = route.size();

	position_t curLoc = driver.pos, nextLoc;
	double curTime = driver.curTime;
	double ret = -1;

	for (int i=0; i<sz; ++i) {
		const int placeId = route[i]->val.node.placeId;
		const int orderId = route[i]->val.node.orderId;
		nextLoc = (placeId < R) ? rests[orderId] : dists[orderId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, orders[orderId].tid+waitTime);

		// maybe useless even using time as objective function.
		if (placeId < R) {
			riders[orderId].begTime = curTime;
		} else {
			riders[orderId].endTime = curTime;
			ret = max(ret, riders[orderId].endTime-orders[orderId].tid);
		}

		curLoc = nextLoc;
	}
	// restore the status of driver
	driver.pos = preLoc;
	driver.curTime = preTime;

	return ret;
}

vector<int> taxiSearching(const int orderId) {
	double bestCost = inf, cost;
	vector<int> ret(1, -1);

	for (int driverId=0; driverId<M; ++driverId) {
		cost = calcUnfinishedCost(driverId, orders[orderId].tid);
		if (cost < bestCost) {
			bestCost = cost;
			ret[0] = driverId;
		}
	}

	return ret;
}

vector<treeNode*> bestRoute, curRoute;
double bestVal;
int curOrderId, curDriverId, curInitCap;
bool validRoute;
int routeIdx;

bool makeCluster(treeNode* rt, const node_t& a);
bool makeCluster(const node_t& a, const node_t& b);
bool copyNodes(treeNode*& rt, const vector<treeNode*>& src, int cap);
bool insertNode(treeNode*& rt, const vector<node_t>& src, int cap);
void findBestSchedule(treeNode* rt, int dep);

int calcCap(const int driverId) {
	driver_t& driver = drivers[driverId];
	vector<treeNode*>& route = driver.route;
	const int sz = route.size();
	int ret = 0;

	for (int i=0; i<sz; ++i) {
		node_t& node = route[i]->val.node;
		if (node.placeId>=R && taken[node.orderId]==0)
			++ret;
	}

	return ret;
}

void updateRoute() {
	#ifdef LOCAL_DEBUG
	assert(bestRoute.size() == curRoute.size());
	#endif

	driver_t& driver = drivers[curDriverId];
	order_t& order = orders[curOrderId];
	position_t curLoc = driver.pos, nextLoc;
	double val = -1;
	const int sz = curRoute.size();
	double curTime = order.tid;
	int cap = curInitCap;
//	#ifdef LOCAL_DEBUG
//	printf("Route_%d: ", routeIdx);
//	#endif
	
	for (int i=0; i<sz; ++i) {
		const int placeId = curRoute[i]->val.node.placeId;
		const int orderId = curRoute[i]->val.node.orderId;
//		#ifdef LOCAL_DEBUG
//		if (i)
//			printf(" -> ");
//		printf("(%d,%d,%d)", placeId, orderId, curRoute[i]->val.spotId);
//		#endif
		nextLoc = (placeId < R) ? rests[placeId] : dists[placeId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, orders[orderId].tid+waitTime);

		if (placeId < R) {
			riders[orderId].begTime = curTime;
			if (++cap > C) return ;
		} else {
			riders[orderId].endTime = curTime;
			val = max(val, riders[orderId].endTime-orders[orderId].tid);
			--cap;
		}

		curLoc = nextLoc;
	}
//	#ifdef LOCAL_DEBUG
//	putchar('\n');
//	++routeIdx;
//	#endif

	if (val < bestVal) {
		bestVal = val;
		bestRoute = curRoute;
	}
}

void appendTree(treeNode* root) {
	driver_t& driver = drivers[curDriverId];
	order_t& order = orders[curOrderId];
	vector<treeNode*>& route = driver.route;
	int sz = route.size();
	treeNode *p = root, *np;
	treeNode *nd, *nd2;
	
	for (int i=0; i<sz; ++i) {
		np = NULL;
		for (int j=p->size()-1; j>=0; --j) {
			if (p->children[j] == route[i]) {
				#ifdef LOCAL_DEBUG
				assert(np == NULL);
				#endif
				np = p->children[j];
			} else {
				deleteTree(p->children[j]);
			}
		}
		#ifdef LOCAL_DEBUG
		assert(np != NULL);
		#endif
		p = np;
	}
	#ifdef LOCAL_DEBUG
	assert(p->children.empty());
	#endif
	
	node_t pickNode(order.sid, curOrderId);
	node_t deliverNode(order.eid+R, curOrderId);
	int nxtSpotId = (p->val.spotId==0) ? 1 : 0;
	
	nd = new treeNode(hotspot_t(pickNode, nxtSpotId));
	if (makeCluster(pickNode, deliverNode)) {
		nd2 = new treeNode(hotspot_t(deliverNode, nxtSpotId));
	} else {
		nd2 = new treeNode(hotspot_t(deliverNode, nxtSpotId^1));
	}
	nd->children.push_back(nd2);
	p->children.push_back(nd);
}

void scheduling(const int driverId, const int orderId) {
	// update the status of driver to now
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	treeNode* root = kineticRoots[driverId];
	curInitCap = calcCap(driverId);
	
	bestVal = inf;
	curDriverId = driverId;
	curOrderId = orderId;
	validRoute = false;

	bestRoute.clear();
	curRoute.clear();
	bestRoute.resize(driver.route.size()+2, NULL);
	curRoute.resize(bestRoute.size(), NULL);
	vector<node_t> pairs;

	pairs.push_back(node_t(order.sid, orderId));
	pairs.push_back(node_t(order.eid+R, orderId));

	#ifdef LOCAL_DEBUG
	printf("\n\n\norder%d:\n", orderId);
	routeIdx = 0;
	#endif

	if (root->children.empty()) {
		// update the tree
		treeNode *distNode, *restNode;
		if (makeCluster(pairs[0], pairs[1])) {
			distNode = new treeNode(hotspot_t(pairs[1], 0));
			restNode = new treeNode(hotspot_t(pairs[0], 0));
		} else {// one hotspot
			distNode = new treeNode(hotspot_t(pairs[1], 1));
			restNode = new treeNode(hotspot_t(pairs[0], 0));
		}
		restNode->children.push_back(distNode);
		root->children.push_back(restNode);
		findBestSchedule(root, -1);

		return ;
	}
	treeNode* newTreeRoot;
	copyTree(newTreeRoot, root);

	if (!insertNode(newTreeRoot, pairs, curInitCap)) {
		// if still no valid, keep the main route and append two points at the tail
		appendTree(root);
		findBestSchedule(root, -1);
	} else {
		deleteTree(root);
		kineticRoots[driverId] = newTreeRoot;
		findBestSchedule(newTreeRoot, -1);
	}

	// vector<node_t> ret;
	// for (int i=0; i<bestRoute.size(); ++i) {
		// hotspot_t& spot = bestRoute[i]->val;
		// ret.push_back(spot.node);
	// }

	// return ret;
}

void responseDriver(const int driverId, const int orderId) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	driver.curTime = order.tid;
	driver.route = bestRoute;
}

void Kinetic() {
	for (int orderId=0; orderId<N; ++orderId) {
		for (int driverId=0; driverId<M; ++driverId) {
			updateIndex(driverId, orders[orderId].tid);
		}

		vector<int> canDrivers = taxiSearching(orderId);
		if (canDrivers.empty() || canDrivers[0]<0)
			continue;

		int driverId = canDrivers[0];
		updateDriverPosition(driverId, orders[orderId].tid);
		scheduling(driverId, orderId);
		if (bestVal < inf)
			responseDriver(driverId, orderId);
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
	Kinetic();

	printAns();
	
	deleteAll();
}

void readNetwork() {
	vector<double> rests_tmp;
	vector<double> dists_tmp;
	vector<int> orders_tmp;

	readInput(R, D, M, C, N, rests_tmp, dists_tmp, orders_tmp);
	
	initAll();
	for (int i=0,j=0; j<R; i+=2,++j) {
		rests[j] = position_t(rests_tmp[i], rests_tmp[i+1]);
#ifdef LOCAL_DEBUG
		printf("rests[%d]: %.2lf, %.2lf\n", j, rests[j].x, rests[j].y);
#endif
	}
	for (int i=0,j=0; j<D; i+=2,++j) {
		dists[j] = position_t(dists_tmp[i], dists_tmp[i+1]);
#ifdef LOCAL_DEBUG
		printf("dists[%d]: %.2lf, %.2lf\n", j, dists[j].x, dists[j].y);
#endif
	}
	for (int i=0,j=0; j<N; i+=3,++j) {
		orders[j] = order_t(orders_tmp[i], orders_tmp[i+1], orders_tmp[i+2]);
#ifdef LOCAL_DEBUG
		printf("orders[%d]: %d, %d, %d\n", j, orders[j].tid, orders[j].sid, orders[j].eid);
#endif
	}
#ifdef LOCAL_DEBUG
	fflush(stdout);
#endif

	initGrid();
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

bool makeCluster(treeNode *rt, const node_t& node) {
	treeNode* p = rt;
	const int spotId = rt->val.spotId;
	position_t apos = (node.placeId < R) ? rests[node.placeId] : dists[node.placeId-R];
	position_t bpos;
	
	while (p->size()==1 && p->children[0]->val.spotId==spotId) {
		hotspot_t& spot = p->val;
		node_t& node = spot.node;
		bpos = (node.placeId < R) ? rests[node.placeId] : dists[node.placeId-R];
		if (Length(apos, bpos) > theta)
			return false;
		p = p->children[0];
	}
//	printf("%d\n", p->size());
//	fflush(stdout);
	
	hotspot_t& spot = p->val;
	node_t& anode = spot.node;
	bpos = (anode.placeId < R) ? rests[anode.placeId] : dists[anode.placeId-R];
	if (Length(apos, bpos) > theta)
		return false;
	else
		return true;
}

bool makeCluster(const node_t& a, const node_t& b) {
	position_t apos = (a.placeId < R) ? rests[a.placeId] : dists[a.placeId-R];
	position_t bpos = (b.placeId < R) ? rests[b.placeId] : dists[b.placeId-R];
	return Length(apos, bpos) <= theta;
} 

treeNode *endOfCluster(treeNode* rt) {
	const int spotId = rt->val.spotId;
	treeNode* p = rt;
	
	while (p->size()==1 && p->children[0]->val.spotId==spotId)
		p = p->children[0];
	
	return p;
}

treeNode *endOfCluster(treeNode* rt,  int initCap, int& curCap) {
	const int spotId = rt->val.spotId;
	treeNode* p = rt;
	bool flag = false;
	
	curCap = initCap;
	while (p->size()==1 && p->children[0]->val.spotId==spotId) {
		if (p->val.node.placeId < R) {
			if (++curCap > C)
				flag = true;
		} else {
			--curCap;
		}
		p = p->children[0];
	}
	if (p->val.node.placeId < R) {
		if (++curCap > C)
			flag = true;
	} else {
		--curCap;
	}
	if (flag) curCap = INT_MAX;
	
	return p;
}

int calcCup_Cluster(treeNode* rt, int curCap) {
	const int spotId = rt->val.spotId;
	treeNode* p = rt;
	
	while (p->size()==1 && p->children[0]->val.spotId==spotId) {
		if (p->val.node.placeId < R) {
			if (++curCap > C)
				return INT_MAX;
		} else {
			--curCap;
		}
		p = p->children[0];
	}
	if (p->val.node.placeId < R) {
		if (++curCap > C)
			return INT_MAX;
	} else {
		--curCap;
	}
	
	return curCap;
}

int calcCap(treeNode *rt, int curCap) {
	if (rt->val.node.placeId < R) {
		if (++curCap > C)
			return INT_MAX;
	} else {
		--curCap;
	}
	
	return curCap;
}

bool copyNodes(treeNode*& rt, const vector<treeNode*>& src, int curCap) {
	if (src.empty()) return true;

	const int sz = src.size();
	bool flag = false;
	int newCurCap;

	for (int i=0; i<sz; ++i) {
		treeNode* srcNode = src[i];
		newCurCap = calcCap(srcNode, curCap);
		if (newCurCap > C) continue;
		
		treeNode* child = new treeNode(srcNode->val);
		if (copyNodes(child, srcNode->children, newCurCap)) {
			flag = true;
			rt->push_back(child);
		} else {
			delete child;
		}
	}

	if (!flag) {
		deleteTree(rt);
		return false;
	} else {
		return true;	
	}
}

bool copyNodes_inverse(treeNode*& rt, const vector<treeNode*>& src, int curCap) {
	if (src.empty()) return true;

	const int sz = src.size();
	bool flag = false;
	int newCurCap;

	for (int i=0; i<sz; ++i) {
		treeNode* srcNode = src[i];
		newCurCap = calcCap(srcNode, curCap);
		if (newCurCap > C) continue;
		
		treeNode* child = new treeNode(srcNode->val);
		child->val.spotId ^= 1;
		if (copyNodes_inverse(child, srcNode->children, newCurCap)) {
			flag = true;
			rt->push_back(child);
		} else {
			delete child;
		}
	}

	if (!flag) {
		deleteTree(rt);
		return false;
	} else {
		return true;	
	}
}

void findBestSchedule(treeNode* rt, int dep) {
	if (dep >= 0)
		curRoute[dep] = rt;

	const int sz = rt->size();
	for (int i=0; i<sz; ++i) {
		findBestSchedule(rt->children[i], dep+1);
	}
	if (rt->isEmpty())
		updateRoute();
}

bool insertNode(treeNode*& rt, const vector<node_t>& src, int curCap) {
	treeNode *ert = endOfCluster(rt);
	treeNode *nd = NULL;
	treeNode *nrt;
	int newCurCap;
	vector<treeNode*> validNodes;
	bool reachLeaf = rt->empty();
	
	int delta = (src.size() > 1) ? 1 : -1;
	int nxtSpotId = (rt->val.spotId==0) ? 1 : 0;
	
	for (int i=rt->children.size()-1; i>=0; --i) {
		nrt = rt->children[i];
		// pickup makes it at last, drop makes it at first
		newCurCap = (delta==1) ? (calcCup_Cluster(nrt, curCap)+1) : (calcCup_Cluster(nrt, curCap-1));
		if (makeCluster(nrt, src[0])) {
			if (newCurCap <= C)
				validNodes.push_back(nrt);
			// remove hotspot from the kinetic temporialy
			rt->children[i] = *(rt->children.rbegin());
			rt->children.pop_back();
		}
	}
	int fail = 1;
	if (reachLeaf || !rt->empty()) {
		nd = new treeNode(hotspot_t(src[0], nxtSpotId));
		
		// pickup & deliver can form a cluster directly
		if (delta==1 && makeCluster(nd, src[1])) {
			treeNode *nd2 = new treeNode(hotspot_t(src[1], nxtSpotId));
			if (copyNodes_inverse(nd2, rt->children, curCap)) {
				nd->children.push_back(nd2);
				fail = 0;
			} else {
				if (nd2) delete nd2;
			}
			#ifdef LOCAL_DEBUG
			assert(fail == 0);
			#endif
		}
		
		if (fail && copyNodes_inverse(nd, rt->children, curCap+delta)) {
			fail = 0;

			// if deliver hasn't been inserted yet.
			if (delta == 1) {
				vector<node_t> vtmp(1, src[1]);
				if (insertNode(nd, vtmp, curCap+delta)) {
					fail = 0;
				} else {
					fail = 1;
					deleteTree(nd);
				}
			}
		}

		if (fail && nd!=NULL)
			delete nd;
	}

	{// insert the other locations
		for (int i=rt->children.size()-1; i>=0; --i) {
			nrt = rt->children[i];
			ert = endOfCluster(nrt, curCap, newCurCap);
			if (newCurCap<=C && insertNode(ert, src, newCurCap)) {
				/* do nothing */;
			} else {
				deleteTree(nrt);
				rt->children[i] = *(rt->children.rbegin());
				rt->children.pop_back();
			}
		}
	}

	if (fail == 0) {
		#ifdef LOCAL_DEBUG
		assert(nd != NULL);
		#endif
		rt->children.push_back(nd);
	}

	// insert validNodes, remove at first
	if (!validNodes.empty()) {
		if (delta == 1) {
			int sz = validNodes.size();
			bool pairCluster = makeCluster(src[0], src[1]);
			vector<node_t> vtmp(1, src[1]);
			
			for (int i=0; i<sz; ++i) {
				nrt = validNodes[i];
				ert = endOfCluster(nrt, curCap, newCurCap);
				if (++newCurCap > C) {
					deleteTree(nrt);
					continue;
				}
				
				if (pairCluster && makeCluster(nrt, src[1])) {
					treeNode* nd2 = new treeNode(hotspot_t(src[1], nxtSpotId));
					treeNode* nd = new treeNode(hotspot_t(src[0], nxtSpotId));
					nd2->children = ert->children;
					nd->children.push_back(nd2);
					ert->children.clear();
					ert->children.push_back(nd);
					rt->children.push_back(nrt);
				} else if (insertNode(ert, vtmp, newCurCap)) {
					treeNode* nd = new treeNode(hotspot_t(src[0], nxtSpotId));
					nd->children = ert->children;
					ert->children.clear();
					ert->children.push_back(nd);
					rt->children.push_back(nrt);
				} else {
					deleteTree(nrt);
				}
			}
		} else {
			int sz = validNodes.size();

			for (int i=0; i<sz; ++i) {
				treeNode* nd = new treeNode(hotspot_t(src[0], nxtSpotId));
				nd->children.push_back(validNodes[i]);
				rt->children.push_back(nd);
			}
		}
	}
	// #ifdef LOCAL_DEBUG
	// printf("rt=(%d,%d), size=%d\n", rt->val.node.placeId, rt->val.node.orderId, rt->size());
	// fflush(stdout);
	// #endif
	
	if (rt->isEmpty()) {
		deleteTree(rt);
		rt = NULL;
		return false;
	} else {
		return true;
	}	
}
