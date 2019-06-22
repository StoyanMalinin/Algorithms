#include<iostream>
#include<cstring>
#include<vector>
#include<stack>
#include<map>
#include<algorithm>

using namespace std;

const int MAXN = 3e5 + 5;

struct edge
{
    int u, v;
};

int n, m;
int A, B;
vector <edge> allEdges;

vector <int> graph[MAXN];
vector <int> graphOriginal[MAXN], graphDirected[MAXN], graphDirectedInv[MAXN];

stack <int> st;
bool used[MAXN];
vector <int> elements[MAXN];
int component[MAXN], componentCnt = 0;

void DFSDirect(int x, int last)
{
    used[x] = true;

    for(int i = 0;i<graphOriginal[x].size();i++)
    {
        int y = graphOriginal[x][i];
        if(y==last) continue;

        graphDirected[x].push_back(y);
        graphDirectedInv[y].push_back(x);

        if(used[y]==false)
        {
            DFSDirect(y, x);
        }
    }
}

void DFSLoad(int x)
{
    used[x] = true;

    for(int i = 0;i<graphDirected[x].size();i++)
    {
        int y = graphDirected[x][i];

        if(used[y]==false)
        {
            DFSLoad(y);
        }
    }

    st.push(x);
}

void DFSGen(int x)
{
    used[x] = true;
    component[x] = componentCnt;
    elements[componentCnt].push_back(x);

    for(int i = 0;i<graphDirectedInv[x].size();i++)
    {
        int y = graphDirectedInv[x][i];

        if(used[y]==false)
        {
            DFSGen(y);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int u, v, value;
        cin >> u >> v >> value;

        graphOriginal[u].push_back(v);
        graphOriginal[v].push_back(u);
    }

    memset(used, false, sizeof(used));
    DFSDirect(1, -1);

    memset(used, false, sizeof(used));
    for(int i = 1;i<=n;i++)
    {
        if(used[i]==false)
        {
            DFSLoad(i);
        }
    }

    memset(used, false, sizeof(used));
    while(st.empty()==false)
    {
        if(used[st.top()]==false)
        {
            componentCnt++;
            DFSGen(st.top());
        }

        st.pop();
    }

    cout << " --- Components --- " << '\n';
    for(int i = 1;i<=componentCnt;i++)
    {
        cout << i << ":";
        for(int j = 0;j<elements[i].size();j++)
        {
            cout << " " << elements[i][j];
        }
        cout << '\n';
    }
}
