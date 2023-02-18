#include <iostream>

using namespace std;

const int MAXN = 300;

int n, m;
int a[MAXN+5][MAXN+5], b[MAXN+5][MAXN+5], bRowPref[MAXN+5][MAXN+5];

int calcOddSubMatrices()
{
    for (int i = 0; i < n; i++)
    {
        bRowPref[i][0] = b[i][0];
        for (int j = 1; j < m; j++)
        {
            bRowPref[i][j] = bRowPref[i][j-1] + b[i][j];
        }
    }

    int ans = 0;
    for (int c1 = 0; c1 < m; c1++)
    {
        for (int c2 = c1; c2 < m; c2++)
        {
            int currPref = 0;
            int cntPref[2] = {1, 0};
            for (int r = 0; r < n; r++)
            {
                int currVal = bRowPref[r][c2];
                if (c1!=0) currVal -= bRowPref[r][c1 - 1];
                currPref = (currPref + currVal) & 1;


                ans += cntPref[(currPref & 1) ^ 1];
                cntPref[currPref & 1]++;
            }
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
