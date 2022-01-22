#include <iostream>

using namespace std;

const int MAXN = 2005;

int n, m, k, s;
int a[MAXN][MAXN];

int upLeft[11], upRight[11];
int maxDist[11][11];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> s;
    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            cin >> a[i][j];

    for(int i = 1;i<=k;i++)
        upLeft[i] = upRight[i] = -MAXN*5;

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            upLeft[a[i][j]] = max(upLeft[a[i][j]], -j-i);
            upRight[a[i][j]] = max(upRight[a[i][j]], j-i);

            for(int p = 1;p<=k;p++)
            {
                maxDist[a[i][j]][p] = max(maxDist[a[i][j]][p], j+i+upLeft[p]);
                maxDist[a[i][j]][p] = max(maxDist[a[i][j]][p], -j+i+upRight[p]);

                maxDist[p][a[i][j]] = max(maxDist[p][a[i][j]], maxDist[a[i][j]][p]);
            }
        }
    }

    int ans = 0;

    int last;
    cin >> last;
    for(int i = 1;i<s;i++)
    {
        int x;
        cin >> x;

        ans = max(ans, maxDist[last][x]);
        last = x;
    }

    cout << ans << '\n';
}
