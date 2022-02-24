//Gives Time Limit exceeded
//for now...

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int MAXN = 2e5;

struct SegmentTreeNode
{
    int sum;
    int l, r;

    SegmentTreeNode *L, *R;

    SegmentTreeNode() : sum(0), L(nullptr), R(nullptr) {}
    SegmentTreeNode(int l, int r) : SegmentTreeNode()
    {
        this->l = l;
        this->r = r;
    }

    void recalc()
    {
        sum = L->sum + R->sum;
    }

    void build();
    int query(int ql, int qr);
    void update(int q, int change);
};

void SegmentTreeNode::build()
{
        if(l==r) return;

        L = new SegmentTreeNode(l, (l+r)/2);
        R = new SegmentTreeNode((l+r)/2+1, r);

        L->build();
        R->build();
        recalc();
}

int SegmentTreeNode::query(int ql, int qr)
{
    if(ql<=l && r<=qr) return sum;
    if(r<ql || l>qr) return 0;

    return L->query(ql, qr) + R->query(ql, qr);
}

void SegmentTreeNode::update(int q, int change)
{
    if(l==r && q==l)
    {
        sum += change;
        return;
    }
    if(r<q || l>q)
        return;

    L->update(q, change);
    R->update(q, change);
    recalc();
}

struct Query
{
    bool type;

    //false
    int k, x;

    //true
    int a, b;
};

Query makeUpdate(int k, int x)
{
    Query q;

    q.type = false;
    q.k = k - 1;q.x = x;

    return q;
}

Query makeQuestion(int a, int b)
{
    Query q;

    q.type = true;
    q.a = a;q.b = b;

    return q;
}

int n, Q;

set <int> allSalaries;
map <int, int> salary2Id;

void init(SegmentTreeNode *&T, int p[], Query queries[])
{
    for(int i = 0;i<n;i++)
        allSalaries.insert(p[i]);
    for(int q = 0;q<Q;q++)
    {
        if(queries[q].type==false)
            allSalaries.insert(queries[q].x);
    }

    int id = 0;
    for(int x: allSalaries)
    {
        salary2Id[x] = id;
        id++;
    }

    T = new SegmentTreeNode(0, salary2Id.size()-1);
    T->build();

    for(int i = 0;i<n;i++)
        T->update(salary2Id[p[i]], +1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p[MAXN+5];
    Query queries[MAXN+5];

    SegmentTreeNode *T;

    cin >> n >> Q;
    for(int i = 0;i<n;i++) cin >> p[i];

    for(int q = 0;q<Q;q++)
    {
        char type;
        cin >> type;

        if(type=='!')
        {
            int k, x;
            cin >> k >> x;

            queries[q] = makeUpdate(k, x);
        }
        else
        {
            int a, b;
            cin >> a >> b;

            queries[q] = makeQuestion(a, b);
        }
    }

    init(T, p, queries);
    for(int i = 0;i<Q;i++)
    {
        Query q = queries[i];

        if(q.type==false)
        {
            T->update(salary2Id[p[q.k]], -1);
            p[q.k] = q.x;
            T->update(salary2Id[p[q.k]], +1);
        }
        else
        {
            auto lIt = allSalaries.lower_bound(q.a);
            if(lIt==allSalaries.end())
            {
                cout << "0" << '\n';
                continue;
            }

            auto rIt = allSalaries.upper_bound(q.b);
            if(rIt==allSalaries.begin())
            {
                cout << "0" << '\n';
                continue;
            }
            rIt--;

            int lId = salary2Id[*lIt], rId = salary2Id[*rIt];
            if(lId<=rId) cout << T->query(lId, rId) << '\n';
            else cout << "0" << '\n';
        }
    }
}
