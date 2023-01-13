#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 100;
const int inf = 1e9;

struct MaxFlowGraph
{
    int n;
    int G[MAXN+5][MAXN+5];

    bool used[MAXN+5];

    MaxFlowGraph(int n) : n(n)
    {
        memset(G, 0, sizeof(G));
    }

    void addEdge(int u, int v, int cap)
    {
        G[u][v] += cap;
    }

    int dfs(int x, int bottleneck, const int sink)
    {
        used[x] = true;
        if (x == sink)
        {
            return bottleneck;
        }

        for(int y = 1; y <= n; y++)
        {
            if (G[x][y] > 0 && used[y] == false)
            {
                int flow = dfs(y, min(bottleneck, G[x][y]), sink);
                if (flow > 0)
                {
                    G[x][y] -= flow;
                    G[y][x] += flow;

                    return flow;
                }
            }
        }

        return 0;
    }

    int FordFulkerson(int source, int sink)
    {
        int maxFlow = 0;

        while (true)
        {
            memset(used, 0, sizeof(used));
            int flow = dfs(source, inf, sink);

            maxFlow += flow;
            if (flow == 0)
            {
                break;
            }
        }

        return maxFlow;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    MaxFlowGraph G(n);
    for(int i = 0; i < m; i++)
    {
        int u, v;
        int64_t cap;
        cin >> u >> v;

        G.addEdge(u, v, 1);
        G.addEdge(v, u, 1);
    }

    int paths = G.FordFulkerson(1, n);
    cout << paths << '\n';

    int Q;
    cin >> Q;

    while (Q--)
    {
        int u, v;
        cin >> u >> v;

        G.addEdge(u, v, 1);
        G.addEdge(v, u, 1);

        paths += G.FordFulkerson(1, n);
        cout << paths << '\n';
    }
}
