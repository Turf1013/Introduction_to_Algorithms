/**
	\author:	Trasier
	\date:		2017.10.27
*/
#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
using namespace std;
#include "global.h"

void read_roadNetwork(istream& fin, int& nV, int& nE, vector<pdd>& positions, vector<pair<pii,double> >& edges);
void read_roadNetwork(string fileName, int& nV, int& nE, vector<pdd>& positions, vector<pair<pii,double> >& edges);
void read_shortEdges(istream& fin, int& nV, vector<vector<double> >& dists);
void read_shortEdges(string fileName, int& nV, vector<vector<double> >& dists);
void read_ruralDegree(istream& fin, int& nV, vector<double>& degs);
void read_ruralDegree(string fileName, int& nV, vector<double>& degs);
void read_chargers(istream& fin, int& chargerN, vector<charger_t>& chargers);
void read_chargers(string fileName, int& chargerN, vector<charger_t>& chargers);
void read_demands(istream& fin, int& nV, vector<int>& demands);
void read_demands(string fileName, int& nV, vector<int>& demands);
void read_input(istream& fin, double& lambda, double& alpha, double& rmax, double& B);
void read_input(string fileName, double& lambda, double& alpha, double& rmax, double& B);

#endif
