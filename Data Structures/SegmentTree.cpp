#include <iostream>

using namespace std;

struct SegmentTreeNode
{
    int l, r;
    int64_t sum, lazy;

    SegmentTreeNode *L, *R;

    SegmentTreeNode() : sum(0), lazy(0), L(nullptr), R(nullptr) {}
    SegmentTreeNode(int l, int r) : SegmentTreeNode()
    {
        this->l = l;
        this->r = r;
    }

    void recalc()
    {
        sum = L->sum + R->sum;
    }

    void build()
    {
        if(l==r) return;

        L = new SegmentTreeNode(l, (l+r)/2);
        R = new SegmentTreeNode((l+r)/2+1, r);

        L->build();
        R->build();
        recalc();
    }

    void updateLazy()
    {
        sum += (r-l+1)*lazy;
        if(l!=r)
        {
            L->lazy += lazy;
            R->lazy += lazy;
        }

        lazy = 0;
    }

    int64_t query(int ql, int qr)
    {
        updateLazy();
        if(ql<=l && r<=qr) return sum;
        if(r<ql || l>qr) return 0;

        return L->query(ql, qr) + R->query(ql, qr);
    }

    void update(int ql, int qr, int64_t change)
    {
        updateLazy();
        if(ql<=l && r<=qr)
        {
            sum += (r-l+1)*change;
            if(l!=r)
            {
                L->lazy += change;
                R->lazy += change;
            }

            return;
        }
        if(r<ql || l>qr)
            return;

        L->update(ql, qr, change);
        R->update(ql, qr, change);
        recalc();
    }
};

int main()
{

}
