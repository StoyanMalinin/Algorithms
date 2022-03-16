#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 2e7;
const int MAXA = 4e6;

int A[MAXN+5], B[MAXN+5];
int diffCnt[2*MAXA+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, L, P, F;
    int M, R, Q, G;

    cin >> N >> L >> P >> F;
    A[0] = L%P;
    for(int i = 1;i<N;i++) A[i] = (A[i-1]+L)%P;
    for(int i = 0;i<F;i++) A[i] = -A[i];

    cin >> M >> R >> Q >> G;
    B[0] = R%Q;
    for(int i = 1;i<M;i++) B[i] = (B[i-1]+R)%Q;
    for(int i = 0;i<G;i++) B[i] = -B[i];

    sort(A, A+N);
    sort(B, B+M);
    int uniqueDiffs = 0, ptr = 0;

    for(int i = 0;i<M;i++)
    {
        while(ptr+1<N && A[ptr+1]<=B[i]) ptr++;

        int diff = MAXA*2;
        diff = min(diff, abs(B[i]-A[ptr]));
        if(ptr+1<N) diff = min(diff, A[ptr+1]-B[i]);

        diffCnt[diff]++;
        if(diffCnt[diff]==1) uniqueDiffs++;
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
