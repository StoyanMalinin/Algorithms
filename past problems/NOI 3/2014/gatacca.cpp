#include <iostream>
#include <cstring>
#include <string>
#include <array>
#include <map>

using namespace std;

const int MAXN = 1e5;
const array <int64_t, 2> key = {7, 11};
const array <int64_t, 2> mod = {(int64_t)1e9+7, (int64_t)1e9+9};
int64_t pKey[2][MAXN+5];

int charCode(char c)
{
    if(c=='A') return 1;
    if(c=='T') return 2;
    if(c=='G') return 3;
    if(c=='C') return 4;
}

struct Hash
{
    array <int64_t, 2> h;

    Hash()
    {
        h = {0, 0};
    }

    void addChar(char c)
    {
        for(int i = 0;i<h.size();i++)
            h[i] = (h[i]*key[i] + charCode(c))%mod[i];
    }
};

bool operator <(const Hash& A, const Hash &B)
{
    for(int i = 0;i<A.h.size();i++)
        if(A.h[i]!=B.h[i]) return A.h[i] < B.h[i];

    return false;
}

Hash operator -(const Hash &A, const Hash &B)
{
    Hash C;
    for(int i = 0;i<A.h.size();i++)
        C.h[i] = (A.h[i] - B.h[i] + mod[i])%mod[i];

    return C;
}

Hash operator *(const Hash &A, int len)
{
    Hash res = A;
    for(int i = 0;i<A.h.size();i++)
        res.h[i] = (A.h[i]*pKey[i][len])%mod[i];

    return res;
}

int n, m, k;
string s1, s2;

Hash h1[MAXN+5], h2[MAXN+5];

Hash getHash(Hash *h, int l, int r)
{
    if(l==0) return h[r];
    return h[r] - h[l-1]*(r-l+1);
}

void init()
{
    pKey[0][0] = pKey[1][0] = 1;
    for(int p = 1;p<=MAXN;p++)
        for(int i = 0;i<2;i++)
            pKey[i][p] = (pKey[i][p-1]*key[i])%mod[i];

    Hash currH;

    for(int i = 0;i<s1.size();i++)
    {
        currH.addChar(s1[i]);
        h1[i] = currH;
    }

    currH = Hash();
    for(int i = 0;i<s2.size();i++)
    {
        currH.addChar(s2[i]);
        h2[i] = currH;
    }
}

bool check(int len)
{
    map <Hash, int> mp;
    for(int i = 0;i<m-len+1;i++)
        mp[getHash(h2, i, i+len-1)]++;

    for(int i = 0;i<n-len+1;i++)
        if(mp[getHash(h1, i, i+len-1)]>=k) return true;

    return false;
}

/*
Реално тази част теоретично е бавна,
но автора също така я прави и казва,
че реално не е успял да направи тест, където това да бъде проблем.
По-тази причина оставяме нещата така.
*/
string getSmallestGoodString(int len)
{
    map <Hash, int> mp;
    for(int i = 0;i<m-len+1;i++)
        mp[getHash(h2, i, i+len-1)]++;

    string ans = "";
    for(int i = 0;i<n-len+1;i++)
    {
        if(mp[getHash(h1, i, i+len-1)]>=k)
        {
            if(ans.size()==0) ans = s1.substr(i, len);
            else if(strcmp(ans.data(), s1.data()+i)>0) ans = s1.substr(i, len);
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    cin >> s1 >> s2;
    init();

    int l = 1, r = min(n, m), mid;
    while(l+1<r)
    {
        mid = (l+r)/2;

        if(check(mid)==true) l = mid;
        else r = mid - 1;
    }

    int ansLen = -1;
    if(check(r)==true) ansLen = r;
    else ansLen = l;

    cout << getSmallestGoodString(ansLen) << '\n';
}
/*
7 19 3
GATTACA
TACATTACGCATTACACAT
*/
