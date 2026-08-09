#include <bits/stdc++.h>
using namespace std;

vector<long long> bellmanFord(int V, vector<array<int,3>>& edges, int src, bool& hasNegativeCycle) {
    vector<long long> dist(V, LLONG_MAX);
    dist[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    hasNegativeCycle = false;
    for (auto& e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }

    return dist;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<array<int,3>> edges(E);
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    int src;
    cin >> src;

    bool hasNegativeCycle;
    vector<long long> dist = bellmanFord(V, edges, src, hasNegativeCycle);

    if (hasNegativeCycle) {
        cout << "Negative Cycle Detected" << endl;
        return 0;
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == LLONG_MAX) cout << "INF" << " ";
        else cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}
