#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 2000;

int n, m;
char grid[MAXN+5][MAXN+5];

int reporterDist[MAXN+5][MAXN+5];
void bfs()
{
    queue <pair <int, int>> q;
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            reporterDist[i][j] = MAXN*MAXN;
            if(grid[i][j]=='+')
            {
                reporterDist[i][j] = 0;
                q.emplace(i, j);
            }
        }
    }

    while(q.empty()==false)
    {
        pair <int, int> x = q.front();
        q.pop();

        int currD = reporterDist[x.first][x.second];

        if(x.first-1>=0 && reporterDist[x.first-1][x.second]>currD+1)
        {
            q.emplace(x.first-1, x.second);
            reporterDist[x.first-1][x.second] = currD + 1;
        }
        if(x.first+1<n && reporterDist[x.first+1][x.second]>currD+1)
        {
            q.emplace(x.first+1, x.second);
            reporterDist[x.first+1][x.second] = currD + 1;
        }
        if(x.second-1>=0 && reporterDist[x.first][x.second-1]>currD+1)
        {
            q.emplace(x.first, x.second-1);
            reporterDist[x.first][x.second-1] = currD + 1;
        }
        if(x.second+1<m && reporterDist[x.first][x.second+1]>currD+1)
        {
            q.emplace(x.first, x.second+1);
            reporterDist[x.first][x.second+1] = currD + 1;
        }
    }
}

pair <int, int> P, C;
void init()
{
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            if(grid[i][j]=='P') P = {i, j};
            else if(grid[i][j]=='C') C = {i, j};
        }
    }

    bfs();
}

int dist[MAXN+5][MAXN+5];

using DijkstraPQ = priority_queue <pair <int, pair <int, int>>>;

void useVertex(pair <int, int> x, DijkstraPQ& pq)
{
    int currD = dist[x.first][x.second];

    if(x.first-1>=0 && dist[x.first-1][x.second]<min(currD, reporterDist[x.first-1][x.second]))
    {
        dist[x.first-1][x.second] = min(currD, reporterDist[x.first-1][x.second]);
        pq.emplace(dist[x.first-1][x.second], make_pair(x.first-1, x.second));
    }
    if(x.first+1<n && dist[x.first+1][x.second]<min(currD, reporterDist[x.first+1][x.second]))
    {
        dist[x.first+1][x.second] = min(currD, reporterDist[x.first+1][x.second]);
        pq.emplace(dist[x.first+1][x.second], make_pair(x.first+1, x.second));
    }
    if(x.second-1>=0 && dist[x.first][x.second-1]<min(currD, reporterDist[x.first][x.second-1]))
    {
        dist[x.first][x.second-1] = min(currD, reporterDist[x.first][x.second-1]);
        pq.emplace(dist[x.first][x.second-1], make_pair(x.first, x.second-1));
    }
    if(x.second+1<m && dist[x.first][x.second+1]<min(currD, reporterDist[x.first][x.second+1]))
    {
        dist[x.first][x.second+1] = min(currD, reporterDist[x.first][x.second+1]);
        pq.emplace(dist[x.first][x.second+1], make_pair(x.first, x.second+1));
    }
}

int Dijkstra()
{
    DijkstraPQ pq;
    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            dist[i][j] = -MAXN*MAXN;

    dist[P.first][P.second] = reporterDist[P.first][P.second];
    pq.emplace(reporterDist[P.first][P.second], P);

    while(pq.empty()==false)
    {
        auto top = pq.top();
        pq.pop();

        pair <int, int> x = top.second;
        if(dist[x.first][x.second]!=top.first) continue;

        useVertex(x, pq);
    }

    return dist[C.first][C.second];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<n;i++) cin >> grid[i];

    init();

    cout << Dijkstra() << '\n';
}
