#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 1000;

struct Edge
{
    int y;
    bool isAdditional;

    Edge() {}
    Edge(int y, bool isAdditional) : y(y), isAdditional(isAdditional) {}
};

struct DSU
{
    int parent[MAXN+5];

    DSU(int n)
    {
        for(int x = 1;x<=n;x++)
            parent[x] = x;
    }

    int Find(int x)
    {
        if(parent[x]==x) return x;

        parent[x] = Find(parent[x]);
        return parent[x];
    }

    bool Union(int u, int v)
    {
        u = Find(u);
        v = Find(v);
        if(u==v) return false;

        parent[v] = u;
        return true;
    }

    bool areConnected(int u, int v)
    {
        return (Find(u)==Find(v));
    }
};

struct Multigraph
{
    int n;
    DSU dsu;
    vector <Edge> adj[MAXN+5];

    Multigraph(int n) : n(n), dsu(n) {}

    int deg(int x)
    {
        assert(x<=n);
        return adj[x].size();
    }

    bool addEdge(int u, int v, bool isAdditional)
    {
        adj[u].emplace_back(v, isAdditional);
        adj[v].emplace_back(u, isAdditional);
        dsu.Union(u, v);
    }

    void makeEulerian()
    {
        for(int x = 1;x<=n;x++)
        {
            if(deg(x)%2!=0)
            {
                for(int y = x+1;y<=n;y++)
                {
                    if(deg(y)%2!=0 && dsu.areConnected(x, y)==false)
                    {
                        addEdge(x, y, true);
                        break;
                    }
                }
            }
        }

        while(true)
        {
            bool update = false;
            for(int x = 1;x<=n;x++)
            {
                if(deg(x)%2!=0)
                {
                    for(int y = 1;y<=n;y++)
                    {
                        if(dsu.areConnected(x, y)==false)
                        {
                            addEdge(x, y, true);

                            update = true;
                            break;
                        }
                    }
                }
            }

            if(update==false) break;
        }

        for(int x = 1;x<=n;x++)
        {
            if(deg(x)%2!=0)
            {
                for(int y = x+1;y<=n;y++)
                {
                    if(deg(y)%2!=0)
                    {
                        addEdge(x, y, true);
                        break;
                    }
                }
            }
        }

        vector <int> components;
        for(int x = 1;x<=n;x++)
        {
            if(x==dsu.Find(x)) components.push_back(x);
        }

        if(components.size()!=1)
        {
            for(int i = 0;i+1<components.size();i++) addEdge(components[i], components[i+1], true);
            addEdge(components.front(), components.back(), true);
        }
    }

    int getAdditionalEdgesCount()
    {
        int ans = 0;
        for(int x = 1;x<=n;x++)
        {
            for(const Edge& e: adj[x])
                if(e.isAdditional==true) ans++;
        }

        return ans/2;
    }

    void printAdditionalEdges()
    {
        for(int x = 1;x<=n;x++)
        {
            for(const Edge& e: adj[x])
            {
                if(x<e.y && e.isAdditional==true) cout << x << " " << e.y << '\n';
            }
        }
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    Multigraph G(n);

    for(int i = 0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;

        G.addEdge(u, v, false);
    }

    G.makeEulerian();
    cout << G.getAdditionalEdgesCount() << '\n';
    G.printAdditionalEdges();
}
