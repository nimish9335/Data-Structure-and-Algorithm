#include <bits/stdc++.h>
using namespace std;

bool dfsCheck(int node, vector<int> adj[], vector<int> &visited, vector<int> &pathVisited) {
    visited[node] = 1;
    pathVisited[node] = 1;
    for (auto it : adj[node]) {
        if (!visited[it]) {
            if (dfsCheck(it, adj, visited, pathVisited)) return true;
        } else if (pathVisited[it]) {
            return true;
        }
    }
    pathVisited[node] = 0;
    return false;
}

bool isCyclic(int V, vector<int> adj[]) {
    vector<int> visited(V, 0), pathVisited(V, 0);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfsCheck(i, adj, visited, pathVisited)) return true;
        }
    }
    return false;
}

int32_t main() {
    int V = 5;
    vector<int> adj[5];
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(1);
    adj[4].push_back(0);

    if (isCyclic(V, adj)) cout << "Cycle detected" << endl;
    else cout << "No cycle" << endl;

    return 0;
}
