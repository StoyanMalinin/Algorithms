#include <iostream>

using namespace std;

const int MAXN = 30;

int64_t dpPref[MAXN+5][MAXN+5];
int64_t dp[MAXN+5][MAXN+5];

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    dp[0][0] = 1;//празната редица

    dpPref[0][0] = dp[0][0];
    for(int x = 1;x<=m;x++) dpPref[0][x] = dpPref[0][x-1] + dp[0][x];

    for(int len = 1;len<=n;len++)
    {
        for(int x = 1;x<=m;x++)
        {
            for(int p = 1;p<=min(len, k);p++)
            {
                dp[len][x] += dpPref[len-p][x-1];
            }
        }

        dpPref[len][0] = dp[len][0];
        for(int x = 1;x<=m;x++) dpPref[len][x] = dpPref[len][x-1] + dp[len][x];
    }

    int64_t ans = 0;
    for(int x = 1;x<=m;x++) ans += dp[n][x];

    cout << ans << '\n';
}
