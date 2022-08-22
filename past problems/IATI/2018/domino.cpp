#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <set>

using namespace std;

const int MAXN = 1024;

struct Edge
{
    int u, v;
    bool isAdditional;

    Edge(){}
    Edge(int u, int v, bool isAdditional) : u(u), v(v), isAdditional(isAdditional) {}
};

struct Adjacent
{
    int y;
    bool isAdditional;
    int id;

    Adjacent(){}
    Adjacent(int y, bool isAdditional, int id) : y(y), isAdditional(isAdditional), id(id) {}
};

int n, m;
bool seenDotCount[MAXN+5];
vector <Adjacent> graph[MAXN+5];

bool used[MAXN+5];
void dfs(int x, vector <int> &oddNodes)
{
    used[x] = true;
    if(graph[x].size()%2!=0) oddNodes.push_back(x);

    for(Adjacent e: graph[x])
    {
        if(used[e.y]==false) dfs(e.y, oddNodes);
    }
}

namespace _addEdge
{
    int edgeId = 0;
}
void addEdge(int u, int v, bool isAdditional)
{
    graph[u].emplace_back(v, isAdditional, _addEdge::edgeId);
    graph[v].emplace_back(u, isAdditional, _addEdge::edgeId);
    _addEdge::edgeId++;
}

vector <Edge> getEulerianCircuit()
{
    vector <int> edgeInd(n+1, 0);
    vector <bool> usedEdges(_addEdge::edgeId, false);

    stack <pair<int, Edge>> currPath;
    vector <Edge> res;

    int start = -1;
    for(int x = 0;x<=n;x++)
    {
        if(seenDotCount[x]==true)
        {
            start = x;
            break;
        }
    }

    currPath.emplace(start, Edge(-1, -1, false));
    while(currPath.empty()==false)
    {
        int x = currPath.top().first;
        Edge e = currPath.top().second;

        while(edgeInd[x]<graph[x].size() && usedEdges[graph[x][edgeInd[x]].id]==true)
            edgeInd[x]++;

        if(edgeInd[x]<graph[x].size())
        {
            currPath.emplace(graph[x][edgeInd[x]].y, Edge(x, graph[x][edgeInd[x]].y, graph[x][edgeInd[x]].isAdditional));
            usedEdges[graph[x][edgeInd[x]].id] = true;

            edgeInd[x]++;
        }
        else
        {
            currPath.pop();
            res.push_back(e);
        }
    }

    res.pop_back();
    reverse(res.begin(), res.end());

    return res;
}

bool removed[MAXN+5][MAXN+5];

int main()
{
    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;
        if(u>v) swap(u, v);

        removed[u][v] = true;
    }

    for(int u = 0;u<=n;u++)
    {
        for(int v = u;v<=n;v++)
        {
            if(removed[u][v]==false)
            {
                seenDotCount[u] = true;
                seenDotCount[v] = true;
                addEdge(u,v, false);
            }
        }
    }

    vector <pair <int, int>> components;
    for(int x = 0;x<=n;x++)
    {
        if(used[x]==false && seenDotCount[x]==true)
        {
            vector <int> oddNodes;
            dfs(x, oddNodes);

            while(oddNodes.size()>2)
            {
                int x = oddNodes.back();oddNodes.pop_back();
                int y = oddNodes.back();oddNodes.pop_back();
                addEdge(x, y, true);
            }

            if(oddNodes.size()==2) components.emplace_back(oddNodes[0], oddNodes[1]);
            else components.emplace_back(x, x);
        }
    }

    if(components.size()==1)
    {
        if(components.front().first!=components.front().second)
            addEdge(components.front().first, components.front().second, true);
    }
    else
    {
        for(int i = 0;i+1<components.size();i++)
            addEdge(components[i].second, components[i+1].first, true);
        addEdge(components.front().first, components.back().second, true);
    }

    vector <Edge> circuit = getEulerianCircuit();
    vector <vector<Edge>> chains(1);

    for(const Edge& e: circuit)
    {
        if(e.isAdditional==false) chains.back().push_back(e);
        else
        {
            if(chains.back().empty()==false)
                chains.push_back({});
        }
    }

    if(chains.size()>1)
    {
        for(const Edge &e: chains[0]) chains.back().push_back(e);
        chains.erase(chains.begin());
    }

    cout << chains.size() << '\n';
    for(const auto& chain: chains)
    {
        if(chain.empty()==false)
        {
             cout << chain[0].u << " ";
            for(const Edge& e: chain) cout << e.v << " ";
            cout << "-1" << '\n';
        }
    }
}
