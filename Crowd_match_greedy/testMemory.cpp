/**
	\author: Trasier
	\date: 2017.04.02
*/
#include <bits/stdc++.h>
using namespace std;
#include <unistd.h>
#include "monitor.h"

int main(int argc, char* argv[]) {

	string dataPath, fileName, execName;
	program_t begProg, endProg;

	if (argc > 2) {
		execName = string(argv[1]);
		fileName = string(argv[2]);
		for (int i=dataPath.length()-1; i>=0; --i) {
			if (fileName[i] == '/') {
				dataPath = fileName.substr(0, i);
				break;
			}
		}
	} else {
		printf("lack of paremeter\n");
		return -1;
	}

	string logName = execName + "_mem.log";
	freopen(logName.c_str(), "w", stdout);

	int pid;

	for (int i=0; i<100; ++i) {
		fileName = dataPath + "/order" + to_string(i) + ".txt";
		pid = fork();

		if (pid < 0) {
			printf("fork error\n");
		} else if (pid == 0) {
			execl(execName.c_str(), fileName.c_str());
			exit(0);
		}
		wait(pid, NULL, 0);
	}

	return 0;
}