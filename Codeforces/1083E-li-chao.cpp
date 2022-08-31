#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e6 + 5;
const int64_t inf = 1e18;
const int64_t MAXX = 1e9;

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

    LiChaoTree(int64_t l, int64_t r) : line(0, -inf), l(l), r(r), L(nullptr), R(nullptr) {}
    LiChaoTree(int64_t l, int64_t r, const Line& line) : line(line), l(l), r(r), L(nullptr), R(nullptr) {}

    void update(const Line &newLine)
    {
        int64_t mid = (l+r)/2;

        bool stateL = newLine.get(l) < line.get(l);
        bool stateMid = newLine.get(mid) < line.get(mid);

        Line lower = line;
        Line upper = newLine;
        if(stateMid==true)
        {
            lower = newLine;
            upper = line;
        }

        line = upper;
        if(stateL!=stateMid)
        {
            if(L==nullptr) L = new LiChaoTree(l, mid, lower);
            else L->update(lower);
        }
        else
        {
            if(R==nullptr) R = new LiChaoTree(mid+1, r, lower);
            else R->update(lower);
        }
    }

    int64_t query(int64_t x)
    {
        if(x<=(l+r)/2)
        {
            if(L==nullptr) return line.get(x);
            else return max(line.get(x), L->query(x));
        }
        else
        {
            if(R==nullptr) return line.get(x);
            else return max(line.get(x), R->query(x));
        }
    }

    ~LiChaoTree()
    {
        if(L!=nullptr) delete L;
        if(R!=nullptr) delete R;
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

    LiChaoTree *lct = new LiChaoTree(-MAXX, 0);

    dp[0] = rectangles[0].x*rectangles[0].y - rectangles[0].a;
    lct->update(Line(rectangles[0].x, dp[0]));

    for(int i = 1;i<n;i++)
    {
        int64_t currVal = rectangles[i].x*rectangles[i].y - rectangles[i].a;
        dp[i] = max(currVal, lct->query(-rectangles[i].y) + currVal);

        lct->update(Line(rectangles[i].x, dp[i]));
    }

    delete lct;

    int64_t ans = 0;
    for(int i = 0;i<n;i++) ans = max(ans, dp[i]);

    cout << ans << '\n';
}

