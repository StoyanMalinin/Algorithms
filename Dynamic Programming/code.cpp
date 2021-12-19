#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 60;

int n;

vector <int> v;
int64_t memo[MAXN+5];

int64_t rec(int ind)
{
    if(ind==v.size())
        return 1;
    if(memo[ind]!=-1)
        return memo[ind];

    int64_t ans = 0;
    ans += rec(ind+1);//буква
    if(ind+1<v.size() && v[ind]*10+v[ind+1]<=9+n && v[ind]*10+v[ind+1]>=10) ans += rec(ind+2);

    memo[ind] = ans;
    return ans;
}

int main()
{
    cin >> n;

    string s;
    cin >> s;
    for(char c: s)
        v.push_back(c-'0');

    memset(memo, -1, sizeof(memo));
    cout << rec(0) << '\n';
}
