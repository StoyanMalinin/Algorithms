#include <iostream>
#include <cstring>
#include <set>
#include <map>

using namespace std;

const int MAXN = 1000;
const int MAXM = 1e4;

ostream& operator <<(ostream &o, const pair <int, int> &A)
{
    o << "(" << A.first << ", " << A.second << ")";
    return o;
}

int64_t getSquaredLen(pair <int, int> A, pair <int, int> B)
{
    return (A.first-B.first)*1LL*(A.first-B.first) + (A.second-B.second)*1LL*(A.second-B.second);
}

bool check(pair <int, int> A, pair <int, int> B, pair <int, int> C)
{
    if(getSquaredLen(A, B)==getSquaredLen(A, C) + getSquaredLen(B, C))
        return true;

    return false;
}

//приемаме, че точки А и В образуват диагонала на правоъгълника
int getCnt(pair <int, int> A, pair <int, int> B, pair <int, int> C, int16_t mp[MAXN+5][MAXN+5], int xValue[], int yValue[])
{
    if(getSquaredLen(A, B)!=getSquaredLen(A, C) + getSquaredLen(B, C))
        return 0;

    return mp[xValue[B.first+(A.first-C.first)+MAXM]][yValue[B.second+(A.second-C.second)+MAXM]];
}

int64_t calcDoubledSurface(pair <int, int> A, pair <int, int> B, pair <int, int> C)
{
    return (A.first*1LL*B.second + A.second*1LL*C.first + B.first*1LL*C.second)
           - (A.second*1LL*B.first + A.first*1LL*C.second + B.second*1LL*C.first);
}

void compress(int xValue[], int yValue[], pair <int, int> a[], int n)
{
    set <int> s;
    for(int i = 0;i<n;i++) s.insert(a[i].first);

    int ind = 0;
    for(int x: s)
    {
        xValue[x+MAXM] = ind;
        ind++;
    }

    s.clear();
    for(int i = 0;i<n;i++) s.insert(a[i].second);

    ind = 0;
    for(int y: s)
    {
        yValue[y+MAXM] = ind;
        ind++;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    pair <int, int> a[MAXN+5];

    int16_t mp[MAXN+5][MAXN+5];
    memset(mp, 0, sizeof(mp));

    int xValue[MAXM*2+5], yValue[MAXM*2+5];

    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i].first >> a[i].second;

    for(int i = 0;i<MAXM*2+3;i++)
        xValue[i] = yValue[i] = MAXN+2;
    compress(xValue, yValue, a, n);

    int ans = 0;
    for(int i1 = 0;i1<n;i1++)
    {
        for(int i2 = i1+1;i2<n;i2++)
        {
            for(int i3 = i2+1;i3<n;i3++)
            {
                if(check(a[i1], a[i2], a[i3])==true) ans += getCnt(a[i1], a[i2], a[i3], mp, xValue, yValue);
                else if(check(a[i1], a[i3], a[i2])==true) ans += getCnt(a[i1], a[i3], a[i2], mp, xValue, yValue);
                else if(check(a[i2], a[i3], a[i1])==true) ans += getCnt(a[i2], a[i3], a[i1], mp, xValue, yValue);
            }
        }

        mp[xValue[a[i1].first+MAXM]][yValue[a[i1].second+MAXM]]++;
    }

    cout << ans << '\n';
}
