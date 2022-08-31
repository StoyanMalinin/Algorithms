#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e6 + 5;
const int64_t inf = 1e18;

struct Rectangle
{
    int64_t x, y, a;

    Rectangle(){}
    Rectangle(int64_t x, int64_t y, int64_t a) : x(x), y(y), a(a) {}
};

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
Rectangle rectangles[MAXN+5];

int64_t dp[MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0;i<n;i++) cin >> rectangles[i].x >> rectangles[i].y >> rectangles[i].a;
    sort(rectangles, rectangles+n,
    [](const Rectangle &A, const Rectangle &B)
    {
        if(A.x!=B.x) return A.x<B.x;
        if(A.y!=B.y) return A.y<B.y;
        return A.a<B.a;
    });

    ConvexHullTrick cht;

    dp[0] = rectangles[0].x*rectangles[0].y - rectangles[0].a;
    cht.add(Line(rectangles[0].x, dp[0]));

    for(int i = 1;i<n;i++)
    {
        int64_t currVal = rectangles[i].x*rectangles[i].y - rectangles[i].a;
        dp[i] = max(currVal, cht.get(-rectangles[i].y) + currVal);

        cht.add(Line(rectangles[i].x, dp[i]));
    }

    int64_t ans = 0;
    for(int i = 0;i<n;i++) ans = max(ans, dp[i]);

    cout << ans << '\n';
}
