#include <bits/stdc++.h>
using namespace std;

vector<int> shortestPath(int V, vector<vector<int>> &edges, int src) {
    vector<vector<int>> adj(V);
    for (auto &e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }

    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            if (dist[node] + 1 < dist[neighbor]) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }

    return dist;
}

int main() {
    int V = 9;
    vector<vector<int>> edges = {
        {0, 1}, {0, 3}, {3, 4}, {4, 5},
        {5, 6}, {1, 2}, {2, 6}, {6, 7}, {7, 8}
    };
    int src = 0;

    vector<int> dist = shortestPath(V, edges, src);

    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " -> Distance: " << dist[i] << endl;
    }

    return 0;
}
