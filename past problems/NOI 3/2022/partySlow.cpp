#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

const int MAXN = 3e5;

int n;
bool isInvited[2][MAXN+5];
vector <int> graph[MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int x = 1;x<=n;x++) cin >> isInvited[0][x];

    int m;
    cin >> m;
    for(int i = 0;i<m;i++)
    {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    double startTime = clock();

    int ans = 0;
    for(int x = 1;x<=n;x++) ans += isInvited[0][x];

    for(int iter = 1;iter<2*n;iter++)
    {
        if((clock()-startTime)/CLOCKS_PER_SEC > 0.5) break;

        for(int x = 1;x<=n;x++)
        {
            bool found = false;
            for(int y: graph[x])
            {
                if(isInvited[(iter&1)^1][y]==true)
                {
                    found = true;
                    break;
                }
            }

            isInvited[iter&1][x] = found;
        }

        int curr = 0;
        for(int x = 1;x<=n;x++) curr += isInvited[iter&1][x];
        ans = max(ans, curr);
    }

    cout << ans << '\n';
}
