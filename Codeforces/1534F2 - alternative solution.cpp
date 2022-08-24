#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>

using namespace std;

const int MAXN = 4e5 + 5;

struct DirectedGraph
{
    int n;
    vector <vector <int>> graph;
    vector <vector <int>> graphInv;

    vector <bool> used;
    vector <pair <int, int>> dp;

    DirectedGraph(){}
    DirectedGraph(int n)
    {
        this->n = n;
        this->graph.resize(n);
        this->graphInv.resize(n);

        this->used.resize(n);
        this->dp.assign(n, {MAXN, -MAXN});
    }

    void updateRange(pair <int, int> &r, pair <int, int> newInfo)
    {
        r.first = min(r.first, newInfo.first);
        r.second = max(r.second, newInfo.second);
    }

    void addEdge(int u, int v)
    {
        graph[u].push_back(v);
        graphInv[v].push_back(u);
    }

    void fixEdges()
    {
        for(vector <int> &v: graph)
        {
            sort(v.begin(), v.end());
            v.resize(unique(v.begin(), v.end()) - v.begin());
        }
    }

    void dfs(int x, stack <int> &st)
    {
        used[x] = true;
        for(int y: graph[x])
        {
            if(used[y]==false) dfs(y, st);
        }

        st.push(x);
    }

    void dfsInv(int x, vector <int> &v)
    {
        used[x] = true;
        for(int y: graphInv[x])
        {
            if(used[y]==false) dfsInv(y, v);
        }

        v.push_back(x);
    }

    void dfsTopsort(int x, vector <int> &v)
    {
        used[x] = true;
        for(int y: graph[x])
            if(used[y]==false) dfsTopsort(y, v);

        v.push_back(x);
    }

    pair<DirectedGraph*, vector <int>*> compress()
    {
        stack <int> st;
        fill(used.begin(), used.end(), false);
        for(int x = 0;x<n;x++)
        {
            if(used[x]==false) dfs(x, st);
        }

        vector <vector <int>> SCCs;
        fill(used.begin(), used.end(), false);

        while(st.empty()==false)
        {
            int x = st.top();
            st.pop();

            if(used[x]==false)
            {
                SCCs.push_back({});
                dfsInv(x, SCCs.back());
            }
        }

        DirectedGraph *G = new DirectedGraph(SCCs.size());
        vector <int> *mp = new vector <int>(n);

        for(int i = 0;i<SCCs.size();i++)
            for(int x: SCCs[i]) (*mp)[x] = i;

        for(int x = 0;x<n;x++)
        {
            for(int y: graph[x])
                if((*mp)[x]!=(*mp)[y])
                    G->addEdge((*mp)[x], (*mp)[y]);
        }
        G->fixEdges();

        return {G, mp};
    }

    void evalDp()
    {
        vector <int> topSort;
        fill(used.begin(), used.end(), false);
        for(int x = 0;x<n;x++)
        {
            if(used[x]==false)
                dfsTopsort(x, topSort);
        }

        reverse(topSort.begin(), topSort.end());
        for(int x: topSort)
        {
            for(int y: graphInv[x])
                updateRange(dp[x], dp[y]);
        }
    }
};

struct Grid
{
    int n, m;
    char **a;

    int **cellNode;

    Grid(){}
    Grid(int n, int m)
    {
        this->n = n;
        this->m = m;

        this->a = new char*[n];
        for(int i = 0;i<n;i++) this->a[i] = new char[m+1];

        this->cellNode = new int*[n+5];
        for(int i = 0;i<n;i++) this->cellNode[i] = new int[m+5];
    }

    int sandCnt = 0;
    void read(istream &in)
    {
        for(int i = 0;i<n;i++)
            in >> a[i];

        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<m;j++)
            {
                if(a[i][j]=='#')
                {
                    cellNode[i][j] = sandCnt;
                    sandCnt++;
                }
            }
        }
    }

    DirectedGraph* convertToGraph()
    {
        DirectedGraph *G = new DirectedGraph(sandCnt);

        for(int j = 0;j<m;j++)
        {
            int row = -1;
            for(int i = n-1;i>=0;i--)
            {
                if(a[i][j]=='#')
                {
                    if(row!=-1) G->addEdge(cellNode[i][j], cellNode[row][j]);
                    row = i;
                }
            }
        }
        for(int j = 0;j<m;j++)
        {
            int row = -1;
            for(int i = 0;i<n;i++)
            {
                if(a[i][j]=='#')
                {
                    if(row!=-1 && row==i-1) G->addEdge(cellNode[i][j], cellNode[row][j]);
                    row = i;
                }
            }
        }

        for(int j = 1;j<m;j++)
        {
            int row = -1;
            for(int i = n-1;i>=0;i--)
            {
                if(a[i][j-1]=='#') row = i;
                if(a[i][j]=='#' && row!=-1)
                    G->addEdge(cellNode[i][j], cellNode[row][j-1]);
            }
        }
        for(int j = 0;j<m-1;j++)
        {
            int row = -1;
            for(int i = n-1;i>=0;i--)
            {
                if(a[i][j+1]=='#') row = i;
                if(a[i][j]=='#' && row!=-1)
                    G->addEdge(cellNode[i][j], cellNode[row][j+1]);
            }
        }

        return G;
    }
};

Grid grid;
int a[MAXN];

DirectedGraph* readAndInit()
{
    int n, m;
    cin >> n >> m;

    grid = Grid(n, m);grid.read(cin);
    for(int i = 0;i<m;i++) cin >> a[i];

    return grid.convertToGraph();
}

int findMinimalCoverage(DirectedGraph *G, const vector <pair <int, int>> &v)
{
    set <int> waiting;
    map <int, vector<int>> start2Ends;

    for(const auto& item: v)
        start2Ends[item.first].push_back(item.second);

    int ans = 0;
    for(int x = 0;x<grid.m;x++)
    {
        for(int r: start2Ends[x]) waiting.insert(r);
        if(waiting.count(x)==true)
        {
            ans++;
            waiting.clear();
        }
    }

    return ans;
}

void initDp(DirectedGraph *G, vector <int> &mp)
{
    for(int i = 0;i<grid.n;i++)
        for(int j = 0;j<grid.m;j++)
            if(grid.a[i][j]=='#')
                G->dp[mp[grid.cellNode[i][j]]] = make_pair(j, j);
}

vector <pair <int, int>> getRanges(DirectedGraph *G, vector <int> &mp)
{
    vector <pair <int, int>> ranges;
    for(int j = 0;j<grid.m;j++)
    {
        int added = 0;
        for(int i = grid.n-1;i>=0;i--)
        {
            if(grid.a[i][j]=='#')
            {
                added++;
                if(added==a[j])
                {
                    ranges.push_back(G->dp[mp[grid.cellNode[i][j]]]);
                    break;
                }
            }
        }
    }

    return ranges;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    DirectedGraph *gridGraph = readAndInit();

    auto res = gridGraph->compress();
    vector <int> mp = std::move(*res.second);
    DirectedGraph *G = res.first;
    delete res.second;

    initDp(G, mp);
    G->evalDp();
    vector <pair <int, int>> ranges = getRanges(G, mp);

    cout << findMinimalCoverage(G, ranges) << '\n';
}
