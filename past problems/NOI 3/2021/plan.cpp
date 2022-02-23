#include <functional>
#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 5e5 + 5;

struct CompositeDist
{
    int bfsDist;
    int64_t lenDist;

    CompositeDist(){}
    CompositeDist(int bfsDist, int64_t lenDist)
    {
        this->bfsDist = bfsDist;
        this->lenDist = lenDist;
    }
};

bool operator !=(CompositeDist A, CompositeDist B)
{
    if(A.bfsDist!=B.bfsDist) return true;
    if(A.lenDist!=B.lenDist) return true;

    return false;
}

bool operator ==(CompositeDist A, CompositeDist B)
{
    return (A!=B)^1;
}

CompositeDist operator -(CompositeDist A, CompositeDist B)
{
    return CompositeDist(A.bfsDist-B.bfsDist, A.lenDist-B.lenDist);
}

bool operator <(const CompositeDist &A, const CompositeDist &B)
{
    if(A.bfsDist!=B.bfsDist) return A.bfsDist<B.bfsDist;
    return A.lenDist<B.lenDist;
}

bool operator >(const CompositeDist &A, const CompositeDist &B)
{
    if(A.bfsDist!=B.bfsDist) return A.bfsDist>B.bfsDist;
    return A.lenDist>B.lenDist;
}

struct Tree
{
    vector <int> children[MAXN];
    vector <pair <int, int>> queries[MAXN];

    void addEdge(int u, int v)
    {
        children[u].push_back(v);
    }

    void addQuery(int x, int y, int ind)
    {
        queries[y].push_back({x, ind});
    }

    bool isAbove[MAXN];
    void dfs(int x, bool isValid[])
    {
        isAbove[x] = true;

        for(pair <int, int> q: queries[x]) isValid[q.second] = isAbove[q.first];
        for(int y: children[x]) dfs(y, isValid);

        isAbove[x] = false;
    }

    void answerQueries(int root, bool isValid[])
    {
        memset(isAbove, false, sizeof(isAbove));
        dfs(root, isValid);
    }
};

bool inQueue[MAXN];
CompositeDist dist[MAXN];
vector <pair <int, int>> graph[MAXN];

void bfs(int n, int x)
{
    for(int i = 1;i<=n;i++) dist[i] = CompositeDist(MAXN, 1e15);

    queue <int> q;q.push(1);
    dist[1] = CompositeDist(0, 0);

    while(q.empty()==false)
    {
        int x = q.front();
        q.pop();

        for(pair <int, int> e: graph[x])
        {
            int y = e.first, w = e.second;

            CompositeDist newDist = CompositeDist(dist[x].bfsDist+1, dist[x].lenDist+w);
            if(dist[y] > newDist)
            {
                dist[y] = newDist;
                if(inQueue[y]==false)
                {
                    q.push(y);
                    inQueue[y] = true;
                }
            }
        }
    }

}

Tree T;
bool isValid[MAXN];

void buildTree(int n)
{
    for(int x = 1;x<=n;x++)
    {
        for(pair <int, int> e: graph[x])
        {
            if(dist[e.first] == CompositeDist(dist[x].bfsDist+1, dist[x].lenDist+e.second))
            {
                T.addEdge(x, e.first);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int u, v, val;
        cin >> u >> v >> val;

        graph[u].push_back({v, val});
        graph[v].push_back({u, val});
    }

    bfs(n, 1);
    buildTree(n);

    int Q;
    cin >> Q;

    vector <pair <int, int>> queries;
    for(int q = 0;q<Q;q++)
    {
        int x, y;
        cin >> x >> y;

        queries.push_back({x, y});
        T.addQuery(x, y, q);
    }

    T.answerQueries(1, isValid);

    cout << dist[n].bfsDist - 1 << " " << dist[n].lenDist << '\n';
    for(int q = 0;q<Q;q++)
    {
        if(isValid[q]==false) cout << "0" << '\n';
        else
        {
            int x = queries[q].first;
            int y = queries[q].second;

            CompositeDist d = dist[y] - dist[x];
            cout << max(0, d.bfsDist - 1) << " " << d.lenDist << '\n';
        }
    }
}
