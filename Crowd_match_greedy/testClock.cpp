/**
	\author: Trasier
	\date: 2017.04.02
*/
#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>
#include "monitor.h"

int main(int argc, char* argv[]) {
	string dataPath, fileName, execPath, execName;

	if (argc > 2) {
		execPath = string(argv[1]);
		execName = execPath;
		for (int i=execPath.length()-1; i>=0; --i) {
			if (execPath[i] == '/') {
				execName = execPath.substr(i+1, execPath.length());
				break;
			}
		}
		dataPath = string(argv[2]);
	} else {
		printf("lack of paremeter\n");
		return -1;
	}
	
	string logName = execName + "_clk.log";
	freopen(logName.c_str(), "w", stdout);

	int pid, status;

	for (int i=0; i<10; ++i) {
		fileName = dataPath + "/order" + to_string(i) + ".txt";
		pid = fork();

		if (pid < 0) {
			printf("fork error\n");
		} else if (pid == 0) {
			execl(execPath.c_str(), execName.c_str(), fileName.c_str());
			printf("fileName = %s\n", fileName.c_str());
			//exit(0);
		} else {
			wait(&status);
		}
	}

	return 0;
}