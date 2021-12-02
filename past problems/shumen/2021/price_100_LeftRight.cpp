#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 5e5;
const int MAXK = 100;
const int64_t inf = 1e18;

int n, k;
int a[MAXN+5];

int64_t sign(int x)
{
    if(x%2==0) return +1;
    return -1;
}

int64_t dp[2][MAXK];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 0;i<n;i++) cin >> a[i];

    dp[0&1][0] = a[0];
    for(int talks = 1;talks<=k;talks++)
        dp[0&1][talks] = -dp[0&1][talks-1];

    for(int i = 1;i<n;i++)
    {
        for(int talks = 0;talks<=k;talks++)
        {
            int64_t opt1 = inf, opt2 = inf;

            //да сме говорили
            if(talks!=0) opt1 = dp[(i-1)&1][talks-1] + sign(talks)*a[i];

            //да не сме говорили
            opt2 = dp[(i-1)&1][talks] + sign(talks)*a[i];

            dp[i&1][talks] = min(opt1, opt2);
        }
    }

    int64_t ans = inf;
    for(int talks = 0;talks<=k;talks++)
        ans = min(ans, dp[(n-1)&1][talks]);

    cout << ans << '\n';
}
