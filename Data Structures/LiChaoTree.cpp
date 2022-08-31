#include <iostream>

using namespace std;

const int64_t inf = 1e18;

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

        Line lower, upper;
        if(stateMid==true) {lower = newLine; upper = line;}
        else {lower = line;upper = newLine;}

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

    int64_t query(int64_t x) const
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

int main()
{

}
