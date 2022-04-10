#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5;

enum STATES
{
    DONE = 0,
    BUILDING_SELECTED = 1,
    BUILDING_WAITING = 2
};

int F[MAXN+5];
int64_t dp[MAXN+5][3];
vector <int> children[MAXN+5];

void reset(int n)
{
    for(int x = 1;x<=n;x++)
        children[x].clear();
    for(int x = 1;x<=n;x++)
        dp[x][STATES::DONE] = dp[x][STATES::BUILDING_SELECTED] = dp[x][BUILDING_WAITING] = 0;
}

void dfs(int x)
{
    if(children[x].empty()==true)
    {
        dp[x][STATES::DONE] = dp[x][STATES::BUILDING_SELECTED] = F[x];
        dp[x][BUILDING_WAITING] = 0;

        return;
    }

    int64_t doneSum = 0;
    for(int c: children[x])
    {
        dfs(c);
        doneSum += dp[c][STATES::DONE];
    }

    for(int c: children[x])
    {
        int64_t sum = doneSum - dp[c][STATES::DONE];

        dp[x][STATES::DONE] = max(dp[x][STATES::DONE], sum + dp[c][STATES::BUILDING_SELECTED]);
        dp[x][STATES::DONE] = max(dp[x][STATES::DONE], sum + dp[c][STATES::BUILDING_WAITING] + F[x]);

        dp[x][STATES::BUILDING_SELECTED] = max(dp[x][STATES::BUILDING_SELECTED],
                                               sum + dp[c][STATES::BUILDING_SELECTED]);
        dp[x][STATES::BUILDING_SELECTED] = max(dp[x][STATES::BUILDING_SELECTED],
                                               sum + dp[c][STATES::BUILDING_WAITING] + F[x]);

        dp[x][STATES::BUILDING_WAITING] = max(dp[x][STATES::BUILDING_WAITING],
                                              sum + dp[c][STATES::BUILDING_WAITING]);
    }
}

void solveTestcase(int testCase)
{
    int n;
    cin >> n;
    reset(n);

    for(int x = 1;x<=n;x++)
        cin >> F[x];

    vector <int> roots;
    for(int x = 1;x<=n;x++)
    {
        int par;
        cin >> par;

        if(par!=0)
            children[par].push_back(x);
        else
            roots.push_back(x);
    }

    int64_t ans = 0;
    for(int x: roots)
    {
        dfs(x);
        ans += dp[x][STATES::DONE];
    }

    cout << "Case #" << testCase << ": " << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for(int t = 1;t<=T;t++)
        solveTestcase(t);
}
