#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int e1, e2;
    long long c, f = 0;
    Edge(int e1, int e2, long long c) : e1(e1), e2(e2), c(c) {}
};

struct Dinic {
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> level, ptr, parent;
    queue<int> q;
    int n, s, t, m = 0;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
        parent.resize(n, -1);
    }

    void add(int u, int v, long long c) {
        edges.emplace_back(u, v, c);
        edges.emplace_back(v, u, 0);
        adj[u].push_back(m);
        adj[v].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q = queue<int>();
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                auto &e = edges[id];
                if (e.c - e.f <= 0 || level[e.e2] != -1) continue;
                level[e.e2] = level[v] + 1;
                q.push(e.e2);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;

        for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            auto &e = edges[id];
            if (level[e.e2] != level[v] + 1 || e.c - e.f <= 0) continue;

            parent[e.e2] = v;
            long long tr = dfs(e.e2, min(pushed, e.c - e.f));
            if (tr == 0) continue;

            e.f += tr;
            edges[id ^ 1].f -= tr;


            if (v == s) printPath(tr);

            return tr;
        }
        return 0;
    }

    void printPath(long long flow) {
        vector<int> path;
        int cur = t;
        while (cur != -1) {
            path.push_back(cur);
            cur = parent[cur];
        }
        reverse(path.begin(), path.end());

        cout << "Augmenting path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << "->";
        }
        cout << " | Flow: " << flow << "\n";
    }

    long long maxFlow() {
        long long flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            fill(parent.begin(), parent.end(), -1);
            while (long long pushed = dfs(s, LLONG_MAX)) {
                flow += pushed;
                fill(parent.begin(), parent.end(), -1);
                parent[s] = -1;
            }
        }
        return flow;
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic d(n, s, t);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        d.add(u, v, w);
    }

    long long f = d.maxFlow();
    cout << "Maximum Flow: " << f << "\n";
    return 0;
}
