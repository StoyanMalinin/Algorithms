#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 50;

int memo[MAXN+5][MAXN+5][30];
int rec(int l, int r, int c, const string& s)
{
    if(l>r) return 0;
    if(l==r) return (s[l]!='A'+c);
    if(memo[l][r][c]!=-1) return memo[l][r][c];

    int ans = MAXN*2;
    for(int i = l;i<=r;i++)
        if(s[i]==c+'A') ans = min(ans, rec(l, i-1, c, s) + rec(i+1, r, c, s));

    for(int l1 = l;l1<=r;l1++)
    {
        for(int r1 = l1;r1<=r;r1++)
        {
            if(s[l1]!=s[r1]) continue;
            ans = min(ans, 1 + rec(l, l1-1, c, s) + rec(l1+1, r1-1, s[l1]-'A', s) + rec(r1+1, r, c, s));
        }
    }

    memo[l][r][c] = ans;
    return ans;
}

void solveTestcase()
{
    string s;
    cin >> s;

    memset(memo, -1, sizeof(memo));
    cout << rec(0, s.size()-1, 27, s) << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--) solveTestcase();
}
