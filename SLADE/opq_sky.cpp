#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const double EPS = 1e-8;
const double INF = 1e300;
int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0.) return 1;
    return -1;
}

//-----------------------------------------Input----------------------------------------------//

/* N : max number of tasks
 * M : max number of task bins
 */
const int maxBinNum = 10;
const int N = 1e6 + 7;
const int M = 1e6 + 7;
int n;
double t[N];
struct TaskBin {
    int l;
    double c, r;
    TaskBin (int _l = 0, double _c = 0, double _r = 0) : l(_l), c(_c), r(_r) {}
};
int m;
TaskBin bin[M];

void init() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%lf", &t[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++ i) {
        scanf("%d %lf %lf", &bin[i].l, &bin[i].c, &bin[i].r);
    }
}

//-----------------------------------------Greedy---------------------------------------------//

/* calculate the ratio
 */
double Ratio(const TaskBin &b, const vector <double> &V) {
    return b.c / min(- log(1. - b.r) * b.l, b.l <= n ? V[b.l - 1] : V[n - 1]);
}

/* Algorithm Greedy
 */
double greedy() {
    double cost = 0.;
    vector <double> ratio(m, 0.);
    vector <double> theta_sum(n, 0.);
    vector <double> theta(n, 0.);
    for (int i = 0; i < n; ++ i) {
        theta[i] = - log(1. - t[i]);
    }
    sort(theta.rbegin(), theta.rend());
    for (int i = 0; i < n; ++ i) {
        theta_sum[i] = theta[i] + (i ? theta_sum[i - 1] : 0.);
    }
    for (int i = 0; i < m; ++ i) {
        ratio[i] = Ratio(bin[i], theta_sum);
    }
    while (dcmp(theta[0]) > 0) {
        int pos = 0;
        for (int i = 0; i < m; ++ i) {
            if (ratio[i] < ratio[pos]) {
                pos = i;
            }
        }
        cost += bin[pos].c;
        for (int k = 0; k < bin[pos].l && k < n; ++ k) {
            theta[k] = max(0., theta[k] + log(1. - bin[pos].r));
        }
        sort(theta.rbegin(), theta.rend());
        for (int i = 0; i < n; ++ i) {
            theta_sum[i] = theta[i] + (i ? theta_sum[i - 1] : 0.);
        }
        for (int i = 0; i < m; ++ i) {
            ratio[i] = Ratio(bin[i], theta_sum);
        }
    }
    return cost;
}

//-------------------------------------------OPQ----------------------------------------------//

LL GCD(LL x, LL y) {
    return y == 0 ? x : GCD(y, x % y);
}

LL LCM(LL x, LL y) {
    LL g = GCD(x, y);
    return x * y / GCD(x, y);
}

void dfs(int x, double q, pair <LL, double> nw, double T, int num, set <pair <LL, double> > &S) {
    if (num >= maxBinNum) return;
    for (int k = x; k < m; ++ k) {
        pair <LL, double> tmp = make_pair(LCM(nw.first, bin[k].l), nw.second + bin[k].c / bin[k].l);
        bool flag = true;
        for (set <pair <LL, double> >::iterator iter = S.begin(); iter!=S.end(); ++iter) {
			pair<LL,double> p = *iter;
            if (p.first < tmp.first && p.second < tmp.second) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        if (dcmp(q - log(1. - bin[k].r) + log(1. - T)) >= 0) {
        	set <pair <LL, double> >::iterator iter = S.begin(), tmpIter;
        	while (iter != S.end()) {
        		pair<LL,double> p = *iter;
        		tmpIter = iter++;
        		if (p.first == tmp.first && p.second > tmp.second) {
					S.erase(tmpIter);
				}
        	}
            S.insert(tmp);
        } else {
            dfs(x, q - log(1. - bin[k].r), tmp, T, num + 1, S);
        }
    }
}

void build_OPQ(double threshold, set <pair <LL, double> > &S) {
    dfs(0, 0., make_pair(1ll, 0.), threshold, 0, S);
    set <pair <LL, double> > tmpS(S.begin(), S.end());
    set <pair <LL, double> >::iterator i, j;
    for (i=tmpS.begin(); i!=tmpS.end(); ++i) {
        for (j=tmpS.begin(); j!=tmpS.end(); ++j) {
            if (i == j) continue;
            if (i->first <= j->first && dcmp(i->second - j->second) <= 0) {
                S.erase(*j);
            }
        }
    }
}

void printQ(set <pair <LL, double> >& S) {
	priority_queue <pair <LL, double> > q;
    for (set <pair <LL, double> >::iterator iter = S.begin(); iter!=S.end(); ++iter) {
        q.push(*iter);
    }
	while (!q.empty()) {
		printf("(%lld,%.3lf) ", q.top().first, q.top().second);
		q.pop();
	}
	putchar('\n');
}

double OPQ(int N, double T) {
	printf("N = %d, thresh = %.3lf\n", N, T);
    double cost = 0.;
    set <pair <LL, double> > S;
    build_OPQ(T, S);
	printQ(S);
    priority_queue <pair <LL, double> > q;
    for (set <pair <LL, double> >::iterator iter = S.begin(); iter!=S.end(); ++iter) {
        q.push(*iter);
    }
    double cost_pre = INF;
    while (N) {
        while (!q.empty() && q.top().first > N) q.pop();
        pair <LL, double> u = q.top();
        int k = N / u.first;
        if (k * u.first * u.second > cost_pre) {
            cost += cost_pre;
            N = 0;
        } else {
            cost += k * u.first * u.second;
            N -= k * u.first;
            cost_pre = u.first * u.second;
        }
    }
    return cost;
}

//------------------------------------OPQ-Extended-------------------------------------------//

double OPQ_Extended() {
    double cost = 0.;
    sort(t, t + n);
    int alpha = log(- log(1. - t[0])) / log(2.);
    int beta = ceil(log(log(1. - t[n - 1]) / log(1. - t[0])) / log(2.));
    int pos = 0;
    for (int i = 0; i <= beta; ++ i) {
        int num = 0;
        while (pos < n && - log(1. - t[pos]) < pow(2, i + alpha + 1)) {
            pos ++;
            num ++;
        }
        if (pos == n) {
            cost += OPQ(num, t[n - 1]);
        } else {
            cost += OPQ(num, 1 - exp(-pow(2, alpha + i + 1)));
        }
    }
    return cost;
}

int main(int argc, char **argv) {

	if (argc > 1)
		freopen(argv[1], "r", stdin);
	if (argc > 2)
		freopen(argv[2], "w", stdout);

    init();
    double ans = 0;

    // greedy
    //ans = greedy();

    // OPQ
    ans = OPQ(n, t[0]);

    //OPQ-Extended
    //ans = OPQ_Extended();

    clock_t begTime, endTime;
  	begTime = clock();
  	endTime = clock();
  	double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
    printf("opqe %.3lf %.3lf\n", ans, usedTime);
    fflush(stdout);

    return 0;
}
