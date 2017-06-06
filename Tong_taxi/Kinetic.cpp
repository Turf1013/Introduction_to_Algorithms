/**
	\author: 	Trasier
	\date: 		2017.6.4
	\source: 	VLDB14 Large Scale Real-time Ridesharing with Service Guarantee on Road Networks
	\note: 		Kinetic Tree
			The main difference between Kinetic-Tree and Branch-and-Bound is
			1) there are always multiple routes in the tree, while driver still chooses the best route;
			2) As soon as the driver reaches some key locations, the tree needs to be pruned since some routes are out of date.
			In summary, both `taxiScheduling` and `updateMove` need to be coded.
	\readme:	1) During the process of insertNode, supposed that there is no valid route at last, 
					the original route is still deleted due to `If insert failed, delete(l,c)`.
					But driver should stick to his original route.
					My replacement is rebuild a whole tree, if there is some valid route, then use the new one to replace the old.
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"
#include "treeNode.h"

#define LOCAL_DEBUG

const double waitTime = 0.0;
int graphLength, graphWidth;
int gridLength, gridWidth;
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
};

typedef treeNode_t<node_t> treeNode;

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

	void clear() {
		route.clear();
	}

	vector<int> getBucket() {
		const int sz = route.size();
		vector<int> ret;

		for (int i=0; i<sz; ++i) {
			if (route[i].placeId >= R)
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
vector<position_t> vRest, vDist;
vector<order_t> vOrder;
vector<rider_t> riders;
vector<driver_t> drivers;
vector<treeNode*> kineticRoots;
vector<vector<move_t> > moves;
vector<vector<double> > R2D, R2R, D2D;


inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt((pa.x-pb.y)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
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
	kineticRoots.clear();
	for (int i=0; i<M; ++i) {
		drivers.push_back(driver_t());
		treeNode* rt = new treeNode(node_t(-1, -1));
		kineticRoots.push_back(rt);
	}
}

void initMove() {
	moves.clear();
	for (int i=0; i<M; ++i) {
		moves.push_back(vector<move_t>());
	}
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
}

void init() {
	initDriver();
	initRider();
	initMove();
	initGrid();
}

bool checkConstraint(double curTime, const node_t& nd) {
	const int placeId = nd.placeId;
	const int orderId = nd.orderId;

	double l, r;

	if (placeId < R) {// pickup 
		l = vOrder[orderId].tid;
		r = l + waitTime;
	} else {// dropoff
		l = vOrder[orderId].tid;
		r = inf;
	}

	if (l<=curTime && curTime<=r)
		return true;
	else
		return false;
}

void updateMove(const int driverId) {
	driver_t& driver = drivers[driverId];
	if (driver.empty()) return ;

	node_t node = driver.route[0];
	const int placeId = driver.route[0].placeId;
	const int orderId = driver.route[0].orderId;
	position_t& nextPos = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
	double arriveTime = driver.curTime + Length(driver.pos, nextPos);
	double driverTid = (placeId < R) ? max(arriveTime, vOrder[orderId].tid+waitTime) : arriveTime;

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
	driver.pop_front();
	move.bucket = driver.getBucket();
	moves[driverId].push_back(move);

	// update the driver: position, time
	driver.pos = nextPos;
	driver.curTime = driverTid;

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

void updateDriverPosition(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.isEmpty())
		return ;

	if (dcmp(driver.curTime-orderTid) == 0)
		return ;

	position_t src = driver.pos;
	const int placeId = driver.route[0].placeId;
	position_t des = (placeId<R) ? vRest[placeId] : vDist[placeId-R];
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
		position_t& nextPos = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		double arriveTime = driver.curTime + Length(driver.pos, nextPos);
		double driverTid = (placeId < R) ? max(arriveTime, vOrder[orderId].tid+waitTime) : arriveTime;

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
		nextLoc = (placeId < R) ? vRest[orderId] : vDist[orderId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, vOrder[orderId].tid+waitTime);

		// maybe useless even using time as objective function.
		if (placeId < R) {
			riders[orderId].begTime = curTime;
		} else {
			riders[orderId].endTime = curTime;
			ret = max(ret, riders[orderId].endTime-vOrder[orderId].tid);
		}

		curLoc = nextLoc;
	}

	return ret;
}

vector<int> taxiSearching(const int orderId) {
	double bestCost = inf, cost;
	vector<int> ret(1, -1);

	for (int driverId=0; driverId<N; ++driverId) {
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
	order_t& order = vOrder[orderId];
	vector<node_t> route;

	route.push_back(node_t(order.sid, orderId));
	route.push_back(node_t(order.eid+R, orderId));

	position_t curLoc = driver.pos, nextLoc;
	double curTime = order.tid;
	const int sz = route.size();

	for (int i=0; i<sz; ++i) {
		const int placeId = route[i].placeId;
		const int orderId = route[i].orderId;
		nextLoc = (placeId<R) ? vRest[placeId] : vDist[placeId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, (double)vOrder[orderId].tid);

		if (!checkConstraint(curTime, route[i]))
			return vector<node_t>();

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
bool feasible(treeNode* rt, const node_t& node, double detour);
void findBestSchedule(treeNode* rt, int dep);

void updateRoute() {
	#ifdef LOCAL_DEBUG
	assert(bestRoute.size() == curRoute.size());
	#endif

	driver_t& driver = drivers[curDriverId];
	order_t& order = vOrder[curOrderId];
	position_t curLoc = driver.pos, nextLoc;
	double val = -1;
	const int sz = curRoute.size();
	double curTime = order.tid;
	int cap = 0;
	
	for (int i=0; i<sz; ++i) {
		const int placeId = curRoute[i]->val.placeId;
		const int orderId = curRoute[i]->val.orderId;
		nextLoc = (placeId < R) ? vRest[placeId] : vDist[placeId-R];
		curTime += Length(curLoc, nextLoc);
		if (placeId < R)
			curTime = max(curTime, vOrder[orderId].tid+waitTime);

		if (placeId < R) {
			riders[orderId].begTime = curTime;
			if (++cap > C) return ;
		} else {
			riders[orderId].endTime = curTime;
			val = max(val, riders[orderId].endTime-vOrder[orderId].tid);
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
	order_t& order = vOrder[orderId];
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

	if (root == NULL) {
		// if there is no valid route for the driver, then we can just assign the task immediately.
		return directAssign(driverId, orderId);;
	}
	treeNode* newTreeRoot;
	copyTree(newTreeRoot, root);
	// add fake head 
	// treeNode* fakeHead;
	// fakeHead = new treeNode(node_t(-1, -1));
	// fakeHead->push_back(newTreeRoot);
	vector<node_t> pairs;

	pairs.push_back(node_t(order.sid, orderId));
	pairs.push_back(node_t(order.eid+R, orderId));
	insertNode(newTreeRoot, pairs, order.tid, 0);
	if (newTreeRoot == NULL) {
		return vector<node_t>();
	} else {
		deleteTree(root);
		kineticRoots[driverId] = newTreeRoot;
		findBestSchedule(newTreeRoot, -1);
	}

	vector<node_t> ret;
	for (int i=0; i<bestRoute.size(); ++i)
		ret.push_back(bestRoute[i]->val);

	return ret;
}

void responseDriver(const int driverId, const int orderId, vector<node_t>& newRoute) {
	driver_t& driver = drivers[driverId];
	//order_t& order = vOrder[orderId];
	driver.route = newRoute;
}

void Kinetic() {
	for (int orderId=0; orderId<M; ++orderId) {
		for (int driverId=0; driverId<N; ++driverId) {
			updateIndex(driverId, vOrder[orderId].tid);
		}

		vector<int> canDrivers = taxiSearching(orderId);
		if (canDrivers.empty() || canDrivers[0]<0)
			continue;

		int driverId = canDrivers[0];
		vector<node_t> newRoute = scheduling(driverId, orderId);
		if (!newRoute.empty())
			responseDriver(driverId, orderId, newRoute);
	}

	for (int driverId=0; driverId<N; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			updateMove(driverId);
	}
}

void printAns() {
	for (int driverId=0; driverId<N; ++driverId) {
		const int sz = moves[driverId].size();
		printf("%d %d\n", driverId, sz);
		dumpOutput(moves[driverId]);
	}

	double ans = -1;
	for (int orderId=0; orderId<M; ++orderId)
		ans = max(ans, riders[orderId].endTime-vOrder[orderId].tid);

	printf("%.10lf\n", ans);
}

void solve() {
	init();

	Kinetic();

	printAns();
}

void readNetwork() {
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


double calcTime(const treeNode* rt, const node_t& node, double curTime) {
	#ifdef LOCAL_DEBUG
	assert(rt != NULL);
	#endif

	const node_t& fnode = rt->val;
	position_t curLoc, nextLoc;

	if (fnode.orderId < 0) {
		curLoc = drivers[curDriverId].pos;
	} else {
		curLoc = (fnode.placeId<R) ? vRest[fnode.placeId] : vDist[fnode.placeId-R];
	}
	nextLoc = (node.placeId<R) ? vRest[node.placeId] : vDist[node.placeId-R];

	double newCurTime = curTime + Length(curLoc, nextLoc);
	if (node.placeId < R)
		newCurTime = max(newCurTime, vOrder[node.orderId].tid+waitTime);

	return newCurTime;
}

bool insertNode(treeNode*& rt, const vector<node_t>& src, double curTime, int dep) {
	if (feasible(rt, src[0], curTime)) {
		int fail = 0;
		treeNode* nd = new treeNode(src[0]);
		double newCurTime;
		{// insert the children of rt into nd
			newCurTime = calcTime(rt, nd->val, curTime);
			if (!copyNodes(nd, rt->children, newCurTime, dep+1))
				fail = 1;
		}
		{// insert the dropoff into the subtree of nd
			if (fail==0 && src.size()>1) {
				vector<node_t> vtmp(1, src[1]);
				if (!insertNode(nd, vtmp, newCurTime, dep+1))
					fail = 1;
			}
			// if (fail == 0)
			// 	validRoute = true;
		}

		bool flag = false;
		{// insert the (pickup,dropoff) into the subtree of rt
			const int sz = rt->size();
			for (int i=sz-1; i>=0; --i) {
				treeNode* nrt = rt->children[i];
				newCurTime = calcTime(rt, nrt->val, curTime);
				if (insertNode(nrt, src, newCurTime, dep+1)) {
					flag = true;
				} else {
					deleteTree(nrt);
					rt->children[i] = *(rt->children.rbegin());
					rt->children.pop_back();
				}
			}
			// if (flag)
			// 	validRoute = true;
		}

		#ifdef LOCAL_DEBUG
		assert(flag || rt->isEmpty());
		#endif

		if (fail == 0) {
			rt->children.push_back(nd);
		}
		if (rt->isEmpty()) {
			deleteTree(rt);
			rt = NULL;
			return false;
		} else {
			return true;
		}
	}

	return false;
}

bool copyNodes(treeNode*& rt, const vector<treeNode*>& src, double curTime, int dep) {
	if (src.empty()) return true;

	const int sz = src.size();
	bool flag = false;

	for (int i=0; i<sz; ++i) {
		treeNode* srcNode = src[i];
		if (!feasible(rt, srcNode->val, curTime))
			continue;

		treeNode *child = new treeNode(srcNode->val);
		double newCurTime = calcTime(rt, srcNode->val, curTime);
		if (copyNodes(child, srcNode->children, newCurTime, dep+1)) {
			flag = true;
			rt->push_back(child);
		}
	}

	if (!flag) {
		deleteTree(rt);
		return false;
	} else {
		return true;	
	}
}

bool feasible(treeNode* rt, const node_t& node, double curTime) {
	double newCurTime = calcTime(rt, node, curTime);

	return checkConstraint(newCurTime, node);
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