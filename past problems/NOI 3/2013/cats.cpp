#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int MAXN = 35;
const int inf = 1e9 + 5;
const int MAXM = MAXN*MAXN*2;

int n, m;
string grid[MAXN];

int G[MAXM][MAXM];
vector <int> graph[MAXM];
pair <int, int> nodes[MAXM][MAXM];

queue <int> q;
int dist[MAXM], last[MAXM];

struct MaxFlowGraph
{
    int n;
    int G[MAXN*MAXN*2+5][MAXN*MAXN*2+5];

    bool used[MAXN*MAXN*2+5];

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
    cin.tie(NULL);

    cin >> n;
    for(int i = 0;i<n;i++)
    {
        cin >> grid[i];
    }
    m = grid[0].size();

    int newNode = 3;
    int s = 1, t = 2;
    MaxFlowGraph G(n*m*2+2);
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            nodes[i][j] = {newNode, newNode+1};
            newNode += 2;

            G.addEdge(nodes[i][j].first, nodes[i][j].second, 1);
            if (grid[i][j] == '1')
            {
                G.addEdge(s, nodes[i][j].first, 1);
            }
            if (i == 0 || i == n-1 || j == 0 || j == m - 1)
            {
                G.addEdge(nodes[i][j].second, t, 1);
            }
        }
    }

    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<m; j++)
        {
            if(i-1 >= 0 && grid[i-1][j] != '1')
            {
                G.addEdge(nodes[i][j].second, nodes[i-1][j].first, 1);
            }
            if(i+1 < n && grid[i+1][j] != '1')
            {
                G.addEdge(nodes[i][j].second, nodes[i+1][j].first, 1);
            }
            if(j-1 >= 0 && grid[i][j-1] != '1')
            {
                G.addEdge(nodes[i][j].second, nodes[i][j-1].first, 1);
            }
            if(j+1 < m && grid[i][j+1] != '1')
            {
                G.addEdge(nodes[i][j].second, nodes[i][j+1].first, 1);
            }
        }
    }

    cout << G.FordFulkerson(s, t) << '\n';
}
/*
5
111010
000101
111101
111001
001000
*/
