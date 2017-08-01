/**
	\author: 	Trasier
	\date:   	2017.8.1
	\source: 	KM
	\note: 		
*/
#ifndef KM_H
#define KM_H

static const double INF = 1e18;
static const double eps = 1e-6;
struct Hungarian_t {
	int *xy, *yx;
	double *lx, *ly;
	bool *S, *T;
	double *slack;
	int nx, ny;
	double **g;
	
	int dcmp(double x) {
		if (fabs(x) < eps) return 0;
		return x>0 ? 1:-1;
	}
	
	void init(int _nx, int _ny) {
		nx = _nx;
		ny = _ny;
		xy = new int[nx];
		yx = new int[ny];
		lx = new double[nx];
		ly = new double[ny];
		slack = new double[ny];
		S = new bool[nx];
		T = new bool[ny];
		g = new double*[nx];
		
		
		for (int i=0; i<nx; ++i) {
			g[i] = new double[ny];
			for (int j=0; j<ny; ++j)
				g[i][j] = 0.0;
		}
		
		for (int x=0; x<nx; ++x) {
			xy[x] = -1;
			lx[x] = 0.0;
			S[x] = false;
		}
		for (int y=0; y<ny; ++y) {
			yx[y] = -1;
			ly[y] = 0.0;
			T[y] = false;
		}
	}
	
	void init(int n) {
		init(n, n);
	}
	
	void clear() {
		delete[] xy;
		delete[] yx;
		delete[] lx;
		delete[] ly;
		delete[] S;
		delete[] T;
		delete[] slack;
		for (int i=0; i<nx; ++i)
			delete[] g[i];
		delete[] g;
	}
	
	void addEdge(int u, int v, double w) {
		assert(ux<nx && v<ny);
		g[u][v] = w;
	}
	
	bool dfs(int x) {
		S[x] = true;
		for (int y=0; y<ny; ++y) {
			if (T[y])  continue;
			
			double tmp = lx[x] + ly[y] - g[x][y];
			if (dcmp(tmp) == 0) {
				T[y] = true;
				if (yx[y]==-1 || dfs(yx[y])) {
					xy[x] = y;
					yx[y] = x;
					return true;
				}
			} else {
				slack[y] = min(slack[y], tmp);
			}
		}
		
		return false;
	}
	
	void update() {
		double mn = INF;
		
		for (int y=0; y<ny; ++y) {
			if (!T[y])
				mn = min(mn, slack[y]);
		}
		
		for (int x=0; x<nx; ++x) {
			if (S[x])
				lx[x] -= mn;
		}
		
		for (int y=0; y<ny; ++y) {
			if (T[y])
				ly[y] += mn;
			else
				slack[y] -= mn;
		}
	}
	
	void match() {
		for (int x=0; x<nx; ++x) {
			for (int y=0; y<ny; ++y) {
				lx[x] = max(lx[x], g[x][y]);
			}
		}
		
		for (int x=0; x<nx; ++x) {
			for (int y=0; y<ny; ++y) slack[y] = INF;
			
			for (;;) {
				for (int xx=0; xx<nx; ++xx) S[xx] = false;
				for (int yy=0; yy<ny; ++yy) T[yy] = false;
				if (dfs(x))
					break;
				else
					update();
			}
		}
	}
};

#endif