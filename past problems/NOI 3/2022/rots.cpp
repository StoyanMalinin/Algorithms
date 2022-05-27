#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LEN = 6;
const int MAXN = 1e6;

struct DigitTable
{
    int a[MAX_LEN+2][MAX_LEN+2];

    DigitTable()
    {
        memset(this->a, 0, sizeof(this->a));
    }

    void addNum(const string& s)
    {
        for(int i = 0;i<s.size();i++)
            a[s.size()][i] += s[s.size()-1-i] - '0';
    }

    void rot(int64_t rotations)
    {
        int tmp[MAX_LEN+2];
        for(int len = 1;len<=MAX_LEN;len++)
        {
            for(int i = 0;i<len;i++) tmp[i] = a[len][(i+rotations)%len];
            for(int i = 0;i<len;i++) a[len][i] = tmp[i];
        }
    }

    int64_t eval() const
    {
        int64_t ans = 0;
        for(int len = 1;len<=MAX_LEN;len++)
        {
            int64_t coef = 1;
            for(int i = 0;i<len;i++)
            {
                ans += coef*a[len][i];
                coef *= 10;
            }
        }

        return ans;
    }
};

DigitTable operator +(const DigitTable& lhs, const DigitTable &rhs)
{
    DigitTable res;
    for(int len = 1;len<=MAX_LEN;len++)
        for(int i = 0;i<len;i++)
            res.a[len][i] = lhs.a[len][i] + rhs.a[len][i];

    return res;
}

struct SegmentTreeNode
{
    int64_t lazy;
    DigitTable dt;

    int l, r;
    SegmentTreeNode *L, *R;

    SegmentTreeNode() : L(nullptr), R(nullptr), lazy(0) {}
    SegmentTreeNode(int l, int r) : SegmentTreeNode()
    {
        this->l = l;
        this->r = r;
    }

    void build(const string *a)
    {
        if(l==r)
        {
            dt.addNum(a[l]);
            return;
        }

        L = new SegmentTreeNode(l, (l+r)/2);
        R = new SegmentTreeNode((l+r)/2+1, r);

        L->build(a);
        R->build(a);
        dt = L->dt + R->dt;
    }

    void updateLazy()
    {
        dt.rot(lazy);
        if(l!=r)
        {
            L->lazy += lazy;
            R->lazy += lazy;
        }

        lazy = 0;
    }

    void update(int ql, int qr, int64_t rot)
    {
        updateLazy();

        if(ql<=l && r<=qr)
        {
            lazy += rot;
            updateLazy();

            return;
        }
        if(r<ql || qr<l)
            return;

        L->update(ql, qr, rot);
        R->update(ql, qr, rot);
        dt = L->dt + R->dt;
    }

    int64_t query(int ql, int qr)
    {
        updateLazy();

        if(ql<=l && r<=qr) return dt.eval();
        if(r<ql || qr<l) return 0;

        return L->query(ql, qr) + R->query(ql, qr);
    }
};

int n, Q;
string a[MAXN+5];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> Q;
    for(int i = 0;i<n;i++) cin >> a[i];

    SegmentTreeNode *T = new SegmentTreeNode(0, n-1);
    T->build(a);

    while(Q--)
    {
        int type, ql, qr;
        cin >> type >> ql >> qr;
        ql--;qr--;

        if(type==1) T->update(ql, qr, 1);
        else cout << T->query(ql, qr) << '\n';
    }
}
