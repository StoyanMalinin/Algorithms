#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2e5 + 5;
const double inf = 1e18;

struct Line
{
    int64_t a, b;

    Line(){}
    Line(int64_t a, int64_t b) : a(a), b(b) {}

    int64_t get(int64_t x)
    {
        return a*x + b;
    }
};

double intersect(const Line& l1, const Line& l2)
{
    return (l1.b-l2.b)/(l2.a-l1.a);
}

struct ConvexHullTrick
{
    vector <Line> v;
    vector <double> from;

    void addLine(const Line &l)
    {
        while(v.size()>=2 && from.back()<=intersect(v[v.size()-2], l))
        {
            v.pop_back();
            from.pop_back();
        }

        if(v.empty()==true)
        {
            v.push_back(l);
            from.push_back(inf);
        }
        else
        {
            from.push_back(intersect(v.back(), l));
            v.push_back(l);
        }
    }

    int64_t get(int64_t x)
    {
        if(v.empty()==true) return -inf;
        if(v.size()==1) return v[0].get(x);

        int l = 0, r = from.size() - 1, mid;
        while(l+1<r)
        {
            mid = (l+r)/2;

            if(from[mid]>=x) l = mid;
            else r = mid - 1;
        }

        if(from[r]>=x) return v[r].get(x);
        return v[l].get(x);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ConvexHullTrick cht;

    int n;
    cin >> n;

    int64_t ans = 0;
    int64_t p = 0, pHat = 0;

    for(int i = 0;i<n;i++)
    {
        int64_t x;
        cin >> x;

        p += x;
        pHat += (i+1)*x;

        ans = max(ans, cht.get(p) + pHat);
        ans = max(ans, pHat);

        cht.addLine(Line(-(i+1), -pHat + (i+1)*p));
    }

    cout << ans << '\n';
}
