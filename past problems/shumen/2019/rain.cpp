#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e6;

int n;
int h[MAXN+5];
int lift[MAXN+5];

int maxSuff[MAXN+5];

int64_t evalOperations() //смятаме колко повдигания са ни нужни и "оправяме" масива lift
{
    maxSuff[n] = 0;
    for(int i = n-1;i>=0;i--)
        maxSuff[i] = max(h[i]+lift[i], maxSuff[i+1]);

    int maxPref = 0;
    for(int i = 0;i<n;i++)
    {
        if(h[i]+lift[i]<=maxPref && h[i]+lift[i]<=maxSuff[i+1]) //първи случай
        {
            lift[i] = 0;
        }
        else if(h[i]+lift[i]>=maxPref && h[i]+lift[i]>=maxSuff[i+1]) //втори случай
        {
            if(maxPref==maxSuff[i+1])
            {
                lift[i] = 0;
            }
            else
            {
                int maxWaterLevel = max(maxPref, maxSuff[i+1]);

                lift[i] = maxWaterLevel - h[i];
                if(lift[i]<0) lift[i] = 0; //може да стане отрицателен lift, ако се окаже, че стената си е била оригинално твърде висока
            }
        }
        else //трети случай
        {
            //не пипаме, понеже операцията е имала смисъл
        }

        maxPref = max(maxPref, h[i]+lift[i]);
    }

    int64_t ans = 0;
    for(int i = 0;i<n;i++) ans += (lift[i]!=0);//смятаме броя на стените, които получават увеличение

    return ans;
}

int64_t evalOptimum() //смятаме водата, вече с новия масив lift, очевидно със стария отговорът щеше да е същия,
                      //понеже се опитваме да го коригираме без да намаляваме водата
{
    int64_t ans = 0;

    maxSuff[n] = 0;
    for(int i = n-1;i>=0;i--)
        maxSuff[i] = max(h[i]+lift[i], maxSuff[i+1]);

    int maxPref = 0;
    for(int i = 0;i<n;i++)
    {
        maxPref = max(maxPref, h[i]+lift[i]);
        ans += min(maxPref, maxSuff[i+1]);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0;i<n;i++) cin >> h[i];

    int k;
    cin >> k;
    for(int i = 0;i<k;i++)
    {
        int ind;
        cin >> ind;
        cin >> lift[ind];
    }

    cout << evalOperations() << " " << evalOptimum() << '\n';
}
