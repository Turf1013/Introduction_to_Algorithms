#include <bits/stdc++.h>
using namespace std;

const int maxn = 80000;
int a[maxn][maxn];

int main() {
	// int *a;
	
	// a = new int[1LL*maxn*maxn];
	
	int k = 0;
	long long s = 0;
	
	for (int i=0; i<maxn; ++i) {
		for (int j=0; j<maxn; ++j) {
			a[i][j] = rand() % 1024;
			s += a[i][j];
			++k;
		}
	}
	
	cout << a << ' ' << s << endl;
	
	
	return 0;
}