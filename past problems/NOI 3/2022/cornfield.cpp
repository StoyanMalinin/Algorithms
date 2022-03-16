#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <array>

using namespace std;

const int MAXN = 1000;
const array <pair <int, int>, 4> moves = {make_pair(0, -1), make_pair(0, +1), make_pair(-1, 0), make_pair(+1, 0)};

struct GroupMember
{
    int i, j, s;
};

int n, m, k;
int grid[MAXN+5][MAXN];
GroupMember members[MAXN*MAXN+5];

bool isInside(int i, int j)
{
    if(i<0 || j<0) return false;
    if(i>=n || j>=m) return false;

    return true;
}

bool isBorder(int i, int j)
{
    return i==0 || j==0 || i==n-1 || j==m-1;
}

bool used[MAXN+5][MAXN+5];
bool dfs(int i, int j, int s)
{
    used[i][j] = true;
    bool ans = isBorder(i, j);

    for(pair <int, int> mv: moves)
    {
        if(isInside(i+mv.first, j+mv.second)==true && used[i+mv.first][j+mv.second]==false
           && grid[i+mv.first][j+mv.second]<=s)
        {
            ans |= dfs(i+mv.first, j+mv.second, s);
        }
    }

    return ans;
}

bool check(int D)
{
    memset(used, false, sizeof(used));
    for(int i = 0;i<k;i++)
    {
        if(used[members[i].i][members[i].j]==false)
        {
            if(grid[members[i].i][members[i].j]>members[i].s+D)
                return false;

            bool res = dfs(members[i].i, members[i].j, members[i].s+D);
            if(res==false) return false;
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for(int i = 0;i<n;i++)
        for(int j =0 ;j<m;j++)
            cin >> grid[i][j];
    for(int i = 0;i<k;i++)
    {
        cin >> members[i].i >> members[i].j >> members[i].s;
        members[i].i--;members[i].j--;
    }

    sort(members, members+k,
    [](const GroupMember &A, const GroupMember &B)
    {
        return A.s > B.s;
    });

    int l = 0, r = 1e9, mid;
    while(l+1<r)
    {
        mid = (l+r)/2;

        if(check(mid)==true) r = mid;
        else l = mid + 1;
    }

    if(check(l)==true) cout << l << '\n';
    else cout << r << '\n';
}
