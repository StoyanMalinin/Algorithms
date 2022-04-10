// O(N^3*log(M*A))

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 105;
const int64_t inf = 1e17;

int n, refuels;
vector <pair <int, int64_t>> Graph[MAXN];
map <string, int> hashMap;

struct State
{
    int index, refuels;
    int64_t usedFuel;

    State(){}
    State(int index, int refuels, int64_t usedFuel)
        :index(index), refuels(refuels), usedFuel(usedFuel){}
};

int64_t dist[MAXN][MAXN];
void init(int n)
{
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            if(i!=j && dist[i][j]==0) dist[i][j] = inf;

    for(int k = 0;k<n;k++)
        for(int i = 0;i<n;i++)
            for(int j = 0;j<n;j++)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

bool check(const int totalAirports, int64_t flightDistance)
{
    int refuelCnt[MAXN];
    for(int x = 0;x<totalAirports;x++)
    {
        memset(refuelCnt, -1, sizeof(refuelCnt));

        queue <int> q;

        q.push(x);
        refuelCnt[x] = 1;

        int reached = 0;
        while(q.empty()==false)
        {
            int vertex = q.front();
            q.pop();reached++;

            if(refuelCnt[vertex]>refuels+1)
                return false;

            for(int y = 0;y<totalAirports;y++)
            {
                if(refuelCnt[y]==-1 && dist[vertex][y]<=flightDistance)
                {
                    refuelCnt[y] = refuelCnt[vertex] + 1;
                    q.push(y);
                }
            }
        }

        if(reached!=totalAirports)
            return false;
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> refuels;

    int totalAirports = 0;
    int64_t left = 0, right = 0;
    for (int i = 0; i < n; i++)
    {
        string airport1, airport2;
        int64_t distance;

        int start, finish;
        cin >> airport1 >> airport2 >> distance;
        right += distance;

        if (hashMap.find(airport1) == hashMap.end())
            hashMap[airport1] = totalAirports++;
        if (hashMap.find(airport2) == hashMap.end())
            hashMap[airport2] = totalAirports++;

        start = hashMap[airport1];
        finish = hashMap[airport2];

        dist[start][finish] = dist[finish][start] = distance;
        Graph[start].push_back({finish, distance});
        Graph[finish].push_back({start, distance});
    }

    init(totalAirports);

    while (left + 1 < right)
    {
        int64_t mid = (left+right)/2;

        if (check(totalAirports, mid) == true)
            right = mid;
        else
            left = mid + 1;

    }

    if(check(totalAirports, left)==true) cout << left << '\n';
    else cout << right << '\n';

    return 0;
}
