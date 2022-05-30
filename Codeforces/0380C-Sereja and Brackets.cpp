#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct QueryState
{
    int CorrectSequences, UnusedBracketsLeft, UnusedBracketsRight;
    QueryState(){}
    QueryState(int CorrectSequences, int UnusedBracketsLeft, int UnusedBracketsRight)
    {
        this->CorrectSequences = CorrectSequences;
        this->UnusedBracketsLeft = UnusedBracketsLeft;
        this->UnusedBracketsRight = UnusedBracketsRight;
    }
};

class SegmentTree
{
public:
    SegmentTree()
        :m_UnusedLeftBrackets(0), m_UnusedRightBrackets(0), m_CorrectSequences(0){}

    SegmentTree(int leftBorder, int rightBorder):SegmentTree()
    {
        m_LeftBorder = leftBorder;
        m_RightBorder = rightBorder;
    }

    void Build(const string& brackets)
    {
        if (m_LeftBorder == m_RightBorder)
        {
            if (brackets[m_LeftBorder] == '(')
                m_UnusedLeftBrackets++;

            else if (brackets[m_LeftBorder] == ')')
                m_UnusedRightBrackets++;

            return;
        }

        m_LeftTree = new SegmentTree(m_LeftBorder, (m_LeftBorder + m_RightBorder)/2);
        m_RightTree = new SegmentTree((m_LeftBorder + m_RightBorder)/2 + 1, m_RightBorder);

        m_LeftTree->Build(brackets);
        m_RightTree->Build(brackets);


        this->Recalculate();

        /*cout << m_LeftBorder+1 << " " << m_RightBorder+1 << endl;
        cout << m_UnusedLeftBrackets << " " << m_UnusedRightBrackets << " " << m_CorrectSequences << endl << endl;*/
    }

    QueryState Query(int queryLeft, int queryRight) const
    {
        if (m_RightBorder < queryLeft || queryRight < m_LeftBorder)
            return QueryState(0, 0, 0);

        if (queryLeft <= m_LeftBorder && m_RightBorder <= queryRight)
            return QueryState(m_CorrectSequences, m_UnusedLeftBrackets, m_UnusedRightBrackets);

        QueryState l = m_LeftTree->Query(queryLeft, queryRight);
        QueryState r = m_RightTree->Query(queryLeft, queryRight);

        QueryState newQueryState;
        newQueryState.CorrectSequences = l.CorrectSequences + r.CorrectSequences + min(l.UnusedBracketsLeft, r.UnusedBracketsRight);
        newQueryState.UnusedBracketsLeft = l.UnusedBracketsLeft + r.UnusedBracketsLeft - min(l.UnusedBracketsLeft, r.UnusedBracketsRight);
        newQueryState.UnusedBracketsRight = l.UnusedBracketsRight + r.UnusedBracketsRight - min(l.UnusedBracketsLeft, r.UnusedBracketsRight);

        return newQueryState;

    }

private:
    int32_t m_LeftBorder, m_RightBorder;
    int32_t m_UnusedLeftBrackets, m_UnusedRightBrackets, m_CorrectSequences;

    SegmentTree *m_LeftTree, *m_RightTree;

    void Recalculate()
    {
        int32_t newSequences = min(m_LeftTree->m_UnusedLeftBrackets,
                                   m_RightTree->m_UnusedRightBrackets);

        this->m_UnusedLeftBrackets = m_LeftTree->m_UnusedLeftBrackets +
        m_RightTree->m_UnusedLeftBrackets - newSequences;

        this->m_UnusedRightBrackets = m_LeftTree->m_UnusedRightBrackets +
        m_RightTree->m_UnusedRightBrackets - newSequences;

        this->m_CorrectSequences = m_LeftTree->m_CorrectSequences
         + m_RightTree->m_CorrectSequences + newSequences;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string input;
    cin >> input;

    int n = input.size();

    SegmentTree *T = new SegmentTree(0, n-1);
    T->Build(input);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        int l, r, cntL = 0, cntR = 0;
        cin >> l >> r;

        cout << 2*(T->Query(l-1, r-1).CorrectSequences) << endl;
    }

    return 0;
}


