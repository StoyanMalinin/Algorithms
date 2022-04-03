#include <iostream>
#include <vector>
#include <stack>
#include <list>

using namespace std;

const int MAXN = 2e6;

struct SegmentTree
{
    int left, right, sum;
    SegmentTree *L, *R;

    SegmentTree()
        :sum(0), L(nullptr), R(nullptr){}

    SegmentTree(int left, int right):SegmentTree()
    {
        this->left = left;
        this->right = right;
    }

    void reCalc()
    {
        sum = L->sum + R->sum;
    }

    void build()
    {
        if (left == right)
        {
            return;
        }

        L = new SegmentTree(left, (left+right)/2);
        R = new SegmentTree((left+right)/2 + 1, right);

        L->build();
        R->build();
        reCalc();
    }

    int query(int queryL, int queryR)
    {
        if (queryL > right || queryR < left)
            return 0;

        if (queryL <= left && right <= queryR)
            return sum;

        return L->query(queryL, queryR) + R->query(queryL, queryR);
    }

    void update(int q, int change)
    {
        if(left==right && left==q)
        {
            sum += change;
            return;
        }
        if(q<left || q>right)
            return;

        L->update(q, change);
        R->update(q, change);
        reCalc();
    }
};

int n;
int a[MAXN+5];

int leftLarger[MAXN+5], rightLarger[MAXN+5]; //the first occurrence of a larger number
void init()
{
    stack <int> st;
    for(int i = n-1;i>=0;i--)
    {
        while(st.empty()==false && a[i]>=a[st.top()]) st.pop();

        if(st.empty()==false) rightLarger[i] = st.top();
        else rightLarger[i] = n;

        st.push(i);
    }

    while(st.empty()==false) st.pop();
    for(int i = 0;i<n;i++)
    {
        while(st.empty()==false && a[i]>=a[st.top()]) st.pop();

        if(st.empty()==false) leftLarger[i] = st.top();
        else leftLarger[i] = -1;

        st.push(i);
    }
}

list <int> lBorderOfIndex[MAXN+5];
int64_t eval3()
{
    int64_t ans = 0;

    for(int i = 0;i<n;i++)
        lBorderOfIndex[leftLarger[i]+1].push_back(i);

    SegmentTree *T = new SegmentTree(0, n-1);
    T->build();

    for(int i = 0;i<n;i++)
    {
        if(i-1>=0) T->update(i-1, -1);
        for(int ind: lBorderOfIndex[i])
            T->update(ind, +1);

        ans += T->query(i, rightLarger[i]-1);
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];
    init();

    int64_t ans = 0;
    for(int i = 0;i<n;i++) ans += rightLarger[i] - i;//1
    for(int i = 0;i<n;i++) ans += i - leftLarger[i];//2s
    ans -= eval3();//3

    cout << ans - n << '\n';
}
