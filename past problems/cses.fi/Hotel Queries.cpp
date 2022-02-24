#include <iostream>

using namespace std;

const int MAXN = 2e5;
const int inf = 1e9;

struct SegmentTreeNode
{
    int l, r;
    int maxVal, lazy;

    SegmentTreeNode *L, *R;

    SegmentTreeNode() : maxVal(-inf), lazy(0), L(nullptr), R(nullptr) {}
    SegmentTreeNode(int l, int r) : SegmentTreeNode()
    {
        this->l = l;
        this->r = r;
    }

    void recalc()
    {
        maxVal = max(L->maxVal, R->maxVal);
    }

    void build(int h[])
    {
        if(l==r)
        {
            maxVal = h[l];
            return;
        }

        L = new SegmentTreeNode(l, (l+r)/2);
        R = new SegmentTreeNode((l+r)/2+1, r);

        L->build(h);
        R->build(h);
        recalc();
    }

    void updateLazy()
    {
        maxVal += lazy;
        if(l!=r)
        {
            L->lazy += lazy;
            R->lazy += lazy;
        }

        lazy = 0;
    }

    int query(int ql, int qr)
    {
        updateLazy();
        if(ql<=l && r<=qr) return maxVal;
        if(r<ql || l>qr) return -inf;

        return max(L->query(ql, qr), R->query(ql, qr));
    }

    void update(int ql, int qr, int64_t change)
    {
        updateLazy();
        if(ql<=l && r<=qr)
        {
            maxVal += change;
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

int n;
int h[MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> n >> Q;
    for(int i = 0;i<n;i++) cin >> h[i];

    SegmentTreeNode *T = new SegmentTreeNode(0, n-1);
    T->build(h);

    while(Q--)
    {
        int groupSz;
        cin >> groupSz;

        int l = 0, r = n-1, mid;
        while(l+1<r)
        {
            mid = (l+r)/2;

            if(T->query(0, mid)>=groupSz) r = mid;
            else l = mid + 1;
        }

        int k = -1;
        if(T->query(0, l)>=groupSz) k = l;
        else if(T->query(0, r)>=groupSz) k = r;

        if(k==-1)
            cout << "0" << " ";
        else
        {
            T->update(k, k, -groupSz);
            cout << k + 1 << " ";
        }
    }

    cout << '\n';
}
