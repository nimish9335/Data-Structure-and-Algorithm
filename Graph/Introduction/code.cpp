#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    int n;
    vector<vector<int>> adj;
    vector<vector<pair<int, int>>> weightedAdj;
    vector<vector<int>> matrix;

    Graph(int nodes)
    {
        n = nodes;
        adj.resize(n + 1);
        weightedAdj.resize(n + 1);
        matrix.assign(n + 1, vector<int>(n + 1, 0));
    }

    void addUndirectedEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);

        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    void addDirectedEdge(int u, int v)
    {
        adj[u].push_back(v);
        matrix[u][v] = 1;
    }

    void addWeightedUndirectedEdge(int u, int v, int w)
    {
        weightedAdj[u].push_back({v, w});
        weightedAdj[v].push_back({u, w});
    }

    void addWeightedDirectedEdge(int u, int v, int w)
    {
        weightedAdj[u].push_back({v, w});
    }

    void printAdjacencyList()
    {
        cout << "Adjacency List\n";

        for (int i = 1; i <= n; i++)
        {
            cout << i << " : ";

            for (auto node : adj[i])
                cout << node << " ";

            cout << "\n";
        }
    }

    void printAdjacencyMatrix()
    {
        cout << "\nAdjacency Matrix\n";

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                cout << matrix[i][j] << " ";

            cout << "\n";
        }
    }

    void printWeightedGraph()
    {
        cout << "\nWeighted Adjacency List\n";

        for (int i = 1; i <= n; i++)
        {
            cout << i << " : ";

            for (auto edge : weightedAdj[i])
                cout << "(" << edge.first << "," << edge.second << ") ";

            cout << "\n";
        }
    }

    void dfs(int node, vector<int> &vis)
    {
        vis[node] = 1;

        cout << node << " ";

        for (int child : adj[node])
        {
            if (!vis[child])
                dfs(child, vis);
        }
    }

    void connectedComponents()
    {
        vector<int> vis(n + 1, 0);

        int components = 0;

        cout << "\nConnected Components\n";

        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                components++;

                cout << "Component " << components << " : ";

                dfs(i, vis);

                cout << "\n";
            }
        }

        cout << "\nTotal Components : " << components << "\n";
    }

    void degreeUndirected()
    {
        cout << "\nDegree of Nodes\n";

        for (int i = 1; i <= n; i++)
            cout << "Node " << i << " : " << adj[i].size() << "\n";
    }

    void degreeDirected()
    {
        vector<int> indegree(n + 1, 0);
        vector<int> outdegree(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            outdegree[i] = adj[i].size();

            for (int child : adj[i])
                indegree[child]++;
        }

        cout << "\nIn-Degree and Out-Degree\n";

        for (int i = 1; i <= n; i++)
        {
            cout << "Node " << i << " -> ";
            cout << "In: " << indegree[i] << " ";
            cout << "Out: " << outdegree[i] << "\n";
        }
    }
};
