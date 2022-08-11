#include <iostream>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 1e5;

struct Edge
{
    int u, v;

    Edge() {}
    Edge(int u, int v)
    {
        if(u>v) swap(u, v);
        this->u = u;
        this->v = v;
    }
};

bool operator <(const Edge& A, const Edge& B)
{
    if(A.u!=B.u) return A.u<B.u;
    return A.v<B.v;
}

int n, m;
Edge edges[2*MAXN+5];
vector <int> graph[MAXN+5];

set <Edge> bridges;

void resetGraph()
{
    for(int x = 1;x<=n;x++)
        graph[x].clear();
}

int dp[MAXN+5], depth[MAXN+5];
bool used[MAXN+5];

void dfs1(int x, int last, int level)
{
    used[x] = true;
    depth[x] = level;

    for(int y: graph[x])
    {
        if(used[y]==false)
        {
            dfs1(y, x, level+1);
            dp[x] += dp[y];
        }
        else
        {
            if(y!=last)
            {
                if(depth[y]>depth[x]) dp[x]--;
                else if(depth[y]<depth[x]) dp[x]++;
            }
        }
    }

    if(last!=-1 && dp[x]==0)
        bridges.emplace(x, last);
}

int dfs2(int x)
{
    int sz = 1;
    used[x] = true;

    for(int y: graph[x])
    {
        if(used[y]==false && bridges.count(Edge(x, y))==false)
            sz += dfs2(y);
    }

    return sz;
}

void findBridges()
{
    resetGraph();
    for(int i = 0;i<m;i++)
    {
        graph[edges[i].u].push_back(edges[i].v);
        graph[edges[i].v].push_back(edges[i].u);
    }

    memset(used, 0, sizeof(used));
    dfs1(1, -1, 0);
}

int64_t countPairs()
{
    int64_t ans = 0;

    memset(used, 0, sizeof(used));
    for(int x = 1;x<=n;x++)
    {
        if(used[x]==false)
        {
            int64_t sz = dfs2(x);
            ans += ((sz-1)*sz)/2;
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;

        edges[i] = Edge(u, v);
    }

    findBridges();
    cout << countPairs() << '\n';
}
