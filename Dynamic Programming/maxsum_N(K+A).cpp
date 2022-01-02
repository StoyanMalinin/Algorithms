#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 500;
const int MAXK = 50;
const int MAXA = 1000;

int n;
int k[MAXN+5];
int a[MAXN+5][MAXK+5];

int dp[2][MAXA+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0;i<n;i++)
    {
        cin >> k[i];
        for(int j = 0;j<k[i];j++) cin >> a[i][j];
        sort(a[i], a[i]+k[i]);
    }

    for(int i = 0;i<n;i++)
    {
        int ptr = 0;
        int maxDpVal = 0;

        for(int j = 0;j<k[i];j++)
        {
            if(i>=1)
            {
                while(ptr+1<=a[i][j])
                {
                    maxDpVal = max(maxDpVal, dp[(i-1)&1][ptr+1]);
                    ptr++;
                }
            }

            dp[i&1][a[i][j]] = maxDpVal + a[i][j];
        }

        if(i>=1)
        {
            for(int x = 1;x<=MAXA;x++)
                dp[i&1][x] = max(dp[i&1][x], dp[(i-1)&1][x]);
        }
    }

    int ans = 0;
    for(int x = 1;x<=MAXA;x++)
        ans = max(ans, dp[(n-1)&1][x]);

    cout << ans << '\n';
}
