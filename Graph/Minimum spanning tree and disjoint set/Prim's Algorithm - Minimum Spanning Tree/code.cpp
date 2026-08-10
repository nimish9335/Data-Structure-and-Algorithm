#include <bits/stdc++.h>
using namespace std;

int primsMST(int V, vector<vector<pair<int,int>>>& adj) {
    vector<bool> visited(V, false);
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
    > pq;

    pq.push({0, 0, -1});

    int totalWeight = 0;
    vector<tuple<int,int,int>> mstEdges;

    while (!pq.empty()) {
        auto x = pq.top();
        int w = get<0>(x);
        int u = get<1>(x);
        int parent = get<2>(x);
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;
        totalWeight += w;

        if (parent != -1) {
            mstEdges.push_back({parent, u, w});
        }

        for (auto& it : adj[u]) {
            int v = it.first;
            int wt = it.second;

            if (!visited[v]) {
                pq.push({wt, v, u});
            }
        }
    }

    return totalWeight;
}

int main() {
    return 0;
}