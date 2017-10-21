/**
	1. program name
	2. \author: Trasier
	3. \date:   2017.10.5
*/
#include <glpk.h>
#include <bits/stdc++.h>
using namespace std;

#include "global.h"
#include "input.h"
#include "output.h"
#include "monitor.h"

#define USE_SIMPLE
// #define LOCAL_DEBUG
// #define WATCH_MEM

int taskN, binN;
double* threshs;
bin_t* bins;
double* thetas;
double *vals;
int *inds;
int usedMem = -1;

void initial() {
  double theta;
	thetas = new double[taskN];
	for (int i=0; i<taskN; ++i) {
    thetas[i] = -log(1.0 - threshs[i]);
	}
	sort(thetas, thetas+taskN);
  vals = new double[taskN+1];
  inds = new int[taskN+1];
  for (int i=0; i<=taskN; ++i) {
    inds[i] = i;
    vals[i] = 0;
  }
}

void freeMem() {
  delete[] threshs;
	delete[] bins;
  delete[] thetas;
  delete[] vals;
  delete[] inds;
}

void add_col(glp_prob* lp) {
  int colN = (taskN*2 - (binN-1)) * binN / 2, colId = 1;

  #ifdef LOCAL_DEBUG
  printf("colN = %d, ", colN);
  fflush(stdout);
  #endif

  glp_add_cols(lp, colN);
  for (int i=0; i<binN; ++i) {
    double r = -log(1.0 - bins[i].r);
    for (int j=1; j<=bins[i].l; ++j) vals[j] = r;
    for (int j=1; j+bins[i].l-1<=taskN; ++j,++colId) {
      vals[j-1] = 0;
      vals[j+bins[i].l-1] = r;
      glp_set_mat_col(lp, colId, taskN, inds, vals);
      glp_set_col_bnds(lp, colId, GLP_LO, 0.0, 0.0);
      glp_set_obj_coef(lp, colId, bins[i].c);
    }
    for (int j=taskN-bins[i].l; j<=taskN; ++j)
      vals[j] = 0;
  }

  #ifdef LOCAL_DEBUG
  printf("colId = %d\n", colId);
  #endif

  assert(colId == colN+1);
}

double ans;

bool check(glp_prob *lp) {
  int colN = (taskN*2 - (binN-1)) * binN / 2, colId = 1;
  double *sum = new double[taskN+1];

  memset(sum, 0, sizeof(double)*(taskN+1));
  for (int i=0; i<binN; ++i) {
    double r = -log(1.0 - bins[i].r);
    for (int j=1; j+bins[i].l-1<=taskN; ++j,++colId) {
      #ifdef USE_SIMPLE
      double x = glp_get_col_prim(lp, colId);
      #else
      double x = glp_ipt_col_prim(lp, colId);
      #endif
      int tmp = ceil(x);
      for (int k=0; k<bins[i].l; ++k)
        sum[j+k] += r * tmp;
    }
  }
  #ifdef LOCAL_DEBUG
  for (int i=1; i<=taskN; ++i) {
      printf("cur = %.2lf, theta = %.2lf\n", sum[i], thetas[i-1]);
  }
  #endif

  bool ret = true;

  for (int i=1; i<=taskN; ++i) {
    // if (sum[i] < thetas[i-1]) {
    //   double r = -log(1.0 - bins[0].r);
    //   int tmp = ceil((thetas[i-1] - sum[i]) / r);
    //   ans += tmp * bins[0].c;
    //   sum[i] += tmp * r;
    // }
    if (sum[i] < thetas[i-1]) {
      ret = false;
      break;
    }
  }

  delete[] sum;

  return ret;
}

double getResult(glp_prob *lp) {
  double ret = 0.;
  int colN = (taskN*2 - (binN-1)) * binN / 2, colId = 1;

  for (int i=0; i<binN; ++i) {
    double r = -log(1.0 - bins[i].r);
    for (int j=1; j+bins[i].l-1<=taskN; ++j,++colId) {
      #ifdef USE_SIMPLE
      double x = glp_get_col_prim(lp, colId);
      #else
      double x = glp_ipt_col_prim(lp, colId);
      #endif
      ret += bins[i].c * ceil(x);
      #ifdef LOCAL_DEBUG
      printf("x%d = %.2lf\n", colId, x);
      #endif
    }
  }
  ans = ret;
  assert(check(lp));
  ret = ans;

  return ret;
}

double solve(string progName) {
  double ret = 0.0;

 #ifdef LOCAL_DEBUG
  printf("progName = %s\n", progName.c_str());
 #endif

  glp_prob *lp;

  lp = glp_create_prob();
  glp_set_prob_name(lp, progName.c_str());
  glp_set_obj_dir(lp, GLP_MIN);
  glp_add_rows(lp, taskN);
  for (int i=1; i<=taskN; ++i) {
    glp_set_row_bnds(lp, i, GLP_LO, thetas[i-1], thetas[i-1]);
  }
  add_col(lp);

  int colN = (taskN*2 - (binN-1)) * binN / 2;
  #ifdef USE_SIMPLE
  glp_smcp parm;
  glp_init_smcp(&parm);
  parm.msg_lev = GLP_MSG_ERR;
  parm.tol_bnd = 5e-5;
  parm.it_lim = 2e5;
  // parm.msg_lev = GLP_MSG_ALL;
  // parm.meth = GLP_PRIMAL;
  // parm.pricing = GLP_PT_PSE;
  // parm.r_test = GLP_RT_HAR;
  // parm.tol_bnd = 1e-5;
  // parm.tol_dj = 1e-5;
  // parm.tol_piv = 1e-9;
  // parm.obj_ll = -DBL_MAX;
  // parm.obj_ul = DBL_MAX;
  // parm.it_lim = 1e5;
  // parm.tm_lim = INT_MAX;
  // parm.out_frq = 500;
  // parm.out_dly = 0;
  // parm.presolve = GLP_OFF;
  glp_simplex(lp, &parm);
  #else
  glp_interior(lp, NULL);
  #endif
  ret = getResult(lp);
  glp_delete_prob(lp);

  #ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMem);
  #endif

	return ret;
}

string getProgName(char *s) {
  string ret = "^";
  int len = strlen(s), i;
  for (i=len-1; i>=0; --i) {
    if (s[i] == '/')
      break;
  }
  --i;
  ret += s[len-6];
  ret += s[len-5];
  for (int k=2; k>0; --k) {
	  while (i>=0 && s[i]!='_') {
      ret += s[i];
      --i;
    }
	  --i;
  }
  while (i>=0 && isdigit(s[i])) {
    ret += s[i];
    --i;
  }

  return ret;
}

int main(int argc, char **argv) {
	string execName = "base", progName = "cip";
	double result, usedTime = -1;

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
    progName = getProgName(argv[1]);
	  //printf("progName = %s\n", progName.c_str());
  }
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	/**
		\step 1: read the input
	*/
	readInput(taskN, threshs, binN, bins);

	/**
		\step 1.5: initial the group
	*/
	initial();


	/**
		\step 2: solve the problem and return the result
	*/
	clock_t begTime, endTime;
	begTime = clock();
	result = solve(progName);
	endTime = clock();
	usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMem);
	#endif


	/**
		\step 3: print the result
	*/
	dumpResult(execName, result, usedTime, usedMem/1024.0);


	/**
		\step 4: free the memoroy
	*/
	freeMem();

	return 0;
}
