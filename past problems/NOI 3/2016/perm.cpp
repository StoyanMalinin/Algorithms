#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 60;

int64_t fact[MAXN+5];
int64_t comb[MAXN+5][MAXN+5];

void init()
{
    comb[0][0] = 1;
    for(int i = 1;i<=MAXN;i++)
    {
        comb[i][0] = 1;
        for(int j = 1;j<=i;j++)
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
    }

    fact[0] = 1;
    for(int i = 1;i<=MAXN;i++)
        fact[i] = fact[i-1]*i;
}

int64_t invCountSlow(int n)
{
    int p[MAXN+1];
    for(int x = 1;x<=n;x++) p[x] = x;

    int64_t ans = 0;
    do
    {
        bool fail = false;
        for(int i = 1;i<=n;i++)
        {
            if(p[p[i]]!=i)
            {
                fail = true;
                break;
            }
        }

        if(fail==false)
            ans++;
    }
    while(next_permutation(p+1, p+n+1));

    return ans;
}

int64_t invCountFast(int n)
{
    int64_t ans = 0;
    for(int fixed = 0;fixed<=n;fixed++)
    {
        if((n-fixed)%2!=0) continue;

        //това е формулата, но ние ще я смятаме по тъп начин, за да избегнем overflow
        //ans += comb[n][fixed]*(fact[n-fixed]/((1LL<<((n-fixed)/2))*fact[(n-fixed)/2]));

        //алтернативна сметка
        //ans += comb[n][fixed]*((comb[n-fixed][(n-fixed)/2]*fact[(n-fixed)/2])/(1LL<<((n-fixed)/2)));

        int64_t curr = 1;
        int toDiv2 = (n-fixed)/2;

        for(int x = (n-fixed)/2+1;x<=n-fixed;x++)
        {
            curr *= x;
            while(curr%2==0 && toDiv2>0)
            {
                toDiv2--;
                curr /= 2;
            }
        }

        ans += comb[n][fixed]*curr;
    }

    return ans;
}

bool used[MAXN];
int perm[MAXN+5];

void genPerm(int n, int ind, int emptyPos, int64_t k)
{
    if(ind==n+1) return;
    if(perm[ind]!=-1) genPerm(n, ind+1, emptyPos, k);

    for(int i = 1;i<=n;i++)
    {
        if(used[i]==false)
        {
            int64_t amount = 0;
            if(i!=ind) amount = invCountFast(emptyPos-2);
            else amount = invCountFast(emptyPos-1);

            if(amount<=k)
                k -= amount;
            else
            {
                if(i!=ind) emptyPos -= 2;
                else emptyPos--;

                perm[ind] = i;
                perm[i] = ind;
                used[i] = used[ind] = true;
                genPerm(n, ind+1, emptyPos, k);

                break;
            }
        }
    }
}

int main()
{
    init();

    //cout << invCountFast(4) << '\n';
    //for(int n = 1;n<=30;n++)
    //    cout << "invCount[" << n << "] = " << invCountFast(n) << " == " << invCountSlow(n) << '\n';

    int n;
    int64_t k;
    cin >> n >> k;

    for(int i = 1;i<=n;i++) perm[i] = -1;
    genPerm(n, 1, n, k-1);

    cout << perm[1];
    for(int i = 2;i<=n;i++) cout << " " << perm[i];
    cout << '\n';
}
