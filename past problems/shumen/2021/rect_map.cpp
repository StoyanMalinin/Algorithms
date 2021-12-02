#include <iostream>
#include <map>

using namespace std;

const int MAXN = 1000;

ostream& operator <<(ostream &o, const pair <int, int> &A)
{
    o << "(" << A.first << ", " << A.second << ")";
    return o;
}

map <pair <int, int>, int> mp;

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
int getCnt(pair <int, int> A, pair <int, int> B, pair <int, int> C)
{
    auto it = mp.find(make_pair(B.first+(A.first-C.first), B.second+(A.second-C.second)));

    if(it==mp.end()) return 0;
    return it->second;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    pair <int, int> a[MAXN+5];

    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i].first >> a[i].second;

    int ans = 0;
    for(int i1 = 0;i1<n;i1++)
    {
        for(int i2 = i1+1;i2<n;i2++)
        {
            for(int i3 = i2+1;i3<n;i3++)
            {
                if(check(a[i1], a[i2], a[i3])==true) ans += getCnt(a[i1], a[i2], a[i3]);
                else if(check(a[i1], a[i3], a[i2])==true) ans += getCnt(a[i1], a[i3], a[i2]);
                else if(check(a[i2], a[i3], a[i1])==true) ans += getCnt(a[i2], a[i3], a[i1]);
            }
        }

        mp[a[i1]]++;
    }

    cout << ans << '\n';
}
