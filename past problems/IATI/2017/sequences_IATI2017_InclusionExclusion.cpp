#include <iostream>

using namespace std;

const int MAXN = 60;

int64_t comb[MAXN+5][MAXN+5];

void init()
{
    comb[0][0] = 1;
    for(int i = 1;i<=MAXN;i++)
    {
        comb[i][0] = 1;
        for(int j = 1;j<=i;j++)
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
}

int sign(int x)
{
    if(x%2==0) return +1;
    return -1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int n, m, k;
    cin >> n >> m >> k;

    int64_t ans = comb[n+m-1][n];
    for(int bad = 1;bad<=m;bad++)
    {
        if(bad*(k+1)>n) break;
        ans += sign(bad)*comb[m][bad]*comb[(n-bad*(k+1))+m-1][n-bad*(k+1)];
    }

    cout << ans << '\n';
}
