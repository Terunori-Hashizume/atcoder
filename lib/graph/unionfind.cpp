#include <bits/stdc++.h>
using namespace std;

class UnionFind {
    public:
    vector<int> rank, parent, size;

    UnionFind();
    UnionFind(int n) {
        rank.resize(n, 0);
        parent.resize(n, 0);
        size.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
            size[i] = 1;
        }
    }

    int getSize(int x) { return size[root(x)]; }

    bool same(int x, int y) { return root(x) == root(y); }

    void unite(int x, int y) {
        int a = root(x), b = root(y);
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) ++rank[a];
        size[a] += size[b];
    }

    int root(int x) {
        if (parent[x] != x) {
            parent[x] = root(parent[x]);
        }
        return parent[x];
    }
};