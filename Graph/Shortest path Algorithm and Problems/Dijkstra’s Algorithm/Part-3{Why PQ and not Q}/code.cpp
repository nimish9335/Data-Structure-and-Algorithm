#include <bits/stdc++.h>
using namespace std;

vector<long long> dijkstra(int V, vector<vector<pair<int,int>>>& adj, int src) {
    vector<long long> dist(V, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& [v, w] : adj[u]) {
            long long nd = dist[u] + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    return dist;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int,int>>> adj(V);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int src;
    cin >> src;

    vector<long long> dist = dijkstra(V, adj, src);

    for (int i = 0; i < V; i++) {
        if (dist[i] == LLONG_MAX) cout << "INF" << " ";
        else cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}
