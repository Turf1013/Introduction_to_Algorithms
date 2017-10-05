/**
	1. output data
	2. \author: Trasier
	3. \date:   2017.10.5
*/
#ifndef OUTPUT_H
#define OUTPUT_H

#include <bits/stdc++.h>
using namespace std;

#include "input.h"

void dumpResult(string progName, double result, double usedTime=-1.0, double usedMem=-1.0);

void dumpResult(string progName, double result, double usedTime, double usedMem) {
	printf("%s %.3lf", progName.c_str(), result);
	if (usedTime >= 0)
		printf(" %.3lf", usedTime);
	if (usedMem >= 0)
		printf(" %.3lf", usedMem);
	putchar('\n');
	fflush(stdout);
}

#endif
