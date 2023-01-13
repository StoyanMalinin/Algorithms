#include<iostream>
#include<cstring>
#include<vector>
#include<queue>

using namespace std;

const int MAXN = 2005;

struct outfit
{
    int a, b, c, w;
};

int ptr[MAXN];
int dist[MAXN];
long long G[MAXN][MAXN];
vector <int> graph[MAXN];

bool bought[MAXN];
vector <outfit> done;
int contribution[MAXN];

int nodeCnt = 3;
int clothing2Node[MAXN], outfit2Node[MAXN];

void addEdge(int u, int v, long long value)
{
    G[u][v] += value;
    graph[u].push_back(v);
    graph[v].push_back(u);
}

int S, T;
vector <int> answer;

queue <int> q;
bool BFS(int x)
{
    memset(dist, -1, sizeof(dist));
    while(q.empty()==false) q.pop();

    q.push(x);
    dist[x] = 0;
    while(q.empty()==false)
    {
        x = q.front();q.pop();
        if(x==T) break;

        for(int y: graph[x])
        {
            if(dist[y]==-1 && G[x][y]>0)
            {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }

    if(dist[T]==-1) return false;
    return true;
}

long long DFS(int x, long long minValue)
{
    if(x==T) return minValue;

    for(int i = ptr[x];i<graph[x].size();i++)
    {
        int y = graph[x][i];
        if(dist[y]==dist[x]+1 && G[x][y]>0)
        {
            long long flow = DFS(y, min(minValue, G[x][y]));

            if(flow!=-1)
            {
                G[x][y] -= flow;
                G[y][x] += flow;

                return flow;
            }
        }

        //ptr[x]++;
    }

    return -1;
}

long long Dinic()
{
    long long flow = 0;
    while(BFS(S)==true)
    {
        memset(ptr, 0, sizeof(ptr));

        bool pass = false;
        while(true)
        {
            long long add = DFS(S, 696969696969);
            if(add==-1) break;

            pass = true;
            flow += add;
        }

        if(pass==false) break;
    }

    return flow;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector <outfit> v;
    long long profit = 0;
    vector <long  long> prices;

    long long outfitSum = 0;

    int n, m;
    cin >> n >> m;

    S = 1;T = 2;
    for(int i = 0;i<n;i++)
    {
        clothing2Node[i] = nodeCnt;
        nodeCnt++;

        int t, c;
        cin >> t >> c;

        prices.push_back(c);
        addEdge(clothing2Node[i], T, c);
    }
    for(int i = 0;i<m;i++)
    {
        outfit2Node[i] = nodeCnt;
        nodeCnt++;

        int a, b, c, w;
        cin >> a >> b >> c >> w;
        a--;b--;c--;

        v.push_back({a, b, c, w});

        outfitSum += w;
        addEdge(S, outfit2Node[i], w);
        addEdge(outfit2Node[i], clothing2Node[a], 696969696969);
        addEdge(outfit2Node[i], clothing2Node[b], 696969696969);
        addEdge(outfit2Node[i], clothing2Node[c], 696969696969);
    }

    cout << outfitSum - Dinic();
    for(int i = 0;i<n;i++)
    {
        if(dist[ clothing2Node[i] ]!=-1)
        {
            answer.push_back(i+1);
        }
    }

    cout << " " << answer.size() << '\n';
    for(int x: answer)
    {
        cout << x << " ";
    }
    cout << '\n';

    //cout << currSum << '\n';
}

