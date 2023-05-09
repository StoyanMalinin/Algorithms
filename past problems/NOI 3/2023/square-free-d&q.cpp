#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 1e7;

int mu[MAXN + 5];
vector<int> primes;
int lowestPrime[MAXN + 5];

vector<int64_t> usefulNums;
vector<int> muOfUsefulNums;
vector<int> muPrefOfUsefulNums;

int getMuSum(int l, int r)
{
    if (l == 0)
    {
        return muPrefOfUsefulNums[r];
    }

    return muPrefOfUsefulNums[r] - muPrefOfUsefulNums[l - 1];
}

void init()
{
    primes.reserve(MAXN / 10);

    mu[1] = 1;
    for (int i = 2; i <= MAXN ;i++)
    {
        if (lowestPrime[i] == 0)
        {
            mu[i] = -1;
            lowestPrime[i] = i;
            primes.push_back(i);
        }

        for (int j = 0; j < primes.size() && i * primes[j] <= MAXN; j++)
        {
            lowestPrime[i * primes[j]] = primes[j];

            if(i % primes[j] == 0)
            {
                mu[i * primes[j]] = 0;
                break;
            }
            else
            {
                mu[i * primes[j]] = mu[i] * mu[primes[j]];
            }
        }
    }

    usefulNums.reserve(MAXN / 10);
    for (int x = 2; x <= MAXN; x++)
    {
        if (mu[x] != 0)
        {
            usefulNums.push_back(x);

            muOfUsefulNums.push_back(mu[x]);
            if (muOfUsefulNums.size() == 1)
            {
                muPrefOfUsefulNums.push_back(mu[x]);
            }
            else
            {
                muPrefOfUsefulNums.push_back(muPrefOfUsefulNums.back() + mu[x]);
            }
        }
    }
}

int64_t solveInternal(int l, int r, int64_t lVal, int64_t rVal, const int64_t N)
{
    if (l > r)
    {
        return 0;
    }
    if (lVal == rVal)
    {
        return getMuSum(l, r) * lVal;
    }

    int m1 = (l + r) / 2;
    int m2 = m1 + 1;

    int64_t m1Val = N / (usefulNums[m1] * usefulNums[m1]);
    int64_t m2Val = N / (usefulNums[m2] * usefulNums[m2]);

    return solveInternal(l, m1, lVal, m1Val, N) + solveInternal(m2, r, m2Val, rVal, N);
}

int64_t solve(int64_t N)
{
    int64_t lVal = N / (usefulNums[0] * usefulNums[0]);
    int64_t rVal = N / (usefulNums[usefulNums.size() - 1] * usefulNums[usefulNums.size() - 1]);

    return N + solveInternal(0, usefulNums.size() - 1, lVal, rVal, N);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();

    int Q;
    cin >> Q;

    while (Q--)
    {
        int64_t N;
        cin >> N;

        cout << solve(N) << '\n';
    }
}
