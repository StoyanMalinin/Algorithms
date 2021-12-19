#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1000;
const int offset = 1e6;
const int MAXSUM = 2e6;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int a[MAXN+5];
    bool dp[MAXSUM+5] = {false};

    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];

    for(int i = 0;i<n;i++)
    {
        if(a[i]<=0)
        {
            for(int s = 0;s<=MAXSUM+a[i];s++)
                dp[s] |= dp[s-a[i]];
        }
        else
        {
            for(int s = MAXSUM;s>=a[i];s--)
                dp[s] |= dp[s-a[i]];
        }

        dp[a[i]+offset] = true;
    }

    int cnt = 0;
    for(int s = 0;s<=MAXSUM;s++)
        cnt += dp[s];

    cout << cnt << '\n';
}
