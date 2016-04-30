#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define DEBUG

const int maxn = 2000;
int HASH_SIZE = 1009;
int seed = 67;
int C[maxn];
string hstr[maxn];

inline int calcHash(const string& line) {
	unsigned int val = 0;
	int len = line.length();

	for (int i=0; i<len; ++i) val = val * seed + line[i];

	val %= HASH_SIZE;
	// #ifdef DEBUG
	// printf("%s %d\n", line.c_str(), val);
	// #endif
	return val;
}

void testHash(const string& filename) {
	ifstream fin(filename.c_str());
	string line;

	// skip header
	getline(fin, line);
	
	// calc topn;
	int topn = 0;
	{
		getline(fin, line);
		int len = line.length();
		for (int i=4; i<len; ++i) {
			if (isdigit(line[i]))
				topn = 10*topn + line[i]-'0';
			else
				break;
		}
	}

	memset(C, 0, sizeof(C));
	while (getline(fin, line)) {
		if (*line.rbegin() == '\n')	line.erase(line.length()-1);
		string slice = line.substr(line.length()-10, 10);
		int h = calcHash(slice);
		++C[h];
		if (C[h] > 1) {
			printf("%s %s\n", hstr[h].c_str(), slice.c_str());
		}
		hstr[h] = slice;
	}
	fin.close();

	int tot = 0, cnt = 0;
	for (int i=0; i<HASH_SIZE; ++i) {
		if (C[i] > 1) {
			tot += (C[i]-1) * (C[i] - 1);
			++cnt;
		}
	}

	printf("[TOP-%d]HASH_SIZE = %d, seed = %d, score = %d, cnt = %d\n", topn, HASH_SIZE, seed, tot, cnt);
}

int main(int argc, char **argv) {
	string filename("merge_top200.out");

	if (argc > 1) filename = string(argv[1]);
	if (argc > 2) sscanf(argv[2], "%d", &HASH_SIZE);
	if (argc > 3) sscanf(argv[3], "%d", &seed);

	testHash(filename);

	return 0;
}
