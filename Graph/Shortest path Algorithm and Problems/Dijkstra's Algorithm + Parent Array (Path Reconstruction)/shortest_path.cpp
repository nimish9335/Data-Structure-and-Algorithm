#include <bits/stdc++.h>
using namespace std;

vector<int> shortestPath(int V, vector<vector<pair<int,int>>>& adj, int src, int dest) {
    vector<long long> dist(V, LLONG_MAX);
    vector<int> parent(V);
    for (int i = 0; i < V; i++) parent[i] = i;

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
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    if (dist[dest] == LLONG_MAX) return {-1};

    vector<int> path;
    int cur = dest;
    while (parent[cur] != cur) {
        path.push_back(cur);
        cur = parent[cur];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());

    return path;
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

    int src, dest;
    cin >> src >> dest;

    vector<int> path = shortestPath(V, adj, src, dest);

    for (int i = 0; i < (int)path.size(); i++) {
        cout << path[i];
        if (i != (int)path.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
