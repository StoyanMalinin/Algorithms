#include <iostream>

using namespace std;

const int MAXN = 1e4;
const int MAXM = 20;
const int inf = 1e9;

int n, m;
int s[MAXM+5];

int dp[2][MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<m;i++) cin >> s[i];
    if(n==0)
    {
        cout << "0" << '\n';
        return 0;
    }

    int ans = -inf;
    const int MAX_HITS = 70;
    for(int hitCount = 1;hitCount<=MAX_HITS;hitCount++)
    {
        for(int sum = 0;sum<=n;sum++) dp[0][sum] = -inf;
        dp[0][0] = 0;

        for(int hit = 1;hit<=hitCount;hit++)
        {
            for(int sum = 0;sum<=n;sum++) dp[hit&1][sum] = -inf;

            for(int i = 0;i<m;i++)
            {
                for(int sum = 0;sum+s[i]*(hitCount-hit+1)<=n;sum++)
                    dp[hit&1][sum+s[i]*(hitCount-hit+1)] = max(dp[hit&1][sum+s[i]*(hitCount-hit+1)], dp[(hit&1)^1][sum] + s[i]);
            }
        }

        ans = max(ans, dp[hitCount&1][n]);
    }


    if(ans<0) cout << "Impossible" << '\n';
    else cout << ans << '\n';
}
