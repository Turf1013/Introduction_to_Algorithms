#include <vector>
#include <algorithm>
#include <stdio.h>
#include "li_treeNode.h"
#include "li_output.h"
using namespace std;
const double inf = 1e20;
int R, D, M, C, N;
double waittime = 2000;
double detour = 2000;	//��·ϵ�� 
double theta = 200;	// hotspot ��ϵ�� 
const double eps = 1e-6;
int taken=0;
int dcmp(double x) {
	if (fabs(x) < eps)
		return 0;
	return x<0 ? -1 : 1;
}

struct position_t {
	double x, y;

	position_t(double x = 0., double y = 0.) :
		x(x), y(y) {}
};

position_t *rests;
position_t *dists;

struct order_t {
	int tid, sid, eid;
	double takentime;		//�ӵ�ʱ�� 
	double droptime;

	order_t(int tid = 0, int sid = 0, int eid = 0) :
		tid(tid), sid(sid), eid(eid) {
		takentime = droptime = -1;
	}
};


// ������һ��Ҫ��¼ x,y ���� 
struct node_t {
	int placeId, orderId;
	int cap;
	int spotId;
	double slackTime;
	double time;
	double x;
	double y;

	node_t(int placeId_t = -1, int orderId_t = 0, int cap_t = 0) {
		placeId = placeId_t;
		orderId = orderId_t;
		cap = cap_t;
		position_t temp = placeId<R ? rests[placeId] : dists[placeId - R];
		x = temp.x;
		y = temp.y;
		spotId = 0;
		slackTime = inf;
		time = 0;
	}

	bool operator==(const node_t& oth) const {
		return placeId == oth.placeId && orderId == oth.orderId;
	}

};

typedef treeNode_t<node_t> treeNode;
struct driver_t {
	position_t pos;
	double curTime;
	vector<treeNode*> route;
	int cap;
	double run;

	driver_t(double x = 0., double y = 0.) {
		pos.x = x;
		pos.y = y;
		this->curTime = curTime;
		cap = 0;
		run = 0;
	}

	bool isEmpty() {
		return route.empty();
	}

	bool empty() {
		return this->isEmpty();
	}

	void push_back(treeNode* p) {
		route.push_back(p);
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
			node_t& node = route[i]->val;
			if (node.placeId < R)				// ��δ�ӵ��� 
				unpicked.insert(node.orderId);
			if (node.placeId>=R && unpicked.count(node.orderId)==0)			// �ѽӵ�����δ�ʹ��  ֻ����һ���ֲ��ڳ����� 
				ret.push_back(node.orderId);
		}

		return ret;
	}	

};


//	void printTree(treeNode* root, int level);
order_t *orders;
driver_t *drivers;
treeNode** kineticRoots;
vector<vector<move_t> > moves;

struct randomInsert {
	treeNode* rt;
	double depth;
	randomInsert(treeNode*  x = NULL, double y = 0.) {
		rt = x;
		depth = y;
	}
};



inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt((pa.x - pb.x)*(pa.x - pb.x) + (pa.y - pb.y)*(pa.y - pb.y));
}

inline double Length(const node_t& nodea, const node_t& nodeb) {
	return sqrt((nodea.x - nodeb.x)*(nodea.x - nodeb.x) + (nodea.y - nodeb.y)*(nodea.y - nodeb.y));
}

inline double countMax(vector<double> &list) {
	double max = -1;
	for (int i = 0; i<list.size(); i++) {
		if (list[i]>max) max = list[i];
	}
	return max;
}


//  ��������һ�Ҫϸϸ��һ�� 
bool makeCluster(treeNode *rt, const node_t& node, vector<randomInsert>& list, double depth) {
	treeNode* p = rt;
	const int spotId = rt->val.spotId;
	position_t apos = (node.placeId < R) ? rests[node.placeId] : dists[node.placeId - R];
	position_t bpos = (p->val.placeId<R) ? rests[p->val.placeId] : dists[p->val.placeId - R];
	if (Length(apos, bpos) >= theta) return false;
//	if(p->val.cap>C) return false; 
	struct randomInsert temp;
	temp.depth = depth;
	temp.rt = rt;
	list.push_back(temp);
	for (int i = 0; i<p->size(); i++) {
		if (p->children[i]->val.spotId == spotId) {
			return makeCluster(p->children[i], node, list, depth + Length(p->val, p->children[i]->val));
		}
	}
	return true;
}

bool makeCluster(const node_t& a, const node_t& b) {
	position_t apos = (a.placeId < R) ? rests[a.placeId] : dists[a.placeId - R];
	position_t bpos = (b.placeId < R) ? rests[b.placeId] : dists[b.placeId - R];
	return Length(apos, bpos) < theta;
}


void recordMove(const int driverId,int orderTid) {
	driver_t& driver = drivers[driverId];
	// �ſ�ʼ����ֹͣ������һ��ʱ�� 
	if (driver.isEmpty()){		
		if (!moves[driverId].empty())
			moves[driverId].back().leave=orderTid;
		return ;
	} 
	position_t src = driver.pos;
	move_t move;
	move.x = src.x;
	move.y = src.y;
	move.arrive = move.leave = orderTid;
	if (!moves[driverId].empty())
		move.bucket = moves[driverId].rbegin()->bucket;
	moves[driverId].push_back(move);

}


void initGrid() {
	srand((unsigned)time(NULL));
	for (int i = 0; i<M; ++i) {
	int placeId = rand() % R;			// Ϊ��debug������������ʱ���ٸĻ��� 
	//	int placeId=orders[i].sid;
		drivers[i].pos = rests[placeId];
		drivers[i].curTime = 1.0;
		drivers[i].cap = 0;
		move_t move;

		move.x = drivers[i].pos.x;
		move.y = drivers[i].pos.y;
		move.arrive = move.leave = 0;
		moves[i].push_back(move);		
	}
	
}

void initAll() {
	orders = new order_t[N];
	rests = new position_t[R];
	dists = new position_t[D];
	drivers = new driver_t[M];
	kineticRoots = new treeNode*[M];
	node_t node(-1, -1, -1);  //��ʾ��ǰ��� 
	for (int i = 0; i<M; ++i) {
		kineticRoots[i] = new treeNode(node);
	}
	moves.clear();
	for (int i=0; i<M; ++i) {
		moves.push_back(vector<move_t>());
	}

}

void readInput(vector<double>& vRest, vector<double>& vDist, vector<int>& vOrder) {
	vRest.clear();
	vDist.clear();
	vOrder.clear();
	scanf("%d %d %d %d %d", &R, &D, &M, &C, &N);

	double x, y;
	for (int i = 0; i<R; ++i) {
		scanf("%lf %lf", &x, &y);
		vRest.push_back(x);
		vRest.push_back(y);
	}

	for (int i = 0; i<D; ++i) {
		scanf("%lf %lf", &x, &y);
		vDist.push_back(x);
		vDist.push_back(y);
	}

	int tid, rid, did;
	for (int i = 0; i<N; ++i) {
		scanf("%d %d %d", &tid, &rid, &did);
		--rid; --did;
		vOrder.push_back(tid);
		vOrder.push_back(rid);
		vOrder.push_back(did);
	}
}


void inputHandler() {
	vector<double> rests_tmp;
	vector<double> dists_tmp;
	vector<int> orders_tmp;
	readInput(rests_tmp, dists_tmp, orders_tmp);

	initAll();

	for (int i = 0, j = 0; j<R; i += 2, ++j) {
		rests[j] = position_t(rests_tmp[i], rests_tmp[i + 1]);
	}
	for (int i = 0, j = 0; j<D; i += 2, ++j) {
		dists[j] = position_t(dists_tmp[i], dists_tmp[i + 1]);
	}
	for (int i = 0, j = 0; j<N; i += 3, ++j) {
		orders[j] = order_t(orders_tmp[i], orders_tmp[i + 1], orders_tmp[i + 2]);
	}

	initGrid();

}



void deleteSubtree(const int driverId, const treeNode* node) {
	treeNode *rt = kineticRoots[driverId], *nrt = NULL;
	const int childSz = rt->size();
	for (int i = 0; i < childSz; ++i) {
		if (rt->children[i]== node) {	// ����Ӧ��ͨ���Ƚϵķ�ʽ   ����ط��Ƚ�ָ��Ϳ��ܳ��� 
			nrt = rt->children[i];
		}
		else {
			deleteTree(rt->children[i]);
		}
	}
	rt->children = nrt->children;
	if (nrt) {
		delete nrt;
	}
}


// �����һ����������Ƚϴ� 
void updateMove(const int driverId) {
	driver_t& driver = drivers[driverId];
	if (driver.empty()) return;
	const int placeId = driver.route[0]->val.placeId;
	position_t& nextPos = (placeId < R) ? rests[placeId] : dists[placeId - R];
	double cost = Length(driver.pos, nextPos);
	double arriveTime = driver.curTime + cost;


	move_t move;
	move.x = nextPos.x;
	move.y = nextPos.y;
	move.arrive = arriveTime;
	double& leaveTime = move.leave;
	leaveTime = arriveTime;					// ���赽�����뿪   �����ǳ�����deleteSubTree 
	
	vector<treeNode*>::iterator iter = driver.route.begin();

	while (iter != driver.route.end()) {
		node_t node = (*iter)->val;
		if (node.placeId != placeId) break;
		if (placeId < R) {
			driver.cap++;
			orders[node.orderId].takentime = arriveTime;
		}
		else {
			driver.cap--;
		}
		deleteSubtree(driverId, *iter);
		++iter;
	}
	driver.run += cost;
	driver.erase(driver.route.begin(), iter);
	
	move.bucket = driver.getBucket();
	moves[driverId].push_back(move);
		
	driver.pos = nextPos;
	driver.curTime = arriveTime;
}

void updateIndex(const int driverId, const double orderTid) {
	driver_t& driver = drivers[driverId];
	if (driver.curTime > orderTid) return;

	if (driver.isEmpty()) {
		driver.curTime = orderTid;
	}

	while (!driver.isEmpty()) {
//		printf("not empty\n");
		const int placeId = driver.route[0]->val.placeId;
		const int orderId = driver.route[0]->val.orderId;
		position_t& nextPos = (placeId < R) ? rests[placeId] : dists[placeId - R];
//		printf("herehahah\n");
		double arriveTime = driver.curTime + Length(driver.pos, nextPos);
		if (arriveTime > orderTid) {		// ע����һ�仰 
			position_t des = (placeId < R) ? rests[placeId] : dists[placeId - R];
			position_t src = driver.pos;

			double t = Length(src, des);
			double dx = (des.x - src.x) / t;
			double dy = (des.y - src.y) / t;

			// update the driver's position
			driver.pos.x = src.x + dx * (orderTid - driver.curTime);
			driver.pos.y = src.y + dy * (orderTid - driver.curTime);
			driver.run += orderTid - driver.curTime;
			driver.curTime = orderTid;
			
			move_t move;
			move.x = driver.pos.x;
			move.y = driver.pos.y;
			move.arrive = move.leave=orderTid;			
			move.bucket = driver.getBucket();
			moves[driverId].push_back(move);			
			
			break;
		}
		//����updateMove�򲻴��ڳ����õ�������� 
//		printf("update move\n");
		updateMove(driverId);			//���ܵ���Ľڵ㶼����һ��
		updateIndex(driverId,orderTid); 
	}

}

vector<treeNode*> bestRoute, curRoute;
double bestVal;
int curOrderId, curDriverId, curInitCap;
bool validRoute;
int routeIdx;


void printRoute(vector<treeNode*> route) {
	printf("printRoute\n");
	if (route.size() == 0) printf("null\n");
	for (int i = 0; i < route.size(); i++){
		printf("placeId:  %d  time:  %lf", route[i]->val.placeId,route[i]->val.time);
	}
	printf("\n");
}

// ��Ѱ����������ʻʱ����С�ķ��� 
void updateRoute() {

	driver_t& driver = drivers[curDriverId];		// �ҳ�������������������û�и���ֵ
	order_t& order = orders[curOrderId];
	position_t curLoc = driver.pos, nextLoc;
	double val;
	const int sz = curRoute.size();
	double curTime = 0;

	for (int i = 0; i<sz; ++i) {
		const int placeId = curRoute[i]->val.placeId;
		const int orderId = curRoute[i]->val.orderId;

		nextLoc = (placeId < R) ? rests[placeId] : dists[placeId - R];
		curTime += Length(curLoc, nextLoc);
		curLoc = nextLoc;
	}
	val = curTime;
	if (val < bestVal) {
		bestVal = val;
		bestRoute = curRoute;
	}
//	printRoute(bestRoute);
}

// �����������Ѱ�������ʻ·�� 
// �ɹ�������·������ 
// ����һ��ʵ���˼�֦ 
int findBestSchedule(treeNode* rt, int dep, int size) {
	if (dep >= 0)
		curRoute[dep] = rt;

	
	const int sz = rt->size();
	for (int i = sz - 1; i >= 0; --i) {
		if (findBestSchedule(rt->children[i], dep + 1, size) == -1) {
			deleteTree(rt->children[i]);
			rt->children.erase(rt->children.begin() + i);
		}
	}
	if (rt->isEmpty()) {
		if (dep != (size - 1)) {
			curRoute[dep] = NULL;
			return -1;
		}
		updateRoute();
	}
	if (dep >= 0)
		curRoute[dep] = NULL;
	return 0;
}


inline double calExtraCost(node_t origin1, node_t insert, node_t origin2) {
	return Length(origin1, insert) + Length(origin2, insert) - Length(origin1, origin2);
}

bool fitWaitTime(node_t preNode, node_t insertNode, double depth, double & slackTime) {
	double cost = Length(preNode, insertNode) + depth;
	if (cost<waittime) {
		slackTime = waittime - cost;
		return true;
	}
	return false;
}

bool fitDetour(node_t preNode, node_t dropNode, double depth, double costLimit, double & slack) {
	double cost = Length(preNode, dropNode) + depth;
	slack = costLimit - cost;
	return cost<costLimit;
}

// ���ýڵ�slackTime ������ ������û�б�Ҫ���������  answer: ����������� 

// ����drop 
int feasible(node_t preNode, node_t insertNode, node_t nextNode, int depth, double &cost, double costLimit, double &slack) {
	if (!fitDetour(preNode, insertNode, depth, costLimit, slack)) return 1;
	if (preNode.cap>C) return 1;
	cost = calExtraCost(preNode, insertNode, nextNode);
	double slackTime = nextNode.slackTime;
	if (cost>slackTime) return 2;
	return 0;
}

// ����pick 
int feasible(node_t preNode, node_t insertNode, node_t nextNode, int depth, double &cost, double &slackTime) {
	if (!fitWaitTime(preNode, insertNode, depth, slackTime)) return 1;
	cost = calExtraCost(preNode, insertNode, nextNode);
	double slack = nextNode.slackTime;
	if (cost>slack) return 2;
	if (preNode.cap >= C) return 3;
	return 0;
}

void updateCap(treeNode*& pre, treeNode*& insert) {
	if (insert->val.placeId<R) insert->val.cap = pre->val.cap + 1;
	else insert->val.cap = pre->val.cap - 1;
}

// �Ҿ���bugӦ����copyNodes��һ��� 
void copyNodes(treeNode* &node, treeNode* source, double detour) {
	treeNode* newSource = new treeNode(source->val);	//�½�һ�� newһ���ڵ����   �ѵ���newNode �����ĺ�ԭ�����й������� 
	node->children.push_back(newSource);
	treeNode* & newNode = node->children.back();
	newNode->val.time = node->val.time + detour;
	newNode->val.slackTime -= detour;
	//	printf("placeId:  %d   dep:  %d   size: %d:\n",source->val.placeId,dep,source->children.size());

	updateCap(node, newNode);
	for (int i = 0; i<source->children.size(); i++) {
		treeNode* temp = source->children[i];
		if (detour<temp->val.slackTime) {
			copyNodes(newNode, temp, detour);
		}
	}

}

double updateSlackTime(treeNode*& rt) {

	if (rt->size() == 0) return rt->val.slackTime;

	vector<double> timelist;
	double maxSlack = inf;
	for (int i = 0; i<rt->children.size(); i++) {
		double temp = updateSlackTime(rt->children[i]);
		timelist.push_back(temp);
	}
	maxSlack = countMax(timelist);
	rt->val.slackTime = min(maxSlack, rt->val.slackTime);
	return rt->val.slackTime;
}


// ��һ�ּ򻯵Ĵ�����  ��������е�ľ���
// ���Դ�һ����������¼����hotSpot���treeNode �����������е�̫�鷳�ˣ��Ȳ��ü򵥵ķ��� 

// ֻ�в���hotSpot insertPick�Ż��޸�spotId 
// ����ͳһ�޸ķ���ֵ 
int insertDrop(treeNode* & rt, node_t dropNode, double depth, double costLimit, int spotId) {
	int fail = 1;
	double extraCost;
	double slack;
	// û���ӽڵ�
	if (rt->children.size() == 0) {
//		printf("no child\n");
		double l = Length(rt->val, dropNode);
		double cost = l + depth;
		if (cost<costLimit&&rt->val.cap<=C) {
			treeNode* nd = new treeNode(dropNode);
			nd->val.slackTime = costLimit - cost;
			nd->val.time = rt->val.time + l;
			nd->val.cap = rt->val.cap-1;
			nd->val.spotId = spotId;
			rt->children.push_back(nd);
			// ����������һ�ֽ��ƣ�����Ӧ�ò�Ӱ���� 
			if(makeCluster(rt->val, dropNode)){
				if(spotId==0){
					if(rt->val.spotId==0){
						int id = (dropNode.orderId + 1)*N + 1;
						rt->val.spotId = id;
						rt->children[0]->val.spotId = id;
						return 1;						
					} 
					else return 0;				
				}
				else{
					rt->children[0]->val.spotId = spotId;
					return 1;						
				}
			}			
			return 0;
		}
		else {
			//		deleteTree(rt);			// ��ͳһ��ɾ����֧ 
			return -1;
		}
	}


	if (spotId != 0) {
		for (int i = rt->children.size() - 1; i >= 0; i--) {
			int flag = feasible(rt->val, dropNode, rt->children[i]->val, depth, extraCost, costLimit, slack);
			if (flag == 0) {
				treeNode *nd = new treeNode(dropNode);
				nd->val.time = rt->val.time + Length(rt->val, dropNode);
				nd->val.slackTime = slack;
				nd->val.cap = rt->val.cap + 1;
				copyNodes(nd, rt->children[i], extraCost);
				nd->val.slackTime = min(nd->val.slackTime, nd->children[0]->val.slackTime);
				nd->val.spotId = spotId;
				rt->children.push_back(nd);
				return 1;
			}
		}
		return -1;
	}


	if (spotId == 0) {
		for (int i = rt->children.size() - 1; i >= 0; i--) {
			// ��һ���ڵ������hotSpot 
			if (rt->children[i]->val.spotId == 0&& rt->val.cap<=C) {
//				printf("drop potential hotsopt\n");
				if (makeCluster(dropNode, rt->children[i]->val)) {									// ����һ���Ǽ�1����n��һ 
					if (insertDrop(rt->children[i], dropNode, depth + Length(rt->val, rt->children[i]->val), costLimit, (dropNode.orderId + 1)*N + 1) != -1) {
						rt->children[i]->val.spotId = (dropNode.orderId + 1)*N + 1;
						return 1;			// ���ڵ������ǵݹ��ȥ���ܲ�����ֹ�㷨 
					}
				}
			}

			// ��һ���ڵ�û�����hotSpot 
			if (rt->children[i]->val.spotId != 0&&rt->val.cap<=C) {
				// ��������ô�϶��޷����� 
//				printf("drop alreary hotspot\n");
				if (rt->val.spotId != rt->children[i]->val.spotId) {
					vector<randomInsert> list;
					// ���������������ײ������� 
					if (makeCluster(rt->children[i], dropNode, list, depth + Length(rt->val, rt->children[i]->val))) {
						int size = list.size();
						vector<int> satisfied;
						for(int i=0;i<size;i++){
							if(list[i].rt->val.cap>C) break;
							else satisfied.push_back(i);
						}
						size=satisfied.size();
						int n = 0;			// ���Բ���Ĵ��� 
						vector<int> used;
						used.resize(size, 0);
						while (n<size) {
							int choice = rand() % size;
							if (used[choice] == 0) {
								used[choice] = 1;
								n++;
							}
							else continue;		// ����һ������
							struct randomInsert temp = list[i];
							if (insertDrop(temp.rt, dropNode, temp.depth, costLimit, rt->children[i]->val.spotId) != -1) {
								return 1;		// �����ĵ�������û�취�˳� 
							}
						}
					}
				}
			}

//			printf("drop no hotspot\n");
			int flag = feasible(rt->val, dropNode, rt->children[i]->val, depth, extraCost, costLimit, slack);
			if (flag == 0) {
				// �����һ��Ԫ��û�г�spot 
				treeNode *nd = new treeNode(dropNode);
				nd->val.time = rt->val.time + Length(rt->val, dropNode);
				nd->val.slackTime = slack;
				nd->val.cap = rt->val.cap + 1;
				copyNodes(nd, rt->children[i], extraCost);
				nd->val.slackTime = min(nd->val.slackTime, nd->children[0]->val.slackTime);
				rt->children.push_back(nd);			//����������Ǽӽ�ȥ�� 
				fail = 0;
			}
			// �ݹ�������	
			if (flag != 1) {
				int result = insertDrop(rt->children[i], dropNode, depth + Length(rt->val, rt->children[i]->val), costLimit, 0);
				if (result == 1) return 1;
				else if (result == 0) fail = 0;
				else if (result == -1) {
					deleteTree(rt->children[i]);
					rt->children.erase(rt->children.begin() + i);
				}
			}
			else {
				deleteTree(rt->children[i]);
				rt->children.erase(rt->children.begin() + i);
			}
		}
	}

	if (fail == 0) return 0;
	else return -1;

}

//  ���ڵ������Ǳ�����һ���ź����̽������� 
//  ���¶��巵��ֵ
//  -1 ����ʧ��  0 ��������  1 ����hotSpot Ѹ���˳� 
int insertPick(treeNode*& rt, vector<node_t>& src, double depth, int spotId) {

	node_t pickNode = src[0];
	node_t dropNode = src[1];
	double extraCost;
	double costLimit;
	double slack;
	int fail = 1;
	// û���ӽڵ�   �������Ҳ����ֱ���ж� ��Ҫ�ж�insertDrop����� 
	if (rt->children.size() == 0) {
		double l = Length(rt->val, pickNode);
		double cost = l + depth;
		if (cost <= waittime&&rt->val.cap<C) {
			treeNode *nd = new treeNode(pickNode);
			nd->val.slackTime = waittime - cost;
			nd->val.time = rt->val.time + l;
			nd->val.cap = rt->val.cap+1;
			nd->val.spotId=spotId;
			costLimit = Length(pickNode, dropNode)*(1 + detour);

			//  û�в���ɹ� 
			if (insertDrop(nd, dropNode, 0, costLimit, 0) == -1) {	// ����Ӧ�øĽ�һ����������insertDrop ����2 ˵��drop��pick��һ�𹹳���hotSpot 
				deleteTree(nd);					// ��ȷ	   
				return -1;
			}
			// ����ɹ� 
	//		if(spotId!=0) nd->val.spotId = spotId;
			rt->children.push_back(nd);
			return 0;
		}
		//	deleteTree(rt);
		return -1;
	}

	// ��һ����Բ����Լ�֦ 
	if (spotId != 0) {				// ������Ҫ����ĳ��Ԫ�غ���	
		for (int i = rt->children.size() - 1; i >= 0; i--) {
			int flag = feasible(rt->val, pickNode, rt->children[i]->val, depth, extraCost, slack);
			if (flag == 0) {
				treeNode *nd = new treeNode(pickNode);
				//		rt->children.push_back(nd);   �Ȳ�bush_back ����ɹ�����push 

				nd->val.time = rt->val.time + Length(rt->val, pickNode);
				nd->val.slackTime = slack;
				nd->val.cap = rt->val.cap + 1;
				copyNodes(nd, rt->children[i], extraCost);
				nd->val.slackTime = min(nd->val.slackTime, nd->children[0]->val.slackTime);
				costLimit = Length(pickNode, dropNode)*(1 + detour);
				if (insertDrop(nd, dropNode, 0, costLimit, 0) != -1) {
					fail = 0;
					nd->val.spotId = spotId;				//����spotId 
					rt->children.push_back(nd);			// ѹ������
					return 1;
				}
				else {
					deleteTree(nd);
				}
			}
		}
		return -1;
	}

	if (spotId == 0) {
	//	assert(0);
		for (int i = rt->children.size() - 1; i >= 0; i--) {
			// ��һ���ڵ������hotSpot 
	//		printf("index: %d\n",i);
			if (rt->children[i]->val.spotId == 0) {
	//			printf("potential hotspot\n");
				if (makeCluster(pickNode, rt->children[i]->val)) {									// ����һ���Ǽ�1����n��һ 
					if (insertPick(rt->children[i], src, depth + Length(rt->val, rt->children[i]->val), (pickNode.orderId + 1)*N) != -1) {
						rt->children[i]->val.spotId = (pickNode.orderId + 1)*N;
						return 1;			// ���ڵ������ǵݹ��ȥ���ܲ�����ֹ�㷨 
					}
				}
			}
			// ��һ���ڵ�û�����hotSpot 
			
			if (rt->children[i]->val.spotId != 0) {
	//			printf("already hotspot\n");
				// ��������ô�϶��޷����� 
				if (rt->val.spotId != rt->children[i]->val.spotId) {
					vector<randomInsert> list;
					if (makeCluster(rt->children[i], pickNode, list, depth + Length(rt->val, rt->children[i]->val))) {
						int size = list.size();
						int n = 0;			// ���Բ���Ĵ��� 
						vector<int> used;
						used.resize(size, 0);
						while (n<size) {
							int choice = rand() % size;
							if (used[choice] == 0) {
								used[choice] = 1;
								n++;
							}
							else continue;		// ����һ������
							struct randomInsert temp = list[i];
							if (insertPick(temp.rt, src, temp.depth, rt->children[i]->val.spotId) != -1) {
								return 1;		// �����ĵ�������û�취�˳� 
							}
						}
						//  ������е����˵������ȫ������ʧ��  ������Ϊ��ʵ��̫���� 
					}
				}
			}

	//		printf("not hotspot\n");
			int flag = feasible(rt->val, pickNode, rt->children[i]->val, depth, extraCost, slack);
			if (flag == 0) {
				// �����һ��Ԫ��û�г�spot 
				treeNode *nd = new treeNode(pickNode);
				nd->val.time = rt->val.time + Length(rt->val, pickNode);
				nd->val.slackTime = slack;
				nd->val.cap = rt->val.cap + 1;
				copyNodes(nd, rt->children[i], extraCost);
				nd->val.slackTime = min(nd->val.slackTime, nd->children[0]->val.slackTime);
				costLimit = Length(pickNode, dropNode)*(1 + detour);
				if (insertDrop(nd, dropNode, 0, costLimit, 0) != -1) {			// �����ʵҲ���ԸĽ�һ����� 
					fail = 0;
					nd->val.spotId = spotId;	// 
					rt->children.push_back(nd);
	//				printf("insert pick succeed\n");
					
				}
				else {
	//				printf("insertPick fail\n");
					deleteTree(nd);
				}
			}
			// �ݹ�������	
			if (flag != 1) {			
				int result = insertPick(rt->children[i], src, depth + Length(rt->val, rt->children[i]->val), 0);
				if (result == 1) return 1;
				else if (result == 0) fail = 0;
				/* 
				else if (result == -1) {
					printf("delete1\n");
					deleteTree(rt->children[i]);
					rt->children.erase(rt->children.begin() + i);
				}*/ 
			}
			/* 
			else {
				printf("delete2\n");
				deleteTree(rt->children[i]);
				rt->children.erase(rt->children.begin() + i);
			}*/ 
		}
	}
	if (fail == 0) return 0;
	else {
		//	delete(rt);		//��֦ 
	//	printf("after scan return \n"); 
		return -1;
	}
}

void responseDriver(const int driverId, const int orderId) {
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	driver.curTime = order.tid;
	driver.route = bestRoute;
}
// Ѱ�ҽ�һ���������driver����ѷ�������Ĳ���Ӧ����һЩ���� 
// ���ص��ǵȴ�ʱ�� 
/* 
void printTree(treeNode* root, int level) {
	if (root == NULL || root->children.size() == 0) return;
	printf("level: %d    size: %d  ", level, root->children.size());
	for (int i = 0; i<root->children.size(); i++) {
		treeNode* child = root->children[i];
		printf("%d ", child->val.placeId);
	}
	printf("\n");
	for (int i = 0; i<root->children.size(); i++) {
		treeNode* child = root->children[i];
		printTree(child, level + 1);
	}
}
*/ 

bool scheduling(const int driverId, const int orderId) {
	// update the status of driver to now
	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	treeNode*& root = kineticRoots[driverId];

	bestVal = inf;
	curDriverId = driverId;
	curOrderId = orderId;
	validRoute = false;

	bestRoute.clear();
	curRoute.clear();
	bestRoute.resize(driver.route.size() + 2, NULL);
	curRoute.resize(bestRoute.size(), NULL);
	vector<node_t> pairs;

	pairs.push_back(node_t(order.sid, orderId));
	pairs.push_back(node_t(order.eid + R, orderId));

	root->val.cap = driver.cap;
	root->val.time = driver.curTime;
	root->val.x = driver.pos.x;
	root->val.y = driver.pos.y;
/*	
	treeNode* newTreeRoot;
	copyTree(newTreeRoot, root);
*/

	// ���������tree�Ժ���ܻ��deleteSubtree��ľ�����Ӱ��	
	printf("orderId: %d  driverId: %d \n", orderId, driverId);
//	printf("pick:  %d  drop:  %d\n",pairs[0].placeId,pairs[1].placeId);
	// �������ʧ�� 
//	printf("Tree before Insert\n");
//	printTree(root,0);
//	printf("\n\n\n\n");
	if (insertPick(root, pairs, 0, 0)==-1){ 		// ����ʧ���ƺ�û�м�֦ 
		return false;
	} 
	// �������ɹ��� 
//	printf("Tree after Insert\n");
//	printTree(root,0);
//	printf("\n\n\n\n");
	findBestSchedule(root, -1, bestRoute.size());  // ����������֦���� 
//	printf("\n\n\n\n");
//	printf("Tree after prune\n");
//	printTree(root,0);
//	printf("\n\n\n\n");
	updateSlackTime(root);
	responseDriver(driverId, orderId);
}

void findBestResult(treeNode* rt,double tid,int dep,int size) {
	if(rt==NULL) return ;
	const int sz = rt->size();
	for (int i=0; i<sz; ++i) {
		findBestResult(rt->children[i], tid,dep+1,size);
	}
	if (rt->isEmpty()){
	//	printf("dep :  %d   size:  %d \n",dep,size);
		if(size!=dep) return ;
		double cost=rt->val.time-tid;
		if(cost<bestVal) bestVal=cost; 
	}
}

double simulateInsert(const int driverId, const int orderId) {

	driver_t& driver = drivers[driverId];
	order_t& order = orders[orderId];
	treeNode*& root = kineticRoots[driverId];
	
	
	
	bestVal = inf;
	vector<node_t> pairs; 
	pairs.push_back(node_t(order.sid, orderId));
	pairs.push_back(node_t(order.eid+R, orderId));

	root->val.time=driver.curTime;
	root->val.cap=driver.cap;
	root->val.x=driver.pos.x;
	root->val.y=driver.pos.y;
	treeNode* newTreeRoot;
	copyTree(newTreeRoot, root);
	
	

	if(insertPick(newTreeRoot,pairs,0,0)==-1){
		deleteTree(newTreeRoot);
		return bestVal;	
	}

	double time;
	if(driver.empty()) time=driver.curTime;
	else time=driver.route.back()->val.time;
	findBestResult(newTreeRoot,time,0,driver.route.size()+2);
	deleteTree(newTreeRoot); 
	return bestVal; 
}

vector<int> taxiSearching(const int orderId) {
	double bestCost = inf, cost;
	vector<int> ret(1, -1);

	for (int driverId = 0; driverId<M; ++driverId) {
		cost = simulateInsert(driverId, orderId);
	//	printf("%lf\n",cost);
		if (cost < bestCost) {
			bestCost = cost;
			ret[0] = driverId;
		}
	}
	return ret;
}

void Kinetic() { 
	int tid = -1;
	int newtid = 0;
	double minCost;
	int takenId;
	for (int orderId = 0; orderId<N; ++orderId) {
		newtid = orders[orderId].tid;
		minCost = inf;
	//	printf("here1\n"); 
		if (tid == -1) tid = newtid;
		else if (newtid>tid) {
//			printf("updateIndex\n");
			tid = newtid;
			for (int driverId = 0; driverId<M; ++driverId)
				updateIndex(driverId, newtid);
		}

		vector<int> canDrivers = taxiSearching(orderId);
		if (canDrivers.empty() || canDrivers[0]<0)
			continue;
		int takenId = canDrivers[0];
		recordMove(takenId,newtid);
		if (scheduling(takenId, orderId)) taken++;  // �ɹ���ɵĸ��� 

	}

	// ��һ��Ҳ�ܺ����,���Լ����� 
	for (int driverId = 0; driverId<M; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			updateMove(driverId);
	}

}

void  printAns() {
	printf("taken number: %d\n",taken);
	double run = 0;
	for (int i = 0; i<M; i++) {
		printf("driverId: %d  run: %lf\n", i, drivers[i].run);
		run += drivers[i].run;
	}
	printf("total run: %lf\n", run);
	
	freopen("result.txt", "w", stdout);
	
	for (int driverId=0; driverId<M; ++driverId) {
		const int sz = moves[driverId].size();
		printf("%d %d\n", driverId+1, sz);
		dumpOutput(moves[driverId]);
	}
	printf("%lf",run);
}

int main(int argc, char **argv) {
	if (argc > 1)
		freopen(argv[1], "r", stdin);
	else
		freopen("data2.txt", "r", stdin);
	if (argc > 2)
		freopen(argv[2], "w", stdout);
	

	inputHandler();
	Kinetic();
	printAns();
}

// �ִ�����⣬�����Ժ���ܻᷢ�ֲ����˺ܶ��Ŷ�� 
//inf
