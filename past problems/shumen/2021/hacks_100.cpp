#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 50, MAXM = 1e4;

int n, m, k;
int a[MAXM+5][MAXN+5];

int calcMaxNumHacks()
{
    int ans = 0;
    for(int i = 0;i<m;i++)
    {
        if(i==k) continue;
        for(int j = 0;j<n;j++)
        {
            if(a[i][j]!=0 && a[k][j]!=0)
                ans++;
        }
    }

    return ans;
}

vector <int> v[MAXM];
void init()
{
    for(int i = 0;i<m;i++)
    {
        if(i==k) continue;

        for(int j = 0;j<n;j++)
        {
            if(a[k][j]!=0 && a[i][j]!=0)
                v[i].push_back(a[i][j]);
        }
        sort(v[i].begin(), v[i].end(), greater<int>());
    }
}

bool check(int hacks)
{
    int64_t myRes = hacks*100;
    for(int i = 0;i<n;i++) myRes += a[k][i];

    int minHacks = 0;
    for(int i = 0;i<m;i++)
    {
        if(i==k) continue;

        int64_t currRes = 0;
        for(int j = 0;j<n;j++)
        {
            currRes += a[i][j];
        }

        if(v[i].empty()==false)
        {
            for(int x: v[i])
            {
                if(currRes<myRes) break;

                currRes -= x;
                minHacks++;
            }
        }

        if(currRes>=myRes) return false;
        if(minHacks>hacks) return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;k--;
    for(int i = 0;i<m;i++)
        for(int j = 0;j<n;j++)
            cin >> a[i][j];
    init();

    int maxHacks = calcMaxNumHacks();
    int l = 0, r = maxHacks, mid;

    while(l+1<r)
    {
        mid = (l+r)/2;

        if(check(mid)==true) r = mid;
        else l = mid + 1;
    }

    if(check(l)==true) cout << l << '\n';
    else if(check(r)==true) cout << r << '\n';
    else cout << "-1" << '\n';
}
