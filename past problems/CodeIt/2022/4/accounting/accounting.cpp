#include <iostream>

using namespace std;

const int MAXN = 1e5;

int n;
int a[MAXN+5];

struct SegmentTreeNode
{
    int64_t arrVal, modVal;
    int64_t lazyMult, lazyModVal;

    int l, r;
    SegmentTreeNode *L, *R;

    SegmentTreeNode() : arrVal(0), modVal(0), lazyMult(+1), lazyModVal(0), L(nullptr), R(nullptr) {}
    SegmentTreeNode(int l, int r) : SegmentTreeNode()
    {
        this->l = l;
        this->r = r;
    }

    void build(int *a)
    {
        if(l==r)
        {
            arrVal = a[l];
            return;
        }

        L = new SegmentTreeNode(l, (l+r)/2);
        R = new SegmentTreeNode((l+r)/2+1, r);

        L->build(a);
        R->build(a);
        recalc();
    }

    void updateLazy()
    {
        modVal = modVal*lazyMult + (r-l+1)*lazyModVal;
        arrVal = arrVal*lazyMult;

        if(l!=r)
        {
            L->lazyMult *= lazyMult;
            R->lazyMult *= lazyMult;

            L->lazyModVal += lazyModVal;
            R->lazyModVal += lazyModVal;
        }

        lazyModVal = 0;
        lazyMult = 1;
    }

    void recalc()
    {
        arrVal = L->arrVal + R->arrVal;
        modVal = L->modVal + R->modVal;
    }

    void update(int ql, int qr, int64_t change)
    {
        updateLazy();

        if(ql<=l && r<=qr)
        {
            lazyMult = -1;
            lazyModVal = change;

            updateLazy();
            return;
        }
        if(r<ql || l>qr) return;

        L->update(ql, qr, change);
        R->update(ql, qr, change);
        recalc();
    }

    int64_t query(int ql, int qr)
    {
        updateLazy();

        if(ql<=l && r<=qr) return modVal + arrVal;
        if(r<ql || l>qr) return 0;

        return L->query(ql, qr) + R->query(ql, qr);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> n >> Q;
    for(int i = 0;i<n;i++) cin >> a[i];

    SegmentTreeNode *T = new SegmentTreeNode(0, n-1);
    T->build(a);

    while(Q--)
    {
        char type;
        cin >> type;

        if(type=='-')
        {
            int l, r, x;
            cin >> l >> r >> x;

            T->update(l-1, r-1, x);
        }
        else
        {
            int l, r;
            cin >> l >> r;

            cout << T->query(l-1, r-1) << '\n';
        }
    }
}
