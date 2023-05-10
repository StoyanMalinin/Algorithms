#include <iostream>
#include <random>
#include <vector>

using namespace std;

const int MAXN = 1e6;
const int MAXLog = 22;

mt19937_64 rnd(22);

int64_t randInRange(int64_t l, int64_t r)
{
    return l + rnd() % (r - l + 1);
}

struct SegmentTreeNode
{
    int l, r;
    int64_t sum, lazy;

    SegmentTreeNode *L, *R;

    SegmentTreeNode() : sum(0), lazy(0), L(nullptr), R(nullptr) {}
    SegmentTreeNode(int l, int r) : SegmentTreeNode()
    {
        this->l = l;
        this->r = r;
    }

    void recalc()
    {
        sum = L->sum + R->sum;
    }

    void build()
    {
        if(l==r) return;

        L = new SegmentTreeNode(l, (l+r)/2);
        R = new SegmentTreeNode((l+r)/2+1, r);

        L->build();
        R->build();
        recalc();
    }

    void updateLazy()
    {
        sum += (r-l+1)*lazy;
        if(l!=r)
        {
            L->lazy += lazy;
            R->lazy += lazy;
        }

        lazy = 0;
    }

    int64_t query(int ql, int qr)
    {
        updateLazy();
        if(ql<=l && r<=qr) return sum;
        if(r<ql || l>qr) return 0;

        return L->query(ql, qr) + R->query(ql, qr);
    }

    void update(int ql, int qr, int64_t change)
    {
        updateLazy();
        if(ql<=l && r<=qr)
        {
            sum += (r-l+1)*change;
            if(l!=r)
            {
                L->lazy += change;
                R->lazy += change;
            }

            return;
        }
        if(r<ql || l>qr)
            return;

        L->update(ql, qr, change);
        R->update(ql, qr, change);
        recalc();
    }
};


int in[MAXN + 5], out[MAXN + 5];
vector<int> dfsOrder;

vector<int> adj[MAXN + 5];

int depth[MAXN + 5];
int parent[MAXN + 5];
int64_t edgeVal[MAXN + 5];
int sparse[MAXLog+2][MAXN];

void dfs(int x, int last)
{
    if (last == -1)
    {
        depth[x] = 0;
    }
    else
    {
        depth[x] = depth[last] + 1;
    }
    parent[x] = last;

    in[x] = dfsOrder.size();
    dfsOrder.push_back(x);

    for (int y : adj[x])
    {
        if (y != last)
        {
            dfs(y, x);
        }
    }

    out[x] = dfsOrder.size();
    dfsOrder.push_back(x);
}

SegmentTreeNode *T;

void init (int N, std::vector< std::pair<int,int> > edges)
{
    for (const pair<int, int> &e : edges)
    {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    dfs(1, -1);

    T = new SegmentTreeNode(0, dfsOrder.size() - 1);
    T->build();

    for (int x = 1; x <= N; x++)
    {
        sparse[0][x] = parent[x];
    }
    for (int l = 1; l <= MAXLog; l++)
    {
        for (int x = 1; x <= N; x++)
        {
            if(sparse[l-1][x]==-1)
            {
                sparse[l][x] = -1;
            }
            else
            {
                sparse[l][x] = sparse[l-1][sparse[l-1][x]];
            }
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

bool question (int u, int v)
{
    int p = lca(u, v);
    if (in[u] > in[v])
    {
        swap(u, v);
    }

    int64_t pathVal = 0;
    if (p == u)
    {
        pathVal = T->query(in[u], in[v]);
    }
    else
    {
        pathVal = T->query(out[u], in[v]) + T->query(in[p], in[p]);
    }

    pathVal -= edgeVal[p];
    return (pathVal == 0);
}

void close (int u, int v)
{
    if (parent[v] == u)
    {
        swap(u, v);
    }
    if (edgeVal[u] != 0)
    {
        return;
    }

    edgeVal[u] = randInRange(1, 1e9);

    T->update(in[u], in[u], +edgeVal[u]);
    T->update(out[u], out[u], -edgeVal[u]);
}
