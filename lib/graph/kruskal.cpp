#include <bits/stdc++.h>
using namespace std;

class Kruskal {
    class Edge {
        public:
        int u, v, w;
        Edge(int source, int target, int cost) {
            u = source;
            v = target;
            w = cost;
        }
        bool operator<(const Edge &e) const { return w < e.w; }
    };

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

    private:
    int size;
    vector<Edge> edges;

    public:
    int total_cost;
    vector<Edge> mst;

    Kruskal(int n) {
        total_cost = 0;
        size = n;
    }

    void add_edge(int u, int v, int w) {
        Edge e(u, v, w);
        edges.push_back(e);
    }

    void set_mst() {
        UnionFind uf(size);

        sort(edges.begin(), edges.end());
        for (Edge e : edges) {
            if (!uf.same(e.u, e.v)) {
                total_cost += e.w;
                mst.push_back(e);
                uf.unite(e.u, e.v);
            }
        }
    }
};
