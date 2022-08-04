#include "werewolf.h"
//#include "grader.cpp"

#include <vector>
#include <cstring>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

const int MAXN = 2e5 + 5;
const int MAXLog = 18;

struct Event
{
    int type;
    int pos;

    int y;
    int y1, y2, ind;

    Event(){}
    Event(int type, int pos, int y)
    {
        this->type = type;
        this->pos = pos;
        this->y = y;
    }
    Event(int type, int pos, int y1, int y2, int ind)
    {
        this->type = type;
        this->pos = pos;
        this->ind = ind;
        this->y1 = y1;
        this->y2 = y2;
    }
};

struct DSU
{
    int parent[MAXN];

    DSU(){}
    DSU(int n)
    {
        for(int i = 0;i<n;i++)
            this->parent[i] = i;
    }

    int Find(int x)
    {
        if(parent[x]==x) return x;

        parent[x] = Find(parent[x]);
        return parent[x];
    }

    void Union(int u, int v)
    {
        u = Find(u);
        v = Find(v);
        if(u==v) return;

        parent[v] = u;
    }
};

struct Tree
{
    int n;
    DSU dsu;
    vector <int> graph[MAXN];

    int parent[25][MAXN];
    vector <int> order, invOrder;
    int treeSize[MAXN], orderPos[MAXN];

    Tree(){}
    Tree(int n)
    {
        this->n = n;
        this->dsu = DSU(n);
    }

    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void DFS(int x, int last)
    {
        orderPos[x] = order.size();
        order.push_back(x);

        treeSize[x] = 1;
        parent[0][x] = last;

        for(int y: graph[x])
        {
            if(y==last) continue;

            DFS(y, x);
            treeSize[x] += treeSize[y];
        }
    }

    void init(int root)
    {
        DFS(root, -1);
        for(int step = 1;step<=MAXLog;step++)
        {
            for(int x = 0;x<n;x++)
            {
                if(parent[step-1][x]==-1)
                    parent[step][x] = -1;
                else
                    parent[step][x] = parent[step-1][ parent[step-1][x] ];
            }
        }

        invOrder.resize(order.size());
        for(int i = 0;i<order.size();i++) invOrder[ order[i] ] = i;
    }
};

struct FenwickTree
{
    int n;
    int tree[MAXN];

    FenwickTree(){}
    FenwickTree(int n)
    {
        this->n = n;
        memset(this->tree, 0, sizeof(this->tree));
    }

    void update(int ind, int change)
    {
        ind++;
        while(ind<=n)
        {
            tree[ind] += change;
            ind += ind&(-ind);
        }
    }

    int query(int ind)
    {
        ind++;
        int sum = 0;

        while(ind>0)
        {
            sum += tree[ind];
            ind -= ind&(-ind);
        }

        return sum;
    }

    int query(int l, int r)
    {
        return query(r) - query(l-1);
    }
};

int n;
vector <int> graph[MAXN];

vector<int> check_validity(int N, vector<int> X, vector<int> Y,
                                  vector<int> S, vector<int> E,
                                  vector<int> L, vector<int> R)
{
    n = N;
    for(int i = 0;i<X.size();i++)
    {
        graph[ X[i] ].push_back(Y[i]);
        graph[ Y[i] ].push_back(X[i]);
    }

    Tree Tv(n);
    for(int x = 0;x<n;x++)
    {
        for(int y: graph[x])
        {
            if(y>=x) continue;

            int xPar = Tv.dsu.Find(x);
            int yPar = Tv.dsu.Find(y);
            if(xPar==yPar) continue;

            Tv.addEdge(xPar, yPar);
            Tv.dsu.Union(x, y);
        }
    }
    Tv.init(n-1);

    Tree Tu(n);
    for(int x = n-1;x>=0;x--)
    {
        for(int y: graph[x])
        {
            if(y<=x) continue;

            int xPar = Tu.dsu.Find(x);
            int yPar = Tu.dsu.Find(y);
            if(xPar==yPar) continue;

            Tu.addEdge(xPar, yPar);
            Tu.dsu.Union(x, y);
        }
    }
    Tu.init(0);

    vector <Event> v;
    for(int i = 0;i<Tu.order.size();i++)
    {
        v.push_back(Event(1, i, Tv.invOrder[ Tu.order[i] ]));
    }
    for(int i = 0;i<S.size();i++)
    {
        int s = S[i], e = E[i];
        int l = L[i], r = R[i];

        for(int step = MAXLog;step>=0;step--)
        {
            if(Tu.parent[step][s]!=-1 && Tu.parent[step][s]>=l) s = Tu.parent[step][s];
            if(Tv.parent[step][e]!=-1 && Tv.parent[step][e]<=r) e = Tv.parent[step][e];
        }

        pair <int, int> seg1 = {Tu.orderPos[s], Tu.orderPos[s]+Tu.treeSize[s]-1};
        pair <int, int> seg2 = {Tv.orderPos[e], Tv.orderPos[e]+Tv.treeSize[e]-1};

        v.push_back(Event(0, seg1.first, seg2.first, seg2.second, i));
        v.push_back(Event(2, seg1.second, seg2.first, seg2.second, i));
    }
    sort(v.begin(), v.end(),
    [&](Event A, Event B)
    {
        if(A.pos!=B.pos) return A.pos<B.pos;
        return A.type<B.type;
    });

    vector <int> queryAnswers, inRect;
    queryAnswers.assign(S.size(), 0);
    inRect.assign(S.size(), 0);

    FenwickTree ft(n);
    for(Event e: v)
    {
        if(e.type==0)
        {
            inRect[e.ind] -= ft.query(e.y1, e.y2);
        }
        else if(e.type==1)
        {
            ft.update(e.y, +1);
        }
        else if(e.type==2)
        {
            inRect[e.ind] += ft.query(e.y1, e.y2);
        }
    }

    for(int i = 0;i<S.size();i++)
    {
        if(inRect[i]>0) queryAnswers[i] = 1;
        else queryAnswers[i] = 0;
    }

    return queryAnswers;
}

