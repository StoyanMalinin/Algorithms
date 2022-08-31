#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2e5 + 5;
const int64_t MAXA = 1e9;
const int64_t inf = 1e18 + 5;

struct Line
{
    int64_t a, b;

    Line(){}
    Line(int64_t a, int64_t b) : a(a), b(b) {}

    int64_t get(int64_t x) const
    {
        return a*x + b;
    }
};

struct LiChaoTree
{
    Line line;

    int64_t l, r;
    LiChaoTree *L, *R;

    LiChaoTree(int64_t l, int64_t r) : line(0, +inf), l(l), r(r), L(nullptr), R(nullptr) {}
    LiChaoTree(int64_t l, int64_t r, const Line& line) : line(line), l(l), r(r), L(nullptr), R(nullptr) {}

    void update(const Line &newLine)
    {
        int64_t mid = (l+r)/2;

        bool stateL = newLine.get(l) < line.get(l);
        bool stateMid = newLine.get(mid) < line.get(mid);

        Line lower = line;
        Line upper = newLine;
        if(stateMid==true) swap(lower, upper);

        line = lower;
        if(l!=r)
        {
            if(stateL!=stateMid)
            {
                if(L==nullptr) L = new LiChaoTree(l, mid, upper);
                else L->update(upper);
            }
            else
            {
                if(R==nullptr) R = new LiChaoTree(mid+1, r, upper);
                else R->update(upper);
            }
        }
    }

    int64_t query(int64_t x) const
    {
        if(x<=(l+r)/2)
        {
            if(L==nullptr) return line.get(x);
            else return min(line.get(x), L->query(x));
        }
        else
        {
            if(R==nullptr) return line.get(x);
            else return min(line.get(x), R->query(x));
        }
    }

    void print() const
    {
        cout << l << " " << r << " -> " << "(" << line.a << ", " << line.b << ")" << '\n';

        if(L!=nullptr) L->print();
        if(R!=nullptr) R->print();
    }

    ~LiChaoTree()
    {
        if(L!=nullptr) delete L;
        if(R!=nullptr) delete R;
    }
};

int n;
int64_t a[MAXN], b[MAXN];

int64_t dp[MAXN];
LiChaoTree *lct = new LiChaoTree(-MAXA, +MAXA);

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
    lct->update(Line(a[n-1], dp[n-1]));

    for(int i = n-2;i>=0;i--)
    {
        dp[i] = lct->query(b[i]);
        lct->update(Line(a[i], dp[i]));
    }

    delete lct;

    cout << dp[0] << '\n';
}
