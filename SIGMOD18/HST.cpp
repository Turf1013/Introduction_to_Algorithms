/**
	\author: 	Trasier
	\date: 		2017.10.14
*/
#include <bits/stdc++.h>
using namespace std;

#include "HST.h"
#include "input.h"

position_t *points;
int V;

void readInput() {
  cin >> V;
  points = new position_t[V];
  for (int i=0; i<V; ++i) {
    cin >> points[i].x >> points[i].y;
  }
}

void FreeMem() {
  delete[] points;
}

void test() {
  treeNode_t *root = NULL;

  HST_Construction(V, points, root);

  HST_dump(root);

  HST_delete(root);
}

int main(int argc, char **argv) {
  string execName("HST demo");

  if (argc > 1)
    freopen(argv[1], "r", stdin);
  if (argc > 2)
    freopen(argv[2], "w", stdout);

  readInput();

  test();

  FreeMem();

  return 0;
}
