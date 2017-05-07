#include <bits/stdc.h>
using namespace std;

#include "input.h"
#include "output.h"

#define LOCAL_DEBUG

void init() {
	
}

void solve() {
	init();
}

int main(int argc, char **argv) {
	string orderFileName;

	if (argc > 1)
		orderFileName = string(argv[1]);
	else
		orderFileName = "data.in";
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	solve();

	return 0;
}