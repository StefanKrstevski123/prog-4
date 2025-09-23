#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e12;

int main() {
    int n, m;
    long long L;
    cin >> n >> m >> L;

    vector<vector<long long>> graph(n, vector<long long>(n, INF));
    vector<tuple<int,int,long long>> edges;

    for (int i = 0; i < n; i++) graph[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int a, b; long long s;
        cin >> a >> b >> s;
        --a; --b;
        graph[a][b] = min(graph[a][b], s);
        graph[b][a] = min(graph[b][a], s);
        edges.push_back({a, b, s});
    }

    auto floyd = [&](vector<vector<long long>> dist) {
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
        return dist;
    };

    auto dist = floyd(graph);

    auto total_cost = [&](vector<vector<long long>> &d) {
        long long total = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                total += (d[i][j] >= INF ? L : d[i][j]);
        return total;
    };

    long long initial_cost = total_cost(dist);
    long long max_cost = initial_cost;

    for (auto &e : edges) {
        int u, v; long long w;
        tie(u, v, w) = e;

        auto temp = graph;
        temp[u][v] = temp[v][u] = L;
        auto d2 = floyd(temp);
        long long cost2 = total_cost(d2);
        max_cost = max(max_cost, cost2);
    }

    cout << initial_cost << " " << max_cost << "\n";
    return 0;
}
