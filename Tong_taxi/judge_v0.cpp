#include <bits/stdc++.h>
using namespace std;

#define LOCAL_DEBUG

struct place_t {
  double x, y;
  
  place_t(double x=0., double y=0.):
    x(x), y(y) {}
    
  bool operator< (const place_t& o) const {
    if (x != o.x)
      return x < o.x;
    return y < o.y;
  }
  
  bool operator< (const place_t& o) const {
    return x==o.x && y==o.y;
  }
};

struct sender_t {
  place_t p;    // place
  double bt, et // bt: begTime, et: endTime
  int c;      // cap
  vector<int> vo; // vector of orderId
  
  sender_t(int C=0) {
    bt = et = 0.;
    c = C;
  }
};

struct order_t {
  int cid;    // index of cook places
  int eid;    // index of eat places 
  double bt, et // bt: begTime, et: endTime
  
  order_t(int tid = 0, int cid = 0, int eid = 0):
    cid(cid), eid(eid), bt(tid), et(tid) {}
};

vector<place_t> cookPlaces;
map<place_t,int> cookPlacesMap;
vector<place_t> eatPlaces;
map<place_t,int> eatPlacesMap;
vector<order_t> orders;
vector<sender_t> senders;
int R;  // the number of send places
int D;  // the number of receive places
int M;  // the number of senders
int C;  // the capacity of every sender's box
int N;  // the number of orders

void readInFile(const string& fileName);
int checkResult(const string& fileName);
void calcScore(int status);

void init() {
  cookPlaces.clear();
  earPlaces.clear();
  orders.clear();
  senders.clear();
}

const double eps = 1e-8;
bool dcmp(double x) {
  if (fabs(x) < eps)
    return 0;
  return x>0 ? 1:-1;
}

void initPlaceMap(const vector<place_t&>& places, map<place_t&,int>& placeMap) {
  const int sz = places.size();
  
  for (int i=0; i<sz; ++i) {
    placeMap[places[i]] = i;
  }
}

inline double Distance(const place_t& a, const place_t& b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

inline double Distance(const sender_t& a, const sender_t& b) {
  return Distance(a.p, b.p);
}

inline int getEid(const place_t& plc) {
  if (eatPlacesMap.count(plc))
    return eatPlacesMap[plc];
  return -1;
}

inline int getCid(const place_t& plc) {
  if (cookPlacesMap.count(plc))
    return cookPlacesMap[plc];
  return -1;
}

void readInFile(const string& fileName){
  ifstream fin(fileName.c_str(), ios::in);
  
  if (!fin.is_open()) {
    printf("inFile %s not exists.", fileName.c_str());
    exit(1);
  }
  
  init();
  fin >> R >> D >> M >> C >> N;
  place_t plc;
  
  // next R lines
  for (int i=0; i<R; ++i) {
    fin >> plc.x >> plc.y;
    cookPlaces.push_back(plc);
  }
  
  // next D lines
  for (int i=0; i<D; ++i) {
    fin >> plc.x >> plc.y;
    eatPlaces.push_back(plc);
  }
  
  // next M lines
  int tid, cid, eid;
  for (int i=0; i<N; ++i) {
    fin >> tid >> cid >> eid;
    orders.push_back(order_t(tid, cid, eid));
  }
  
  // init places Map to get Id
  initPlaceMap(cookPlaces, cookPlacesMap);
  initPlaceMap(eatPlaces, eatPlacesMap);
}

template <class data>
bool isDistinct(const vector<data>& vc) {
  const int sz = vc.size();
  
  for (int i=0; i<sz; ++i) {
    for (int j=i+1; j<sz; ++j) {
      if (vc[i] == vc[j])
        return false;
    }
  }
  
  return true;
}

int updateOrders(sender_t& pre, const sender_t& cur, const vector<int>& vecTaken, const vector<int>& vecReceive,
          vector<int>& orderTakenAt, vector<int>& orderReceiveAt) {
  
  // vecTaken & vecReceive should be distince
  if (!isDistinct(vecTaken) || !isDistinct(vecReceive))
    return -1;
  
  
  // the best strategry to deliver is deliver as fast as possible
  /**
    \forall orderId \in vecReceive, it must satisfy:
    1) orderId \in pre.vo
    2) orderId \in vecTaken and we can find enough capacity to store it.
  */
  
  const int sz_vecReceive = vecReceive.size();
  const int sz_vecTaken = vecTaken.size();
  
  // check out the orders taken from other places.
  for (int i=0; i<sz_vecReceive; ++i) {
    const int orderId = vecReceive[i];
    
    for (vector<int>::iterator iter=pre.vo.begin(); iter!=pre.vo.end(); ++iter) {
      if (*iter == orderId) {
        inPre = true;
        ++pre.c;
        pre.vo.erase(iter);
        // obviously, this order can be delivered at cur.bt, because we want GAP as small as possible.
        orderReceiveAt[orderId] = cur.bt;
        break;
      }
    }
  }
  
  // check out the orders taken from this place.
  for (int i=0; i<sz_vecReceive; ++i) {
    const int orderId = vecReceive[i];
    
    for (int j=0; j<sz_vecTaken; ++j) {
      if (orderId == vecTaken[j]) {
        // if the current capacity is zero, then this operation is invalid no matter what.
        if (pre.c == 0) {
          return -1;
        }
        
        // obviously, this order should be delivered orders[orderId].bt exactly, because we want GAP as small as possible.
        orderReceiveAt[orderId] = orders[orderId].bt;
        break;
      }
    }
    
    // if this order is not delivered, then the operation must be wrong
    if (orderReceiveAt[orderId] < 0) {
      return -1;
    }
  }
  
  // add waiting delivered orders
  for (int i=0; i<sz_vecReceive; ++i) {
    const int orderId = vecReceive[i];
    
    if (orderReceiveAt[orderId] >= 0)
      continue;
    
    pre.vo.push_back(orderId);
    // check the valid capacity.
    if (--pre.c < 0) {
      return -1;
    }
  }
  
  pre.p = cur.p;
  pre.bt = cur.bt;
  pre.et = cur.et;
  
  return 0;
}

int checkResult(const string& fileName) {
  ifstream fin(fileName.c_str(), ios::in);
  
  if (!fin.is_open()) {
    printf("outFile %s not exists.", fileName.c_str());
    exit(1);
  } 
  
  vector<double> orderTakenAt(N+5, -1.0);
  vector<double> orderReceiveAt(N+5, -1.0);
  int numVer, senderN = 0;
  
  while (fin >> numVer) {
    // sender constrict 
    if (++senderN > M) {
      printf("The number of sender is beyond %d.\n", M);
      return -1;
    }
    
    sender_t cur, pre;
    int num1, num2;
    
    for (int i=0; i<numVer; ++i) {
      fin >> cur.p.x >> cur.p.y >> cur.bt >> cur.et;
      if (i == 0) {
        pre.p = cur.p;
        pre.c = C;
      }
      
      // the time between adjacent places should above DISTANCE.
      if (i>0 && dcmp(pre.et+Distance(cur, pre) - cur.bt)>0) {
        printf("No.%d sender\'s time is wrong.\n", i);
        return -1;
      }
      
      fin >> num1;
      // check whether this position is the real restaurant
      if (num1>0 && getCid(cur.p)<0) {
        printf("(%.3lf, %.3lf) is not a cook place.\n", cur.p.x, cur.p.y);
        return -1;
      }
      vector<int> vecTaken(num1, -1);
      for (int j=0; j<num1; ++j) {
        fin >> vecTaken[j];
        const int orderId = vecTaken[j];
        
        // Nobody has picked up this order before.
        if (orderTakenAt[orderId] >= 0) {
          printf("Order %d has picked up by someone else.\n", orderId);
          return -1;
        }
        
        // the time of this order should earlier than endTime
        if (dcmp(orders[orderId] - cur.et) > 0) {
          printf("Order %d has not arrived yet.\n", orderId);
          return -1;
        }
      }
      
      fin >> num2;
      if (num2>0 && getEid(cur.p)<0) {
        printf("(%.3lf, %.3lf) is not a eat place.\n", cur.p.x, cur.p.y);
        return -1;
      }
      vector<int> vecReceive(num2, -1);
      for (int j=0; j<num2; ++j) {
        fin >> vecReceive[j];
        const int orderId = vecReceive[j];
        
        // This is the first time to receive this order.
        if (orderReceiveAt[orderId] >= 0) {
          printf("Order %d has received before.\n", orderId);
          return -1;
        }
        
        // the time of this order should later than begTime
        if (dcmp(orders[orderId] - cur.et) > 0) {
          printf("Order %d has not arrived yet.\n", orderId);
          return -1;
        }
      }
      
      int status = updateOrders(pre, cur, vecTaken, vecReceive, orderTakenAt, orderReceiveAt);
      if (status < 0) {
        printf("No.%d sender at place (%.3lf, %.3lf) has invalid operations.\n", i, cur.p.x, cur.p.y);
        exit(1);
      }
    }
    
    double result = -1;
    
    // check whether all order is taken & receive
    for (int i=0; i<N; ++i) {
      if (orderTakenAt[i]<0 || orderReceiveAt[i]<0) {
        printf("Order %s is not taken or received.\n", i);
        return -1;
      }
      double tmp = orderReceiveAt[i] - orderTakenAt[i];
      result = max(result, tmp);
    }
  }
}

void calcScore(int status) {
  puts("0.0");
}

int main(int argc, char **argv) {
  string infileName;
  string outfileName;
  
  if (argc > 2) {
    inFileName = string(argv[1]);
    outFileName = string(argv[2]);
  } else {
    inFileName = "data.in";
    outFileName = "data.out";
  }
  
  readInFile(inFileName);
  int status = checkResult(outFileName);
  calcScore(status);
  
  return 0;
}