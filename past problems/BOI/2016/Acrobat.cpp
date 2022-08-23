#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 3e5;

struct Modification
{
    int type;
    int i, j;

    Modification(){}
    Modification(int type, int i, int j) : type(type), i(i), j(j) {}
};

int n, m;
bool parA[MAXN+5];
multiset <pair <int, int>> ropes;

bool used[2][MAXN+5];
vector <int> graphA[MAXN+5];
vector <int> graph2[2][MAXN+5];

struct Forest
{
    vector <int> adj[MAXN+5];

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int x, int last, const int ODD_CNT, vector <pair <int, int>> &edges)
    {
        int subOddCnt = 0;
        if(parA[x]==true) subOddCnt++;


        for(int y: adj[x])
        {
            if(y!=last)
            {
                subOddCnt += dfs(y, x, ODD_CNT, edges);
            }
        }

        if(last!=-1)
        {
            int par = (subOddCnt%2)*((ODD_CNT-subOddCnt)%2);
            if(par==1)
            {
                if(ropes.count(make_pair(x, last))==true)
                    edges.emplace_back(x, last);
                else
                    edges.emplace_back(last, x);
            }
        }

        return subOddCnt;
    }
};

Forest F;
int dfs1(int x)
{
    used[0][x] = true;

    int oddCnt = 0;
    if(parA[x]==true) oddCnt++;

    for(int y: graphA[x])
    {
        if(used[0][y]==false)
        {
            F.addEdge(x, y);
            oddCnt += dfs1(y);
        }
    }

    return oddCnt;
}

int dfs2(int side, int x, vector <int> &oddNodes)
{
    used[side][x] = true;
    if(side==1 && graph2[1][x].size()%2!=0)
        oddNodes.push_back(x);

    int sz = 1;
    for(int y: graph2[side][x])
    {
        if(used[side^1][y]==false)
            sz += dfs2(side^1, y, oddNodes);
    }

    return sz;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector <Modification> ans;

    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;

        ropes.emplace(u, v);
        graphA[u].push_back(v);
        graphA[v].push_back(u);
        parA[u] ^= true;
    }

    vector <pair <int, int>> edges;
    for(int x = 1;x<=n;x++)
    {
        if(used[0][x]==false)
        {
            int oddCnt = dfs1(x);
            F.dfs(x, -1, oddCnt, edges);

            if(oddCnt%2!=0)
            {
                cout << "-1" << '\n';
                return 0;
            }
        }
    }

    for(const auto& item: edges)
    {
        ropes.erase(ropes.find(item));
        ropes.emplace(item.second, item.first);

        ans.emplace_back(1, item.first, item.second);
    }

    for(auto item: ropes)
    {
        int u = item.first, v = item.second;

        graph2[0][u].push_back(v);
        graph2[1][v].push_back(u);
    }

    memset(used, 0, sizeof(used));
    vector <pair <int, int>> components;

    for(int x = 1;x<=n;x++)
    {
        if(used[1][x]==false)
        {
            vector <int> oddNodes;
            int sz = dfs2(1, x, oddNodes);

            if(sz>1)
            {
                while(oddNodes.size()>2)
                {
                    int x = oddNodes.back();oddNodes.pop_back();
                    int y = oddNodes.back();oddNodes.pop_back();
                    ans.emplace_back(2, x, y);
                }

                if(oddNodes.empty()==false)
                    components.emplace_back(oddNodes[0], oddNodes[1]);
                else
                    components.emplace_back(x, x);
            }
        }
    }

    if(components.empty()==false)
    {
        if(components.size()>1)
        {
            for(int i = 0;i+1<components.size();i++)
                ans.emplace_back(2, components[i].second, components[i+1].first);
            ans.emplace_back(2, components.front().first, components.back().second);
        }
        else
        {
            if(components.front().first!=components.front().second)
                ans.emplace_back(2, components.front().first, components.front().second);
        }
    }

    cout << ans.size() << '\n';
    for(const auto& item: ans)
        cout << item.type << " " << item.i << " " << item.j << '\n';

    return 0;
}
