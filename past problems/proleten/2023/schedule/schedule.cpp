#include <iostream>
#include <random>
#include <vector>

using namespace std;

const int MAXN = 1e6;

vector<int> adj[MAXN + 5];
map<pair<int, int>, int> edgeInd;

int compCnt = 0;
int compId[MAXN + 5];

void init (int N, std::vector< std::pair<int,int> > edges)
{
    for (const pair<int, int> &e : edges)
    {
        edgeInd[{e.first, e.second}] = adj[e.first].size();
        edgeInd[{e.second, e.first}] = adj[e.second].size();

        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    dfs(1, -1);
}

struct DFSState
{
    int x, last;
    int ind;

    DFSState()
    {}
    DFSState(int x, int last, int ind) : x(x), last(last), ind(ind)
    {}

    void proceed(stack<DFSState> &st, vector<int> &cmp)
    {
        st.pop();

        if (ind < adj[x].size())
        {
            st.emplace(x, last, ind + 1);
            if (last != adj[x][ind])
            {
                st.emplace(adj[x][ind], x, 0);
            }
        }
    }
};

bool question (int u, int v)
{
    return (compId[u] == compId[v]);
}

void removeEdge(int u, int v)
{
    int pos = edgeInd[{u, v}];

    edgeInd[{u, adj[u].back()}] = pos;
    edgeInd.erase({u, v});

    swap(adj[u][pos], adj[u].back());
    adj[u].pop_back();
}

void close (int u, int v)
{
    removeEdge(u, v);
    removeEdge(v, u);
}
