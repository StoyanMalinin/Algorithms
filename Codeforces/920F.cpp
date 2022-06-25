#include <iostream>

using namespace std;

const int MAXN = 3e5;
const int MAXA = 1e6;

int n;
int a[MAXN+5];
int D[MAXA+5];

bool checkIsWorthUpdating(int x)
{
    return (D[x]!=x);
}

struct SegmentTree
{
    int64_t sum;
    bool isWorthUpdating;

    int l, r;
    SegmentTree *L, *R;

    SegmentTree() : sum(0), isWorthUpdating(false), L(nullptr), R(nullptr) {}
    SegmentTree(int l, int r) : SegmentTree()
    {
        this->l = l;
        this->r = r;
    }

    void recalc()
    {
        sum = L->sum + R->sum;
        isWorthUpdating = L->isWorthUpdating | R->isWorthUpdating;
    }

    void build(int *a)
    {
        if(l==r)
        {
            sum = a[l];
            isWorthUpdating = checkIsWorthUpdating(a[l]);

            return;
        }

        L = new SegmentTree(l, (l+r)/2);
        R = new SegmentTree((l+r)/2+1, r);

        L->build(a);
        R->build(a);
        recalc();
    }

    void update(int ql, int qr)
    {
        if(isWorthUpdating==false)
            return;
        if(r<ql || qr<l)
            return;
        if(l==r)
        {
            sum = D[sum];
            isWorthUpdating = checkIsWorthUpdating(sum);

            return;
        }

        L->update(ql, qr);
        R->update(ql, qr);
        recalc();
    }

    int64_t query(int ql, int qr)
    {
        if(ql<=l && r<=qr) return sum;
        if(r<ql || qr<l) return 0;

        return L->query(ql, qr) + R->query(ql, qr);
    }
};

SegmentTree *T;

void init()
{
    for(int d = 1;d<=MAXA;d++)
        for(int x = d;x<=MAXA;x+=d)
            D[x]++;

    T = new SegmentTree(0, n-1);
    T->build(a);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> n >> Q;
    for(int i = 0;i<n;i++) cin >> a[i];

    init();

    while(Q--)
    {
        int type, l, r;
        cin >> type >> l >> r;
        l--;r--;

        if(type==1) T->update(l, r);
        else cout << T->query(l, r) << '\n';
    }
}
