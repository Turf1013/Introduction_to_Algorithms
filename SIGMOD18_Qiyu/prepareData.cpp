/**
	\author:	Trasier
	\date:		2017.10.30
*/
#include <bits/stdc++.h>
using namespace std;

const double inf = 1e30;
typedef pair<double,double> pdd;

const int maxn = 78565;
double g[maxn];
	
double Length(pdd& a, pdd& b) {
	return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

int main() {
	const double rmax = 2500;
	double sum = 0.0, avg = 0.0;
	double mxVal = -inf, mnVal = inf, tmp;
	
	freopen("roadNetwork.txt", "r", stdin);
	int nV, nE;
	vector<pdd> points;
	pdd p;
	
	cin >> nV >> nE;
	for (int i=0; i<nV; ++i) {
		cin >> p.first >> p.second;
		points.push_back(p);
	}
	
	vector<int> demands;
	ifstream fin("demands.txt", ios::in);
	int x;
	
	fin >> nV;
	for (int i=0; i<nV; ++i) {
		fin >> x;
		demands.push_back(x);
	}
	
	freopen("shortEdges.txt", "r", stdin);
	double mxg = -inf, mng = inf;
	cin >> nV;
	for (int i=0; i<nV; ++i) {
		for (int j=0; j<nV; ++j) {
			cin >> g[j];
			if (g[j] < 0)
				g[j] = inf;
			if (i != j && g[j]<inf) {
				mxg = max(mxg, g[j]);
				mng = min(mng, g[j]);
			}
		}
		
		tmp = 0;
		for (int j=0; j<nV; ++j) {
			if (g[j] <= rmax) {
				tmp += demands[j];
			}
		}
		
		sum += tmp;
		mxVal = max(mxVal, tmp);
		mnVal = min(mnVal, tmp);
	}
	printf("mxg = %.12lf, mng = %.12lf\n", mxg, mng);
	
	avg = sum / nV;
	
	printf("sum = %.2lf, avg = %.2lf, mx = %.2lf, mn = %.2lf\n", sum, avg, mxVal, mnVal);
	
	return 0;
}