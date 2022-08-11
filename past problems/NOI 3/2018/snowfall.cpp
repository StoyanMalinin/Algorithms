#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 5e4;
const int MAXM = 2e5;

struct Edge
{
    int u, v;
    int snow;

    Edge(){}
    Edge(int u, int v, int snow) : u(u), v(v), snow(snow) {}
};

bool operator <(const Edge &A, const Edge &B)
{
    if(A.snow!=B.snow) return A.snow<B.snow;
    if(A.u!=B.u) return A.u<B.u;
    return A.v<B.v;
}

int n, m, k;
Edge edges[MAXM+5];

int depth[MAXN+5], minDepth[MAXN+5];
bool used[MAXN+5];

vector <int> AP;
vector <pair <int, int>> graph[MAXN+5];

void dfs(int x, int last, int level, const int SNOWFALL)
{
    used[x] = true;
    depth[x] = level;
    minDepth[x] = MAXN;

    bool isAP = false;
    int children = 0;

    for(pair <int, int> e: graph[x])
    {
        int y = e.first;
        int snowLimit = e.second;
        if(snowLimit<=SNOWFALL) continue;

        if(used[y]==false)
        {
            dfs(y, x, level+1, SNOWFALL);

            children++;
            minDepth[x] = min(minDepth[x], minDepth[y]);

            if(minDepth[y]>=depth[x]) isAP = true;
        }
        else
        {
            if(x!=last)
            {
                if(depth[y]<depth[x])
                    minDepth[x] = min(minDepth[x], depth[y]);
            }
        }
    }

    if(last==-1)
    {
        if(children>=2) AP.push_back(x);
    }
    else
    {
        if(isAP==true) AP.push_back(x);
    }
}

/*
-1 -> too low
+1 -> too high
0 -> just right
*/
int check(int snowfall)
{
    AP.clear();
    memset(used, 0, sizeof(used));
    dfs(1, -1, 0, snowfall);

    for(int x = 1;x<=n;x++)
    {
        if(used[x]==false) return +1;
    }

    if(AP.size()<k) return -1;
    return 0;
}

int main()
{
    cin >> n >> m >> k;
    for(int i = 0;i<m;i++)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].snow;

        graph[edges[i].u].emplace_back(edges[i].v, edges[i].snow);
        graph[edges[i].v].emplace_back(edges[i].u, edges[i].snow);
    }
    sort(edges, edges+m);

    int l = 0, r = m - 1, mid;
    while(l+1<r)
    {
        mid = (l+r)/2;
        int res = check(edges[mid].snow);

        if(res==-1) l = mid + 1;
        else if(res==+1) r = mid - 1;
        else r = mid;
    }

    int snow = 0;
    int res = check(snow);

    if(res!=0)
    {
        snow = edges[l].snow;
        res = check(snow);
    }
    if(res!=0)
    {
        snow = edges[r].snow;
        res = check(snow);
    }
    if(res!=0)
    {
        cout << "-1 0" << '\n';
        return 0;
    }

    sort(AP.begin(), AP.end());
    cout << snow << " " << AP.size() << '\n';
    cout << AP[0];
    for(int i = 1;i<AP.size();i++) cout << " " << AP[i];
    cout << '\n';
}
