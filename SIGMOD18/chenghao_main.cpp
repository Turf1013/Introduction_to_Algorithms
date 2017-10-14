//
//  main.cpp
//  Ridesharing with a single car
//
//  Created by 程浩 on 17/10/12.
//  Copyright (c) 2017年 程浩. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <queue>
#include <map>
#include <assert.h>

using namespace std;

#define LOCAL_DEBUG

int V, M, C, N; // V 地点数量，M 配送员数量，CAP 容量，N 订单数量

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

position_t *stations;

double Length(const position_t& pa, const position_t& pb) {
    return sqrt((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

struct order_t {
    int orderId;
    double time;
    int sourceId, destId;
    
    order_t(int orderId=0, double time=0, int sourceId=0, int destId=0):
    orderId(orderId), time(time), sourceId(sourceId), destId(destId) {}
    
    bool operator<(const order_t& order) const {
        return Length(stations[sourceId], stations[destId]) > Length(stations[order.sourceId], stations[order.destId]);
    }
};

struct node_t {
    int placeId, orderId;
    int type; // 0上车，1下车
    
    node_t(int placeId=0, int orderId=0, int type=0):
    placeId(placeId), orderId(orderId), type(type) {}
    
    bool operator==(const node_t& oth) const {
        return placeId==oth.placeId && orderId==oth.orderId;
    }
    
    bool operator!=(const node_t& oth) const {
        return placeId!=oth.placeId || orderId!=oth.orderId;
    }
};

/*
 每次往离当前位置最近的地方走
 */
vector<node_t> schedule(vector<node_t>& unfinishedNodes, position_t pos, vector<double>& routeLength, map<int, int> tmpOrderStatus) {
    vector<node_t> route;
    position_t curPos = pos;
    routeLength.clear();
    while (unfinishedNodes.size() > 0) {
        // find the nearest node to current position
        double minDist = -1;
        int minIdx = 0;
        for (int i = 0; i < unfinishedNodes.size(); i++) {
            node_t node = unfinishedNodes[i];
            if (tmpOrderStatus[node.orderId] == 0 && node.type == 1) {
                // 如果订单还没接上车，就先忽略它的下车结点
                continue;
            }
            
            position_t nodePos = stations[node.placeId];
            double dist = Length(nodePos, curPos);
            if (minDist < 0) {
                minDist = dist;
                minIdx = i;
            }
            else if (dist < minDist) {
                minDist = dist;
                minIdx = i;
            }
        }
        route.push_back(unfinishedNodes[minIdx]);
        routeLength.push_back(minDist);
        if (unfinishedNodes[minIdx].type == 0) {
            tmpOrderStatus[unfinishedNodes[minIdx].orderId] = 1;
        }
        curPos = stations[unfinishedNodes[minIdx].placeId];
        vector<node_t>::iterator iter = unfinishedNodes.begin()+ minIdx;
        unfinishedNodes.erase(iter);
    }
    return route;
}

struct driver_t {
    position_t curPos;
    double curTime;
    map<int, int> orderStatus; // key是orderId,val是订单状态,0未接到,1已上车
    vector<node_t> route;
    vector<double> routeLength;
    
    driver_t(double x=0., double y=0., double curTime=0.) {
        curPos.x = x;
        curPos.y = y;
        this->curTime = curTime;
    }
    
    int curLoad() const {
        return (int) orderStatus.size();
    }
    
    bool isEmpty() const {
        return route.empty();
    }
    
    bool empty() const {
        return this->isEmpty();
    }
    
    void push_order(order_t order) {
        orderStatus[order.orderId] = 0;
        vector<node_t> unfinishedNodes;
        if (!isEmpty()) {
            for (int i = 0; i < route.size(); i++) {
                unfinishedNodes.push_back(route[i]);
            }
        }
        unfinishedNodes.push_back(node_t(order.sourceId, order.orderId, 0));
        unfinishedNodes.push_back(node_t(order.destId, order.orderId, 1));
        route = schedule(unfinishedNodes, curPos, routeLength, orderStatus);
        
//        for (int i = 0; i < route.size(); i++) {
//            node_t node = route[i];
//            if (node.type == 0) {
//                cout << node.orderId << "上车" << endl;
//            }
//            else if (node.type == 1) {
//                cout << node.orderId << "下车" << endl;
//            }
//        }
    }
    
    void pickUpOrder(order_t order) {
        orderStatus[order.orderId] = 1;
    }
    
    double nextAvailableTime() {
        position_t tmpPos = curPos;
        double tmpTime = curTime;
        if (curLoad() < C) {
            return tmpTime;
        }
        for (int i = 0; i < route.size(); i++) {
            double dist = Length(tmpPos, stations[route[i].placeId]);
            tmpTime += dist;
            tmpPos = stations[route[i].placeId];
            if (route[i].type == 1) {
                break;
            }
        }
        return tmpTime;
    }
    
    double nextFinishTime() {
        position_t tmpPos = curPos;
        double tmpTime = curTime;
        for (int i = 0; i < route.size(); i++) {
            double dist = Length(tmpPos, stations[route[i].placeId]);
            tmpTime += dist;
            tmpPos = stations[route[i].placeId];
            if (route[i].type == 1) {
                break;
            }
        }
        return tmpTime;
    }
    
    void push_back(int placeId, int orderId) {
        route.push_back(node_t(placeId, orderId));
    }
    
    void pop_front() {
        if (!route.empty())
            route.erase(route.begin());
    }
    
    void pop_front_N(int N) {
        if (!route.empty()) {
            route.erase(route.begin(), route.begin() + N);
            routeLength.clear();
            for (int i = 0; i < route.size(); i++) {
                position_t startPos;
                if (i == 0) {
                    startPos = curPos;
                }
                else {
                    startPos = stations[route[i-1].placeId];
                }
                position_t endPos = stations[route[i].placeId];
                double dist = Length(startPos, endPos);
                routeLength.push_back(dist);
            }
        }
    }
    
    void removeOrder(int orderId) {
        orderStatus.erase(orderId);
    }
    
    void erase(vector<node_t>::iterator biter, vector<node_t>::iterator eiter) {
        route.erase(biter, eiter);
    }
    
    void clear() {
        route.clear();
    }
};

order_t *orders;
driver_t *drivers;
double *flowTimes;

void readData(int& V, int& M, int& C, int& N) {
    scanf("%d %d %d %d", &V, &M, &C, &N);
    
    stations = new position_t[V];
    orders = new order_t[N];
    drivers = new driver_t[M];
    flowTimes = new double[N];
    
    double x, y;
    for (int i = 0; i < V; i++) {
        scanf("%lf %lf", &x, &y);
        stations[i] = position_t(x, y);
    }
    
    double time;
    int sourceId, destId;
    for (int i = 0; i < N; i++) {
        scanf("%lf %d %d", &time, &sourceId, &destId);
        orders[i] = order_t(i, time, sourceId - 1, destId - 1);
    }
}

void distributeDrivers() {
    for (int i = 0; i < M; i++) {
        int idx = rand() % V;
        drivers[i].curPos = stations[idx];
        drivers[i].route.clear();
        drivers[i].routeLength.clear();
    }
}

/*
 计算所有车里下一个有空余的时间
 */
double getNextAvailableTime(double curTime) {
    double minFinishTime = -1;
    for (int i = 0; i < M; i++) {
        double finishTime = drivers[i].nextFinishTime();
        if (finishTime == curTime) {
            return curTime; // 表示当前有空车
        }
        if (minFinishTime < 0) {
            minFinishTime = finishTime;
        }
        else if (finishTime < minFinishTime) {
            minFinishTime = finishTime;
        }
    }
    return minFinishTime;
}

/*
 计算所有车里下一个完成订单的时间
 */
double getNextFinishTime(double curTime) {
    double minFinishTime = -1;
    for (int i = 0; i < M; i++) {
        double finishTime = drivers[i].nextFinishTime();
        if (minFinishTime < 0) {
            minFinishTime = finishTime;
        }
        else if (finishTime < minFinishTime) {
            minFinishTime = finishTime;
        }
    }
    return minFinishTime;
}

void updateDriver(double newTime) {
    for (int i = 0; i < M; i++) {
        if (drivers[i].isEmpty()) {
            // 如果车上没有订单，则原地等待
            drivers[i].curTime = newTime;
        }
        else {
            double curTime = drivers[i].curTime;
            double timeDiff = -1;
            int j;
            for (j = 0; j < drivers[i].route.size(); j++) {
                timeDiff = newTime - curTime;
                if (timeDiff >= drivers[i].routeLength[j]) {
                    // 过完这段时间，司机已经移动到下一个节点了
                    curTime += drivers[i].routeLength[j];
                    node_t node = drivers[i].route[j];
                    if (node.type == 0) {
                        // 订单接上车
                        drivers[i].pickUpOrder(node.orderId);
                    }
                    else if (node.type == 1) {
                        // 订单完成！
                        int orderId = node.orderId;
                        drivers[i].removeOrder(orderId);
                        double orderReleaseTime = orders[orderId].time;
                        flowTimes[orderId] = curTime - orderReleaseTime;
                    }
                }
                else {
                    break;
                }
            }
            timeDiff = newTime - curTime;
            double ratio = 0;
            if (j <= drivers[i].routeLength.size() - 1) {
                ratio = timeDiff / drivers[i].routeLength[j];
            }
            else if (j == drivers[i].routeLength.size()) {
                // 下标超出范围，至少已经走到最后一个点了，在该点等待
#ifdef LOCAL_DEBUG
                assert(timeDiff >= 0);
#endif
                ratio = 0;
            }
#ifdef LOCAL_DEBUG
            assert(ratio < 1 && ratio >= 0);
#endif
            if (ratio == 0) {
                drivers[i].curPos = stations[drivers[i].route[j-1].placeId];
            }
            else {
                position_t startPos;
                if (j > 0) {
                    // 汽车至少能到第一个节点
                    startPos = stations[drivers[i].route[j-1].placeId];
                }
                else {
                    // 汽车连第一个节点也到不了
                    startPos = drivers[i].curPos;
                }
                position_t endPos = stations[drivers[i].route[j].placeId];
                drivers[i].curPos.x = startPos.x + (endPos.x - startPos.x) * ratio;
                drivers[i].curPos.y = startPos.y + (endPos.y - startPos.y) * ratio;
            }
            drivers[i].curTime = newTime;
            drivers[i].pop_front_N(j);
        }
    }
}

int findNearestAvailableDriver(order_t& order) {
    position_t orderPos = stations[order.sourceId];
    double minDist = -1;
    double minIdx = -1;
    for (int i = 0; i < M; i++) {
        if (drivers[i].curLoad() >= C) {
            continue;
        }
        double dist = Length(orderPos, drivers[i].curPos);
        if (minDist < 0) {
            minDist = dist;
            minIdx = i;
        }
        else if (dist < minDist) {
            minDist = dist;
            minIdx = i;
        }
    }
    return minIdx;
}

void solve() {
    double curTime = -1;
    int orderId = 0;
    
    priority_queue<order_t> qOrder;
    // 边分配订单，边完成订单的过程
    while (orderId < N) {
        double oldTime = curTime;
        double nextAvailableTime = getNextAvailableTime(curTime);
        if (nextAvailableTime < orders[orderId].time) {
            // 表示还有空车
            if (qOrder.empty()) {
                // 没有滞留订单，则将时间推进到下一个订单时间
                curTime = orders[orderId].time;
            }
            else {
                // 有滞留订单，则将时间推进到有车空出座位的时间
                curTime = nextAvailableTime;
            }
        }
        else {
            // 没有空车，则将时间推进到下一个订单时间
            curTime = orders[orderId].time;
        }
#ifdef LOCAL_DEBUG
        assert(curTime >= oldTime);
#endif
        updateDriver(curTime);
        
        while (orderId < N && orders[orderId].time <= curTime) {
            qOrder.push(orders[orderId]);
            orderId++;
        }
        
        while (!qOrder.empty()) {
            // 对于每个订单，选择一辆离它最近并且有空座的车
            order_t order = qOrder.top();
            int idx = findNearestAvailableDriver(order);
            if (idx != -1) {
                drivers[idx].push_order(order);
                qOrder.pop();
            }
            else {
                break;
            }
        }
    }
    // 订单已经全部分配完成，只剩完成订单的过程
    while (true) {
        double oldTime = curTime;
        double nextFinishTime = getNextFinishTime(curTime);
        if (nextFinishTime == oldTime) {
            break;
        }
#ifdef LOCAL_DEBUG
        assert(nextFinishTime > oldTime);
#endif
        curTime = nextFinishTime;
        updateDriver(curTime);
    }
}
void readNetwork() {
    readData(V, M, C, N);
    
    distributeDrivers();
}

int main(int argc, const char * argv[]) {
    freopen("/Users/zhongya/Documents/Master/RideSharing/smallDataSet/data_04.txt", "r", stdin);
    readNetwork();
    solve();
//    cout << V << " " << M << " " << C << " " << N << endl;
    
    double totalFlowTime = 0;
    for (int i = 0; i < N; i++) {
        totalFlowTime += flowTimes[i];
    }
    printf("ShortestJobFirst %.3f\n", totalFlowTime);

    return 0;
}
