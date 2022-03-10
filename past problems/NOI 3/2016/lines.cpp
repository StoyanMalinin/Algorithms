#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 1000;
const int64_t mod = 1e9 + 7;

int64_t memo[MAXN+5][MAXN+5]; //може да е int, понеже mod e малък сравнително
                              //но ако е int, трябва да се внимава със сметките в общия случай
int64_t rec(int vertex, int n)
{
    if(n==1) return 1;
    if(memo[vertex][n]!=-1)
        return memo[vertex][n];

    int64_t ans = 0;
    for(int x = 2;x<=n;x++)
    {
        if(x==vertex) ans++;
        else if(x<vertex) ans += rec(vertex-x+1, n-x+1);
        else if(vertex<x) ans += rec(x-vertex+1, x-1);
    }
    ans %= mod;

    memo[vertex][n] = ans;
    return ans;
}

int main()
{
    int n, i, j;
    cin >> n >> i >> j;

    memset(memo, -1, sizeof(memo));
    cout << rec(j-i+1, n) << '\n';
}
