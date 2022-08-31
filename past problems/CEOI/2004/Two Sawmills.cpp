#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2e4;

struct Line
{
    int64_t a, b;

    Line(){}
    Line(int64_t a, int64_t b)
    {
        this->a = a;
        this->b = b;
    }

    int64_t get(int64_t x)
    {
        return a*x + b;
    }
};

double intersect(const Line &A, const Line &B)
{
    return double(B.b-A.b)/double(A.a-B.a);
}

struct ConvexHullTrick
{
    vector <Line> v;
    vector <double> to;

    void add(const Line &l)
    {
        while(v.size()>=2 && to.back()>=intersect(v[v.size()-2], l))
        {
            v.pop_back();
            to.pop_back();
        }

        if(v.empty()==true)
        {
            v.push_back(l);
        }
        else
        {
            to.push_back(intersect(v.back(), l));
            v.push_back(l);
        }
    }

    int64_t get(double x)
    {
        auto it = upper_bound(to.begin(), to.end(), x);
        return v[it-to.begin()].get(x);
    }
};

int n;
int w[MAXN+5], d[MAXN+5];

int64_t dp[2][MAXN+5];
int64_t wPref[MAXN+5], dSuff[MAXN+5];

int main()
{
    const int K = 2;

    cin >> n;
    for(int i = 0;i<n;i++) cin >> w[i] >> d[i];

    wPref[0] = w[0];
    for(int i = 1;i<n;i++) wPref[i] = wPref[i-1] + w[i];

    dSuff[n-1] = d[n-1];
    for(int i = n-2;i>=0;i--) dSuff[i] = dSuff[i+1] + d[i];

    int64_t totalCost = 0;
    for(int i = 0;i<n;i++) totalCost += w[i]*dSuff[i];

    for(int i = 0;i<n;i++)
        dp[0][i] = 0;

    for(int iter = 1;iter<K;iter++)
    {
        ConvexHullTrick cht;

        cht.add(Line(dSuff[n-iter], wPref[n-iter]*dSuff[n-iter] + dp[(iter&1)^1][n-iter]));
        for(int i = n-1-iter;i>=0;i--)
        {
            dp[iter&1][i] = cht.get(-wPref[i]);
            cht.add(Line(dSuff[i], wPref[i]*dSuff[i] + dp[(iter&1)^1][i]));
        }
    }

    int64_t bestRelaxation = 0;
    for(int i = 0;i<n;i++)
    {
        bestRelaxation = max(bestRelaxation, wPref[i]*dSuff[i] + dp[(K-1)&1][i]);
    }

    cout << totalCost - bestRelaxation << '\n';
}
