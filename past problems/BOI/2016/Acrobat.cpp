#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 3e5;

struct Forest
{
    bool isOdd[MAXN+5];
    vector <int> adj[MAXN+5];

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int x, int last, const int ODD_CNT)
    {
        int subOddCnt = 0;

    }
};

int n, m;
pair <int, int> ropes[MAXN+5];

Forest F;
bool used[MAXN+5];
vector <int> graphA[MAXN+5];

int dfs1(int x)
{
    used[x] = true;

    int oddCnt = 0;
    if(graphA[x].size()%2!=0) oddCnt++;

    for(int y: graphA[x])
    {
        if(used[y]==false)
        {
            F.addEdge(x, y);
            oddCnt += dfs1(y);
        }
    }

    return oddCnt;
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<n;i++)
    {
        int u, v;
        cin >> u >> v;

        ropes[i] = make_pair(u, v);
        graphA[u].push_back(v);
        graphA[v].push_back(u);
    }

    for(int x = 1;x<=n;x++)
        F.isOdd[x] = (graphA[x].size()%2==1);
}
