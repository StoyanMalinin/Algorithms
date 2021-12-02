#include <iostream>

using namespace std;

const int MAXN = 5e5 + 5;
const int64_t inf = 1e18;

int n, k;
int64_t a[MAXN+5];

int64_t dp[2][MAXN+5][2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 0;i<n;i++) cin >> a[i];

    int64_t ans;

    dp[0][n-1][0] = dp[0][n-1][1] = a[n-1];
    for(int i = n-2;i>=0;i--) dp[0][i][0] = dp[0][i][1] = a[i] + dp[0][i+1][0];
    ans = dp[0][0][0];

    for(int t = 1;t<=k;t++)
    {
        dp[t&1][n-1][0] = min(dp[t&1][n-1][0], -dp[(t-1)&1][n-1][0]);
        dp[t&1][n-1][1] = max(dp[t&1][n-1][1], -dp[(t-1)&1][n-1][1]);
        for(int i = n - 2;i>=0;i--)
        {
            dp[t&1][i][0] = min(-dp[(t-1)&1][i][1], a[i] + dp[t&1][i+1][0]);
            dp[t&1][i][1] = max(-dp[(t-1)&1][i][0], a[i] + dp[t&1][i+1][1]);
        }

        ans = min(ans, dp[t&1][0][0]);
    }

    cout << ans << '\n';
}
