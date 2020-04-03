#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 32);

class Dijkstra {
    class Node {
        public:
        int num;
        long long cost;

        Node(int v, long long c) {
            num = v;
            cost = c;
        }

        bool operator>(const Node &node) const { return cost > node.cost; }
    };

    private:
    vector<bool> checked;
    vector<long long> d;
    vector<unordered_map<int, long long>> adj;
    priority_queue<Node, deque<Node>, greater<Node>> nodes;

    public:
    Dijkstra(int n) {
        checked.resize(n, false);
        d.resize(n, INF);
        adj.resize(n);
    }

    long long get_distance(int nd) { return d[nd]; }

    void set_distances(int sp) {
        d[sp] = 0;
        Node snd(sp, 0);
        nodes.push(snd);

        while (!nodes.empty()) {
            Node cur = nodes.top();
            nodes.pop();
            checked[cur.num] = true;

            if (d[cur.num] < cur.cost) continue;

            for (auto e : adj[cur.num]) {
                int v = e.first;
                int w = e.second;

                if (checked[v]) {
                    continue;
                } else if (d[v] > d[cur.num] + w) {
                    d[v] = d[cur.num] + w;
                    Node nd(v, d[v]);
                    nodes.push(nd);
                }
            }
        }
    }

    void add_edge(int u, int v, int w) { adj[u][v] = w; }
};