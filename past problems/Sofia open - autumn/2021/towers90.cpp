#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 2000;
const int64_t mod = 1e9 + 7;

int64_t pref[MAXN+5][MAXN+5][2];
int64_t dp[MAXN+5][MAXN+5][2];

void doPref(int s)
{
    for(int par = 0;par<2;par++)
    {
        int64_t sum = 0;
        for(int h = 0;h<=MAXN+1;h++)
        {
            sum += dp[s][h][par];
            pref[s][h][par] = sum;
        }
    }
}

int64_t getSum(int par, int s, int h1, int h2)
{
    return pref[s][h2][par] - pref[s][h1-1][par];
}

int main()
{
    int n;
    cin >> n;

    dp[0][0][0] = 1;
    dp[0][MAXN+1][1] = 1;

    int64_t ans = 0;
    for(int s = 1;s<=n;s++)
    {
        doPref(s-1);

        for(int h = 1;h<=s;h++)
        {
            //0
            dp[s][h][0] = getSum(1, s-h, h+1, MAXN+1)%mod;

            //1
            dp[s][h][1] = getSum(0, s-h, 0, h-1)%mod;

            if(s==n)
                ans = (ans + dp[s][h][0] + dp[s][h][1])%mod;
        }
    }

    cout << (ans - 1 + mod)%mod << '\n';
}
