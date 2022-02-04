#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

int n, m;
int a[5][105];

int memo[20][105];
int calcState(int mask, int column)
{
    if(column==m) return 0;
    if(memo[mask][column]!=-1)
        return memo[mask][column];

    int answer = 0;
    for(int shift = 0;shift<n;shift++)
    {
        for(int applyMask = 0;applyMask<(1<<n);applyMask++)
        {
            //гледаме на кои редове ще сложим макса да седи от тази колона
            int sum = 0;
            for(int i = 0;i<n;i++)
            {
                if(((applyMask>>i)&1)==1 && ((mask>>i)&1)==0)
                    sum += a[(i+shift)%n][column];
            }

            answer = max(answer, sum + calcState((mask|applyMask), column+1));
        }
    }

    memo[mask][column] = answer;
    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    while(T--)
    {
        int answer = 0;

        cin >> n >> m;
        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<m;j++)
            {
                cin >> a[i][j];
            }
        }

        memset(memo, -1, sizeof(memo));
        cout << calcState(0, 0) << '\n';
    }
}
