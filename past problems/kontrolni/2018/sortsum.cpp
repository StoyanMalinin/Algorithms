#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

int getSumOfDigits(int64_t k)
{
    int sum = 0;

    while (k)
    {
        sum += k%10;
        k /= 10;
    }

    return sum;
}

int getNumberOfDigits(int64_t k)
{
    int br = 0;
    while (k)
    {
        k /= 10;
        br++;
    }

    return br;
}

int64_t memo[19][19][180];
int64_t rec(const int SIZE, int pos, int sumSpare)
{
    if (pos == SIZE) return 1;
    if (memo[SIZE][pos][sumSpare] != -1)
        return memo[SIZE][pos][sumSpare];

    int64_t ans = 0;
    for (int i = (pos==0); i < 10; i++)
    {
        if(sumSpare>i)
            ans += rec(SIZE, pos+1, sumSpare-i);
    }

    memo[SIZE][pos][sumSpare] = ans;
    return ans;

}

int64_t soloveTestcase(int n, int64_t k)
{
    int64_t ans = 0;
    int sumOfDigits = getSumOfDigits(k);
    int numberOfDigits = getNumberOfDigits(k);

    if (sumOfDigits != 1) ans++;
    for (int i = numberOfDigits+1; i <= n; i++)
        ans += rec(i, 0, sumOfDigits);

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    memset(memo, -1, sizeof(memo));

    int n, m;
    int64_t k;

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> k;

        int64_t ans = soloveTestcase(n, k);
        if(i==0) cout << ans;
        else cout << " " << ans;
    }
    cout << '\n';

    return 0;
}
