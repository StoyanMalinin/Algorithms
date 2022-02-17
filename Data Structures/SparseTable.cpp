#include <iostream>

using namespace std;

const int MAXN = 1e5;
const int MAXLog = 20;

int n;
int a[MAXN+5];

int log2[MAXN+5];
int sparse[MAXLog+2][MAXN+5];

void init()
{
    log2[1] = 0;
    for(int x = 2;x<=MAXN;x++)
        log2[x] = log2[x/2] + 1;

    for(int i = 0;i<n;i++) sparse[0][i] = a[i];
    for(int l = 1;l<=MAXLog;l++)
    {
        for(int i = 0;i<n;i++)
        {
            if(i+(1<<(l-1)) >= n)
                sparse[l][i] = sparse[l-1][i];
            else
                sparse[l][i] = min(sparse[l-1][i], sparse[l-1][i+(1<<(l-1))]);
        }
    }
}

int rmq(int l, int r) //range minimum query
{
    return min(sparse[log2[r-l+1]][l], sparse[log2[r-l+1]][r - (1<<log2[r-l+1]) + 1]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];

    init();

    int Q;
    cin >> Q;
    while(Q--)
    {
        int l, r;
        cin >> l >> r;

        cout << rmq(l, r) << '\n';
    }
}
