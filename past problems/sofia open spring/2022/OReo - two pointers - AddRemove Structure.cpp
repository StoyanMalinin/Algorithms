#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXBit = 31;
struct ORCounter
{
    int bitCnt[MAXBit+2];

    ORCounter()
    {
        memset(this->bitCnt, 0, sizeof(this->bitCnt));
    }

    void addNum(int x)
    {
        for(int b = 0;b<=MAXBit;b++)
            if(((x>>b)&1)==1) bitCnt[b]++;
    }

    void remNum(int x)
    {
        for(int b = 0;b<=MAXBit;b++)
            if(((x>>b)&1)==1) bitCnt[b]--;
    }

    int eval()
    {
        int ans = 0;
        for(int b = 0;b<=MAXBit;b++)
            if(bitCnt[b]!=0) ans += (1<<b);

        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, k;
    int a[100500];
    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    int64_t ans = 0;

    int lPtr = 0, rPtr = 0;

    ORCounter O;
    O.addNum(a[0]);

    for (int i = 0; i < n; i++)
    {
        while(rPtr<i)
        {
            O.addNum(a[rPtr+1]);
            rPtr++;
        }
        while(lPtr<i)
        {
            O.remNum(a[lPtr]);
            lPtr++;
        }
        while(O.eval()<k && rPtr+1<n)
        {
            O.addNum(a[rPtr+1]);
            rPtr++;
        }

        if(rPtr<n && O.eval()>=k)
            ans += n - rPtr;
    }

    cout << ans << endl;



    return 0;
}
