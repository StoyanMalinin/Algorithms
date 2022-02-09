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

using DijkstraPQ = priority_queue <pair <int, pair <int, int>>, vector <pair <int, pair <int, int>>>, greater <pair <int, pair <int, int>>>>;

int n, m;
vector <Edge> graph[MAXN+5];

int dist[MAXN+5][MAXN*MAXC+5];

void useNode(int u, int m, DijkstraPQ &pq)
{
    for(auto e: graph[u])
    {
        int v = e.v, c = e.c, d = e.d;
        if(dist[v][min(max(0, m-c)+d, n*MAXC)] > dist[u][m] + max(0, c-m))
        {
            dist[v][min(max(0, m-c)+d, n*MAXC)] = dist[u][m] + max(0, c-m);
            pq.push(make_pair(dist[v][min(max(0, m-c)+d, n*MAXC)], make_pair(v, min(max(0, m-c)+d, n*MAXC))));
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        graph[a].emplace_back(b, c, d);
    }

    DijkstraPQ pq;
    for(int x = 1;x<=n;x++)
    {
        for(int magic = 0;magic<=n*30;magic++)
            dist[x][magic] = inf;
    }

    dist[1][0] = 0;
    pq.push(make_pair(0, make_pair(1, 0)));

    while(pq.empty()==false)
    {
        auto top = pq.top();
        pq.pop();

        if(top.second.first==n)
        {
            cout << top.first << '\n';
            return 0;
        }

        if(dist[top.second.first][top.second.second]!=top.first)
            continue;

        useNode(top.second.first, top.second.second, pq);
    }

    cout << "-1" << '\n';
}
