#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 50;
const int MAXA = 1000;

const int inf = 1e7;
const int shortInf = 55000;

int n;
int a[MAXN+5];

int memo[MAXN+5][2*MAXN*MAXA+5];

int rec(int ind, int p1, int p2)
{
    if(ind==n)
    {
        if(p1==p2) return 0;
        return +inf;
    }
    if(memo[ind][p1-p2+MAXN*MAXA]!=-1)
        return memo[ind][p1-p2+MAXN*MAXA];

    int ans = inf;
    ans = min(ans, rec(ind+1, p1, p2) + a[ind]);//тигри
    ans = min(ans, rec(ind+1, p1+a[ind], p2));//пират 1
    ans = min(ans, rec(ind+1, p1, p2+a[ind]));//пират 2

    memo[ind][p1-p2+MAXN*MAXA] = ans;
    return ans;
}

int main()
{
    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];

    memset(memo, -1, sizeof(memo));
    cout << rec(0, 0, 0) << '\n';
}
