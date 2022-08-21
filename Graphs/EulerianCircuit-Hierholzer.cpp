#include <algorithm>
#include <iostream>
#include <vector>
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
    int id;

    Adjacent(){}
    Adjacent(int y, int id) : y(y), id(id) {}
};

int n, m;
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
void addEdge(int u, int v)
{
    graph[u].emplace_back(v, _addEdge::edgeId);
    graph[v].emplace_back(u, _addEdge::edgeId);
    _addEdge::edgeId++;
}

vector <int> getEulerianCircuit()
{
    vector <int> edgeInd(n+1, 0);
    vector <bool> usedEdges(_addEdge::edgeId, false);

    stack <int> currPath;
    vector <int> res;

    currPath.push(1);
    while(currPath.empty()==false)
    {
        int x = currPath.top();

        while(edgeInd[x]<graph[x].size() && usedEdges[graph[x][edgeInd[x]].id]==true)
            edgeInd[x]++;

        if(edgeInd[x]<graph[x].size())
        {
            currPath.push(graph[x][edgeInd[x]].y);
            usedEdges[graph[x][edgeInd[x]].id] = true;

            edgeInd[x]++;
        }
        else
        {
            currPath.pop();
            res.push_back(x);
        }
    }

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

        addEdge(u, v);
    }

    vector <int> circuit = getEulerianCircuit();

    cout << circuit.size() - 1 << '\n';
    for(int x: circuit) cout << x << " ";
    cout << '\n';
}

