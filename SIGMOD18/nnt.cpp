/**
	\author:	Trasier
	\date:		2017.10.18
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "global.h"
// #include "monitor.h"

#define LOCAL_DEBUG


int V, N, C, M;
position_t* points = NULL;
order_t* orders = NULL;
double *deliverTime;
int *orderPool = NULL;

struct driver_nnt_t {
	double curTime;
	position_t pos;
	vector<int> deliverPool;

	driver_nnt_t(double curTime=0.0):
		curTime(curTime) {}

	int getNearestId() const {
		int ret = -1, sz = deliverPool.size();
		double mn = inf;

		for (int i=0; i<sz; ++i) {
		int orderId = deliverPool[i];
			double tmp = (orderId<0) ? Length(pos, points[orders[-orderId].eid]) : Length(pos, points[orders[orderId].sid]);
			if (tmp < mn) {
				mn = tmp;
				ret = i;
			}
		}

		return ret;
	}

	void swap(int a, int b) {
		#ifdef LOCAL_DEBUG
		assert(a>=0 && a<deliverPool.size());
		assert(b>=0 && b<deliverPool.size());
		#endif
		swap(deliverPool[a], deliverPool[b]);
	}

	void appendId(const int id) {
		deliverPool.push_back(id);
	}

	void removeId(const int id) {
		if (id>=0 && id<deliverPool.size()) {
			deliverPool[id] = *deliverPool.rbegin();
			deliverPool.pop_back();
		}
	}

	int poolSize() const {
		return deliverPool.size();
	}

	bool empty() const {
		return deliverPool.empty();
	}

	bool full() const {
		return deliverPool.size() == C;
	}

	bool free() const {
		return empty();
	}
};
driver_nnt_t* drivers;
typedef pair<double,int> pdi;
priority_queue<pdi, vector<pdi>, greater<pdi> > Q;

void init() {
	for (int i=M; i>0; --i) {
		orders[i] = orders[i-1];
	}

	orderPool = new int[M+5];
	deliverTime = new double[M+5];
	for (int i=0; i<M+5; ++i) {
		deliverTime[i] = inf;
	}
	drivers = new driver_nnt_t[N];
	for (int i=0; i<N; ++i) {
		int idx = 0; //rand() % N;
		drivers[i].pos = points[idx];
  	Q.push(make_pair(0.0, i));
	}

	#ifdef LOCAL_DEBUG
	printf("V = %d, N = %d, C = %d, M = %d\n", V, N, C, M);
	#endif
}

void FreeMem() {
	delete[] points;
	delete[] orders;
	delete[] deliverTime;
	delete[] drivers;
	delete[] orderPool;
}

int NN(position_t& pos, int& poolSz) {
	int ret = -1, orderId;
	double mn = inf, tmp;

	for (int i=0; i<poolSz; ++i) {
		orderId = orderPool[i];
		tmp = Length(pos, points[orders[orderId].sid]);
		if (tmp < mn) {
			mn = tmp;
			ret = i;
		}
	}
	if (ret >= 0)
		swap(orderPool[ret], orderPool[poolSz-1]);

	return orderPool[poolSz-1];
}

void nextTarget(driver_nnt_t& driver, int& poolSz) {
	#ifdef LOCAL_DEBUG
  assert(!(driver.empty() && poolSz==0));
  #endif

	// direct fetch from the orderPool
	if (driver.empty()) {
		int orderId = NN(driver.pos, poolSz);
		driver.appendId(orderId);
    driver.swap(0, driver.poolSize()-1);
		--poolSz;
	} else if (driver.full()) {
		int idx = driver.getNearestId();
		driver.swap(0, idx);
	} else {
		double l1, l2;
		int orderId1, orderId2;

		orderId1 = NN(driver.pos, poolSz);
		l1 = Length(driver.pos, points[orders[orderId1].sid]);
		int idx = driver.getNearestId();
		orderId2 = driver.deliverPool[idx];
		if (orderId2 > 0)
			l2 = Length(driver.pos, points[orders[orderId2].sid]);
		else
			l2 = Length(driver.pos, points[orders[-orderId2].eid]);

		if (l2 <= l1) {
			driver.swap(0, idx);
		} else {
			driver.appendId(orderId1);
			driver.swap(0, driver.poolSize()-1);
			--poolSz;
		}
	}
}

void nextFromPool(driver_nnt_t& driver, int& poolSz) {
  int orderId = NN(driver.pos, poolSz);
  driver.appendId(orderId);
  driver.swap(0, driver.poolSize()-1);
  driver.curTime = max(driver.curTime, (double)orders[orderId].tid);
  --poolSz;
}

double nextTargetTime(const driver_nnt_t& driver) {
	if (driver.empty()) return driver.curTime;
	int orderId = driver.deliverPool[0];
	position_t curPos = driver.pos;
	position_t nextPos = (orderId > 0) ? points[orders[orderId].sid] : points[orders[-orderId].eid];
	double ret = driver.curTime + Length(curPos, nextPos);
	return ret;
}

void updateDriverBefore(int& poolSz, double preTime, double nextTime) {
  while (Q.top().first < nextTime) {
    pdi p = Q.top();
    Q.pop();
    int driverId = p.second;
    driver_nnt_t& driver = drivers[driverId];
    // update the current movement
    if (!driver.empty()) {
  		int orderId = driver.deliverPool[0];
  		if (orderId < 0) {
  			deliverTime[-orderId] = p.first;
  			// update the driver
  			driver.curTime = p.first;
  			driver.pos = points[orders[-orderId].eid];
  			driver.removeId(0);
  		} else {
  			driver.curTime = p.first;
  			driver.pos = points[orders[orderId].sid];
  			driver.deliverPool[0] = -orderId;
  		}
    } else {
      driver.curTime = p.first;
    }
    // update the next movement
    if (driver.empty()) {
      if (poolSz ==0) {
        driver.curTime = nextTime;
      } else {
        nextFromPool(driver, poolSz);
      }
    } else {
      nextTarget(driver, poolSz);
    }
    // update the next arriveTime
    double t = nextTargetTime(driver);
    Q.push(make_pair(t, driverId));
  }
}

void udpateDriverAfter(int& poolSz) {
  #ifdef LOCAL_DEBUG
  assert(poolSz == 0);
  #endif
  while (!Q.empty()) {
    pdi p = Q.top();
    Q.pop();
    int driverId = p.second;
    driver_nnt_t& driver = drivers[driverId];
    if (drivers[driverId].empty()) continue;

    int orderId = driver.deliverPool[0];
    if (orderId < 0) {
      deliverTime[-orderId] = p.first;
      // update the driver
      driver.curTime = p.first;
      driver.pos = points[orders[-orderId].eid];
      driver.removeId(0);
    } else {
      driver.curTime = p.first;
      driver.pos = points[orders[orderId].sid];
      driver.deliverPool[0] = -orderId;
    }

    if (drivers[driverId].empty()) continue;

    nextTarget(driver, poolSz);
    // update the next arriveTime
    double t = nextTargetTime(driver);
    Q.push(make_pair(t, driverId));
  }
}

// a.k.a Next Nearest Target
void NNT() {
	int driverId, orderId = 1;
	double curTime = 0, preTime = 0.0;
	int poolSz = 0;

	while (orderId <= M) {
	    curTime = orders[orderId].tid;
	    updateDriverBefore(poolSz, preTime, curTime);
		while (orderId<=M && orders[orderId].tid<=curTime) {
			orderPool[poolSz++] = orderId;
			++orderId;
		}
    	preTime = curTime;
	}

	while (poolSz > 0) {
    	updateDriverBefore(poolSz, preTime, inf);
	}

  	udpateDriverAfter(poolSz);
}

double calcResult() {
	double ans = 0;

	for (int orderId=1; orderId<=M; ++orderId) {
		#ifdef LOCAL_DEBUG
		assert(deliverTime[orderId] < inf);
		#endif
		ans += deliverTime[orderId]-orders[orderId].tid;
	}

	return ans;
}

double solve() {
	init();

	NNT();

	double flowTime = calcResult();
	return flowTime;
}

int main(int argc, char **argv) {
	string execName("NextNearestPlace");

	string srcFileName;
	if (argc > 1) {
		srcFileName = string(argv[1]);
	}
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	// step1: read Input
	if (srcFileName.empty()) {
		readInput(cin, V, N, C, M, points, orders);
	} else {
		readInput(srcFileName, V, N, C, M, points, orders);
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
