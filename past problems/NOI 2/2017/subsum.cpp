#include <iostream>
#include <bitset>

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

    bitset<MAXSUM+5> dp;
    dp.reset();

    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];

    for(int i = 0;i<n;i++)
    {
        if(a[i]<=0) dp |= (dp>>(-a[i]));
        else dp |= (dp<<a[i]);

        dp[a[i]+offset] = true;
    }

    cout << dp.count() << '\n';
}
