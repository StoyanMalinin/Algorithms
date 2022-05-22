#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int inf = 1e9;
const int MAXN = 3e5 + 50;
int n, a[MAXN];

class SegmentTree
{
private:
    int m_leftIndex, m_rightIndex, m_gcd, m_min;
    SegmentTree *m_LeftTree, *m_RightTree;

public:
    SegmentTree()
        :m_min(inf), m_gcd(0), m_LeftTree(nullptr), m_RightTree(nullptr){}

    SegmentTree(int leftIndex, int rightIndex):SegmentTree()
    {
        m_leftIndex = leftIndex;
        m_rightIndex = rightIndex;
    }

    void recalc()
    {
        m_gcd = __gcd(m_LeftTree->m_gcd, m_RightTree->m_gcd);
        m_min = min(m_LeftTree->m_min, m_RightTree->m_min);
    }

    void build(int* arr)
    {
        if (m_leftIndex == m_rightIndex)
        {
            m_gcd = arr[m_leftIndex];
            m_min = arr[m_leftIndex];
            return;
        }

        m_LeftTree = new SegmentTree(m_leftIndex, (m_leftIndex + m_rightIndex)/2);
        m_RightTree = new SegmentTree((m_leftIndex + m_rightIndex)/2 + 1, m_rightIndex);

        m_LeftTree->build(arr);
        m_RightTree->build(arr);

        recalc();
    }

    pair <int, int> query(int queryLeft, int queryRight)
    {
        if (m_rightIndex < queryLeft || queryRight < m_leftIndex)
            return {0, inf};

        if (queryLeft <= m_leftIndex && m_rightIndex <= queryRight)
            return {m_gcd, m_min};

        pair <int, int> newQuery;

        newQuery.first =  __gcd(m_LeftTree->query(queryLeft, queryRight).first, m_RightTree->query(queryLeft, queryRight).first);
        newQuery.second = min(m_LeftTree->query(queryLeft, queryRight).second, m_RightTree->query(queryLeft, queryRight).second);

        return newQuery;

    }

};

bool check(int length, SegmentTree* T)
{
    for (int i = 1; i <= n-length + 1; i++)
    {
        pair <int, int> segment = T->query(i, i+length-1);
        if (segment.first == segment.second)
            return true;
    }

    return false;

}

vector <int> answer;
void recover(int length, SegmentTree* T)
{
    for (int i = 1; i <= n - length + 1; i++)
    {
        pair <int, int> segment = T->query(i, i+length-1);
        if (segment.first == segment.second)
            answer.push_back(i);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    SegmentTree* T = new SegmentTree(1, n);
    T->build(a);

    int left = 1, right = n;

    while (right - left > 1)
    {
        int mid = (right+left)/2;
        if (check(mid, T) == true)
            left = mid;
        else right = mid-1;
    }

    int length;
    if (check(right, T) == true)
    {
        recover(right, T);
        length = right;
    }

    else
    {
        recover(left, T);
        length = left;
    }


    int sz = answer.size();
    cout << sz << " " << length-1 << endl;

    if (sz == 0)
        return 0;

    cout << answer[0];
    for (int i = 1; i < sz; i++)
        cout << " " << answer[i];
    cout << endl;

    return 0;
}
