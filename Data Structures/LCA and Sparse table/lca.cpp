#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5;
const int MAXLog = 20;

int n;
vector <int> graph[MAXN];

int parent[MAXN], depth[MAXN];
int sparse[MAXLog+2][MAXN];

void dfs(int x, int last, int level)
{
    parent[x] = last;
    depth[x] = level;

    for(int y: graph[x])
    {
        if(y!=last)
            dfs(y, x, level+1);
    }
}

void init(int root)
{
    dfs(root, -1, 1);
    for(int x = 1;x<=n;x++) sparse[0][x] = parent[x];

    for(int l = 1;l<=MAXLog;l++)
    {
        for(int x = 1;x<=n;x++)
        {
            if(sparse[l-1][x]==-1)
                sparse[l][x] = -1;
            else
                sparse[l][x] = sparse[l-1][sparse[l-1][x]];
        }
    }
}

int rise(int x, int levelDiff)
{
    for(int bit = 0;bit<=MAXLog;bit++)
    {
        if(((levelDiff>>bit)&1)==1)
        {
            if(x!=-1)
                x = sparse[bit][x];
        }
    }

    return x;
}

int lca(int u, int v)
{
    if(depth[u]>depth[v])
        swap(u, v);

    v = rise(v, depth[v]-depth[u]);
    if(u==v) return u;

    for(int l = MAXLog;l>=0;l--)
    {
        if(sparse[l][u]!=sparse[l][v])
        {
            u = sparse[l][u];
            v = sparse[l][v];
        }
    }

    return parent[u];
}

int main()
{
    cin >> n;
    for(int i = 0;i<n-1;i++)
    {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    int root;
    cin >> root;

    init(root);
}
