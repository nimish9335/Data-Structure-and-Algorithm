#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
    vector<vector<pair<int,int>>> adj(V);
    for (auto &e : edges) {
        adj[e[0]].push_back({e[1], e[2]});
    }

    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (currDist > dist[node]) continue;

        for (auto &edge : adj[node]) {
            int neighbor = edge.first;
            int weight = edge.second;
            if (currDist + weight < dist[neighbor]) {
                dist[neighbor] = currDist + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }

    return dist;
}

int main() {
    int V = 5;
    vector<vector<int>> edges = {
        {0, 1, 4}, {0, 2, 1},
        {2, 1, 2}, {1, 3, 1},
        {2, 3, 5}, {3, 4, 3}
    };
    int src = 0;

    vector<int> dist = dijkstra(V, edges, src);

    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " -> Distance: " << dist[i] << endl;
    }

    return 0;
}
