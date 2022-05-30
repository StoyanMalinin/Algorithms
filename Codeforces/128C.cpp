#include <iostream>

using namespace std;

const int MAXN = 1000;
const int64_t mod = 1e9 + 7;

int64_t dp[MAXN+5][MAXN+5];

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    if(n<m) swap(n, m);
    k++;

    for(int i = 1;i<=n;i++) dp[1][i] = 1;
    for(int turn = 2;turn<=k;turn++)
    {
        int64_t sum1 = 0, sum2 = 0;
        for(int i = 3;i<=n;i++)
        {
            sum1 += dp[turn-1][i-2];
            sum2 += dp[turn-1][i-2]*(i-2+1);
            sum1 %= mod;sum2 %= mod;

            dp[turn][i] = (i*sum1 - sum2 + 5*mod)%mod;
        }
    }

    cout << (dp[k][n]*dp[k][m])%mod << '\n';
}
