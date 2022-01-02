#include <iostream>

using namespace std;

const int MAXN = 30;

int64_t dp[MAXN+5][MAXN+5];

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    dp[0][0] = 1;//�������� ������
    for(int len = 1;len<=n;len++)
    {
        for(int x = 1;x<=m;x++)
        {
            for(int p = 1;p<=min(len, k);p++)
            {
                for(int y = 0;y<x;y++)
                {
                    dp[len][x] += dp[len-p][y];
                }
            }
        }
    }

    int64_t ans = 0;
    for(int x = 1;x<=m;x++) ans += dp[n][x];

    cout << ans << '\n';
}
