#include <bits/stdc++.h>
#include "monitor.h"
using namespace std;
const int NN = 3624;
const int EPS = 1e-8;
int workerN, taskN, sumDegree;
double Umax;

struct node {
  int tim, dl;
  double x, y, r, w;
  node (int _tim = 0, double _x = 0, double _y = 0, double _r = 0, int _dl = 0, double _w = 0) {
    tim = _tim;
    x = _x;
    y = _y;
    r = _r;
    dl = _dl;
    w = _w;
  }
};

vector <pair <char, int> > q;
vector <node> worker, task;

set <int> wk, tk;

double sqr(double x) {
  return x * x;
}

bool judge(int u, int v) {
  if (sqr(task[v].x - worker[u].x) + sqr(task[v].y - worker[u].y) <= sqr(worker[u].r)) {
    return task[v].tim < worker[u].tim + worker[u].dl && worker[u].tim < task[v].tim + task[v].dl;
  }
  return false;
}

vector <pair <double, pair<int, int> > > pp;
bool vis_w[NN], vis_t[NN];

bool used_w[NN], used_t[NN];

double comp(pair <double, pair<int, int> > a, pair <double, pair<int, int> > b) {
  if (a.first != b.first)
    return a.first > b.first;
  if (a.second.first != b.second.first)
    return a.second.first < b.second.first;
  return a.second.second < b.second.second;
}

double tgoa_greedy() {
  memset(used_w, false, sizeof(used_w));
  memset(used_t, false, sizeof(used_t));

  double tot = 0;
  for (int i = 0; i < q.size() / 2; ++ i) {
    auto u = q[i];
    if (u.first == 'w') {
      int max_id = -1;
      double max_w = 0.0;
      for (int v : tk) {
  if (!judge(u.second, v)) {
    continue;
  }
        double side = worker[u.second].w * task[v].w;
  if (max_w < side) {
    max_w = side;
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
      double max_w = 0.0;
      for (int v : wk) {
  if (!judge(v, u.second)) {
    continue;
  }
  double side = worker[v].w * task[u.second].w;
  if (max_w < side) {
    max_w = side;
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
    printf("%.4lf\n", tot);
  }

  wk.clear();
  tk.clear();
  for (int i = q.size() / 2; i < q.size(); ++ i) {
    auto u = q[i];
    if (u.first == 'w') {
      wk.insert(u.second);
   
      pp.clear();
      memset(vis_w, 0, sizeof vis_w);
      memset(vis_t, 0, sizeof vis_t);
      for (int i : wk) {
  for (int j : tk) {
    if (judge(i, j)) {
      pp.push_back(make_pair(worker[i].w * task[j].w, make_pair(i, j)));
      printf("(%.4lf,%.4lf) ", worker[i].w, task[j].w);
    }
  } 
      }
  putchar('\n');
      //sort(pp.rbegin(), pp.rend());
      sort(pp.begin(), pp.end(), comp);
      // printf("E.size() = %d\n", pp.size());
      // for (auto v:pp)
      //   printf("%.4lf ", v.first);
      // putchar('\n');
      for (auto v : pp) {
  if (vis_w[v.second.first] || vis_t[v.second.second]) {
    continue;
  }
  if (v.second.first == u.second) {
    if (!used_t[v.second.second]) {
      tot += v.first;
      used_w[v.second.first] = true;
      used_t[v.second.second] = true;
      break;
    }
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
      pp.push_back(make_pair(worker[i].w * task[j].w, make_pair(i, j)));
      printf("(%.4lf,%.4lf) ", worker[i].w, task[j].w);
    }
  }
      }

  putchar('\n');
      //sort(pp.rbegin(), pp.rend());
  sort(pp.begin(), pp.end(), comp);
      // printf("E.size() = %d\n", pp.size());
      // for (auto v:pp)
      //   printf("%.4lf ", v.first);
      // putchar('\n');
      for (auto v : pp) {
  if (vis_w[v.second.first] || vis_t[v.second.second]) {
    continue;
  }
  if (v.second.second == u.second) {
    if (!used_w[v.second.first]) {
      tot += v.first;
      used_w[v.second.first] = true;
      used_t[v.second.second] = true;
      break;
    }
  }
  vis_w[v.second.first] = vis_t[v.second.second] = true;
      }
    }
    printf("%.4lf\n", tot);
    #ifdef WATCH_MEM
    watchSolutionOnce(getpid(), usedMemory);
    #endif
  }
  return tot;
}

int main() {
  
  program_t begProg, endProg;
  save_time(begProg);
  char s[4];
  int t, cap, dl;
  double x, y, r, w;
  scanf("%d%d%lf%d", &workerN, &taskN, &Umax, &sumDegree);
  double tot = 0;
  for (int iter = 0; iter < workerN + taskN; ++ iter) {
    scanf("%d%s", &t, s);
    if (s[0] == 'w') {
      scanf("%lf%lf%lf%d%d%lf", &x, &y, &r, &cap, &dl, &w);
      for (int i = 0; i < cap; ++ i) {
  worker.push_back(node(t, x, y, r, dl, w));
  q.push_back(make_pair('w', worker.size() - 1));
      }
    } else {
      scanf("%lf%lf%d%lf", &x, &y, &dl, &w);
      task.push_back(node(t, x, y, 0, dl, w));
      q.push_back(make_pair('t', task.size() - 1));
    }
  }
  //printf("%d\n", q.size());
  assert(sumDegree == q.size());
  printf("%f\n", tgoa_greedy());
  
  save_time(endProg);

  double usedTime = calc_time(begProg, endProg);

  printf("time = %f\n", usedTime);
  return 0;
}
