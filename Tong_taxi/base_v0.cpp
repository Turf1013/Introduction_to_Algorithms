/**
	\author: 	Trasier
	\date: 		2017.5.1 
	\describe: 	base_v0 is a baseline method to solve the problem of taxi sharing. 
		The core idea of this method is to force all the workers fill with their package and then send them out ASAP.
		Basically, the less time the workers return to restaurants, the more time they will save. 
		Therefore, the package should be delivered as early as possible.
*/

#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "monitor.h"

#define LOCAL_DEBUG
// #define WATCH_MEM

struct order_t {
	int id;
	int tid, rid, did;

	order_t(int id=0, int tid=0, int rid=0, int did=0):
		id(id), tid(tid), rid(rid), did(did) {}

	void print() {
		printf("Order%d: At T%d from R%d to D%d.\n", id, tid, rid, did);
	}
};

struct sender_t {
	double x, y;
	double curTime;
	vector<int> bucket;

	sender_t(double x=0., double y=0., double curTime=0.):
		x(x), y(y), curTime(curTime) {}

	bool isFull(const int c) const {
		return bucket.size() >= c;
	}

	bool isEmpty() const {
		return bucket.size() == 0;
	}

	void addOrder(const int oid) {
		bucket.push_back(oid);
	}

	int getBucketSize() const {
		return bucket.size();
	}
};

struct receiver_t {
	double begTime, endTime;

	receiver_t(double begTime=0.):
		begTime(begTime), endTime(begTime) {}

	receiver_t(double begTime=0., double endTime=0.):
		begTime(begTime), endTime(endTime) {}
};

const double inf = 1e20;
typedef pair<int,int> position_t;
vector<position_t> vRest, vDist;
vector<order_t> vOrder;
vector<receiver_t> receivers;
vector<sender_t> senders;
vector<vector<move_t> > moves;
vector<bool> visit;
vector<vector<double> > R2D, R2R, D2D;
int R, D, M, C, N;

vector<int> senderPosId;

inline double Length(const position_t& pa, const position_t& pb) {
	return sqrt(1.0*(pa.first-pb.first)*(pa.first-pb.first) + 1.0*(pa.second-pb.second)*(pa.second-pb.second));
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

void init_Receiver() {
	receivers.clear();
	for (int i=0; i<N; ++i) {
		receivers.push_back(receiver_t(vOrder[i].tid));
	}
}

void init_Sender() {
	senders.clear();
	for (int i=0; i<M; ++i) {
		senders.push_back(sender());
	}
	senderPosId.clear();
	senderPosId.resize(M, -1);
}

void init_Move() {
	moves.clear();
	for (int i=0; i<M; ++i) {
		moves.push_back(vector<move_t>());
	}
}

void init_calc() {
	visit.clear();
	visit.resize(N, false);
}

void addMove(const int sid, const move_t& move) {
	#ifdef LOCAL_DEBUG
	assert(sid>=0 && sid<senders.size());
	#endif
	senders[sid].push_back(move);
}

void deliver(sender_t& sender, int& posId) {
	#ifdef LOCAL_DEBUG
	assert(sender.getBucketSize() > 0);
	#endif
	const int c = sender.getBucketSize();
	const int rid = posId;
	vector<int>& bucket = sender.bucket;
	vector<int> permu(c, 0), bestPermu;
	double tmp, curTime;
	double bestVal = inf;

	for (int i=0; i<c; ++i)
		permu[i] = i;

	do {
		tmp = 0.0;
		curTime = sender.curTime;
		for (int i=0; i<c; ++i) {
			const int oid = bucket[permu[i]];
			const int did = vOrder[oid].did;
			if (i == 0) {
				curTime += dist_R2D(rid, did)
			} else {
				curTime += dist_D2D(vOrder[bucket[permu[i-1]]].did, did);
			}
			tmp = max(tmp, curTime-vOrder[oid].tid);
		}
		// choose the best deliver path
		if (tmp < bestVal) {
			bestVal = tmp;
			bestPermu = permu;
		}
	} while (next_permutation(permu.begin(), permu.end()));

	// update the receiver
	curTime = sender.curTime;
	for (int i=0; i<c; ++i) {
		const int oid = bucket[bestPermu[i]];
		const int did = vOrder[oid].did;
		if (i == 0) {
			curTime += dist_R2D(rid, did)
		} else {
			curTime += dist_D2D(vOrder[bucket[bestPermu[i-1]]].did, did);
		}
		receivers[oid].endTime = curTime;
	}

	// update this sender
	int lastPos = vOrder[bucket[bestPermu[c-1]]].did;
	posId = D + lastPos;
	sender.x = vDist[lastPos].first;
	sender.y = vDist[lastPos].second;
	sender.curTime = curTime;
	sender.bucket.clear();
}

void deliver(const int sid) {
	delier(senders[sid], senderPosId[sid]);
}

void addOrder(sender_t& sender, int& posId, const int orderId) {
	const order_t& order = vOrder[orderId];
	const int rid = order.rid;

	senders[i].x = vRest[rid].first;
	senders[i].y = vRest[rid].second;
	if (posId >= D) {
		senders[i].curTime += dist_D2R(posId-D, rid);
	} else {
		senders[i].curTime += dist_R2R(posId, rid);
	}
	senders[i].addOrder(orderId);
	
	// update current posId
	posId = rid;
}

void addOrderWithUpdate(sender_t& sender, int& posId, const int orderId, vector<move_t>& vmove) {
	const order_t& order = vOrder[orderId];
	const int rid = order.rid;
	move_t move;

	senders[i].x = vRest[rid].first;
	senders[i].y = vRest[rid].second;
	if (posId >= D) {
		senders[i].curTime += dist_D2R(posId-D, rid);

	} else {
		senders[i].curTime += dist_R2R(posId, rid);
	}
	senders[i].addOrder(orderId);

	// update current posId
	posId = rid;

	// update the move
	move.x = senders[i].x;
	move.y = senders[i].y;
	move.arrive = senders[i].curTime;
	move.leave = move.arrive;
	vmove.push_back(move);
}


double calcResult() {
	double ret = 0.0;

	for (int i=0; i<N; ++i) {
		#ifdef LOCAL_DEBUG
		assert(receivers[i].endTime >= receivers[i].begTime);
		#endif
		ret = max(ret, receivers[i].endTime - receivers[i].begTime);
	}

	return ret;
}

double calc(int C) {
	#ifdef LOCAL_DEBUG
	assert(N > M);
	#endif
	double ret = 0.0;

	init_calc();	
	/** 
		\step1: obviously the first M order should distributed equally to every sender
	*/
	for (int i=0; i<M; ++i) {
		const int rid = vOrder[i].rid;
		senders[i].curTime = 0;
		senderPosId[i] = rid;
		addOrder(senders[i], senderPosId[i], i);
		if (senders[i].isFull(C))
			deliver(i);
	}

	/**
		\step2: hand the next order
	*/
	for (int i=M; i<N; ++i) {
		const int rid = vOrder[i].rid;
		int v = -1;
		double mn = inf, tmp;
		for (int j=0; j<M; ++j) {
			if (senders[j].isEmpty()) {
				tmp = dist_D2R(senderPosId[j]-D, rid);
			} else {
				tmp = dist_R2R(senderPosId[j], rid);
			}
			if (tmp < mn) {
				v = j;
				mn = tmp;
			}
		}
		addOrder(senders[v], senderPosId[i], i);
		if (senders[v].isFull(C))
			deliver(v);
	}

	/**
		\step 3: deliver all the sender
	*/
	for (int i=0; i<M; ++i) {
		if (!senders[i].isEmpty())
			deliver(i);
	}

	/**
		\step 4: calculate result
	*/
	ret = calcResult();

	return ret;
}

void calcWithUpdate(int C) {
	init_calc();	
	/** 
		\step1: obviously the first M order should distributed equally to every sender
	*/
	for (int i=0; i<M; ++i) {
		const int rid = vOrder[i].rid;
		senders[i].curTime = 0;
		senderPosId[i] = rid;
		addOrderWithUpdate(senders[i], senderPosId[i], i);
		if (senders[i].isFull(C))
			deliverWithUpdate(i);
	}

	/**
		\step2: hand the next order
	*/
	for (int i=M; i<N; ++i) {
		const int rid = vOrder[i].rid;
		int v = -1;
		double mn = inf, tmp;
		for (int j=0; j<M; ++j) {
			if (senders[j].isEmpty()) {
				tmp = dist_D2R(senderPosId[j]-D, rid);
			} else {
				tmp = dist_R2R(senderPosId[j], rid);
			}
			if (tmp < mn) {
				v = j;
				mn = tmp;
			}
		}
		addOrderWithUpdate(senders[v], senderPosId[i], i);
		if (senders[v].isFull(C))
			deliverWithUpdate(v);
	}

	/**
		\step 3: deliver all the sender
	*/
	for (int i=0; i<M; ++i) {
		if (!senders[i].isEmpty())
			deliverWithUpdate(i);
	}

	/**
		\step 4: calculate result
	*/
	ret = calcResult();
}

double fastSolve() {
	#ifdef LOCAL_DEBUG
	assert(M >= N);
	#endif

	double ret = 0.0;
	move_t move;

	for (int i=0; i<N; ++i) {
		const int rid = vOrder[i].rid;
		const int did = vOrder[i].did;
		move.x = vRest[rid].first;
		move.y = vRest[rid].second;
		move.arrive = vOrder[i].tid;
		move.leave = move.arrive;
		move.bucket.clear();
		move.bucket.push_back(i);
		senders[i].push_back(move);
		ret = max(ret, dist_R2D(rid, did));
	}

	return ret;
}

void printAns(double ans) {
	dumpOutput(senders());
	printf("%.4lf\n", ans);
}

void solve() {
	init_Receiver();
	init_Sender();
	init_Move();
	init_Dist();

	if (M >= N) {
		double ans = fastSolve();
		printAns(ans);
		return ;
	}
	double ans = 0.0, tmp;
	int ansc = 1;

	for (int c=1; c<=C; ++c) {
		tmp = calc(ansc);
		if (c==1 || tmp<ans) {
			ansc = c;
			ans = tmp;
		}
	}

	calcWithUpdate(ansc);
	printAns(ans);
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
	readInput(R, D, M, C, N, vRest,  vDist, vOrder);

	/**
		\step 2: solve
	*/
	solve();

	return 0;
}

