#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5;

int n;
vector <int> adj[MAXN+5];

int depth[MAXN+5];
void dfs(int x, int last, int level, vector <int> &eulerTour)
{
    depth[x] = level;

    eulerTour.push_back(x);
    for(int y: adj[x])
    {
        if(y!=last)
        {
            dfs(y, x, level+1, eulerTour);
            eulerTour.push_back(x);
        }
    }
}

int main()
{
    cin >> n;
    for(int i = 0;i<n-1;i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}
/*
//Figure 1
18
1 2
1 18
2 3
2 4
18 11
4 15
3 5
3 7
4 9
11 12
11 13
15 17
7 6
12 8
12 10
17 16
17 14

//Figure 2
9
1 2
1 3
2 4
2 5
5 7
5 8
3 6
6 9
*/
