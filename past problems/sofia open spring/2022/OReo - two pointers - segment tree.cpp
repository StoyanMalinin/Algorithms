#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct SegmentTree
{
    int left, right, OR;
    SegmentTree *L, *R;

    SegmentTree()
        :OR(0), L(nullptr), R(nullptr){}

    SegmentTree(int left, int right):SegmentTree()
    {
        this->left = left;
        this->right = right;
    }

    void reCalc()
    {
        OR = L->OR|R->OR;
    }

    void build(int* arr)
    {
        if (left == right)
        {
            OR = arr[left];
            return;
        }

        L = new SegmentTree(left, (left+right)/2);
        R = new SegmentTree((left+right)/2 + 1, right);

        L->build(arr);
        R->build(arr);

        reCalc();
    }

    int query(int queryL, int queryR)
    {
        if (queryL > right || queryR < left)
            return 0;

        if (queryL <= left && right <= queryR)
            return OR;

        return L->query(queryL, queryR)|R->query(queryL, queryR);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, k;
    int a[100500];
    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    SegmentTree* T = new SegmentTree(0, n-1);
    T->build(a);

    int64_t ans = 0;

    int rPtr = -1;
    for (int i = 0; i < n; i++)
    {
        if(rPtr<i) rPtr = i;
        while(rPtr<n && T->query(i, rPtr)<k) rPtr++;

        if(rPtr<n && T->query(i, rPtr)>=k)
            ans += n - rPtr;
    }

    cout << ans << endl;


    return 0;
}
