#include <iostream>
#include <cstring>
#include <array>

using namespace std;

array <int, 10> digCost = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int64_t memo1[25][2];
int64_t numCount(const string &n, int pos, bool smaller)
{
    if(pos==n.size())
    {
        return 1;
    }
    if(memo1[pos][smaller]!=-1)
        return memo1[pos][smaller];

    int64_t ans = 0;
    for(int d = 0;d<=9;d++)
    {
        if(pos==0 && d==0) continue;
        if(smaller==false && d>(n[pos]-'0')) continue;

        ans += numCount(n, pos+1, smaller|(d<(n[pos]-'0')));
    }

    memo1[pos][smaller] = ans;
    return ans;
}

int64_t memo2[25][2];
int64_t rec(const string &n, int pos, bool smaller)
{
    if(pos==n.size())
    {
        return 0;
    }
    if(memo2[pos][smaller]!=-1)
        return memo2[pos][smaller];

    int64_t ans = 0;
    for(int d = 0;d<=9;d++)
    {
        if(pos==0 && d==0) continue;
        if(smaller==false && d>(n[pos]-'0')) continue;

        bool nextSmaller = smaller|(d<(n[pos]-'0'));

        ans += rec(n, pos+1, nextSmaller);
        ans += digCost[d]*numCount(n, pos+1, nextSmaller);
    }

    memo2[pos][smaller] = ans;
    return ans;
}

int64_t pow(int64_t x, int k)
{
    int64_t ans = 1;
    for(int i = 0;i<k;i++) ans *= x;

    return ans;
}

int64_t kDigitNumCost(int k)
{
    int64_t ans = 0;

    //accounting for the digit 0
    ans += k*9*pow(10, k-1)*digCost[0];

    //accounting for 1..9
    for(int d = 1;d<=9;d++)
        ans += (pow(10, k) + k*9*pow(10, k-1))*digCost[d];

    return ans;
}

int64_t evalSlow(int k)
{
    int64_t ans = 0;
    for(int x = pow(10, k-1);x<=pow(10, k)-1;x++)
    {

        int y = x;
        while(y!=0)
        {
            ans += digCost[y%10];
            y /= 10;
        }
    }

    return ans;
}

int64_t kDigitCost[25];

void init()
{
    /*
    for(int k = 1;k<=18;k++)
    {
        memset(memo1, -1, sizeof(memo1));
        memset(memo2, -1, sizeof(memo2));

        cout <<  "kDigitCost[" << k << "] = " << rec(to_string(pow(10, k)-1), 0, false) << ";" << '\n';
    }
    */

    kDigitCost[1] = 43;
    kDigitCost[2] = 871;
    kDigitCost[3] = 13120;
    kDigitCost[4] = 175300;
    kDigitCost[5] = 2194000;
    kDigitCost[6] = 26350000;
    kDigitCost[7] = 307600000;
    kDigitCost[8] = 3517000000;
    kDigitCost[9] = 39580000000;
    kDigitCost[10] = 439900000000;
    kDigitCost[11] = 4840000000000;
    kDigitCost[12] = 52810000000000;
    kDigitCost[13] = 572200000000000;
    kDigitCost[14] = 6163000000000000;
    kDigitCost[15] = 66040000000000000;
    kDigitCost[16] = 704500000000000000;
    kDigitCost[17] = 7486000000000000000;
}

int64_t f(int64_t n)
{
    if(n<=0) return 0;
    string nStr = to_string(n);

    int64_t ans = 0;
    for(int len = 1;len<nStr.size();len++)
        ans += kDigitCost[len];

    memset(memo1, -1, sizeof(memo1));
    memset(memo2, -1, sizeof(memo2));
    ans += rec(nStr, 0, false);

    return ans;
}

int main()
{
    init();

    int64_t s, n;
    cin >> n >> s;

    if(n==0)
    {
        cout << "0" << '\n';
        return 0;
    }

    int64_t l = s, r = s + n - 1;
    cout << f(r) - f(l-1) + ((s==0)?digCost[0]:0) << '\n';
}
