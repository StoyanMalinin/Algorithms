#include <iostream>
#include <bitset>

using namespace std;

const int MAXN = 300;

int n, m;
int a[MAXN+5][MAXN+5];
bitset <MAXN+5> b[MAXN+5];

int calcOddSubMatrices()
{
    for (int j = 1; j < m; j++)
    {
        b[0][j] = b[0][j] ^ b[0][j - 1];
    }
    for (int i = 1; i < n; i++)
    {
        b[i][0] = b[i][0] ^ b[i - 1][0];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            b[i][j] = b[i][j] ^ b[i - 1][j] ^ b[i][j - 1] ^ b[i - 1][j - 1];
        }
    }

    int ans = 0;
    for (int r1 = 0; r1 < n; r1++)
    {
        for (int r2 = r1; r2 < n; r2++)
        {
            int cnt1 = (r1 == 0) ? b[r2].count() : (b[r1 - 1] ^ b[r2]).count();
            int cnt0 = m - cnt1;

            // cout << r1 << " " << r2 << " -> " << cnt0 << " " << cnt1 << '\n';
            ans += cnt0 * cnt1 + cnt1;
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }

    int64_t ans = 0;
    for (int bit = 0; bit <= 15; bit++)
    {
        for (int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                b[i][j] = (a[i][j] >> bit) & 1;
            }
        }

        ans += (1LL << bit) * calcOddSubMatrices();
    }

    cout << ans << '\n';
}

