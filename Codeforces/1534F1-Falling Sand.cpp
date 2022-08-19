#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const int MAXN = 400050;

char table[MAXN];
int nextSandblock[MAXN], n, m;

vector <int> graph[MAXN];
vector <int> inverse_graph[MAXN];

void ConstructGraphs()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> table[i*m + j];

    for (int i = 0; i < m; i++)
    {
        int a;
        cin >> a;
    }
    for (int j = 0; j < m; j++)
    {
        int last = -1;
        for (int i = n-1; i >= 0; i--)
        {
            nextSandblock[j*n + i] = last;
            if (table[i*m + j] == '#')
                last = i;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (table[i*m + j] != '#')
                continue;

            if (j > 0) //left
            {
                int leftNeighbour = nextSandblock[(j-1)*n + i]; //strictly bellow
                if (table[i*m + j - 1] == '#')
                    leftNeighbour = i;

                if (leftNeighbour != -1)
                {
                    graph[i*m+j].push_back(leftNeighbour*m + j - 1);
                    inverse_graph[leftNeighbour*m + j - 1].push_back(i*m+j);
                }

            }

            if (j < m-1) //right
            {
                int rightNeighbour = nextSandblock[(j+1)*n + i]; //not strictly bellow
                if (table[i*m + j + 1] == '#')
                    rightNeighbour = i;

                if (rightNeighbour != -1)
                {
                    graph[i*m + j].push_back(rightNeighbour*m + j + 1);
                    inverse_graph[rightNeighbour*m + j + 1].push_back(i*m+j);
                }


            }

            if (i < n-1) // down
            {
                int downNeighbour = nextSandblock[j*n + i];
                if (downNeighbour != -1)
                {
                    graph[i*m + j].push_back(downNeighbour*m + j);
                    inverse_graph[downNeighbour*m + j].push_back(i*m+j);
                }
            }

            if (i > 0) // up
            {
                int upNeighbour = -1;
                if (table[(i-1)*m + j] == '#')
                    upNeighbour = i-1;

                if (upNeighbour != -1)
                {
                    graph[i*m + j].push_back(upNeighbour*m + j);
                    inverse_graph[upNeighbour*m + j].push_back(i*m+j);
                }
            }
        }
    }

}

int componentID[MAXN];
bool used[MAXN];
stack <int> st;

void dfs1(int curr)
{
    used[curr] = true;

    for (int i:graph[curr])
        if (!used[i])
            dfs1(i);

    st.push(curr);
}

void dfs2(int curr, int ID)
{
    used[curr] = true;
    componentID[curr] = ID;

    for (int i:inverse_graph[curr])
        if (!used[i])
            dfs2(i, ID);
}
int main()
{
    ios::sync_with_stdio(NULL);
    cin.tie(0);

    set <int> inEdges;

    ConstructGraphs();

    for (int i = 0; i < n*m; i++)
    {
        if (table[i] == '#' && !used[i])
        {
            dfs1(i);
        }
    }


    memset(used, 0, sizeof(used));
    int id = 0;
    while (!st.empty())
    {
        int k = st.top();
        st.pop();

        if (!used[k])
        {
            dfs2(k, id);
            id++;
        }

    }

    for (int i = 0; i < n*m; i++)
    {
        if (table[i] == '#')
        {
            for (int j:graph[i])
            {
                if (componentID[i] != componentID[j])
                {
                    inEdges.insert(componentID[j]);
                }
            }
        }
    }

    cout << id - inEdges.size() << endl;


    return 0;
}
