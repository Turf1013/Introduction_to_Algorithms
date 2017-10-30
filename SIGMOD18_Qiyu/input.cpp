/**
	\author:	Trasier
	\date:		2017.10.27
*/
#include "input.h"

void read_roadNetwork(istream& fin, int& nV, int& nE, vector<pdd>& positions, vector<pair<pii,double> >& edges) {
	double x, y;
	int u, v;
	double w;

	fin >> nV >> nE;
	positions.clear();
	edges.clear();
	for (int i=0; i<nV; ++i) {
		fin >> x >> y;
		positions.push_back(make_pair(x, y));
	}
	// for (int i=0; i<nE; ++i) {
		// fin >> u >> v >> w;
		// edges.push_back(make_pair(make_pair(u, v), w));
	// }
}

void read_roadNetwork(string fileName, int& nV, int& nE, vector<pdd>& positions, vector<pair<pii,double> >& edges) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_roadNetwork(fin, nV, nE, positions, edges);

	fin.close();
}

void read_shortEdges(istream& fin, int& nV, vector<vector<double> >& dists) {
// #ifdef GLOBAL_DEBUG
	//printf("begin read shortEdges.\n");
	// fflush(stdout);
// #endif

	fin >> nV;
	dists.clear();
	vector<double> vtmp(nV, 0.0);
	for (int i=0; i<nV; ++i) {
		for (int j=0; j<nV; ++j) {
			fin >> vtmp[j];
			if (vtmp[j] < 0)
				vtmp[j] = inf;
		}
		dists.push_back(vtmp);
	}
// #ifdef GLOBAL_DEBUG
	//printf("begin read shortEdges.\n");
	//fflush(stdout);
// #endif
}

void read_shortEdges(string fileName, int& nV, vector<vector<double> >& dists) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_shortEdges(fin, nV, dists);

	fin.close();
}

void read_shortEdges(string fileName, int& nV, map<pii, double>& dists) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_shortEdges(fin, nV, dists);

	fin.close();
}

void read_shortEdges(istream& fin, int& nV, map<pii, double>& dists) {
	fin >> nV;
	dists.clear();
	double w;

	for (int i=0; i<nV; ++i) {
		for (int j=0; j<nV; ++j) {
			fin >> w;
			if (w >= 0)
				dists[make_pair(i,j)] = w;
		}
	}
}

void read_ruralDegree(istream& fin, int& nV, vector<double>& degs) {
	double tmp;
	degs.clear();
	fin >> nV;
	for (int i=0; i<nV; ++i) {
		fin >> tmp;
		degs.push_back(tmp);
	}
}

void read_ruralDegree(string fileName, int& nV, vector<double>& degs) {
	// #ifdef GLOBAL_DEBUG
	//printf("begin read degrees.\n");
	//fflush(stdout);
	// #endif

	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_ruralDegree(fin, nV, degs);

	fin.close();

	// #ifdef GLOBAL_DEBUG
	//printf("begin read degrees.\n");
	//fflush(stdout);
	// #endif
}

void read_chargers(istream& fin, int& chargerN, vector<charger_t>& chargers) {
	charger_t charger;
	chargers.clear();
	fin >> chargerN;
	for (int i=0; i<chargerN; ++i) {
		fin >> charger.p >> charger.f;
		chargers.push_back(charger);
	}
}

void read_chargers(string fileName, int& chargerN, vector<charger_t>& chargers) {
	//#ifdef GLOBAL_DEBUG
	//printf("begin read chargers.\n");
	//fflush(stdout);
	//#endif

	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_chargers(fin, chargerN, chargers);

	fin.close();

	//#ifdef GLOBAL_DEBUG
	//printf("begin read chargers.\n");
	//fflush(stdout);
	//#endif
}

void read_demands(istream& fin, int& nV, vector<int>& demands) {
	demands.clear();
	int tmp;
	fin >> nV;
	for (int i=0; i<nV; ++i) {
		fin >> tmp;
		demands.push_back(tmp);
	}
}

void read_demands(string fileName, int& nV, vector<int>& demands) {
//#ifdef GLOBAL_DEBUG
	//printf("begin read demmands.\n");
	//fflush(stdout);
	//#endif

	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_demands(fin, nV, demands);

	fin.close();

	//#ifdef GLOBAL_DEBUG
	//printf("begin read demmands.\n");
	//fflush(stdout);
	//#endif
}

void read_prices(istream& fin, int& nV, vector<double>& prices) {
	prices.clear();
	double tmp;
	fin >> nV;
	for (int i=0; i<nV; ++i) {
		fin >> tmp;
		prices.push_back(tmp);
	}
}

void read_prices(string fileName, int& nV, vector<double>& prices) {
	//#ifdef GLOBAL_DEBUG
	//printf("begin read prices.\n");
	//fflush(stdout);
	//#endif

	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_prices(fin, nV, prices);

	fin.close();

	//#ifdef GLOBAL_DEBUG
	//printf("begin read prices.\n");
	//fflush(stdout);
	// #endif
}

void read_input(istream& fin, double& lambda, double& alpha, double& rmax, double& B, int& K) {
	fin >> lambda >> alpha >> rmax >> B >> K;
}

void read_input(string fileName, double& lambda, double& alpha, double& rmax, double& B, int& K) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_input(fin, lambda, alpha, rmax, B, K);

	fin.close();
}

void read_points(string fileName, int& nV, int& nE, vector<point_t>& points) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_points(fin, nV, nE, points);

	fin.close();
}

void read_points(istream& fin, int& nV, int& nE, vector<point_t>& points) {
	point_t point;

	points.clear();
	fin >> nV >> nE;
	for (int i=0; i<nV; ++i) {
		point.id = i;
		fin >> point.x >> point.y;
		points.push_back(point);
	}
}

void read_all(string paraFileName, string priceFileName) {
	ifstream fin(paraFileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", paraFileName.c_str());
		exit(1);
	}

	read_all(fin, priceFileName);

	fin.close();
}

void read_all(istream& fin, string priceFileName) {
	string fileName;

	/**
		\step 0: parameter
	*/
	fileName = "./roadNetwork.txt";
	read_points(fileName, nV, nE, points);

	/**
		\step 1: read short edges
	*/
	fileName = "./shortEdges.txt";
	read_shortEdges(fileName, nV, dists);

	/**
		\step 2: read rural degree
	*/
	fileName = "./ruralDegrees.txt";
	vector<double> degs;
	read_ruralDegree(fileName, nV, degs);
	for (int i=0; i<nV; ++i) {
		points[i].w = degs[i];
	}

	/**
		\step 3: read demand
	*/
	fileName = "./demands.txt";
	vector<int> demands;
	read_demands(fileName, nV, demands);
	for (int i=0; i<nV; ++i) {
		points[i].d = demands[i];
	}

	/**
		\step 4: read prices
	*/
	fileName = priceFileName;
	vector<double> prices;
	read_prices(fileName, nV, prices);
	for (int i=0; i<nV; ++i) {
		points[i].ep = prices[i];
	}

	/**
		\step 5: read charger
	*/
	fileName = "./chargers.txt";
	read_chargers(fileName, chargerN, chargers);

	/**
		step 6: read input
	*/
	read_input(fin, lambda, alpha, rmax, B, K);
}

void read_incremental(string fileName, string priceFileName, vector<double>& bs) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_incremental(fin, priceFileName, bs);

	fin.close();
}

void read_incremental(istream& fin, string priceFileName, vector<double>& bs) {
	string fileName;

	/**
		\step 0: parameter
	*/
	fileName = "./roadNetwork.txt";
	read_points(fileName, nV, nE, points);

	/**
		\step 1: read short edges
	*/
	fileName = "./shortEdges.txt";
	read_shortEdges(fileName, nV, dists);

	/**
		\step 2: read rural degree
	*/
	fileName = "./ruralDegrees.txt";
	vector<double> degs;
	read_ruralDegree(fileName, nV, degs);
	for (int i=0; i<nV; ++i) {
		points[i].w = degs[i];
	}

	/**
		\step 3: read demand
	*/
	fileName = "./demands.txt";
	vector<int> demands;
	read_demands(fileName, nV, demands);
	for (int i=0; i<nV; ++i) {
		points[i].d = demands[i];
	}

	/**
		\step 4: read prices
	*/
	fileName = priceFileName;
	vector<double> prices;
	read_prices(fileName, nV, prices);
	for (int i=0; i<nV; ++i) {
		points[i].ep = prices[i];
	}

	/**
		\step 5: read charger
	*/
	fileName = "./chargers.txt";
	read_chargers(fileName, chargerN, chargers);

	fin >> lambda >> alpha >> rmax >> B >> K;
	int nB;
	fin >> nB;
	bs.clear();
	bs.push_back(B);
	double budget;
	for (int i=0; i<nB; ++i) {
		fin >> budget;
		bs.push_back(budget);
	}
}

#ifdef USE_ARRAY
void read_shortEdges(istream& fin, int& nV, double dists[][MAXN]) {
	//printf("begin read shortEdges.\n");
	//fflush(stdout);

	double w;

	fin >> nV;
	for (int i=0; i<nV; ++i) {
		for (int j=0; j<nV; ++j) {
			fin >> w;
			//*((double *)(dists + i*MAXN + j)) = w;
			if (w <= 0) w = inf;
			dists[i][j] = w;
		}
	}

	//printf("begin read shortEdges.\n");
	//fflush(stdout);
}

void read_shortEdges(string fileName, int& nV, double dists[][MAXN]) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_shortEdges(fin, nV, dists);

	fin.close();
}
#endif
