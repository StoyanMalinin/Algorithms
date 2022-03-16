#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 3e5;

int n;
bool isInvited[MAXN+5];
vector <int> graph[MAXN+5];

bool used[MAXN+5], color[MAXN+5];
void dfs(int x, bool currColor, int &evenInvitedCnt, int &oddInvitedCnt, int &evenCnt, int &oddCnt, bool &isBipartite)
{
    used[x] = true;
    color[x] = currColor;

    if(currColor==false)
    {
        evenCnt++;
        if(isInvited[x]==true) evenInvitedCnt++;
    }
    else
    {
        oddCnt++;
        if(isInvited[x]==true) oddInvitedCnt++;
    }

    for(int y: graph[x])
    {
        if(used[y]==false)
            dfs(y, currColor^1, evenInvitedCnt, oddInvitedCnt, evenCnt, oddCnt, isBipartite);
        else
        {
            if(color[x]==color[y])
            {
                isBipartite = false;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int x = 1;x<=n;x++) cin >> isInvited[x];

    int m;
    cin >> m;
    for(int i = 0;i<m;i++)
    {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int ans = 0;
    for(int x = 1;x<=n;x++) ans += isInvited[x];

    int evenSum = 0, oddSum = 0, totalSum = 0;
    for(int x = 1;x<=n;x++)
    {
        if(used[x]==false && isInvited[x]==true)
        {
            bool isBipartite = true;
            int evenCnt = 0, oddCnt = 0, evenInvitedCnt = 0, oddInvitedCnt = 0;
            dfs(x, false, evenInvitedCnt, oddInvitedCnt, evenCnt, oddCnt, isBipartite);

            if(isBipartite==false || (evenInvitedCnt!=0 && oddInvitedCnt!=0)) totalSum += evenCnt + oddCnt;
            else
            {
                if(evenCnt+oddCnt>1)
                {
                    evenSum += evenCnt;
                    oddSum += oddCnt;
                }
            }
        }
    }

    ans = max(ans, totalSum + max(evenSum, oddSum));
    cout << ans << '\n';
}
