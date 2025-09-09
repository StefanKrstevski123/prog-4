#include <iostream>
#include <vector>

using namespace std;

void addEdge(vector<vector<int>>& adjMatric, int u, int v) {
    adjMatric [u][v] = 1;
}

void printMatric(const vector<vector<int>>& adjMatric) {
    for (int i = 0; i < adjMatric.size(); i++) {
        for (int j = 0; j < adjMatric.size(); j++) {
            cout << adjMatric[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int V = 6;
    vector<vector<int>> adjMatric(V, vector<int>(V, 0));

    addEdge(adjMatric, 0, 1);
    addEdge(adjMatric, 0, 2);
    addEdge(adjMatric, 1, 3);
    addEdge(adjMatric, 1, 4);
    addEdge(adjMatric, 2, 5);
    addEdge(adjMatric, 2, 6);

    printMatric(adjMatric);

    return 0;
}
