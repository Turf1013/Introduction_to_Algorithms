#include <bits/stdc++.h>
using namespace std;

int main() {
	ifstream fin("roadNetwork.txt", ios::in);
	int nV, nE = 0;
	double x;
	
	fin >> nV;
	for (int i=0; i<nV; ++i) {
		for (int j=0; j<nV; ++j) {
			fin >> x;
			if (i!=j && x>=0)
				++nE;
		}
	}
	
	cout << nV << ' ' << nE << endl;
	
	return 0;
}