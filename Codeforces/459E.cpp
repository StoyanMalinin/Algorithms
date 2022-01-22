#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

const int MAXN = 3e5;

struct Edge
{
    int u, v, w;

    Edge(){}
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int dp[MAXN+5];

int n, m;
vector <Edge> edges;

void clearBuffer(list <pair <int, int>> &updateBuffer)
{
    for(auto item: updateBuffer)
        dp[item.first] = max(dp[item.first], item.second);
    updateBuffer.clear();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<m;i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edges.emplace_back(u, v, w);
    }

    sort(edges.begin(), edges.end(),
    [](Edge A, Edge B)
    {
        if(A.w!=B.w) return A.w<B.w;
        if(A.u!=B.u) return A.u<B.u;
        return A.v<B.v;
    });

    int last = -1;
    list <pair <int, int>> updateBuffer;

    for(Edge e: edges)
    {
        if(e.w!=last) clearBuffer(updateBuffer);
        last = e.w;

        updateBuffer.push_back({e.v, dp[e.u] + 1});
    }
    clearBuffer(updateBuffer);

    int ans = 0;
    for(int x = 1;x<=n;x++)
        ans = max(ans, dp[x]);

    cout << ans << '\n';
}
