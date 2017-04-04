/**
	\author: Trasier
	\date: 2017.04.04
*/
#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>
#include "monitor.h"

int main(int argc, char* argv[]) {
	string dataPath, fileName;

	if (argc > 1) {
		fileName = string(argv[1]);
		for (int i=dataPath.length()-1; i>=0; --i) {
			if (fileName[i] == '/') {
				dataPath = fileName.substr(0, i);
				break;
			}
		}
	} else {
		dataPath = "/home/turf/Code/Data/9";
	}

	

	return 0;
}