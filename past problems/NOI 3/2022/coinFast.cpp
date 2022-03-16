#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

const int MAXN = 6e4;

struct FromVal
{
    static int allocInd;

    int16_t nominal, nominalCnt;
    int last;
};
int FromVal::allocInd = 1;

FromVal pool[MAXN*200];
pair <int16_t, int16_t> from[300][MAXN*2+5], fromNew[MAXN*2+5];

int createFromVal(int nominal, int nominalCnt, int last)
{
    pool[FromVal::allocInd].nominal = nominal;
    pool[FromVal::allocInd].nominalCnt = nominalCnt;
    pool[FromVal::allocInd].last = last;

    FromVal::allocInd++;
    return FromVal::allocInd - 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dp[MAXN*2+5], dpNew[MAXN*2+5];

    int n, p;
    cin >> n >> p;

    for(int s = 1;s<=2*p;s++)
        dp[s] = dpNew[s] = MAXN;

    int nominals[MAXN+5];
    for(int i = 0;i<n;i++) cin >> nominals[i];
    sort(nominals, nominals+n);

    set <int> uniqueNominals;
    for(int i = 0;i<n;i++) uniqueNominals.insert(nominals[i]);

    map <int, int> nominalCount;
    for(int i = 0;i<n;i++) nominalCount[nominals[i]]++;

    deque <int> opt[MAXN*2+5];

    int numInd = 0;
    int evalSum = 0;
    for(int x: uniqueNominals)
    {
        int val;
        int nomCnt = nominalCount[x];

        if(x==0) continue;
        for(int s = 0;s<=evalSum;s++)
        {
            dpNew[s] = dp[s];
        }

        if(nomCnt>1)
        {
            for(int s = 0;s<x;s++) opt[s].clear();

            val = x*(nomCnt-1);
            for(int s = 0;s<=evalSum+val;s++)
            {
                deque <int> &localOpt = opt[s%x];

                while(localOpt.empty()==false && s-localOpt.front()>val) localOpt.pop_front();
                if(localOpt.empty()==false && dp[localOpt.front()]<dpNew[s])
                {
                    dpNew[s] = dp[localOpt.front()];
                    fromNew[s] = {x, (s-localOpt.front())/x};
                }

                while(localOpt.empty()==false && dp[localOpt.back()]>dp[s]) localOpt.pop_back();
                localOpt.push_back(s);
            }
        }

        val = x*nomCnt;
        for(int s = evalSum+val;s>=val;s--)
        {
            if(dp[s-val] + 1 < dpNew[s])
            {
                dpNew[s] = dp[s-val] + 1;
                fromNew[s] = {x, nomCnt};
            }
        }

        evalSum += val;
        for(int s = 0;s<=evalSum;s++)
        {
            dp[s] = dpNew[s];
        }

        numInd++;
    }

    int ansSum = p;
    for(int s = p;s<=2*p;s++)
    {
        if(dp[s]<dp[ansSum])
            ansSum = s;
    }

    cout << uniqueNominals.size() - dp[ansSum] << " " << ansSum << '\n';

    vector <int> coins;
    while(ansSum!=0)
    {
        for(int i = 0;i<from[numInd-1][ansSum].second;i++)
            coins.push_back(from[numInd-1][ansSum].first);

        ansSum -= from[numInd-1][ansSum].first*from[numInd-1][ansSum].second;
    }

    sort(coins.begin(), coins.end());
    for(int x: coins) cout << x << " ";
    cout << '\n';
}
