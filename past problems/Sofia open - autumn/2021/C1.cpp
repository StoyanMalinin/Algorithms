#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAX_N = 3e5;

pair <LL, LL> a[MAX_N];
LL n, h, l, i, k, br;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;
    for (i = 0; i < n; i++)
    {
        cin >> h >> l;
        a[i+n] = {h%l , 1};
        a[i] = {l, h/l};
    }
    sort (a, a+(2*n), greater <pair<LL, LL>>());
    //cout << "******************" << endl;
    for (i = 0; i < 2*n; i++)
    {
        //cout << a[i].first << " " << a[i].second << endl;
        if (a[i].second <= k)
        {

            k = k - a[i].second;
            br = br + (a[i].first*a[i].second);
        }
        else
        {
            br = br + (k*a[i].first);
            k = 0;
            break;
        }
    }
    cout << br << endl;


    return 0;
}
