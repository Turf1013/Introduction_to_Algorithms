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
int theta = 28;
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

struct hotspot_t {
	int spotId;
	//int delta;
	vector<node_t> nodes;
	
	hotspot_t(int spotId = -1) {
		this->spotId = spotId;
	//	delta = 0;
	}
	hotspot_t(const node_t& a, int spotId = -1) {
	//	delta = 0;
		this->spotId = spotId;
		nodes.push_back(a);
	}
	
	void push_back(const node_t& a) {
		nodes.push_back(a);
	}
	
	bool empty() const {
		return nodes.empty();
	}
	
	size_t size() const {
		return nodes.size();
	}
};

typedef treeNode_t<hotspot_t> treeNode;

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
	hotspot_t hotspot;
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

void deleteSubtree(const int driverId, const node_t& node) {
	// update the kinetic tree
	treeNode *rt = kineticRoots[driverId], *nrt = NULL;
	const int childSz = rt->size();

	for (int i=0; i<childSz; ++i) {
		if (rt->children[i]->val == node) {
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
	
	const int placeId = driver.route[0].placeId;
	const int orderId = driver.route[0].orderId;
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
	vector<node_t>::iterator iter = driver.route.begin();
	double driverTid;
	while (iter!=driver.route.end() && iter->placeId==placeId) {
		if (placeId < R) {
			driverTid = max(arriveTime, orders[iter->orderId].tid+waitTime);
			riders[iter->orderId].begTime = driverTid;
			taken[iter->orderId] = 0;
		} else {
			driverTid = arriveTime;
			riders[iter->orderId].endTime = driverTid;
			taken[iter->orderId] = 1;
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

	return ret;
}

vector<int> taxiSearching(const int orderId) {
	double bestCost = inf, cost;
	vector<int> ret(1, -1);

	for (int driverId=0; driverId<M; ++driverId) {
		cost = calcUnfinishedCost(driverId);
		if (cost < bestCost) {
			bestCost = cost;
			ret[0] = driverId;
		}
	}

	return ret;
}

vector<node_t> directAssign(const int driverId, const int orderId) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t> route;

	route.push_back(node_t(order.sid, orderId));
	route.push_back(node_t(order.eid+R, orderId));

	position_t curLoc = driver.pos, nextLoc;
	double curTime = order.tid;
	const int sz = route.size();

	for (int i=0; i<sz; ++i) {
		const int placeId = route[i].placeId;
		const int orderId = route[i].orderId;
		nextLoc = (placeId<R) ? rests[placeId] : dists[placeId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, orders[orderId].tid+waitTime);
		curLoc = nextLoc;
	}

	return route;
}

vector<treeNode*> bestRoute, curRoute;
double bestVal;
int curOrderId, curDriverId;
bool validRoute;

bool copyNodes(treeNode*& rt, const vector<treeNode*>& src, double detour, int dep);
bool insertNode(treeNode*& rt, const vector<node_t>& src, double detour, int dep);
void findBestSchedule(treeNode* rt, int dep);

int calcCap(const int driverId) {
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
	int cap = calcCap(curDriverId);
	
	for (int i=0; i<sz; ++i) {
		const int placeId = curRoute[i]->val.placeId;
		const int orderId = curRoute[i]->val.orderId;
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

	if (val < bestVal) {
		bestVal = val;
		bestRoute = curRoute;
	}
}

vector<node_t> scheduling(const int driverId, const int orderId) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	vector<node_t>& route = driver.route;
	treeNode* root = kineticRoots[driverId];
	
	bestVal = inf;
	curDriverId = driverId;
	curOrderId = orderId;
	validRoute = false;

	bestRoute.clear();
	curRoute.clear();
	bestRoute.resize(route.size()+2, NULL);
	curRoute.resize(route.size()+2, NULL);

	if (root->children.empty()) {
		// if there is no valid route for the driver, then we can just assign the task immediately.
		vector<node_t> ret = directAssign(driverId, orderId);
		// update the tree
		if (!ret.empty()) {
#ifdef LOCAL_DEBUG
		assert(ret.size() == 2);
#endif		
			position_t pickLoc = rests[order.sid], dropLoc = dists[order.eid];
			if (Length(pickLoc, dropLoc) > theta) {
				treeNode *distNode = new treeNode(hotspot_t(ret[1]), 1);
				treeNode *restNode = new treeNode(hotspot_t(ret[0]), 0);
				restNode->push_back(distNode);
				root->push_back(restNode);
			} else {// one hotspot
				hotspot_t spot(0);
				spot.push_back(ret[0]);
				spot.push_back(ret[1]);
				treeNode *node = new treeNode(spot);
				root->push_back(node);
			}
			
		}
		return ret;
	}
	treeNode* newTreeRoot;
	copyTree(newTreeRoot, root);
	vector<node_t> pairs;

	pairs.push_back(node_t(order.sid, orderId));
	pairs.push_back(node_t(order.eid+R, orderId));
	insertNode_hotspot(newTreeRoot, pairs, order.tid);
	if (newTreeRoot == NULL) {
		return vector<node_t>();
	} else {
		deleteTree(root);
		kineticRoots[driverId] = newTreeRoot;
		findBestSchedule(newTreeRoot, -1);
	}

	vector<node_t> ret;
	for (int i=0; i<bestRoute.size(); ++i) {
		hotspot_t& spot = bestRoute[i]->val;
		const int sz = spot.size();
		for (int j=0; j<sz; ++j)
			ret.push_back(spot.nodes[j]);
	}

	return ret;
}

void responseDriver(const int driverId, const int orderId, vector<node_t>& newRoute) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	driver.curTime = order.tid;
	driver.route = newRoute;
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
		vector<node_t> newRoute = scheduling(driverId, orderId);
		if (!newRoute.empty())
			responseDriver(driverId, orderId, newRoute);
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
	}
	for (int i=0,j=0; j<D; i+=2,++j) {
		dists[j] = position_t(dists_tmp[i], dists_tmp[i+1]);
	}
	for (int i=0,j=0; j<N; i+=3,++j) {
		orders[j] = order_t(orders_tmp[i], orders_tmp[i+1], orders_tmp[i+2]);
	}
	
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

int calcCap(treeNode *rt, int curCap) {
	hotspot_t& spot = rt->val;
	vector<node_t>& nodes = spot.nodes;
	const int sz = nodes.size();
	
	for (int i=0; i<sz; ++i) {
		if (nodes[i].placeId < R)
			++curCap;
		else
			--curCap;
		if (curCap > C) return INT_MAX;
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
	treeNode *frt = rt, *trt = rt;
	treeNode *nd = NULL;
	treeNode *nrt;
	int newCurCap;
	vector<treeNode*> validNodes;
	
	int delta = (src.size() > 1) ? -1 : 1;
	
	for (i=rt->children.size()-1; i>=0; --i) {
		nrt = rt->children[i];
		newCurCap = (delta==1) ? (calcCup(nrt, curCap)+1) : (calcCup(nrt, curCap-1));
		if (newCurCap<=C && findCluster(nrt, src[0])) {
			validNodes.push_back(nrt);
			// remove hotspot from the kinetic temporialy
			rt->children[i] = *(rt->children.rbegin());
			rt->children.pop_back();
		}
	}
	int fail = 1;
	if (!rt->children.empty() && curCap+delta<=C) {
		int spotId = rt->children[0]->spotId ^ 1;
		nd = new treeNode(hotspot_t(src[0]), spotId);
		if (copyNodes(nd, rt->children, curCap+delta)) {
			fail = 0;
		} else {
			deleteTree(nd);
		}
	}
	if (fail==0 && delta==1) {
		vector<node_t> vtmp(1, src[1]);
		if (!insertNode(nd, vtmp, curCap+1)) {
			fail = 1;
			deleteTree(nd);
		}
	}
	{// insert the other locations
		for (int i=rt->children.size()-1; i>=0; --i) {
			treeNode* nrt = rt->children[i];
			newCurCap = calcCup(nrt, curCap);
			if (newCurCap<=C && insertNode(nrt, src, newCurCap)) {
				/* do nothing */;
			} else {
				deleteTree(nrt);
				rt->children[i] = *(rt->children.rbegin());
				rt->children.pop_back();
			}
		}
	}
	if (fail == 0) {
		rt->children.push_back(nd);
	}
	// insert validNodes, remove at first
	if (!validNodes.empty()) {
		if (delta == 1) {
			int sz = validNodes.size();
			for (int i=0; i<sz; ++i) {
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! not finished.	
			rt->children.insert(rt->children.end(), validNodes.begin(), validNodes.end());
			}
		} else {
			treeNode* nd = new treeNode(hotspot_t(src[0]), validNodes[0]->spotId);
			rt->children.push_back(nd);
			nd->children = validNodes;
		}
	}
	
	if (rt->isEmpty()) {
		deleteTree(rt);
		rt = NULL;
		return false;
	} else {
		return true;
	}	
}
