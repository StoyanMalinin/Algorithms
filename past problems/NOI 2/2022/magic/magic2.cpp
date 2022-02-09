#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXC = 30;
const int MAXN = 2000;
const int inf = 1e9 + 5;

struct Edge
{
    int v, c, d;

    Edge(){}
    Edge(int v, int c, int d) : v(v), c(c), d(d) {}
};

int n, m;
vector <Edge> graph[MAXN+5];

int dist[MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        graph[b].emplace_back(a, c, d);
    }

    for(int x = 1;x<=n;x++)
        dist[x] = inf;

    dist[n] = 0;
    bool update = false;

    do
    {
        update = false;
        for(int u = 1;u<=n;u++)
        {
            if(dist[u]!=inf)
            {
                for(auto e: graph[u])
                {
                    int v = e.v, c = e.c, d = e.d;
                    if(dist[v] > max(dist[u] - d, 0) + c)
                    {
                        dist[v] = max(dist[u] - d, 0) + c;
                        update = true;
                    }
                }
            }
        }
    }
    while(update==true);

    cout << ((dist[1]==inf)?-1:dist[1]) << '\n';
}
