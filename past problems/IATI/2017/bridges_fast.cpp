#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000;

int n, m;
vector <int> graph[MAXN+5];

bool used[MAXN+5];

void dfs(int x, vector <int> &oddNodes)
{
    used[x] = true;
    if(graph[x].size()%2!=0) oddNodes.push_back(x);

    for(int y: graph[x])
    {
        if(used[y]==false) dfs(y, oddNodes);
    }
}

int main()
{
    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector <pair <int, int>> ans;

    vector <pair <int, int>> components;
    for(int x = 1;x<=n;x++)
    {
        if(used[x]==false)
        {
            vector <int> oddNodes;
            dfs(x, oddNodes);

            while(oddNodes.size()>2)
            {
                int x = oddNodes.back();oddNodes.pop_back();
                int y = oddNodes.back();oddNodes.pop_back();
                ans.emplace_back(x, y);
            }

            if(oddNodes.size()==2) components.emplace_back(oddNodes[0], oddNodes[1]);
            else components.emplace_back(x, x);
        }
    }

    if(components.size()==1)
    {
        if(components.front().first!=components.front().second)
            ans.emplace_back(components.front().first, components.front().second);
    }
    else
    {
        for(int i = 0;i+1<components.size();i++)
            ans.emplace_back(components[i].second, components[i+1].first);
        ans.emplace_back(components.front().first, components.back().second);
    }

    cout << ans.size() << '\n';
    for(const auto& item: ans) cout << item.first << " " << item.second << '\n';
}
