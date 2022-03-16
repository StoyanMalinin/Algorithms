#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 6e4;

struct FromVal
{
    int nominal;
    FromVal *last;

    FromVal(){}
    FromVal(int nominal, FromVal *last) : nominal(nominal), last(last) {}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dp[MAXN*2+5];
    FromVal *from[MAXN*2+5];

    int n, p;
    cin >> n >> p;

    for(int s = 1;s<=2*p;s++)
        dp[s] = MAXN;

    int nominals[MAXN+5];
    for(int i = 0;i<n;i++) cin >> nominals[i];
    sort(nominals, nominals+n);

    set <int> uniqueNominals;
    for(int i = 0;i<n;i++) uniqueNominals.insert(nominals[i]);

    int evalSum = 0;
    from[0] = nullptr;
    for(int i = 0;i<n;i++)
    {
        int addVal = ((i==n-1 || nominals[i+1]!=nominals[i])?1:0);
        for(int s = evalSum+nominals[i];s>=nominals[i];s--)
        {
            if(dp[s-nominals[i]] + addVal < dp[s])
            {
                dp[s] = dp[s-nominals[i]] + addVal;
                from[s] = new FromVal(nominals[i], from[s-nominals[i]]);
            }
        }

        evalSum += nominals[i];
    }

    int ansSum = p;
    for(int s = p;s<=2*p;s++)
    {
        if(dp[s]<dp[ansSum])
            ansSum = s;
    }

    cout << uniqueNominals.size() - dp[ansSum] << " " << ansSum << '\n';

    FromVal *f = from[ansSum];
    vector <int> coins;
    while(ansSum!=0)
    {
        coins.push_back(f->nominal);

        ansSum -= f->nominal;
        f = f->last;
    }

    sort(coins.begin(), coins.end());
    for(int x: coins) cout << x << " ";
    cout << '\n';
}
