#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

class SegmentTreeNode
{

private:
    bool operation;
    int left, right;
    int64_t result;
    SegmentTreeNode *Left, *Right;

    void reCalculate()
    {
        if (operation == 0)
            result = Left->result|Right->result;
        else
            result = Left->result^Right->result;
    }

public:
    SegmentTreeNode()
        :result(0), Left(nullptr), Right(nullptr){}

    SegmentTreeNode(int left, int right, bool operation):SegmentTreeNode()
    {
        this->left = left;
        this->right = right;
        this->operation = operation;
    }

    void build(const int* a)
    {
        if (left == right)
        {
            result = a[left];
            return;
        }

        Left = new SegmentTreeNode(left, (left+right)/2, operation^1);
        Right = new SegmentTreeNode((left+right)/2+1, right, operation^1);

        Left->build(a);
        Right->build(a);

        reCalculate();
    }

    void updateData(int q, int newValue)
    {

        if (!(left <= q && q <= right))
            return;

        if (left == right)
        {
            result = newValue;
            return;
        }


        Left->updateData(q, newValue);
        Right->updateData(q, newValue);

        reCalculate();
    }

    int64_t getResult()
    {
        return result;
    }
};

constexpr int MAXN = (1<<17) + 5;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, Q;
    cin >> n >> Q;

    int a[MAXN];

    for (int i = 0; i < (1<<n); i++)
        cin >> a[i];

    bool operation = n&1?0:1;
    SegmentTreeNode *T = new SegmentTreeNode(0, (1<<n)-1, operation);
    T->build(a);

    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;

        T->updateData(x-1, y);
        cout << T->getResult() << endl;
    }

    return 0;
}
