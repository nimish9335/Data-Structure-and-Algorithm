#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

bool floydWarshall(int V, vector<vector<long long>>& dist) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    bool hasNegativeCycle = false;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            hasNegativeCycle = true;
            break;
        }
    }

    return hasNegativeCycle;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<long long>> dist(V, vector<long long>(V, INF));
    for (int i = 0; i < V; i++) dist[i][i] = 0;

    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
    }

    bool hasNegativeCycle = floydWarshall(V, dist);

    if (hasNegativeCycle) {
        cout << "Negative Cycle Detected" << endl;
        return 0;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << "INF" << " ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
