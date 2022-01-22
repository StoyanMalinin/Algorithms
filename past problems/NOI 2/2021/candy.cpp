#include <iostream>
#include <cstring>
#include <set>

using namespace std;

const int MAXN = 19;

int n, m, k;
long long memo[MAXN][MAXN][MAXN*MAXN];

int countProjections(int i, int j)
{
    set <pair <int, int>> s;
    for(int rep1 = 0;rep1<2;rep1++)
    {
        for(int rep2 = 0;rep2<2;rep2++)
        {
            s.insert({i, j});

            j = m - j- 1;
        }

        i = n - i - 1;
    }

    return s.size();
}

int nLim, mLim;
long long rec(int i, int j, int candies)
{
    if(j==mLim+1)
        return rec(i+1, 0, candies);
    if(i==nLim+1)
    {
        if(candies==0) return 1;
        return 0;
    }
    if(memo[i][j][candies]!=-1)
        return memo[i][j][candies];

    long long answer = 0;
    int cnt = countProjections(i, j);

    answer += rec(i, j+1, candies);
    if(candies>=cnt) answer += rec(i, j+1, candies-cnt);

    memo[i][j][candies] = answer;
    return answer;
}

int main()
{
    cin >> n >> m >> k;
    nLim = (n-1)/2;
    mLim = (m-1)/2;

    memset(memo, -1, sizeof(memo));
    cout << rec(0, 0, k) << '\n';
}
