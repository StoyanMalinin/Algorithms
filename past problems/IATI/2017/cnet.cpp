#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 1600;

int n;

bool used[MAXN+5];
vector <int> graph[MAXN+5], invGraph[MAXN+5];

int inDeg[MAXN+5];
int compId[MAXN+5];
vector <int> cGraph[MAXN+5];

void dfs1(int x, stack <int> &st)
{
    used[x] = true;
    for(int y: graph[x])
    {
        if(used[y]==false)
            dfs1(y, st);
    }

    st.push(x);
}

void dfs2(int x, int id)
{
    used[x] = true;
    compId[x] = id;

    for(int y: invGraph[x])
    {
        if(used[y]==false)
            dfs2(y, id);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> n >> m;

    for(int i = 0;i<m;i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        invGraph[v].push_back(u);
    }

    stack <int> st;
    memset(used, 0, sizeof(used));
    for(int x = 0;x<n;x++)
    {
        if(used[x]==false)
        {
            dfs1(x, st);
        }
    }

    int compNum = 0;
    memset(used, 0, sizeof(used));
    while(st.empty()==false)
    {
        int x = st.top();
        st.pop();

        if(used[x]==false)
        {
            dfs2(x, compNum);
            compNum++;
        }
    }

    if(compNum==1)
    {
        cout << "1 0" << '\n';
        return 0;
    }

    for(int x = 0;x<n;x++)
    {
        for(int y: graph[x])
        {
            if(compId[x]!=compId[y])
                cGraph[compId[x]].push_back(compId[y]);
        }
    }

    for(int x = 0;x<compNum;x++)
    {
        sort(cGraph[x].begin(), cGraph[x].end());
        cGraph[x].resize(unique(cGraph[x].begin(), cGraph[x].end()) - cGraph[x].begin());
    }

    for(int x = 0;x<compNum;x++)
    {
        for(int y: cGraph[x]) inDeg[y]++;
    }

    int ans1 = 0;
    for(int x = 0;x<compNum;x++)
    {
        if(inDeg[x]==0) ans1++;
    }

    int sources = 0, sinks = 0;
    for(int x = 0;x<compNum;x++)
    {
        if(inDeg[x]==0) sources++;
        if(cGraph[x].size()==0) sinks++;
    }
    int ans2 = max(sources, sinks);

    cout << ans1 << " " << ans2 << '\n';
}
