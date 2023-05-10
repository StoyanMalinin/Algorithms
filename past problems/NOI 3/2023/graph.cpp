#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

const int MAXN = 5000;

int n, m = 0;
vector<int> adj[MAXN + 5];

bitset<MAXN + 5> dist2[MAXN + 5], dist1[MAXN + 5];

//O(n^2), provided that m <= n * sqrt(n)
bool checkCycle4()
{
    for (int x = 1; x <= n; x++)
    {
        for (int i = 0; i < adj[x].size(); i++)
        {
            for (int j = i + 1; j < adj[x].size(); j++)
            {
                int u = adj[x][i];
                int v = adj[x][j];
                if (dist2[u][v])
                {
                    return true;
                }

                dist2[u][v] = dist2[v][u] = 1;
            }
        }
    }

    return false;
}

//O(n ^ 2)
bool checkAnsEq2()
{
    if (m > n * sqrt(n))
    {
        return true;
    }

    return checkCycle4();
}

//O(n^2), provided that m <= n * sqrt(n)
bool checkCycle3()
{
    for (int x = 1; x <= n; x++)
    {
        for (int i = 0; i < adj[x].size(); i++)
        {
            for (int j = i + 1; j < adj[x].size(); j++)
            {
                int u = adj[x][i];
                int v = adj[x][j];
                if (dist1[u][v])
                {
                    return true;
                }
            }
        }
    }

    return false;
}

//O(n^2 * sqrt(n) / 32), provided that m <= n * sqrt(n)
//works, provided that there is no cycle of length 3 or 4
bool checkCycle5()
{
    for (int x = 1; x <= n; x++)
    {
        for (int y : adj[x])
        {
            if ((dist2[x] & dist2[y]).any())
            {
                return true;
            }
        }
    }

    return false;
}

//O(n^2 * sqrt(n) / 32), provided that m <= n * sqrt(n)
bool checkAnsEq3()
{
    if (checkCycle3())
    {
        return true;
    }

    if (checkCycle5())
    {
        return true;
    }

    return false;
}

bool checkAnsEq4()
{
    for (int x = 1; x <= n; x++)
    {
        if (!adj[x].empty())
        {
            return true;
        }
    }

    return false;
}

bool used[MAXN + 5];
void dfs(int x, vector<int> &cmp)
{
    used[x] = true;
    cmp.push_back(x);

    for (int y : adj[x])
    {
        if (!used[y])
        {
            dfs(y, cmp);
        }
    }
}

void deleteComponent(const vector<int> &cmp)
{
    int removed = 0;
    for (int x : cmp)
    {
        removed += adj[x].size();

        adj[x].clear();
        dist1[x].reset();
        dist2[x].reset();
    }

    m -= removed / 2;
}

void cleanBadComponents()
{
    for (int x = 1; x <= n; x++)
    {
        if (!used[x])
        {
            vector<int> cmp;
            dfs(x, cmp);

            if (cmp.size() <= 3)
            {
                deleteComponent(cmp);
                continue;
            }

            int cmpEdges = 0;
            for (int x : cmp)
            {
                cmpEdges += adj[x].size();
            }
            cmpEdges /= 2;

            if (cmpEdges == cmp.size() - 1)
            {
                for (int x : cmp)
                {
                    if (adj[x].size() == cmp.size() - 1)
                    {
                        deleteComponent(cmp);
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int x = 1; x < n; x++)
    {
        string s;
        cin >> s;

        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] == '1')
            {
                m++;
                adj[x].push_back(x + j + 1);
                adj[x + j + 1].push_back(x);

                dist1[x][x + j + 1] = dist1[x + j + 1][x] = 1;
            }
        }
    }

    cleanBadComponents();

    if (checkAnsEq2())
    {
        cout << "2" << '\n';
        return 0;
    }

    if (checkAnsEq3())
    {
        cout << "3" << '\n';
        return 0;
    }

    if (checkAnsEq4())
    {
        cout << "4" << '\n';
        return 0;
    }

    cout << "-1" << '\n';
}
