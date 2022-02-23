#include <iostream>

using namespace std;

const int inf = 1e8;

const int MAXN = 2e4;
const int MAXP = 100;
const int MAXK = 50;

int n, k, p;
int a[MAXN+5];

int dp[MAXN+5][MAXK+5];
int sumOpt[MAXP+5], sumOptNew[MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;
    for(int i = 0;i<n;i++) cin >> a[i];

    int sum = 0;
    for(int i = 0;i<n;i++)
    {
        sum = (sum + a[i])%p;
        dp[i][1] = sum;
    }

    for(int fragments = 2;fragments<=k;fragments++)
    {
        for(int x = 0;x<=p;x++)
            sumOpt[x] = sumOptNew[x] = -inf;

        for(int i = 1;i<n;i++)
        {
            dp[i][fragments] = -1;

            for(int x = 0;x<=p;x++)
                sumOptNew[(x+a[i])%p] = sumOpt[x];
            sumOptNew[a[i]%p] = max(sumOptNew[a[i]%p], dp[i-1][fragments-1]);

            for(int x = 0;x<=p;x++)
                sumOpt[x] = sumOptNew[x];

            for(int x = 0;x<=p;x++)
                dp[i][fragments] = max(dp[i][fragments], x + sumOpt[x]);
        }
    }

    cout << dp[n-1][k] << '\n';
}
