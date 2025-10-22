#include <bits/stdc++.h>
using namespace std;

int dfs(int u, int t, int flow, vector<int>& visited,
        vector<vector<int>>& adj, vector<vector<int>>& cap)
{
    if (u == t) return flow;
    visited[u] = 1;

    for (int v : adj[u]) {
        if (!visited[v] && cap[u][v] > 0) {
            int new_flow = min(flow, cap[u][v]);
            int pushed = dfs(v, t, new_flow, visited, adj, cap);
            if (pushed > 0) {
                cap[u][v] -= pushed;
                cap[v][u] += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int fordFulkerson(int n, int s, int t, vector<vector<int>>& adj, vector<vector<int>>& cap)
{
    int maxFlow = 0;
    while (true) {
        vector<int> visited(n, 0);
        int pushed = dfs(s, t, INT_MAX, visited, adj, cap);
        if (pushed == 0) break;
        maxFlow += pushed;
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

    cout << fordFulkerson(n, s, t, adj, cap) << endl;
    return 0;
}
