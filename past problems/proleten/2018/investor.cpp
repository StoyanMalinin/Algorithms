#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

pair <long long, long long> extendedEuclid(long long A, long long B, long long S)
{
    long long x1 = 1, x2 = 0, y1 = 0, y2 = 1;
    long long r, q, temp;

    while (B)
    {
        q = A/B;
        r = A%B;
        A = B;
        B = r;

        temp = x1 - q*x2;
        x1 = x2;
        x2 = temp;

        temp = y1 - q*y2;
        y1 = y2;
        y2 = temp;
    }

    return {x1, y1};
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    long long n, s;
    cin >> n >> s;

    long long fib[50] = {0};
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= n; i++)
        fib[i] = fib[i-1] + fib[i-2];

    long long A = fib[n-2], B = fib[n-1];
    long long gcd = __gcd(A, B);

    if (s % gcd != 0) // Impossible
    {
        cout << 0 << endl;
        return 0;
    }

    A /= gcd;
    B /= gcd;
    s /= gcd;

    pair <long long, long long> roots = extendedEuclid(A, B, s);

    long long x0 = roots.first * s;
    long long y0 = roots.second * s;

    long long k1, k2;

    if (x0 % B == 0)
        k1 = -(x0/B) + 1;
    else k1 = ceil(-1.0*x0/B);

    if (y0 % A == 0)
        k2 = (y0/A) - 1;
    else k2 = floor(1.0*y0/A);

    if (k1 > k2)
    {
        cout << 0 << endl;
        return 0;
    }

    cout << k2 - k1 + 1 << endl;

    return 0;
}
