/*

Edmonds-Karp's algorithm for finding the maximum flow in a graph
Time Complexity O(V*E^2)

*/

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 20;
const int INF = 1e9;

class Graph
{
private:
    int n;
    int graph[MAXN][MAXN];

    int BFS(const int source, const int sink, int *parent)
    {
        int bottleneck[MAXN];
        queue <int> bfsQueue;

        bfsQueue.push(source);
        bottleneck[source] = INF;
        parent[source] = 0;

        while (!bfsQueue.empty())
        {
            int curr = bfsQueue.front();
            bfsQueue.pop();

            if (curr == sink)
            {
                while (parent[curr] != 0)
                {
                    graph[parent[curr]][curr] -= bottleneck[sink];
                    graph[curr][parent[curr]] += bottleneck[sink];

                    curr = parent[curr];
                }

                return bottleneck[sink];
            }


            for (int i = 1; i <= n; i++)
            {
                if (parent[i] == -1 && graph[curr][i] > 0)
                {
                    bottleneck[i] = min(bottleneck[curr], graph[curr][i]);
                    parent[i] = curr;
                    bfsQueue.push(i);
                }
            }
        }



        return 0;
    }

public:
    Graph()
    {
        memset(graph, 0, sizeof(graph));
    }
    Graph(int n):Graph()
    {
        this->n = n;
    }

    void AddEdge(int u, int v, int capacity)
    {
        graph[u][v] += capacity;
    }

    int EdmondsKarp(int source, int sink)
    {
        int maxFlow = 0, flow = 1;
        int parent[MAXN];

        while (flow)
        {
            memset(parent, -1, sizeof(parent));

            flow = BFS(source, sink, parent);
            maxFlow += flow;
        }

        return maxFlow;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int V, E;
    cin >> V >> E;

    Graph *graph = new Graph(V);

    for (int i = 0; i < E; i++)
    {
        int u, v, capacity;
        cin >> u >> v >> capacity;

        graph->AddEdge(u, v, capacity);
    }

    cout << graph->EdmondsKarp(1, V) << endl;

    return 0;
}
