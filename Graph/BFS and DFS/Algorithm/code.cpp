#include <bits/stdc++.h>
using namespace std;

class Graph
{
    int n;
    vector<vector<int>> adj;

public:
    Graph(int nodes)
    {
        n = nodes;
        adj.resize(n + 1);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> bfs(int start)
    {
        vector<int> vis(n + 1, 0);
        vector<int> traversal;
        queue<int> q;

        q.push(start);
        vis[start] = 1;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            traversal.push_back(node);

            for (int child : adj[node])
            {
                if (!vis[child])
                {
                    vis[child] = 1;
                    q.push(child);
                }
            }
        }

        return traversal;
    }

    void dfsHelper(int node, vector<int> &vis, vector<int> &traversal)
    {
        vis[node] = 1;
        traversal.push_back(node);

        for (int child : adj[node])
        {
            if (!vis[child])
                dfsHelper(child, vis, traversal);
        }
    }

    vector<int> dfs(int start)
    {
        vector<int> vis(n + 1, 0);
        vector<int> traversal;

        dfsHelper(start, vis, traversal);

        return traversal;
    }

    vector<vector<int>> bfsDisconnected()
    {
        vector<int> vis(n + 1, 0);
        vector<vector<int>> components;

        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
                continue;

            queue<int> q;
            vector<int> current;

            q.push(i);
            vis[i] = 1;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                current.push_back(node);

                for (int child : adj[node])
                {
                    if (!vis[child])
                    {
                        vis[child] = 1;
                        q.push(child);
                    }
                }
            }

            components.push_back(current);
        }

        return components;
    }

    void dfsDisconnectedHelper(int node, vector<int> &vis, vector<int> &current)
    {
        vis[node] = 1;
        current.push_back(node);

        for (int child : adj[node])
        {
            if (!vis[child])
                dfsDisconnectedHelper(child, vis, current);
        }
    }

    vector<vector<int>> dfsDisconnected()
    {
        vector<int> vis(n + 1, 0);
        vector<vector<int>> components;

        for (int i = 1; i <= n; i++)
        {
            if (vis[i])
                continue;

            vector<int> current;
            dfsDisconnectedHelper(i, vis, current);
            components.push_back(current);
        }

        return components;
    }
};

int main()
{
    Graph g(7);

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(3, 7);

    vector<int> bfsTraversal = g.bfs(1);

    cout << "BFS : ";

    for (int node : bfsTraversal)
        cout << node << " ";

    cout << "\n";

    vector<int> dfsTraversal = g.dfs(1);

    cout << "DFS : ";

    for (int node : dfsTraversal)
        cout << node << " ";

    cout << "\n";

    return 0;
}