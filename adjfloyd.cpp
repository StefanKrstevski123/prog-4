#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<unordered_map<int,int>> adjList(n);

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u][v] = w;
    }

    for (int i = 0; i < n; i++) {
        if (!adjList[i].count(i)) adjList[i][i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!adjList[i].count(k)) continue;
            for (int j = 0; j < n; j++) {
                if (!adjList[k].count(j)) continue;
                int newDist = adjList[i][k] + adjList[k][j];
                if (!adjList[i].count(j) || adjList[i][j] > newDist) {
                    adjList[i][j] = newDist;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!adjList[i].count(j)) cout << "@ ";
            else cout << adjList[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
