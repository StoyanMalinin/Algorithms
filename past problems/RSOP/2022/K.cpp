#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <queue>
#include <deque>
#include <list>

using namespace std;

const int MAXN = 10000;
const int MAXM = 3*MAXN;
const int64_t inf = 1e8;

struct Edge
{
    int u, v;
    int val;

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
    int dist[2*MAXM+5];
    int startInd[2*MAXM+5];

    vector <Edge> edges;
    vector <int> graph[2*MAXM+5];

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

    int DFS(int x, int minVal, int sink)
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

    int Dinic(int source, int sink)
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

struct DAG
{
    struct AdjElement
    {
        int node, id;

        AdjElement(){}
        AdjElement(int node, int id) : node(node), id(id) {}
    };

    int n, m;
    vector <vector<AdjElement>> adj;

    DAG(int n) : n(n), m(0)
    {
        adj.resize(n);
    }

    void addEdge(int u, int v)
    {
        adj[u].emplace_back(v, m);
        m++;
    }

    DAG getEdgeGraph()
    {
        DAG ret(m);
        for(int u = 0; u < n; u++)
        {
            for(auto adj1 : adj[u])
            {
                int v = adj1.node, id1 = adj1.id;
                for(auto adj2 : adj[v])
                {
                    int w = adj2.node, id2 = adj2.id;
                    ret.addEdge(id1, id2);
                }
            }
        }

        return ret;
    }

    void dfs(int startNode, int u, MaxFlowGraph *G, const vector <int> &x, const vector <int> &y, vector <bool> &used)
    {
        used[u] = true;
        //cout << " -> " << u << '\n';
        if (startNode != u)
        {
            G->addEdge(x[startNode+1], y[u+1], 1);
        }

        for (auto item : adj[u])
        {
            if (used[item.node] == false)
            {
                dfs(startNode, item.node, G, x, y, used);
            }
        }
    }

    int getPathCover()
    {
        MaxFlowGraph *G = new MaxFlowGraph();

        int graphNode = 1;
        vector <int> x(n+1), y(n+1);

        for(int &item : x)
        {
            item = graphNode;
            graphNode++;
        }
        for(int &item : y)
        {
            item = graphNode;
            graphNode++;
        }

        cout << "START_BUILDING" << '\n';
        for(int u = 1; u <= n; u++)
        {
            G->addEdge(x[0], x[u], 1);
            G->addEdge(y[u], y[0], 1);
        }
        for(int u = 0; u < n; u++)
        {
            cout << "start: " << u  << '\n';
            vector <bool> used(n, false);
            dfs(u, u, G, x, y, used);
        }
        cout << "END_BUILDING" << '\n';

        cout << "START_ALG" << '\n';
        int res = G->Dinic(x[0], y[0]);
        cout << "END_ALG" << '\n';
        delete G;

        return n - res;
    }

    void dfsTopSort(int x, vector <int> &topSort, vector <int> &topSortId)
    {
        for (auto item : adj[x])
        {
            if (topSortId[item.node] == -1)
            {
                dfsTopSort(item.node, topSort, topSortId);
            }
        }

        topSortId[x] = topSort.size();
        topSort.push_back(x);
    }

    bool checkCyclic()
    {
        vector <int> topSort, topSortId(n, -1);

        for (int u = 0; u < n; u++)
        {
            if (topSortId[u] == -1)
            {
                cout << "start: " << u << '\n';
                dfsTopSort(u, topSort, topSortId);
            }
        }

        for(int u = 0; u < n; u++)
        {
            for(auto adj1 : adj[u])
            {
                int v = adj1.node;
                if (topSortId[u] <= topSortId[v]) return true;
            }
        }

        return false;
    }
};

void solveTestcase()
{
    int n, m = 0;
    cin >> n;

    DAG G(n);
    for(int x = 0; x < n - 1; x++)
    {
        int k;
        cin >> k;
        m += k;

        for(int i = 0; i < k; i++)
        {
            int y;
            cin >> y;

            G.addEdge(x, y-1);
        }
    }

    cout << G.getEdgeGraph().getPathCover() << '\n';
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        solveTestcase();
    }
}
/*
1
8
3 2 3 4
2 6 5
1 5
1 7
2 7 6
1 8
1 8
*/
