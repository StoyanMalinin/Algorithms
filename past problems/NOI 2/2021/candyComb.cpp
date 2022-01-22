#include <iostream>
#include <set>

using namespace std;

const int MAXN = 15;

int n, m, k;
int64_t comb[MAXN*MAXN+5][MAXN*MAXN+5];

void init()
{
    comb[0][0] = 1;
    for(int i = 1;i<=MAXN*MAXN;i++)
    {
        comb[i][0] = 1;
        for(int j = 1;j<=i;j++)
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }
}

int countProjections(int i, int j)
{
    set <pair <int, int>> s;
    for(int rep1 = 0;rep1<2;rep1++)
    {
        for(int rep2 = 0;rep2<2;rep2++)
        {
            s.insert({i, j});

            j = m - j- 1;
        }

        i = n - i - 1;
    }

    return s.size();
}

int main()
{
    cin >> n >> m >> k;

    init();

    int n1 = 0, n2 = 0, n4 = 0;
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            int c = countProjections(i, j);
            if(c==1) n1++;
            else if(c==2) n2++;
            else if(c==4) n4++;
        }
    }

    int64_t ans = 0;
    for(int c4 = 0;c4<=n4/4;c4++)
    {
        for(int c2 = 0;c2<=n2/2;c2++)
        {
            int c1 = k - c2*2 - c4*4;
            if(c1<0) continue;

            ans += comb[n4/4][c4]*comb[n2/2][c2]*comb[n1/1][c1];
        }
    }

    cout << ans << '\n';
}
