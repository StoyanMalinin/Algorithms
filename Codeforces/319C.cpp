#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2e5 + 5;
const int64_t inf = 1e18 + 5;

struct Line
{
    int64_t a, b;

    Line(){}
    Line(double a, double b)
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
int64_t a[MAXN], b[MAXN];

int64_t dp[MAXN];
ConvexHullTrick cht;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0;i<n;i++)
    {
        cin >> a[i];
    }
    for(int i = 0;i<n;i++)
    {
        cin >> b[i];
    }

    dp[n-1] = 0;
    cht.add(Line(a[n-1], dp[n-1]));

    for(int i = n-2;i>=0;i--)
    {
        dp[i] = cht.get(b[i]);
        cht.add(Line(a[i], dp[i]));
    }

    cout << dp[0] << '\n';
}
