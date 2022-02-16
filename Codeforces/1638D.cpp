#include <iostream>
#include <stack>

using namespace std;

const int MAXN = 1000;

int n, m;
int a[MAXN+5][MAXN+5];

int getColor(int i, int j)
{
    int color = -1;
    if(a[i][j]!=-1) color = a[i][j];
    else if(a[i+1][j]!=-1) color = a[i+1][j];
    else if(a[i][j+1]!=-1) color = a[i][j+1];
    else if(a[i+1][j+1]!=-1) color = a[i+1][j+1];

    return color;
}

bool checkCandidate(int i, int j)
{
    if(!(0<=i && 0<=j)) return false;
    if(!(i<n-1 && j<m-1)) return false;

    int color = getColor(i, j);
    if(color==-1) return false;

    if(!(a[i][j]==-1 || a[i][j]==color)) return false;
    if(!(a[i+1][j]==-1 || a[i+1][j]==color)) return false;
    if(!(a[i][j+1]==-1 || a[i][j+1]==color)) return false;
    if(!(a[i+1][j+1]==-1 || a[i+1][j+1]==color)) return false;

    return true;
}

void useCell(int i, int j)
{
    a[i][j] = -1;
    a[i+1][j] = -1;
    a[i][j+1] = -1;
    a[i+1][j+1] = -1;
}

void addNeighbours(stack <pair <int, int>> &candidates, int i, int j)
{
    for(int dRow = -1;dRow<=0;dRow++)
    {
        for(int dCol = -1;dCol<=0;dCol++)
        {
            if(checkCandidate(i+dRow, j+dCol)==true)
                candidates.push({i+dRow, j+dCol});
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            cin >> a[i][j];

    stack <pair <int, int>> candidates;
    for(int i = 0;i<n-1;i++)
        for(int j = 0;j<m-1;j++)
            if(checkCandidate(i, j)==true)
                candidates.push({i, j});

    stack <pair <pair <int, int>, int>> operations;
    while(candidates.empty()==false)
    {
        int i = candidates.top().first, j = candidates.top().second;
        candidates.pop();

        if(checkCandidate(i, j)==false) continue;

        operations.push(make_pair(make_pair(i, j), getColor(i, j)));
        useCell(i, j);

        for(int dRow = 0;dRow<=1;dRow++)
            for(int dCol = 0;dCol<=1;dCol++)
                addNeighbours(candidates, i+dRow, j+dCol);
    }

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            if(a[i][j]!=-1)
            {
                cout << "-1" << '\n';
                return 0;
            }
        }
    }

    cout << operations.size() << '\n';
    while(operations.empty()==false)
    {
        cout << operations.top().first.first + 1 << " " << operations.top().first.second + 1
             << " " << operations.top().second << '\n';
        operations.pop();
    }
}
