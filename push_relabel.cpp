#include <bits/stdc++.h>
using namespace std;//sss

void push(int u, int v, vector<int>& height, vector<int>& excess,
          vector<vector<int>>& capacity, vector<vector<int>>& flow,
          queue<int>& active) {
    int send = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += send;
    flow[v][u] -= send;
    excess[u] -= send;
    excess[v] += send;
    if (send > 0 && excess[v] == send)
        active.push(v);
}

void relabel(int u, vector<int>& height, vector<vector<int>>& capacity,
             vector<vector<int>>& flow) {
    int minHeight = INT_MAX;
    for (int v = 0; v < height.size(); v++) {
        if (capacity[u][v] - flow[u][v] > 0)
            minHeight = min(minHeight, height[v]);
    }
    if (minHeight < INT_MAX)
        height[u] = minHeight + 1;
}

void discharge(int u, vector<int>& height, vector<int>& excess,
               vector<vector<int>>& capacity, vector<vector<int>>& flow,
               vector<int>& nextNeighbor, queue<int>& active) {
    int n = height.size();
    while (excess[u] > 0) {
        if (nextNeighbor[u] < n) {
            int v = nextNeighbor[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(u, v, height, excess, capacity, flow, active);
            else
                nextNeighbor[u]++;
        } else {
            relabel(u, height, capacity, flow);
            nextNeighbor[u] = 0;
        }
    }
}

int maxFlow(int s, int t, vector<vector<int>>& capacity) {
    int n = capacity.size();
    vector<vector<int>> flow(n, vector<int>(n, 0));
    vector<int> height(n, 0), excess(n, 0), nextNeighbor(n, 0);
    queue<int> active;

    height[s] = n;
    excess[s] = INT_MAX;

    for (int v = 0; v < n; v++)
        if (capacity[s][v] > 0)
            push(s, v, height, excess, capacity, flow, active);

    while (!active.empty()) {
        int u = active.front();
        active.pop();
        if (u != s && u != t)
            discharge(u, height, excess, capacity, flow, nextNeighbor, active);
    }

    int result = 0;
    for (int i = 0; i < n; i++)
        result += flow[i][t];
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> capacity(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        capacity[u][v] = w;
    }
    int s, t;
    cin >> s >> t;
    cout << maxFlow(s, t, capacity);
}
