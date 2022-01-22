#include <iostream>
#include <assert.h>
#include <cstring>
#include <array>
#include <queue>

using namespace std;

const int MAXN = 100;

enum BombState
{
    UNUSED = 0,
    USING = 1,
    DETONATING = 2,
    USED = 3
};

struct State
{
    int i, j;
    BombState bombState;

    State moveState(pair <int, int> jump)
    {
        assert(bombState!=BombState::USING);

        if(bombState==BombState::DETONATING) return {i+jump.first, j+jump.second, BombState::USED};
        return {i+jump.first, j+jump.second, bombState};
    }

    State useBomb()
    {
        assert(bombState==BombState::UNUSED);
        return {i, j, BombState::USING};
    }

    State detonateBOMB()
    {
        assert(bombState==BombState::USING);
        return {i, j, BombState::DETONATING};
    }
};

int n, m;
string grid[MAXN+5];

int dist[MAXN+5][MAXN][4];
array <pair <int, int>, 4> dxdy = {make_pair(-1, 0), make_pair(+1, 0), make_pair(0, -1), make_pair(0, +1)};

bool canGo(int i, int j, BombState state)
{
    if(i<0 || j<0) return false;
    if(i>=n || j>=m) return false;
    if(grid[i][j]=='#' && state!=BombState::DETONATING) return false;

    return true;
}

int &getDist(const State &s)
{
    return dist[s.i][s.j][s.bombState];
}

void bfs(int startI, int startJ)
{
    queue <State> q;
    q.push({startI, startJ, BombState::UNUSED});

    memset(dist, -1, sizeof(dist));
    dist[startI][startJ][BombState::UNUSED] = 0;

    while(q.empty()==false)
    {
        State s = q.front();
        q.pop();

        if(s.bombState!=BombState::USING)
        {
            for(pair <int, int> jump: dxdy)
            {
                State newState = s.moveState(jump);
                if(canGo(newState.i, newState.j, s.bombState)==true)
                {
                    int &newStateDist = getDist(newState);
                    if(newStateDist==-1)
                    {
                        newStateDist = getDist(s) + 1;
                        q.push(newState);
                    }
                }
            }
        }

        if(s.bombState==BombState::UNUSED)
        {
            State newState = s.useBomb();
            if(canGo(newState.i, newState.j, s.bombState)==true)
            {
                int &newStateDist = getDist(newState);
                if(newStateDist==-1)
                {
                    newStateDist = getDist(s) + 1;
                    q.push(newState);
                }
            }
        }
        if(s.bombState==BombState::USING)
        {
            State newState = s.detonateBOMB();
            if(canGo(newState.i, newState.j, s.bombState)==true)
            {
                int &newStateDist = getDist(newState);
                if(newStateDist==-1)
                {
                    newStateDist = getDist(s) + 1;
                    q.push(newState);
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0;i<n;i++) cin >> grid[i];

    pair <int, int> startPos, endPos;
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            if(grid[i][j]=='B') startPos = {i, j};
            else if(grid[i][j]=='E') endPos = {i, j};
        }
    }

    bfs(startPos.first, startPos.second);

    int ans = MAXN*MAXN;
    if(dist[endPos.first][endPos.second][0]!=-1) ans = min(ans, dist[endPos.first][endPos.second][0]);
    if(dist[endPos.first][endPos.second][1]!=-1) ans = min(ans, dist[endPos.first][endPos.second][1]);
    if(dist[endPos.first][endPos.second][2]!=-1) ans = min(ans, dist[endPos.first][endPos.second][2]);
    if(dist[endPos.first][endPos.second][3]!=-1) ans = min(ans, dist[endPos.first][endPos.second][3]);

    if(ans==MAXN*MAXN) ans = -1;
    cout << ans << '\n';
}
