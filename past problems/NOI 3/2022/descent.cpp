#include <iostream>
#include <set>

using namespace std;

const int MAXN = 1e5;

int n;
int p[MAXN+5];

set <int> nonzero;
int64_t land(int x, int k)
{
    int64_t ans = 0;

    while(k>0 && *prev(nonzero.end())>=x)
    {
        auto it = nonzero.lower_bound(x);

        int rm = min(k, p[*it]);
        k -= rm; p[*it] -= rm;
        ans += (*it-x)*1LL*rm;

        if(p[*it]==0)
            nonzero.erase(it);
    }

    while(k>0)
    {
        auto it = nonzero.begin();

        int rm = min(k, p[*it]);
        k -= rm; p[*it] -= rm;
        ans += ((n-1-x) + *it + 1)*1LL*rm;

        if(p[*it]==0)
            nonzero.erase(it);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0;i<n;i++) cin >> p[i];

    for(int i = 0;i<n;i++)
        if(p[i]>0) nonzero.insert(i);

    int Q;
    cin >> Q;

    while(Q--)
    {
        int x, k;
        cin >> x >> k;

        cout << land(x-1, k) << '\n';
    }
}
