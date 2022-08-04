#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

const int MAXN = 500;
const int MAXDIST = 2*MAXN*10;
const vector <pair <int, int>> directions = {make_pair(+1, 0), make_pair(-1, 0), make_pair(0, +1), make_pair(0, -1)};

pair <int, int> operator +(pair <int, int> lhs, pair <int, int> rhs)
{
    return {lhs.first+rhs.first, lhs.second+rhs.second};
}

int n, m;
int a[MAXN+5][MAXN+5];

int cost[MAXN+5][MAXN+5];
int distToCol[MAXN+5][MAXN+5][2];

bool isInGrid(pair <int, int> pos)
{
    return ((0<=pos.first && pos.first<n) && (0<=pos.second && pos.second<m));
}

void handleInput()
{
    cin >> n >> m;
    for(int i = 0;i<n;i++)
    {
        string s;
        cin >> s;

        for(int j = 0;j<m;j++)
            a[i][j] = s[j] - '0';
    }
}

struct DPState;

stack <pair <int, int>> pq[MAXDIST+5];
stack <DPState> dpPQ[2*MAXDIST+5];
int dp[MAXN+5][MAXN+5][2][2];

void initDistToCol(bool mode)
{
    int col = ((mode==false)?0:m-1);
    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            distToCol[i][j][mode] = MAXDIST + 5;

    for(int dist = 0;dist<=MAXDIST;dist++)
        while(pq[dist].empty()==false) pq[dist].pop();

    for(int i = 0;i<n;i++)
    {
        distToCol[i][col][mode] = cost[i][col];
        pq[cost[i][col]].emplace(i, col);
    }

    for(int dist = 0;dist<=MAXDIST;dist++)
    {
        while(pq[dist].empty()==false)
        {
            pair <int, int> x = pq[dist].top();
            pq[dist].pop();

            if(dist!=distToCol[x.first][x.second][mode]) continue;

            for(auto dir: directions)
            {
                pair <int, int> y = x + dir;
                if(isInGrid(y)==true && distToCol[y.first][y.second][mode] > distToCol[x.first][x.second][mode] + cost[y.first][y.second])
                {
                    distToCol[y.first][y.second][mode] = distToCol[x.first][x.second][mode] + cost[y.first][y.second];
                    pq[distToCol[y.first][y.second][mode]].push(y);
                }
            }
        }
    }
}

void init(int d)
{
    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            cost[i][j] = abs(a[i][j]-d);

    initDistToCol(false);
    initDistToCol(true);

    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            for(int conLeft = 0;conLeft<2;conLeft++)
                for(int conRight = 0;conRight<2;conRight++)
                    dp[i][j][conLeft][conRight] = 4*MAXDIST + 5;

    for(int dist = 0;dist<=MAXDIST;dist++)
        while(pq[dist].empty()==false) pq[dist].pop();
    for(int dist = 0;dist<=2*MAXDIST;dist++)
        while(dpPQ[dist].empty()==false) dpPQ[dist].pop();
}


struct DPState
{
    pair <int, int> pos;
    bool conLeft, conRight;

    DPState(int i, int j, bool conLeft, bool conRight) : pos(i, j), conLeft(conLeft), conRight(conRight) {}
    DPState(pair <int, int> pos, bool conLeft, bool conRight) : pos(pos), conLeft(conLeft), conRight(conRight) {}

    int& getDP() const
    {
        return dp[pos.first][pos.second][conLeft][conRight];
    }
};

int solve(int d)
{
    init(d);

    for(int j = 0;j<m;j++)
    {
        dp[0][j][false][false] = cost[0][j];
        dpPQ[dp[0][j][0][0]].emplace(0, j, false, false);
    }

    for(int dist = 0;dist<=2*MAXDIST;dist++)
    {
        while(dpPQ[dist].empty()==false)
        {
            DPState s = dpPQ[dist].top();
            dpPQ[dist].pop();

            if(s.getDP()!=dist) continue;
            if(s.conLeft==true && s.conRight==true && s.pos.first==n-1) return dist;

            //cout << s.pos.first << " " << s.pos.second << " || " << s.conLeft << " " << s.conRight << '\n';

            if(s.conLeft==false)
            {
                DPState sNew = s;
                sNew.conLeft = true;

                if(sNew.getDP() > s.getDP() + distToCol[s.pos.first][s.pos.second][false] - cost[s.pos.first][s.pos.second])
                {
                    sNew.getDP() = s.getDP() + distToCol[s.pos.first][s.pos.second][false] - cost[s.pos.first][s.pos.second];
                    dpPQ[sNew.getDP()].push(sNew);
                }
            }
            if(s.conRight==false)
            {
                DPState sNew = s;
                sNew.conRight = true;

                if(sNew.getDP() > s.getDP() + distToCol[s.pos.first][s.pos.second][true] - cost[s.pos.first][s.pos.second])
                {
                    sNew.getDP() = s.getDP() + distToCol[s.pos.first][s.pos.second][true] - cost[s.pos.first][s.pos.second];
                    dpPQ[sNew.getDP()].push(sNew);
                }
            }
            for(auto dir: directions)
            {
                DPState sNew = s;
                sNew.pos = s.pos + dir;

                if(isInGrid(sNew.pos)==true && sNew.getDP() > s.getDP() + cost[sNew.pos.first][sNew.pos.second])
                {
                    sNew.getDP() = s.getDP() + cost[sNew.pos.first][sNew.pos.second];
                    dpPQ[sNew.getDP()].push(sNew);
                }
            }
        }
    }

    return 4*MAXDIST;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    handleInput();

    int ans = MAXDIST + 5;
    for(int d = 0;d<=9;d++)
        ans = min(ans, solve(d));

    cout << ans << '\n';
}
