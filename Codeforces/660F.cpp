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
    return double(l1.b-l2.b)/double(l2.a-l1.a);
}

template <class T>
struct RevVector
{
    vector <T> v;

    T& operator[](int ind)
    {
        return v[v.size()-1-ind];
    }

    void popFront()
    {
        v.pop_back();
    }

    void pushFront(const T& item)
    {
        v.push_back(item);
    }

    int size() const
    {
        return v.size();
    }

    bool empty() const
    {
        return v.empty();
    }
};

struct ConvexHullTrick
{
    RevVector<Line> v;
    RevVector<double> to;

    void add(const Line &l)
    {
        while(v.size()>=2 && to[0]<=intersect(l, v[1]))
        {
            to.popFront();
            v.popFront();
        }

        if(v.empty()==true)
        {
            v.pushFront(l);
        }
        else
        {
            to.pushFront(intersect(l, v[0]));
            v.pushFront(l);
        }
    }

    int64_t get(int64_t x)
    {
        if(v.empty()==true) return -inf;
        if(v.size()==1) return v[0].get(x);

        int l = 0, r = to.size() - 1, mid;
        while(l+1<r)
        {
            mid = (l+r)/2;

            if(to[mid]>=x) r = mid;
            else l = mid + 1;
        }

        if(to[l]>=x) return v[l].get(x);
        if(to[r]>=x) return v[r].get(x);
        return v[to.size()].get(x);
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

        cht.add(Line(-(i+1), -pHat + (i+1)*p));
    }

    cout << ans << '\n';
}
