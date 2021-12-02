#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1e5;
const int MAXK = 100;
const int64_t inf = 1e18;

int n, k;
int a[MAXN+5];

int64_t sign(int x)
{
    if(x%2==0) return +1;
    return -1;
}

int64_t memo[MAXN][MAXK];
int64_t rec(int ind, int pastTalks)
{
    if(ind==n) return 0;
    if(memo[ind][pastTalks]!=-1) return memo[ind][pastTalks];

    int64_t ans = inf;
    ans = min(ans, sign(pastTalks)*a[ind] + rec(ind+1, pastTalks));//да не говоря
    if(pastTalks+1<=k) ans = min(ans, sign(pastTalks+1)*a[ind] + rec(ind+1, pastTalks+1));//говоря

    memo[ind][pastTalks] = ans;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 0;i<n;i++) cin >> a[i];

    memset(memo, -1, sizeof(memo));
    cout << rec(0, 0) << '\n';
}
