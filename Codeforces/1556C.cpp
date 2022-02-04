#include<iostream>

using namespace std;

const int MAXN = 1e3 + 5;
const long long inf = 1e15 + 5;

int n;
long long a[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];

    long long ans = 0;
    for(int i = 0;i<n;i+=2)
    {
        long long sum = 0, minVal = inf;
        for(int j = i;j<n;j++)
        {
            if(j%2==0) sum += a[j];
            else
            {
                sum -= a[j];

                long long lastMinVal = minVal;
                minVal = min(minVal, sum);

                if(sum==0)
                    ans += min(min(a[i], a[j]), lastMinVal+1);
                else if(sum>0 && a[i]>=sum && minVal>=sum)
                    ans += min(a[j], min(a[i]-sum, lastMinVal-sum+1));
                else if(sum<0 && a[j]>=-sum)
                    ans += min(min(a[i], a[j]-(-sum)), lastMinVal+1);

                if(sum<0) break;
            }
        }
    }

    cout << ans << '\n';
}
