#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 32);

class FloydWarshall {
    private:
    int size;
    vector<vector<long long>> d;

    public:
    FloydWarshall(int n) {
        size = n;
        d.resize(n);
        for (int i = 0; i < n; ++i) {
            d[i].resize(n);
            for (int j = 0; j < n; ++j) {
                d[i][j] = i == j ? 0 : INF;
            }
        }
    }

    void add_edge(int u, int v, int w) { d[u][v] = w; }

    long long get_distance(int src, int dest) { return d[src][dest]; }

    void set_distances() {
        for (int k = 0; k < size; ++k)
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
                    if (d[i][k] < INF && d[k][j] < INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }

    bool has_negative_cycle() {
        for (int i = 0; i < size; ++i) {
            if (d[i][i]) return true;
        }
        return false;
    }
};