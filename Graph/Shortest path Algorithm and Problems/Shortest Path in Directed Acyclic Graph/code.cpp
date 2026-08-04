#include <bits/stdc++.h>
using namespace std;

void dfsTopo(int node, vector<vector<pair<int,int>>> &adj, vector<int> &visited, stack<int> &st) {
    visited[node] = 1;
    for (auto &edge : adj[node]) {
        int neighbor = edge.first;
        if (!visited[neighbor]) {
            dfsTopo(neighbor, adj, visited, st);
        }
    }
    st.push(node);
}

vector<int> shortestPathDAG(int V, vector<vector<int>> &edges, int src) {
    vector<vector<pair<int,int>>> adj(V);
    for (auto &e : edges) {
        adj[e[0]].push_back({e[1], e[2]});
    }

    vector<int> visited(V, 0);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfsTopo(i, adj, visited, st);
        }
    }

    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (dist[node] != INT_MAX) {
            for (auto &edge : adj[node]) {
                int neighbor = edge.first;
                int weight = edge.second;
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }

    return dist;
}

int main() {
    int V = 8;
    vector<vector<int>> edges = {
        {6, 4, 1}, {6, 1, 2},
        {4, 0, 1}, {4, 5, 4},
        {1, 0, 2}, {1, 2, 6},
        {5, 0, 1}, {5, 3, 2},
        {0, 3, 3},
        {3, 2, 6},
        {2, 7, 1}
    };
    int src = 6;

    vector<int> dist = shortestPathDAG(V, edges, src);

    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " -> Distance: " << dist[i] << endl;
    }

    return 0;
}
