#include <cstring>
#include <cstdio>
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

#include "monitor.h" 
#define WATCH_MEM

typedef struct tuple {
	int type, s;
	int grid;
	tuple(int a, int b, int d) {
		type = a, s = b, grid = d;
	}
}tri;

bool com(const tri &a,const tri &b)
{
	return a.s<b.s;
}

#ifdef WATCH_MEM
int usedMemory = 0;
#endif
vector<tri> ob;
double ve = 1;//1minute 660m
int t = 96, g = 540;
int gridh = 30, gridw = 18;//map height/width in grid(1.708*2.226)
double f[288];
double Dw, Dr;
const int maxn = 600005;
vector<bool> used;
const char* opath = "rscenario_sort.in";
int main(int argc, char **argv)
{
	program_t begProg, endProg;
	FILE *fp1;

	if (argc > 1)
		fp1 = fopen(argv[1], "r");	
	else
		fp1 = fopen("rscenario.in", "r");
	FILE *fp2 = fopen("rscenario_sort.in", "w");
	//ostream fout(opath);

	//n records num
	int res = 0, n, x, y;
	fscanf(fp1, "%d%d%lf%lf%lf%d%d%d", &x, &y, &Dw, &Dr, &ve, &t, &gridh, &gridw);
	g = gridh*gridw;
	n = x + y;
	fprintf(fp2, "%d %d %f %f %f %d %d %d\n", x, y, Dw, Dr, ve, t, gridh, gridw);
	//x workernum y requestnum
	for (int i = 0;i<t;i++)
		f[i] = Dr;
	for (int i = 0;i<n;i++)
	{
		int t1, t2, t3;
		//double t3,t4;
		fscanf(fp1, "%d%d%d", &t1, &t2, &t3);//type window grid 
		ob.push_back(tri(t1, t2, t3));
	}
	 
	int deg = 0;
	sort(ob.begin(), ob.end(), com);
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif

	save_time(begProg);
	used.clear();
	used.resize(n, false);

	for (int i = 0;i<n;i++)
	{
		fprintf(fp2, "%d %d %d\n", ob[i].type, ob[i].s, ob[i].grid);
		if (ob[i].type == 0)//worker
		{
			int ind = -1;double mindis = 10000000;
			for (int j = 0;j<i;j++)
			{
				if (used[j] || ob[j].type == 0)continue;
				int ex, sw = ob[i].s, sr = ob[j].s, lw = ob[i].grid, lr = ob[j].grid;double dr = f[sr];//dr:function of sr
				int xw = lw%gridh, yw = lw / gridh, xr = lr%gridh, yr = lr / gridh;
				double s1 = sqrt((double)((xw - xr)*(xw - xr) + (yw - yr)*(yw - yr)));
				if (sr>sw) { continue; }
				else ex = sw - sr;
				if (dr - ex - s1 / ve >= 0)deg++;
				if (dr - ex - s1 / ve >= 0&& s1<mindis)
				{
					mindis = s1;
					ind = j;
				}
			}
			if (ind != -1) { used[ind] = used[i] = 1;res++; }
		}
		else
		{
			int ind = -1;double mindis = 10000000;
			for (int j = 0;j<i;j++)
			{
				if (used[j] || ob[j].type == 1)continue;
				int ex, sw = ob[j].s, sr = ob[i].s, lw = ob[j].grid, lr = ob[i].grid;double dr = f[sr];//dr:function of sr
				if (sr - sw > Dw)continue;
				int xw = lw%gridh, yw = lw / gridh, xr = lr%gridh, yr = lr / gridh;
				double s1 = sqrt((double)((xw - xr)*(xw - xr) + (yw - yr)*(yw - yr)));
				if (dr  - s1 / ve >= 0)deg++;
				if (dr - s1 / ve >= 0 && s1<mindis)
				{
					mindis = s1;
					ind = j;
				}
			}
			if (ind != -1) { used[ind] = used[i] = 1;res++; }
		}
	}
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
	
	fclose(fp2);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("Greedy %d %.4lf %d\n", res, usedTime, usedMemory/1024);
	#else
	printf("Greedy %d %.4lf\n", res, usedTime);
	#endif

	return 0;
}
