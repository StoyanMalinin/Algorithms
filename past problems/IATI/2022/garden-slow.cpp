#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 2000;
const int64_t inf = 1e15;

int n;
int c[MAXN+5], t[MAXN+5];
vector <int> graph[MAXN+5];

int64_t memoPrimary[MAXN+5][MAXN+5][2];
int64_t memoSecondary[MAXN+5];

int64_t getCachedValue(int x, int flow, int mode)
{
    if(mode!=2) return memoPrimary[x][flow][mode];
    return memoSecondary[x];
}

bool checkCachedValue(int x, int flow, int mode)
{
    return (getCachedValue(x, flow, mode)!=-1);
}

void cacheValue(int x, int flow, int mode, int64_t ans)
{
    if(mode!=2) memoPrimary[x][flow][mode] = ans;
    else memoSecondary[x] = ans;
}

int64_t rec(int x, int parent, int flow, int mode)
{
    int64_t ans = inf;
    if(flow<=0) flow = 0;
    if(flow>n) return inf;

    if(checkCachedValue(x, flow, mode)==true)
        return getCachedValue(x, flow, mode);

    if(mode==0)
    {
        if(flow>0)
        {
            int64_t curr = 0;
            for(int y: graph[x])
                if(y!=parent) curr += rec(y, x, flow-1, 0);

            ans = min(ans, curr);
        }

        ans = min(ans, rec(x, parent, -1, 2));
    }
    else if(mode==1)
    {
        if(flow==0) return inf;

        if(flow<=t[x])
        {
            int64_t curr = c[flow];
            for(int y: graph[x])
                if(y!=parent)  curr += rec(y, x, flow-1, 0);

            ans = min(ans, curr);
        }

        for(int y1: graph[x])
        {
            if(y1!=parent)
            {
                int64_t curr = rec(y1, x, flow+1, 1);
                for(int y2: graph[x])
                {
                    if(y2==y1 || y2==parent) continue;
                    curr += rec(y2, x, flow-1, 0);
                }

                ans = min(ans, curr);
            }
        }
    }
    else if(mode==2)
    {
        for(int f = 1;f<=n;f++)
            ans = min(ans, rec(x, parent, f, 1));
    }

    cacheValue(x, flow, mode, ans);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1;i<=n;i++) cin >> c[i];
    for(int i = 1;i<=n;i++) cin >> t[i];
    for(int i = 0;i<n-1;i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    memset(memoPrimary, -1, sizeof(memoPrimary));
    memset(memoSecondary, -1, sizeof(memoSecondary));

    int64_t ans = rec(1, -1, 0, 0);
    if(ans==inf) ans = -1;

    cout << ans << '\n';
}
