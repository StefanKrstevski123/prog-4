#include <bits/stdc++.h>
using namespace std;

void dfs(int node, const vector<vector<pair<int,int>>>& G, vector<bool>& visited) {
    visited[node] = true;
    for (auto [neighbor, w] : G[node]) {
        if (!visited[neighbor]) dfs(neighbor, G, visited);
    }
}

bool isConnected(const vector<vector<pair<int,int>>>& G) {
    vector<bool> visited(G.size(), false);
    dfs(0, G, visited);
    return all_of(visited.begin(), visited.end(), [](bool v){ return v; });
}

int main() {
    srand(time(NULL));
    const int N = 50;
    vector<vector<pair<int,int>>> G(N);
    unordered_set<string> seenEdges;

    auto addEdge = [&](int u, int v, int w) {
        string e1 = to_string(u) + "-" + to_string(v);
        string e2 = to_string(v) + "-" + to_string(u);
        if (u != v && !seenEdges.count(e1) && !seenEdges.count(e2)) {
            G[u].push_back({v, w});
            seenEdges.insert(e1);
        }
    };


    for (int i = 0; i < N - 1; i++) {
        int w = (rand() % 106) - 5;
        addEdge(i, i + 1, w);
    }


    for (int i = 0; i < N; i++) {
        int edges = 1 + (rand() % 49);
        for (int j = 0; j < edges; j++) {
            int to = rand() % N;
            int w = (rand() % 106) - 5;
            addEdge(i, to, w);
        }
    }


    cout << (isConnected(G) ? "povrzan" : "nepovrzan") << endl;


    int e = 0;
    for (auto &v : G) e += v.size();
    cout << N << " " << e << endl;


    for (int u = 0; u < N; u++) {
        for (auto [v, w] : G[u]) {
            cout << u << " " << v << " " << w << endl;
        }
    }
    cout<<0;
    return 0;
}
