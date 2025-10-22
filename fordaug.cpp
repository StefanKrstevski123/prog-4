#include <bits/stdc++.h>
using namespace std;

int dfs(int u, int t, int flow, vector<int>& visited, vector<int>& parent,
        vector<vector<int>>& adj, vector<vector<int>>& cap)
{
    if (u == t) return flow;
    visited[u] = 1;

    for (int v : adj[u]) {
        if (!visited[v] && cap[u][v] > 0) {
            parent[v] = u;
            int pushed = dfs(v, t, min(flow, cap[u][v]), visited, parent, adj, cap);
            if (pushed > 0) return pushed;
        }
    }
    return 0;
}

int fordFulkerson(int n, int s, int t, vector<vector<int>>& adj, vector<vector<int>>& cap)
{
    int maxFlow = 0;

    while (true) {
        vector<int> visited(n, 0), parent(n, -1);
        int pushed = dfs(s, t, INT_MAX, visited, parent, adj, cap);
        if (!pushed) break;
        maxFlow += pushed;


        vector<int> path;
        for (int v = t; v != -1; v = parent[v])
            path.push_back(v);
        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << "->";
        }
        cout << endl;

        // Update residual capacities
        for (int v = t; parent[v] != -1; v = parent[v]) {
            int u = parent[v];
            cap[u][v] -= pushed;
            cap[v][u] += pushed;
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

    cout << "Max Flow: " << fordFulkerson(n, s, t, adj, cap) << endl;
    return 0;
}
