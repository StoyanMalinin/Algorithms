//Автор: Марти Недев

#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

constexpr int64_t MAXN = 2e5;

bool check(const int64_t n, const int64_t k, const int32_t *a, const int32_t *b, int64_t mid)
{
    int rightPointer = n;
    int64_t br = 0;
    for (int i = 0; i < n; i++)
    {
        while (b[rightPointer-1] > mid - a[i] && rightPointer > 0)
            rightPointer--;

        br += rightPointer;
    }

    return br < k;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int64_t n, k;
    cin >> n >> k;

    int a[MAXN + 10], b[MAXN+10];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        cin >> b[i];

    sort (a, a+n);
    sort (b, b+n);

    int64_t l = 1, r = INT_MAX, mid;
    while (l <= r)
    {
        mid = (l+r)/2;
        if (check(n, k, a, b, mid))
            l = mid+1;
        else
            r = mid-1;

    }

    cout << l << endl;
    return 0;
}


