#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 2e5 + 5;

template <int treeSz>
struct SegmentTree
{
    int n;
    int tree[treeSz], lazy[treeSz];

    SegmentTree()
    {
        memset(tree, 0, sizeof(tree));
    }
    SegmentTree(int n) : SegmentTree()
    {
        this->n = n;
    }

    void recalc(int node)
    {
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    void buildInternal(int node, int l, int r)
    {
        if(l==r)
        {
            tree[node] = 0;
            return;
        }

        buildInternal(node*2, l, (l+r)/2);
        buildInternal(node*2+1, (l+r)/2+1, r);

        recalc(node);
    }

    void build()
    {
        buildInternal(1, 0, n-1);
    }

    int queryInternal(int node, int l, int r, int ql, int qr)
    {
        if(l>=ql && r<=qr) return tree[node];
        if(r<ql || l>qr) return 0;

        return queryInternal(node*2, l, (l+r)/2, ql, qr) + queryInternal(node*2+1, (l+r)/2+1, r, ql, qr);
    }

    int query(int ql, int qr)
    {
        return queryInternal(1, 0, n-1, ql, qr);
    }

    void updateInternal(int node, int l, int r, int q, int change)
    {
        if(l==r && l==q)
        {
            tree[node] += change;
            return;
        }
        if(r<q || l>q) return;

        updateInternal(node*2, l, (l+r)/2, q, change);
        updateInternal(node*2+1, (l+r)/2+1, r, q, change);

        recalc(node);
    }

    void update(int q, int change)
    {
        updateInternal(1, 0, n-1, q, change);
    }
};

int main()
{

}
