#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <set>
#include <map>

using namespace std;

const int MAXN = 1e5;

struct PersistentDSU
{
    struct Log
    {
        int x, y, sz, parent;
        Log(int x, int y, int sz, int parent) : x(x), y(y), sz(sz), parent(parent) {}
    };
    stack <Log> st;

    int parent[MAXN+5];
    int sz[MAXN];

    PersistentDSU(int n)
    {
        for(int x = 1;x<=n;x++)
        {
            parent[x] = x;
            sz[x] = 1;
        }
    }

    int Find(int x)
    {
        if(parent[x]==x) return x;
        return Find(parent[x]);
    }

    void Union(int x, int y)
    {
        x = Find(x);
        y = Find(y);
        if(sz[x]<sz[y]) swap(x, y);

        //Save
        st.emplace(x, y, sz[x], parent[y]);

        if(x==y) return;

        //Update
        sz[x] += sz[y];
        parent[y] = x;
    }

    bool rollback()
    {
        if(st.empty()==true) return false;

        sz[st.top().x] = st.top().sz;
        parent[st.top().y] = st.top().parent;

        st.pop();

        return true;
    }

    bool areConnected(int u, int v)
    {
        return (Find(u)==Find(v));
    }
};

struct Edge
{
    int u, v;

    Edge(int u, int v)
    {
        if(u>v) swap(u, v);
        this->u = u;
        this->v = v;
    }
};

bool operator <(const Edge& A, const Edge& B)
{
    if(A.u!=B.u) return A.u<B.u;
    return A.v<B.v;
}

struct AskQuery;
struct Query
{
    virtual void execute(map <Edge, int> &availableEdges, vector <tuple<Edge, int, int>> &edgeSegments, vector <AskQuery> &asks) const = 0;
    virtual ~Query() = default;
};

struct AddQuery : public Query
{
    Edge e;

    AddQuery(int u, int v) : e(u, v) {}

    void execute(map <Edge, int> &availableEdges, vector <tuple<Edge, int, int>> &edgeSegments, vector <AskQuery> &asks) const override
    {
        if(availableEdges.count(e)==false)
            availableEdges[e] = asks.size();
    }
};

struct RemQuery : public Query
{
    Edge e;
    RemQuery(int u, int v) : e(u, v) {}

    void execute(map <Edge, int> &availableEdges, vector <tuple<Edge, int, int>> &edgeSegments, vector <AskQuery> &asks) const override
    {
        if(availableEdges.count(e)==true)
        {
            edgeSegments.emplace_back(e, availableEdges[e], asks.size()-1);
            availableEdges.erase(e);
        }
    }
};

struct AskQuery : public Query
{
    Edge e;
    AskQuery(int u, int v) : e(u, v) {}

    void execute(map <Edge, int> &availableEdges, vector <tuple<Edge, int, int>> &edgeSegments, vector <AskQuery> &asks) const override
    {
        asks.push_back(*this);
    }
};

struct QuerySegmentTreeNode
{
    vector <Edge> edges;

    int l, r;
    QuerySegmentTreeNode *L, *R;

    QuerySegmentTreeNode(int l, int r) : l(l), r(r), L(nullptr), R(nullptr) {}

    void build()
    {
        if(l==r) return;

        L = new QuerySegmentTreeNode(l, (l+r)/2);
        R = new QuerySegmentTreeNode((l+r)/2+1, r);

        L->build();
        R->build();
    }

    void addEdge(int ql, int qr, const Edge& e)
    {
        if(ql<=l && r<=qr)
        {
            edges.push_back(e);
            return;
        }
        if(r<ql || qr<l)
            return;

        L->addEdge(ql, qr, e);
        R->addEdge(ql, qr, e);
    }

    void answerQueries(PersistentDSU &dsu, const vector<AskQuery> &asks, vector <bool> &ans)
    {
        for(const Edge &e: edges)
        {
            dsu.Union(e.u, e.v);
        }

        if(l==r)
        {
            ans[l] = dsu.areConnected(asks[l].e.u, asks[l].e.v);
        }
        else
        {
            L->answerQueries(dsu, asks, ans);
            R->answerQueries(dsu, asks, ans);
        }

        for(int i = 0;i<edges.size();i++)
        {
            dsu.rollback();
        }
    }

    ~QuerySegmentTreeNode()
    {
        delete L;
        delete R;
    }
};

void evaluate(int n, const vector<const Query*> &queries, vector <bool> &ans)
{
    map <Edge, int> availableEdges;
    vector <tuple<Edge, int, int>> edgeSegments;
    vector <AskQuery> asks;

    for(const Query* q: queries) q->execute(availableEdges, edgeSegments, asks);
    for(auto item: availableEdges) edgeSegments.emplace_back(item.first, item.second, ((int)asks.size())-1);

    QuerySegmentTreeNode *T = new QuerySegmentTreeNode(0, ((int)asks.size())-1);
    T->build();

    for(const auto &item: edgeSegments)
    {
        T->addEdge(get<1>(item), get<2>(item), get<0>(item));
    }

    PersistentDSU dsu(n);
    ans.resize(asks.size());
    T->answerQueries(dsu, asks, ans);

    delete T;
}

int main()
{

}

