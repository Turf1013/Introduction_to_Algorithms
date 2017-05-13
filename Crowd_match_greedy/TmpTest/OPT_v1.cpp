#include <bits/stdc++.h>
#include "monitor.h"
using namespace std;

const int EPS = 1e-8;
int usedMemory;
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

vector <node> worker, task;

double sqr(double x) {
  return x * x;
}

bool judge(int u, int v) {
  if (sqr(task[v].x - worker[u].x) + sqr(task[v].y - worker[u].y) < sqr(worker[u].r) + EPS) {
    return task[v].tim < worker[u].tim + worker[u].dl && worker[u].tim < task[v].tim + task[v].dl;
  }
  return false;
}

const int MAXN = 10000+25;
const double INF = 1e20;
double love[MAXN][MAXN];   // 记录每个妹子和每个男生的好感度
double ex_girl[MAXN];      // 每个妹子的期望值
double ex_boy[MAXN];       // 每个男生的期望值
bool vis_girl[MAXN];    // 记录每一轮匹配匹配过的女生
bool vis_boy[MAXN];     // 记录每一轮匹配匹配过的男生
int match[MAXN];        // 记录每个男生匹配到的妹子 如果没有则为-1
double slack[MAXN];        // 记录每个汉子如果能被妹子倾心最少还需要多少期望值

int N;


bool dfs(int girl)
{
    vis_girl[girl] = true;

    for (int boy = 0; boy < N; ++boy) {

        if (vis_boy[boy]) continue; // 每一轮匹配 每个男生只尝试一次

        double gap = ex_girl[girl] + ex_boy[boy] - love[girl][boy];

        if (fabs(gap) < 1e-8) {  // 如果符合要求
            vis_boy[boy] = true;
            if (match[boy] == -1 || dfs( match[boy] )) {    // 找到一个没有匹配的男生 或者该男生的妹子可以找到其他人
                match[boy] = girl;
                return true;
            }
        } else {
            slack[boy] = min(slack[boy], gap);  // slack 可以理解为该男生要得到女生的倾心 还需多少期望值 取最小值 备胎的样子【捂脸
        }
    }

    return false;
}

double KM()
{
    memset(match, -1, sizeof match);    // 初始每个男生都没有匹配的女生
    memset(ex_boy, 0, sizeof ex_boy);   // 初始每个男生的期望值为0

    // 每个女生的初始期望值是与她相连的男生最大的好感度
    for (int i = 0; i < N; ++i) {
        ex_girl[i] = love[i][0];
        for (int j = 1; j < N; ++j) {
            ex_girl[i] = max(ex_girl[i], love[i][j]);
        }
    }

    // 尝试为每一个女生解决归宿问题
    for (int i = 0; i < N; ++i) {

        fill(slack, slack + N, INF);    // 因为要取最小值 初始化为无穷大

        while (1) {
            // 为每个女生解决归宿问题的方法是 ：如果找不到就降低期望值，直到找到为止

            // 记录每轮匹配中男生女生是否被尝试匹配过
            memset(vis_girl, false, sizeof vis_girl);
            memset(vis_boy, false, sizeof vis_boy);

            if (dfs(i)) break;  // 找到归宿 退出

            // 如果不能找到 就降低期望值
            // 最小可降低的期望值
            double d = INF;
            for (int j = 0; j < N; ++j)
                if (!vis_boy[j]) d = min(d, slack[j]);

            for (int j = 0; j < N; ++j) {
                // 所有访问过的女生降低期望值
                if (vis_girl[j]) ex_girl[j] -= d;

                // 所有访问过的男生增加期望值
                if (vis_boy[j]) ex_boy[j] += d;
                // 没有访问过的boy 因为girl们的期望值降低，距离得到女生倾心又进了一步！
                else slack[j] -= d;
            }
        }
    }
    
    double res = 0;
    for (int i = 0; i < N; ++i)
        res += love[ match[i] ][i];

    #ifdef WATCH_MEM
    watchSolutionOnce(getpid(), usedMemory);
    #endif
    return res;
}


int main(int argc, char **argv) {
  program_t begProg, endProg;
  save_time(begProg);
  char s[4];
  int t, cap, dl;
  double x, y, r, w;

  freopen(argv[1], "r", stdin);
  scanf("%d%d%lf%d", &workerN, &taskN, &Umax, &sumDegree);

  for (int iter = 0; iter < workerN + taskN; ++ iter) {
    scanf("%d%s", &t, s);
    if (s[0] == 'w') {
      scanf("%lf%lf%lf%d%d%lf", &x, &y, &r, &cap, &dl, &w);
      for (int i = 0; i < cap; ++ i) {
	worker.push_back(node(t, x, y, r, dl, w));
      }
    } else {
      scanf("%lf%lf%d%lf", &x, &y, &dl, &w);
      task.push_back(node(t, x, y, 0, dl, w));
    }
  }
  N = max(worker.size(), task.size());
  for (int i = 0; i < N; ++ i) {
    for (int j = 0; j < N; ++ j) {
      if (i >= worker.size() || j >= task.size()) {
	love[i][j] = 0;
      } else if (judge(i, j)) {
	love[i][j] = worker[i].w * task[j].w;
      } else {
	love[i][j] = 0;
      }
    }
  }
  
  double utility = KM();

  save_time(endProg);

  double usedTime = calc_time(begProg, endProg);
  #ifdef WATCH_MEM
  printf("OPT %.6lf %.6lf %d\n", utility, usedTime, usedMemory);
  #else
  printf("OPT %.6lf %.6lf\n", utility, usedTime);
  #endif
  return 0;
}