#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

int n, m;
int u, v;
vector <int> graph[MAXN];

int discTime;
bool used[MAXN];
int parent[MAXN], disc[MAXN], minValue[MAXN];

bool ap[MAXN];

void DFS(int x, int last)
{
    used[x] = true;
    parent[x] = last;

    disc[x] = discTime;
    discTime++;

    int children = 0;
    minValue[x] = disc[x];

    for(int i = 0;i<graph[x].size();i++)
    {
        if(used[ graph[x][i] ]==false)
        {
            DFS(graph[x][i], x);
            minValue[x] = min(minValue[x], minValue[ graph[x][i] ]);

            children++;
            if(last!=-1)
            {
                if(disc[x]<=minValue[ graph[x][i] ])
                {
                    ap[x] = true;
                }
            }
            else
            {
                if(children>=2)
                {
                    ap[x] = true;
                }
            }
        }
        else if(graph[x][i]!=last)
        {
            minValue[x] = min(minValue[x], disc[ graph[x][i] ]);
        }
    }
}

void findAP()
{
    memset(ap, false, sizeof(ap));
    memset(used, false, sizeof(used));

    DFS(1, -1);

    int found = 0;
    for(int i = 1;i<=n;i++)
    {
        if(ap[i]==true)
        {
            cout << i << " ";
        }
    }
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);

    }

    findAP();
}
