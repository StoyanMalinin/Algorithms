#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 405;

const vector <pair <int ,int>> deltaUp = {{-1, 0}, {0, +1}, {+1, +1}, {+1, 0}, {0, -1}, {-1, -1}};
const vector <pair <int, int>> deltaMid = {{-1, 0}, {0, +1}, {+1, 0}, {+1, -1}, {0, -1}, {-1, -1}};
const vector <pair <int, int>> deltaDown = {{-1, +1}, {0, +1}, {+1, 0}, {+1, -1}, {0, -1}, {-1, 0}};

pair <int, int> operator +(pair <int, int> A, pair <int, int> B)
{
    return make_pair(A.first+B.first, A.second+B.second);
}

int k;
int a[MAXN][MAXN];

pair <int, int> transition(pair <int, int> x, int dir)
{
    if(x.first==k) return x + deltaMid[dir];
    if(x.first<k) return x + deltaUp[dir];
    if(x.first>k) return x + deltaDown[dir];
}

int inv(int dir)
{
    if(dir==0) return 3;
    if(dir==1) return 4;
    if(dir==2) return 5;
    if(dir==3) return 0;
    if(dir==4) return 1;
    if(dir==5) return 2;
}

bool isInside(pair <int, int> x)
{
    if(x.first<=0 || x.second<=0) return false;

    if(x.first>2*k-1) return false;
    if(x.second>(k+2)-abs(x.first-k)) return false;

    return true;
}

bool canTransition(pair <int, int> x, int dir)
{
    pair <int, int> y = transition(x, dir);
    if(isInside(y)==false)  return false;

    if(((a[x.first][x.second]>>dir)&1)==1 && ((a[y.first][y.second]>>inv(dir))&1)==1) return true;
    return false;
}

bool used[MAXN][MAXN];
void dfs(pair <int, int> x, int &sz)
{
    sz++;
    used[x.first][x.second] = true;

    for(int dir = 0;dir<6;dir++)
    {
        if(canTransition(x, dir)==true)
        {
            pair <int, int> y = transition(x, dir);
            if(used[y.first][y.second]==false) dfs(y, sz);
        }
    }
}

int main()
{
    cin >> k;
    for(int i = 1;i<=2*k-1;i++)
        for(int j = 1;j<=(k+2)-abs(k-i);j++)
            cin >> a[i][j];

    int ans = 0;
    for(int i = 1;i<=2*k-1;i++)
    {
        for(int j = 1;j<=(k+2)-abs(k-i);j++)
        {
            if(used[i][j]==false)
            {
                int curr = 0;
                dfs(make_pair(i, j), curr);

                ans = max(ans, curr);
            }
        }
    }

    cout << ans << '\n';
}
