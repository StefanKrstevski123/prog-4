#include <bits/stdc++.h>
using namespace std;

int bfs(int s, int t, vector<int>& parent,
        vector<vector<int>>& adj, vector<vector<int>>& cap)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adj[u]) {
            if (parent[v] == -1 && cap[u][v] > 0) {
                parent[v] = u;
                int new_flow = min(flow, cap[u][v]);
                if (v == t) return new_flow;
                q.push({v, new_flow});
            }
        }
    }
    return 0;
}

int edmondsKarp(int n, int s, int t, vector<vector<int>>& adj, vector<vector<int>>& cap)
{
    int maxFlow = 0;
    vector<int> parent(n);
    int flow;

    while ((flow = bfs(s, t, parent, adj, cap))) {
        maxFlow += flow;
        int v = t;
        while (v != s) {
            int u = parent[v];
            cap[u][v] -= flow;
            cap[v][u] += flow;
            v = u;
        }
    }
    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<vector<int>> cap(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
        adj[v].push_back(u);
        cap[u][v] += w;
    }

    int s, t;
    cin >> s >> t;

    cout << edmondsKarp(n, s, t, adj, cap) << endl;
    return 0;
}

