#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5;
const int MAXLog = 20;

int n;
vector <int> adj[MAXN+5];

int depth[MAXN+5], firstSeen[MAXN+5];
int sparse[MAXLog+2][MAXN*2+5], log2[MAXN*2+5];

void dfs(int x, int last, int level, vector <int> &eulerTour)
{
    depth[x] = level;
    firstSeen[x] = eulerTour.size();

    eulerTour.push_back(x);
    for(int y: adj[x])
    {
        if(y!=last)
        {
            dfs(y, x, level+1, eulerTour);
            eulerTour.push_back(x);
        }
    }
}

int getShallowerVertex(int u, int v)
{
    if(depth[u]<depth[v]) return u;
    return v;
}

void init(int root)
{
    vector <int> eulerTour;
    dfs(root, -1, 0, eulerTour);

    log2[1] = 0;
    for(int x = 2;x<=2*MAXN;x++)
        log2[x] = log2[x/2] + 1;

    for(int i = 0;i<eulerTour.size();i++) sparse[0][i] = eulerTour[i];
    for(int l = 1;l<=MAXLog;l++)
    {
        for(int i = 0;i<eulerTour.size();i++)
        {
            if(i+(1<<(l-1)) >= eulerTour.size())
                sparse[l][i] = sparse[l-1][i];
            else
                sparse[l][i] = getShallowerVertex(sparse[l-1][i], sparse[l-1][i+(1<<(l-1))]);
        }
    }
}

int rmq(int l, int r) //range minimum query
{
    return getShallowerVertex(sparse[log2[r-l+1]][l], sparse[log2[r-l+1]][r - (1<<log2[r-l+1]) + 1]);
}

int lca(int u, int v)
{
    if(firstSeen[u]>firstSeen[v]) swap(u, v);
    return rmq(firstSeen[u], firstSeen[v]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> n >> Q;
    for(int i = 1;i<n;i++)
    {
        int p;
        cin >> p;

        adj[p].push_back(i);
    }

    init(0);
    while(Q--)
    {
        int u, v;
        cin >> u >> v;

        cout << lca(u, v) << '\n';
    }
}

