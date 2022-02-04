#include <iostream>
#include <assert.h>
#include <array>
#include <queue>

using namespace std;

const int MAXN = 100;
const int inf = 1e9;

struct State
{
    int i, j;
    bool usedBomb;

    State(){}
    State(int i, int j, bool usedBomb) : i(i), j(j), usedBomb(usedBomb) {}

    State transition(pair <int, int> x, bool use)
    {
        assert(!(use==true && usedBomb==true));
        return {i+x.first, j+x.second, usedBomb^use};
    }

};

bool operator <(State A, State B)
{
    if(A.i!=B.i) return A.i<B.i;
    if(A.j!=B.j) return A.j<B.j;
    return A.usedBomb<B.usedBomb;
}

const array <pair <int, int>, 4> moves = {make_pair(+1, 0), make_pair(-1, 0), make_pair(0, +1), make_pair(0, -1)};
using DijkstraPQ = priority_queue <pair <int, State>, vector <pair <int, State>>, greater <pair <int, State>>>;

int n, m;
string grid[MAXN+5];

int dist[MAXN+5][MAXN+5][2];

bool isInside(State s)
{
    if(s.i<0 || s.j<0) return false;
    if(s.i>=n || s.j>=m) return false;

    return true;
}

void useVertex(State s, DijkstraPQ &pq)
{
    int currStateDist = dist[s.i][s.j][s.usedBomb];

    for(auto x: moves)
    {
        State newState = s.transition(x, false);
        if(isInside(newState)==true
           && grid[newState.i][newState.j]!='#'
           && dist[newState.i][newState.j][newState.usedBomb] > currStateDist + 1)
        {
            dist[newState.i][newState.j][newState.usedBomb] = currStateDist + 1;
            pq.push({dist[newState.i][newState.j][newState.usedBomb], newState});
        }
    }

    if(s.usedBomb==false)
    {
        for(auto x: moves)
        {
            State newState = s.transition(x, true);
            if(isInside(newState)==true
               && grid[newState.i][newState.j]=='#'
               && dist[newState.i][newState.j][newState.usedBomb] > currStateDist + 3)
            {
                dist[newState.i][newState.j][newState.usedBomb] = currStateDist + 3;
                pq.push({dist[newState.i][newState.j][newState.usedBomb], newState});
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

    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            dist[i][j][0] = dist[i][j][1] = inf;

    DijkstraPQ pq;

    dist[startPos.first][startPos.second][false] = 0;
    pq.push(make_pair(0, State(startPos.first, startPos.second, false)));

    while(pq.empty()==false)
    {
        auto top = pq.top();
        pq.pop();

        int d = top.first;
        State s = top.second;

        if(d!=dist[s.i][s.j][s.usedBomb])
            continue;

        useVertex(s, pq);
    }

    int ans = min(dist[endPos.first][endPos.second][0], dist[endPos.first][endPos.second][1]);
    if(ans==inf) ans = -1;

    cout << ans << '\n';
}
