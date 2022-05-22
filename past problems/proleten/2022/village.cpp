#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

vector <int> convertToVector(int64_t x)
{
    if(x==0) return {0};

    vector <int> res;
    while(x!=0)
    {
        res.push_back(x%2);
        x /= 2;
    }

    reverse(res.begin(), res.end());
    return res;
}

int64_t memo[70][70][2][2];
int64_t rec(int ind, int zeroCount, bool leadindZero, bool isSmaller, const vector <int> &NBinary, const int K)
{
    if(ind==NBinary.size())
    {
        return zeroCount==K;
    }
    if(memo[ind][zeroCount][leadindZero][isSmaller]!=-1)
        return memo[ind][zeroCount][leadindZero][isSmaller];

    int64_t ans = 0;
    for(int d = 0;d<=1;d++)
    {
        if(isSmaller==false && d>NBinary[ind]) continue;

        bool newIsSmaller = isSmaller;
        if(d<NBinary[ind]) newIsSmaller = true;

        bool newLeadingZero = leadindZero;
        if(d==1) newLeadingZero = false;

        int newZeroCount = zeroCount;
        if(d==0 && leadindZero==false) newZeroCount++;

        ans += rec(ind+1, newZeroCount, newLeadingZero, newIsSmaller, NBinary, K);
    }

    memo[ind][zeroCount][leadindZero][isSmaller] = ans;
    return ans;
}

int64_t fHat(int64_t N, int k)
{
    vector <int> NBinary = convertToVector(N);

    memset(memo, -1, sizeof(memo));
    return rec(0, 0, true, false, NBinary, k);
}

int64_t f(int64_t L, int64_t R, int k)
{
    if(L==1) return fHat(R, k);
    return fHat(R, k) - fHat(L-1, k);
}

int main()
{
    int k;
    int64_t L, R;
    cin >> L >> R >> k;

    cout << f(L, R, k) << '\n';
}
