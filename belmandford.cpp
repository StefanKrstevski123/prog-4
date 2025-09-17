#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> BellmanFord(int start, int n, const vector<vector<pair<int,int>>>& G) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;
            for (auto [v, w] : G[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (dist[u] == INT_MAX) continue;
        for (auto [v, w] : G[u]) {
            if (dist[v] > dist[u] + w) {
                cout << "negativen\n";
                return {};
            }
        }
    }

    return dist;
}

int main() {
    int n, e;
    cin >> n >> e;
    vector<vector<pair<int,int>>> G(n);

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }

    int start;
    cin >> start;
    vector<int> dist = BellmanFord(start, n, G);

    if (!dist.empty()) {
        for (int i = 0; i < n; i++) {
            cout << i << ":" << dist[i] << "\n";
        }
    }

    return 0;
}
