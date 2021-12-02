#include <iostream>

using namespace std;

const int MAXN = 5e5;
const int64_t inf = 1e17;

int n, k;
int64_t a[MAXN+5];

//dp[i][j][0] - колко най малко ще ни струва да купим суфикса j....n-1 с не повече от i разговори
//dp[i][j][1] - колко най много ще ни струва да купим суфикса j....n-1 с не повече от i разговори
int64_t dp[3][MAXN+5][2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 0;i<n;i++) cin >> a[i];

    int64_t ans = inf;

    dp[0][n-1][0] = dp[0][n-1][1] = a[n-1];
    for(int i = n-2;i>=0;i--) dp[0][i][0] = dp[0][i][1] = a[i] + dp[0][i+1][0];
    ans = min(ans, dp[0][0][0]);

    if(k>=1)
    {
        dp[1][n-1][0] = min(dp[0][n-1][0], -dp[0][n-1][0]);
        dp[1][n-1][1] = min(dp[0][n-1][1], -dp[0][n-1][1]);
        for(int i = n - 2;i>=0;i--)
        {
            dp[1][i][0] = min(-dp[0][i][1], a[i] + dp[1][i+1][0]);
            dp[1][i][1] = max(-dp[0][i][0], a[i] + dp[1][i+1][1]);
        }


        ans = min(ans, dp[1][0][0]);
    }

    cout << ans << '\n';
}
