#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

const int MAXN = 100;

int n;
int p[MAXN+5];

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    vector <pair <int, int>> ans;

    cin >> n;
    for(int i = 1;i<=n;i++) cin >> p[i];

    for(int i = 1;i<=n;i++)
    {
        int j = i;
        while(p[j]!=i) j++;

        if(j==i) continue;

        for(int ind = j;ind>=i+1;ind--)
        {
            int chainIndex = ind - 1;
            while(p[chainIndex]==chainIndex+1 && chainIndex!=i-1)
            {
                chainIndex--;
            }

            if(chainIndex!=i-1)
            {
                for(int k = chainIndex;k<=ind-2;k++)
                {
                    ans.push_back({k, k+1});
                    swap(p[k], p[k+1]);
                }
            }

            ans.push_back({ind-1, ind});
            swap(p[ind], p[ind-1]);
        }
    }

    cout << ans.size() << '\n';
    for(auto item: ans)
        cout << item.first << " " << item.second << '\n';
}
