#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 2e5;

int n, l, k;
int a[MAXN+5];

int numCnt[MAXN+5];
int dp[2][MAXN+5], dpPref[2][MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> l >> k;
    for(int i = 1;i<=n;i++) cin >> a[i];

    for(int i = 0;i<=n;i++)
        dp[0][i] = dpPref[0][i] = 0;
    for(int done = 1;done<=k;done++)
    {
        memset(numCnt, 0, sizeof(numCnt));
        for(int i = 0;i<=n;i++) dp[done&1][i] = MAXN;

        int ptr = 1, diffNums = 0;
        for(int i = 1;i<=n;i++)
        {
            if(numCnt[a[i]]==0) diffNums++;
            numCnt[a[i]]++;

            while(numCnt[a[ptr]]>1)
            {
                numCnt[a[ptr]]--;
                ptr++;
            }

            if(diffNums==l)
            {
                dp[done&1][i] = dpPref[(done&1)^1][ptr-1] + ((i-ptr+1) - l);
            }
        }

        int minVal = MAXN;
        for(int i = 0;i<=n;i++)
        {
            minVal = min(minVal, dp[done&1][i]);
            dpPref[done&1][i] = minVal;
        }
    }

    int ans = MAXN;
    for(int i = 1;i<=n;i++) ans = min(ans, dp[k&1][i]);

    cout << ans << '\n';
}
