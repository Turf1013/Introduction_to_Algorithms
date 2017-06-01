#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> PII;
const int MAP_SZ = 100;
struct data_size {
    int N, M, R, C, D;
}small, large, used;

bool vis[MAP_SZ][MAP_SZ];
int tim[8192];

void init() {
    small.N = 20;
    small.D = 8;
    small.M = 4;
    small.R = 4;
    small.C = 5;
    large.N = 3000;
    large.M = 50;
    large.R = 600;
    large.D = 1000;
    large.C = 10;
    used = large;
}

PII next_pos() {
    int x, y;
    do {
        x = rand() % MAP_SZ;
        y = rand() % MAP_SZ;
    } while (vis[x][y]);
    vis[x][y] = true;
    return make_pair(x, y);
}

struct Order {
    int s;
    int t;
} order[8192];

PII rust[1024], dest[1024];

double sqr(int x) {
    return x * x;
}

double dist(int x, int y) {
    return sqrt(sqr(rust[x].first - dest[y].first) + sqr(rust[x].second - dest[y].second));
} 
int main(int argc, char **argv) {
    if (argc > 1)
        freopen(argv[1], "w", stdout);

    srand(time(NULL));
    init();
    int R = used.R;
    int M = used.M;
    int N = used.N;
    int D = used.D;
    int C = used.C;
    for (int i = 0; i < R; ++ i) {
        rust[i] = next_pos();
    }
    for (int i = 0; i < D; ++ i) {
        dest[i] = next_pos();
    }
    int t = 0;
    for (int i = 0; i < N; ++ i) {
        t += rand() & 1;
        tim[i] = t;
    }
    for (int i = 0; i < N; ++ i) {
        order[i].s = rand() % R + 1;
        order[i].t = rand() % D + 1;
        if (dist(order[i].s, order[i].t) > 100) -- i;
    }
    
    int a[3000];
    for (int i = 0; i < N; ++ i) {
        a[i] = i;
    }
    for (int tt = 0; tt < 1; ++ tt) {
        random_shuffle(a, a + N);
        printf("%d %d %d %d %d\n", R, D, M, C, N);
        for (int i = 0; i < R; ++ i) {
            printf("%d %d\n", rust[i].first, rust[i].second);
        }
        for (int i = 0; i < D; ++ i) {
            printf("%d %d\n", dest[i].first, dest[i].second);
        }
        for (int i = 0; i < N; ++ i) {
            printf("%d %d %d\n", tim[i], order[a[i]].s, order[a[i]].t);
        }
    }
  
    return 0;
}
