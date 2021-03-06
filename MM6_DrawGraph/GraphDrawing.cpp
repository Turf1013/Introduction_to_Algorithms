// C++11
#include <bits/stdc++.h>
using namespace std;

class GraphDrawing {
public:
    static const int maxn = 701;

public:
    vector<int> plot(int N, const vector<int>& edges) {
		//perror("plot");
        vector<int> ret;
        set<pair<int,int> > st;
        pair<int,int> p;

        srand(123);
        for (int i = 0; i < N; ++i) {
            while (true) {
                p.first = rand() % maxn;
                p.second = rand() % maxn;
                if (st.count(p) == 0)
                    break;
            }
            st.insert(p);
            ret.push_back(p.first);
            ret.push_back(p.second);
        }
        return ret;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------
#include "monitor.h"


int main(int argc, char **argv) {
    GraphDrawing gd;
    int N;
    int E;
    program_t begProg, endProg;

    // if (argc > 1) 
    //     freopen(argv[1], "r", stdin);
    // if (argc > 2)
    //     freopen(argv[2], "w", stdout);

    //scanf("%d", &N);
    cin >> N;
    cin >> E;
    //scanf("%d", &E);
    vector<int> edges(E, 0);
    for (int i=0; i<E; ++i) {
        cin >> edges[i];
        //scanf("%d", &edges[i]);
    }
    
    save_time(begProg);
    vector<int> ret = gd.plot(N, edges);
    save_time(endProg);

    assert(ret.size() == N*2);
    //printf("%d\n", ret.size());
    cout << ret.size() << endl;
    for (int i=0; i<ret.size(); ++i)
        cout << ret[i] << endl;
       // printf("%d\n%d\n", ret[2*i], ret[2*i+1]);
    cout.flush();
    

    //double usedTime = calc_time(begProg, endProg);
    //printf("time = %.3lfs\n", usedTime);

    //fflush(stdout);

    return 0;
}
