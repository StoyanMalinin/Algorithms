#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

const int MAXN = 80;
const int64_t mod = 1e6 + 1;

int n, x, y;
int memo[MAXN+5][MAXN+5][MAXN+5][MAXN+5];

int comb2(int a)
{
    return (a * (a - 1)) / 2;
}

// За итеративното:
// dp[i][cnt][c0][c1][c2]
// dp[0][0][y][0][0] = 1
// dp[0][1][y-1][1][0] = y
// dp[0][2][y-2][0][2] = comb2(y)
// всичко друго е 0

int rec(int i, int cnt, int c0, int c1, int c2)
{
    if (cnt > n)
    {
        return 0;
    }
    if (i == x)
    {
        return (cnt == n);
    }
    if (memo[i][cnt][c0][c1] != -1)
    {
        return memo[i][cnt][c0][c1];
    }

    int64_t ans = 0;

    // put 0
    ans += rec(i + 1, cnt, c0, c1, c2);

    // put 1
    if (c0 >= 1) ans += c0 * rec(i + 1, cnt + 1, c0 - 1, c1 + 1, c2);
    if (c1 >= 1) ans += c1 * rec(i + 1, cnt + 1, c0, c1 - 1, c2 + 1);

    // put 2
    // Специален случай: Правим колоните директно мъртви, понеже редът е "натежал".
    if (c0 >= 2) ans += comb2(c0) * rec(i + 1, cnt + 2, c0 - 2, c1, c2 + 2);

    ans %= mod;
    memo[i][cnt][c0][c1] = ans;

    return ans;
}

int main()
{
    cin >> x >> y >> n;

    memset(memo, -1, sizeof(memo));
    cout << rec(0, 0, y, 0, 0) << '\n';
}
