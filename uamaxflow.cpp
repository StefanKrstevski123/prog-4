#include <bits/stdc++.h>
using namespace std;

int BFS(int s, int t, vector<int>& parent,
        const vector<vector<int>>& adjList,
        vector<vector<int>>& cap)
{
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int v : adjList[u]) {
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

int EdmondsKarp(int n, int s, int t,
                const vector<vector<int>>& adjList,
                vector<vector<int>> cap)
{
    int max_flow = 0;
    vector<int> parent(n);
    int flow;

    while ((flow = BFS(s, t, parent, adjList, cap))) {
        max_flow += flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            cap[prev][cur] -= flow;
            cap[cur][prev] += flow;
            cur = prev;
        }
    }
    return max_flow;
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<int>> adjList(n);
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    vector<tuple<int,int,int>> edges;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        capacity[u][v] = w;
        edges.push_back({u, v, w});
    }

    int bestFlow = INT_MAX;
    pair<int,int> bestEdge;

    for (auto [u, v, w] : edges) {

        auto tempCap = capacity;
        tempCap[u][v] = 0;

        int flow = EdmondsKarp(n, s, t, adjList, tempCap);
        if (flow < bestFlow) {
            bestFlow = flow;
            bestEdge = {u, v};
        }
    }

    cout << bestEdge.first << " -> " << bestEdge.second << "\n";
    cout << "nov max flow: " << bestFlow << "\n";
}
