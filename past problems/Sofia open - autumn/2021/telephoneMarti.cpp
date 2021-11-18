#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e6+100;

int steps[MAX_N];
int firstStrictlyBigger[MAX_N];
int a[MAX_N], firstBiggest[MAX_N];

stack <int> temp;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, i, l, r;
    long long sum = 0;

    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += i;
        while (!temp.empty() && a[i] >= a[temp.top()])
        {
            firstBiggest[temp.top()] = i;
            temp.pop();
        }
        temp.push(i);
    }
    while (!temp.empty())
    {
        firstBiggest[temp.top()] = n;
        temp.pop();
    }
    firstBiggest[n] = n;

    steps[n] = 0;
    for(int i = n-1;i>=0;i--)
        steps[i] = 1 + steps[firstBiggest[i]];

    firstStrictlyBigger[n] = n;
    for(int i = n-1;i>=0;i--)
    {
        if(a[firstBiggest[i]]>a[i]) firstStrictlyBigger[i] = firstBiggest[i];
        else firstStrictlyBigger[i] = firstStrictlyBigger[firstBiggest[i]];
    }

    for (i = 0; i < n; i++)
    {
        l = firstStrictlyBigger[i];
        r = firstBiggest[l];
        if (l == n)continue;

        sum -= (n - l) - steps[l];
        /*
        while (l != n)
        {
            sum = sum - (r-l-1);
            l = r;
            r = firstBiggest[l];
        }
        */
    }
    cout << sum << endl;
    return 0;
}

