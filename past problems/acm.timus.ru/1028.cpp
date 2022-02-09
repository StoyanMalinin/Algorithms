#include <iostream>

using namespace std;

const int MAXN = 2e4 + 5;

struct SegmentTree
{
    int sum;
    int l, r;

    SegmentTree *L, *R;

    SegmentTree() : sum(0), L(nullptr), R(nullptr) {}
    SegmentTree(int l, int r) : SegmentTree()
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

        L = new SegmentTree(l, (l+r)/2);
        R = new SegmentTree((l+r)/2+1, r);

        L->build();
        R->build();
        recalc();
    }

    void update(int q, int change)
    {
        if(l==r && l==q)
        {
            sum += change;
            return;
        }
        if(r<q || l>q) return;

        L->update(q, change);
        R->update(q, change);
        recalc();
    }

    int query(int ql, int qr)
    {
        if(l>=ql && r<=qr) return sum;
        if(r<ql || l>qr) return 0;

        return L->query(ql, qr) + R->query(ql, qr);
    }
};

int levelCnt[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    SegmentTree *T = new SegmentTree(0, 32*1000);
    T->build();

    int n;
    cin >> n;

    for(int i = 0;i<n;i++)
    {
        int x, y;
        cin >> x >> y;

        int level = T->query(0, x);
        levelCnt[level]++;

        T->update(x, +1);
    }

    for(int i = 0;i<n;i++)
        cout << levelCnt[i] << '\n';
}
