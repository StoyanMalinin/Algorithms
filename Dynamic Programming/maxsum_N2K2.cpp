#include <iostream>

using namespace std;

const int MAXN = 500;
const int MAXK = 50;

int n;
int k[MAXN+5];
int a[MAXN+5][MAXK+5];

int dp[MAXN+5][MAXK+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0;i<n;i++)
    {
        cin >> k[i];
        for(int j = 0;j<k[i];j++) cin >> a[i][j];
    }

    int ans = 0;
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<k[i];j++)
        {
            dp[i][j] = a[i][j];//само топче
            for(int iLast = 0;iLast<i;iLast++)
            {
                for(int jLast = 0;jLast<k[iLast];jLast++)
                {
                    if(a[iLast][jLast]<=a[i][j])
                        dp[i][j] = max(dp[i][j], dp[iLast][jLast]+a[i][j]);
                }
            }

            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans << '\n';
}
