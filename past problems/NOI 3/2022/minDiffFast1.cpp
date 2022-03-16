#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 2e7;
const int MAXA = 4e6;
const int inf = 1e9;

bool APlus[MAXA+5], AMinus[MAXA+5];
bool BPlus[MAXA+5], BMinus[MAXA+5];
int BPlusOpt[MAXA+5], BMinusOpt[MAXA+5];

int diffCnt[2*MAXA+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L, P, F;
    int M, R, Q, G;

    cin >> N >> L >> P >> F;

    int val = 0;
    for(int i = 0;i<N;i++)
    {
        val = (val+L)%P;
        if(i<F) AMinus[val] = true;
        else APlus[val] = true;
    }

    cin >> M >> R >> Q >> G;

    val = 0;
    for(int i = 0;i<M;i++)
    {
        val = (val+R)%Q;
        if(i<G) BMinus[val] = true;
        else BPlus[val] = true;
    }

    BMinusOpt[0] = BPlusOpt[0] = inf;

    int uniqueDiffs = 0;

    //A[ptr]<=B[i]
    int lastFound = inf;
    for(int x = MAXA;x>=0;x--)
    {
        if(AMinus[x]==true) lastFound = -x;
        if(BMinus[x]==true)
        {
            if(lastFound==inf) BMinusOpt[x] = inf;
            else BMinusOpt[x] = (-x) - lastFound;
        }
    }
    for(int x = 0;x<=MAXA;x++)
    {
        if(APlus[x]==true) lastFound = x;
        if(BPlus[x]==true)
        {
            if(lastFound==inf) BPlusOpt[x] = inf;
            else BPlusOpt[x] = x - lastFound;
        }
    }

    //A[ptr]>=B[i]
    lastFound = inf;
    for(int x = MAXA;x>=0;x--)
    {
        if(APlus[x]==true) lastFound = x;
        if(BPlus[x]==true)
        {
            if(lastFound!=inf) BPlusOpt[x] = min(BPlusOpt[x], lastFound - x);

            if(x!=0)
            {
                diffCnt[BPlusOpt[x]]++;
                if(diffCnt[BPlusOpt[x]]==1) uniqueDiffs++;
            }

        }
    }
    for(int x = 0;x<=MAXA;x++)
    {
        if(AMinus[x]==true) lastFound = -x;
        if(BMinus[x]==true)
        {
            if(lastFound!=inf) BMinusOpt[x] = min(BMinusOpt[x], lastFound - (-x));

            if(x!=0)
            {
                diffCnt[BMinusOpt[x]]++;
                if(diffCnt[BMinusOpt[x]]==1) uniqueDiffs++;
            }
        }
    }

    if(BMinus[0]==true || BPlus[0]==true)
    {
        int diff0 = min(BMinusOpt[0], BPlusOpt[0]);

        diffCnt[diff0]++;
        if(diffCnt[diff0]==1) uniqueDiffs++;
    }


    cout << uniqueDiffs << '\n';

    bool firstPrinted = true;
    for(int x = 2*MAXA;x>=0;x--)
    {
        if(diffCnt[x]!=0)
        {
            if(firstPrinted==true) cout << x;
            else cout << " " << x;

            firstPrinted = false;
        }
    }
}
