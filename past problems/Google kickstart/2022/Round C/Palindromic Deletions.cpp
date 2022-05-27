#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 400;
const int64_t mod = 1e9 + 7;

int64_t fastPow(int64_t x, int64_t p)
{
    int64_t ans = 1, curr = x;

    while(p!=0)
    {
        if(p%2!=0) ans = (ans*curr)%mod;

        curr = (curr*curr)%mod;
        p /= 2;
    }

    return ans;
}

int64_t inv(int64_t x)
{
    return fastPow(x, mod-2);
}

int memo[MAXN+5][MAXN+5][MAXN+5];
int64_t rec(int l, int r, int sz, const string& s)
{
    if(sz==0) return 1;
    if(l>r) return 0;

    if(memo[l][r][sz]!=-1)
        return memo[l][r][sz];

    int64_t ans = 0;
    if(s[l]==s[r])
    {
        if(l==r)
            ans += rec(l+1, r-1, sz-1, s);
        else
            ans += rec(l+1, r-1, sz-2, s);
    }

    ans += rec(l+1, r, sz, s) + rec(l, r-1, sz, s) - rec(l+1, r-1, sz, s);
    ans = (ans + 5*mod)%mod;

    memo[l][r][sz] = ans;
    return ans;
}

int comb[MAXN+5][MAXN+5];
void solveTestcase(int testcase)
{
    memset(memo, -1, sizeof(memo));

    int n;
    cin >> n;

    string s;
    cin >> s;

    int64_t ans = 0;
    for(int sz = 0;sz<s.size();sz++)
    {
        ans += (rec(0, n-1, sz, s)*inv(comb[s.size()][s.size()-sz]))%mod;
        ans %= mod;
    }
    ans %= mod;

    cout << "Case #" << testcase << ": " << ans << '\n';
}

void init()
{
    comb[0][0] = 0;
    for(int i = 1;i<=MAXN;i++)
    {
        comb[i][0] = comb[i][i] = 1;
        for(int j = 1;j<i;j++) comb[i][j] = (comb[i-1][j] + comb[i-1][j-1])%mod;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    init();

    for(int t = 1;t<=T;t++)
        solveTestcase(t);
}
