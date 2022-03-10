#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int64_t mod = 1e9 + 7;

int n;

int digSum(int x)
{
    //ab -> (+a) + (-b)
    return x/10 - x%10;
}

int memo[105][105][15];
int64_t rec(int num, int even, int odd, int rem)
{
    if(num==n+1)
    {
        if(rem==0) return 1;
        return 0;
    }
    if(memo[num][even][rem]!=-1)
        return memo[num][even][rem];

    int64_t ans = 0;

    //even
    ans += even*rec(num+1, even+1, odd, (rem+digSum(num)+11)%11);

    //odd
    ans += odd*rec(num+1, even, odd+1, (rem-digSum(num)+11)%11);

    ans %= mod;
    memo[num][even][rem] = ans;

    return ans;
}

int main()
{
    cin >> n;

    if(n<10)
    {
        cout << "kofti" << '\n';
        return 0;
    }

    int64_t ans = 0;
    memset(memo, -1, sizeof(memo));

    vector <int> digs = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    do
    {
        int rem = 0;
        for(int i = 0;i<9;i++)
        {
            if(i%2==0) rem = (rem + digs[i])%11;
            else rem = (rem - digs[i] + 11)%11;
        }

        ans = (ans + rec(10, 5, 5, rem))%mod;
    }
    while(next_permutation(digs.begin(), digs.end()));

    cout << ans << '\n';
}
