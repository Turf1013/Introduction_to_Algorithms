#include <bits/stdc++.h>
using namespace std;
const int N = 1024;
const int EPS = 1e-8;
int workerN, taskN, Umax, sumDegree;
struct node {
  int tim;
  double x, y, r;
  node (int _tim = 0, double _x = 0, double _y = 0, double _r = 0) {
    tim = _tim;
    x = _x;
    y = _y;
    r = _r;
  }
} worker[N], task[N];
vector <pair <char, int> > q;
set <int> wk, tk;
double G[N][N];

double sqr(double x) {
  return x * x;
}

bool judge(int u, int v) {
  if (sqr(task[v].x - worker[u].x) + sqr(task[v].y - worker[u].y) < sqr(worker[u].r) + EPS) {
    return true;
  }
  return false;
}
double greedy() {
  double tot = 0;
  for (auto u : q) {
    if (u.first == 'w') {
      int max_id = -1;
      double max_w = -1;
      for (int v : tk) {
	if (!judge(u.second, v)) {
	  continue;
	}
	if (max_w < G[u.second][v]) {
	  max_w = G[u.second][v];
	  max_id = v;
	}
      }
      if (max_id > -1) {
	tot += max_w;
	tk.erase(max_id);
      } else {
	wk.insert(u.second);
      }
    } else {
      int max_id = -1;
      double max_w = -1;
      for (int v : wk) {
	if (!judge(v, u.second)) {
	  continue;
	}
	if (max_w < G[v][u.second]) {
	  max_w = G[v][u.second];
	  max_id = v;
	}
      }
      if (max_id > -1) {
	tot += max_w;
	wk.erase(max_id);
      } else {
	tk.insert(u.second);
      }
    }
  }
  return tot;
}

double threhold_greedy() {
  double tot = 0;
  int theta = log(Umax + 1);
  int kk = 1;
  double ppp = exp(kk);
  for (auto u : q) {
    if (u.first == 'w') {
      int max_id = -1;
      double max_w = -1;
      for (int v : tk) {
	if (!judge(u.second, v)) {
	  continue;
	}
	if (max_w < G[u.second][v]) {
	  max_w = G[u.second][v];
	  max_id = v;
	}
      }
      if (max_id > -1 && max_w > ppp) {
	tot += max_w;
	tk.erase(max_id);
      } else {
	wk.insert(u.second);
      }
    } else {
      int max_id = -1;
      double max_w = -1;
      for (int v : wk) {
	if (!judge(v, u.second)) {
	  continue;
	}
	if (max_w < G[v][u.second]) {
	  max_w = G[v][u.second];
	  max_id = v;
	}
      }
      if (max_id > -1 && max_w > ppp) {
	tot += max_w;
	wk.erase(max_id);
      } else {
	tk.insert(u.second);
      }
    }
  }
  return tot;
}

vector <pair <double, pair<int, int> > > pp;
bool vis_w[N], vis_t[N];
double tot_greedy() {
  double tot = 0;
  for (int i = 0; i < workerN; ++ i) {
    for (int j = 0; j < taskN; ++ j) {
      if (judge(i, j)) {
	pp.push_back(make_pair(G[i][j], make_pair(i, j)));
      }
    } 
  }
  sort(pp.rbegin(), pp.rend());
  for (auto v : pp) {
    if (vis_w[v.second.first] || vis_t[v.second.second]) {
      continue;
    }
    tot += v.first;
    vis_w[v.second.first] = vis_t[v.second.second] = true;
  }
  return tot;
}

double mytgoa_greedy() {
  double tot = 0;
  for (int i = 0; i < (workerN + taskN) / 2; ++ i) {
    auto u = q[i];
    if (u.first == 'w') {
      int max_id = -1;
      double max_w = -1;
      for (int v : tk) {
	if (!judge(u.second, v)) {
	  continue;
	}
	if (max_w < G[u.second][v]) {
	  max_w = G[u.second][v];
	  max_id = v;
	}
      }
      if (max_id > -1) {
	tot += max_w;
	tk.erase(max_id);
      } else {
	wk.insert(u.second);
      }
    } else {
      int max_id = -1;
      double max_w = -1;
      for (int v : wk) {
	if (!judge(v, u.second)) {
	  continue;
	}
	if (max_w < G[v][u.second]) {
	  max_w = G[v][u.second];
	  max_id = v;
	}
      }
      if (max_id > -1) {
	tot += max_w;
	wk.erase(max_id);
      } else {
	tk.insert(u.second);
      }
    }
  }
  wk.clear();
  tk.clear();
  for (int i = (workerN + taskN) / 2; i < workerN + taskN; ++ i) {
    auto u = q[i];
    if (u.first == 'w') {
      wk.insert(u.second);
   
      pp.clear();
      memset(vis_w, 0, sizeof vis_w);
      memset(vis_t, 0, sizeof vis_t);
      for (int i : wk) {
	for (int j : tk) {
	  if (judge(i, j)) {
	    pp.push_back(make_pair(G[i][j], make_pair(i, j)));
	  }
	} 
      }
      sort(pp.rbegin(), pp.rend());
      for (auto v : pp) {
	if (vis_w[v.second.first] || vis_t[v.second.second]) {
	  continue;
	}
	if (v.second.first == u.second) {
	  tot += v.first;
	  wk.erase(v.second.first);
	  tk.erase(v.second.second);
	}
	vis_w[v.second.first] = vis_t[v.second.second] = true;
      }
    } else {
      tk.insert(u.second);
      pp.clear();
      memset(vis_w, 0, sizeof vis_w);
      memset(vis_t, 0, sizeof vis_t);
      for (int i : wk) {
	for (int j : tk) {
	  if (judge(i, j)) {
	    pp.push_back(make_pair(G[i][j], make_pair(i, j)));
	  }
	}
      }
      sort(pp.rbegin(), pp.rend());
      for (auto v : pp) {
	if (vis_w[v.second.first] || vis_t[v.second.second]) {
	  continue;
	}
	if (v.second.second == u.second) {
	  tot += v.first;
	  tk.erase(v.second.second);
	  wk.erase(v.second.first);
	}
	vis_w[v.second.first] = vis_t[v.second.second] = true;
      }
    }
  }
  return tot;
}

vector<string> split(string fileName, char ch) {
  vector<string> vstr;
  int len = fileName.length();

  for (int i=0,j=0; i<=len; ++i) {
    if (i==len || fileName[i]==ch) {
      if (i > j) {
        string str = fileName.substr(j, i-j);
        // puts(str.c_str());
        // fflush(stdout);
        vstr.push_back(str);
      }
      j = i + 1;
    }
  }

  return vstr;
}

int strToInt(string s) {
  int len = s.length(), ret = 0;

  for (int i=0; i<len; ++i)
    ret = ret * 10 + s[i]-'0';

  return ret;
}

string getParaStr(string fileName, double mu) {
  vector<string> vname = split(fileName, '/');
  string info = vname[vname.size()-2];
  vector<string> vinfo = split(info, '_');
  double degrate = strToInt(vinfo[vinfo.size()-2]) * 1.0 / 1000.0;

  string ret = "degrate=" + to_string(degrate) + ",mu=" + to_string(mu);

  // for (int i=0; i<vname.size(); ++i)
  //  puts(vname[i].c_str());
  // for (int i=0; i<vinfo.size(); ++i)
  //  puts(vinfo[i].c_str());

  return ret;
}

int main(int argc, char * argv[]) {
  char s[2];
  int t;
  int id;
  double x, y, r, dt;
  int tmp;
  FILE *fp = fopen(argv[1], "r");
  freopen(argv[2], "r", stdin);
  scanf("%d%d%d%d", &workerN, &taskN, &Umax, &sumDegree);
  for (int i = 0; i < workerN; ++ i) {
    for (int j = 0; j < taskN; ++ j) {
      fscanf(fp, "%lf", &G[i][j]);
    }
  }
  for (int i = 0; i < workerN + taskN; ++ i) {
    scanf("%d%s", &t, s);
    if (s[0] == 'w') {
      scanf("%d%lf%lf%lf%d%d%lf", &id, &x, &y, &r, &tmp, &tmp, &dt);
      q.push_back(make_pair(s[0], id));
      worker[id] = node(t, x, y, r);
    } else {
      scanf("%d%lf%lf%d%lf", &id, &x, &y, &tmp, &dt);
      q.push_back(make_pair(s[0], id));
      task[id] = node(t, x, y, 0);
    }
  }
  double mu;
  sscanf(argv[3], "%lf", &mu);
  string edgeFileName = string(argv[2]);
  string paraStr = getParaStr(edgeFileName, mu);
/*
  double ans = 0;
  int numnum = log(Umax + 1);
  for (int i = 0; i < numnum; ++ i) {
    ans += threhold_greedy(i);
    //printf("%f\n", threhold_greedy(i));
  }
  printf("%f\n", ans / numnum);
  
  N = taskN;
  for (int i = 0; i < workerN; ++ i) {
    for (int j = 0; j < taskN; ++ j) {
       if (judge(i, j)) {
	 love[i][j] = G[i][j];
       }
    }
  }*/
    {
    double result = mytgoa_greedy();
    string paraStr = getParaStr(edgeFileName, mu);
    printf("Xuan %s %.6lf\n", paraStr.c_str(), result);
  }
  return 0;
}