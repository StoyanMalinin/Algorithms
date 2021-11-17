#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 5000;
const int64_t mod = 1e9 + 7;

int32_t pref[MAXN+5][MAXN+5][2];
int32_t dp[MAXN+5][2];

void doPref(int s)
{
    for(int par = 0;par<2;par++)
    {
        int64_t sum = 0;
        for(int h = 0;h<=MAXN+1;h++)
        {
            sum = (sum + dp[h][par])%mod;
            pref[s][h][par] = sum;
        }
    }
}

int64_t getSum(int par, int s, int h1, int h2)
{
    return (pref[s][h2][par] - pref[s][h1-1][par] + mod)%mod;
}

int main()
{
    int n;
    cin >> n;

    //тука малко шано схеми, че да "сийднем" сметките
    //идеята е, че слагаме някви невъзможни стойности за все едно (-1)-вата кула
    //така че да може със сигурност да тръгне сметката
    //примерно - всяка кула ще е повече от 0, затова ако искаме да почнем с "висока" кула
    //правим (-1)-вата да е 0
    dp[0][0] = 1;
    dp[MAXN+1][1] = 1;

    int64_t ans = 0;
    for(int s = 1;s<=n;s++)
    {
        doPref(s-1);
        memset(dp, 0, sizeof(dp));

        for(int h = 1;h<=s;h++)
        {
            //тук границите на търсене не са баш както в пдф-а, понеже малко ми е шано схемата с началните стойности
            //ако желате можете да си го напишете по-добре

            //0
            dp[h][0] = getSum(1, s-h, h+1, MAXN+1)%mod;

            //1
            dp[h][1] = getSum(0, s-h, 0, h-1)%mod;

            if(s==n)
                ans = (ans + dp[h][0] + dp[h][1])%mod;
        }
    }

    //вадим 1 от отговора, понеже броим редицата с дължина 1 два пъти
    cout << (ans - 1 + mod)%mod << '\n';
}
