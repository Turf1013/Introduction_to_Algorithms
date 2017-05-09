
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <set>
#include <iomanip>
using namespace std;

#define EARTH_RADIUS 6378137
#define MAX_V 40000*144//not real num
#define MAX_n 100005//real num

typedef vector<double> VD;
typedef vector<VD> VVD;
typedef long long LL;
int W[MAX_V], R[MAX_V], woc[MAX_n], roc[MAX_n], wlb[MAX_V], rlb[MAX_V];//worker occupied request occupied
int Sw[MAX_n], Lw[MAX_n], Sr[MAX_n], Lr[MAX_n];//real scenario
int Lm[MAX_n], Rm[MAX_n];
double f[288];
int t = 96, g = 540;//windownum gridnum
int gridh = 30, gridw = 18;//map height/width in grid(1.708*2.226)
double ve = 1,Dw,Dr;//velocity: grid num per window
int main()
{
	int x, y;
	
	FILE *fp0 = fopen("prediction.in", "r");
	fscanf(fp0, "%d%d%lf%lf%lf%d%d%d", &x, &y, &Dw, &Dr, &ve, &t, &gridh, &gridw);
	g = gridh*gridw;
	FILE *fp2 = fopen("guide.in", "r");
	for (int i = 0;i<t;i++)
		f[i] = Dr;//deadline request
	printf("deadline=%f,velocity=%f\n", f[0], ve);
	
	x = 0, y = 0;//Workerset size Request size
	for (int i = 0;i<t*g;i++)
	{
		int t1, t2, t3, t4;//window grid worker request
		fscanf(fp0, "%d%d%d%d", &t1, &t2, &t3, &t4);
		x += t3, y += t4;
		int ind = t1*g + t2;
		W[ind] = x;R[ind] = y;
		if (ind != 0)wlb[ind] = W[ind - 1], rlb[ind] = R[ind - 1];
	}
	printf("%d %d %d\n", x + y, x, y);
	//for(int i=0;i<t*g;i++)
	//	printf("%d %d\n",W[i],R[i]);
	memset(Lm, -1, sizeof(Lm));
	memset(Rm, -1, sizeof(Rm));
	int p, q, n;
	while (fscanf(fp2, "%d%d", &p, &q)==2)
	{
		Lm[p] = q;Rm[q] = p;
	}
	printf("guide end...\n");
	
	FILE *fp1 = fopen("rscenario.in", "r");
	fscanf(fp1, "%d%d%lf%lf%lf%d%d%d", &x, &y, &Dw, &Dr, &ve, &t, &gridh, &gridw);
	//n records num
	int res = 0;
	n = x + y;
	x = y = 0;//x workernum y requestnum
	
	for (int i = 0;i<n;i++)
	{
		int t1, t2, t3, ind, loc;
		fscanf(fp1, "%d%d%d", &t1, &t2, &t3);//type window grid 
		ind = t2*g + t3;
		if (t1 == 0)//worker
		{
			Sw[x] = t2;Lw[x++] = t3;
			int j = wlb[ind];
			wlb[ind]++;
			if (j<W[ind])
			{
				if (woc[j] == 0 && Lm[j] != -1)
				{
					woc[j] = 1;
					if (roc[Lm[j]] == 1) {
						//woc[j] = roc[Lm[j]] = -1;
						res++;
					}
				}
			}
		}
		else//request
		{
			Sr[y] = t2;Lr[y++] = t3;
			int j = rlb[ind];
			rlb[ind]++;
			if (j<R[ind])
			{
				if (roc[j] == 0 && Rm[j] != -1)
				{
					roc[j] = 1;
					if (woc[Rm[j]] == 1) {
						//roc[j] = woc[Rm[j]] = -1;
						res++;
					}
				}
			}
		}
	}
	
	
	printf("Polar: %d\n", res);
	
	return 0;
}

