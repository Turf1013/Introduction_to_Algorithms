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
	for (int i=0; i<nE; ++i) {
		fin >> u >> v >> w;
		edges.push_back(make_pair(make_pair(u, v), w));
	}
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
	fin >> nV;
	dists.clear();
	vector<double> vtmp(0.0, nV);
	for (int i=0; i<nV; ++i) {
		for (int j=0; j<nV; ++j)
			fin >> vtmp[j];
		dists.push_back(vtmp);
	}
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
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_ruralDegree(fin, nV, degs);

	fin.close();
}

void read_chargers(istream& fin, int& chargerN, vector<charger_t>& chargers) {
	charger_t charger;
	chargers.clear();
	fin >> chargerN;
	for (int i=0; i<chargerN; ++i) {
		fin >> charger.f >> charger.p;
		chargers.push_back(charger);
	}
}

void read_chargers(string fileName, int& chargerN, vector<charger_t>& chargers) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_chargers(fin, chargerN, chargers);

	fin.close();
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
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	read_demands(fin, nV, demands);

	fin.close();
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

void read_all(string paraFileName) {
	ifstream fin(paraFileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", paraFileName.c_str());
		exit(1);
	}

	read_all(fin);

	fin.close();
}

void read_all(istream& fin) {
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
	fileName = "./demand.txt";
	vector<int> demands;
	read_demands(fileName, nV, demands);
	for (int i=0; i<nV; ++i) {
		points[i].d = demands[i];
	}

	/**
		\step 4: read charger
	*/
	fileName = "./chargers.txt";
	read_chargers(fileName, chargerN, chargers);

	/**
		step 5: read input
	*/
	read_input(fin, lambda, alpha, rmax, B, K);
}
