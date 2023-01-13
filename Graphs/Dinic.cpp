#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1e4;
const int inf = 1e9 + 5;

struct Edge
{
    int u, v;
    int64_t val;

    Edge(){}
    Edge(int u, int v, int64_t val)
    {
        this->u = u;
        this->v = v;
        this->val = val;
    }
};

struct MaxFlowGraph
{
    int dist[MAXN+5];
    int startInd[MAXN+5];

    vector <Edge> edges;
    vector <int> graph[MAXN+5];

    MaxFlowGraph(){}

    void addEdge(int u, int v, int64_t val)
    {
        edges.push_back(Edge(u, v, val));
        edges.push_back(Edge(v, u, 0));

        graph[u].push_back(edges.size()-2);
        graph[v].push_back(edges.size()-1);
    }

    void BFS(int x)
    {
        queue <int> q;
        memset(dist, 0, sizeof(dist));

        q.push(x);
        dist[x] = 1;
        while (q.empty() == false)
        {
            x = q.front();
            q.pop();

            for (int ind : graph[x])
            {
                Edge e = edges[ind];
                if(dist[e.v] == 0 && e.val > 0)
                {
                    q.push(e.v);
                    dist[e.v] = dist[x] + 1;
                }
            }
        }
    }

    int64_t DFS(int x, int64_t minVal, int sink)
    {
        if (x==sink)
        {
            return minVal;
        }

        for (int i = startInd[x]; i < int(graph[x].size()); i++, startInd[x]++)
        {
            Edge e = edges[ graph[x][i] ];
            if(e.val > 0 && dist[e.v] == dist[x] + 1)
            {
                int flow = DFS(e.v, min(minVal, e.val), sink);
                if(flow!=0)
                {
                    edges[graph[x][i]] .val -= flow;
                    edges[graph[x][i] ^ 1].val += flow;

                    return flow;
                }
            }
        }

        return 0;
    }

    int64_t Dinic(int source, int sink)
    {
        int64_t maxFlow = 0;
        while (true)
        {
            BFS(source);
            if(dist[sink]==0) break;

            while (true)
            {
                int flow = DFS(source, inf, sink);
                if (flow==0) break;

                maxFlow += flow;
            }

            memset(startInd, 0, sizeof(startInd));
        }

        return maxFlow;
    }
};

MaxFlowGraph G;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++)
    {
        int u, v;
        int64_t cap;
        cin >> u >> v >> cap;

        G.addEdge(u, v, cap);
        G.addEdge(v, u, cap);
    }

    cout << G.Dinic(1, n) << '\n';
}
