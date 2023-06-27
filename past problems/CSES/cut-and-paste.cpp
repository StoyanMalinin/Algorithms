#include <iostream>
#include <random>
#include <set>

using namespace std;

mt19937 rnd(22);
const int inf = 1e9 + 5;

struct TreapNode
{
    int sz;
    char x;

    int priority;
    TreapNode *L, *R;

    TreapNode(char x)
    {
        this->x = x;
        this->sz = 1;

        this->priority = rnd();
        this->L = this->R = nullptr;
    }

    void recalc()
    {
        sz = 1;
        if (L != nullptr)
        {
            sz += L->sz;
        }
        if (R != nullptr)
        {
            sz += R->sz;
        }
    }

    void print()
    {
        if (L != nullptr)
        {
            L->print();
        }

        cout << x;

        if (R != nullptr)
        {
            R->print();
        }
    }

    void println()
    {
        print();
        cout << '\n';
    }
};

TreapNode *Merge(TreapNode *small, TreapNode *big)
{
    if(small==nullptr) return big;
    if(big==nullptr) return small;

    if(small->priority > big->priority)
    {
        small->R = Merge(small->R, big);
        small->recalc();

        return small;
    }
    else
    {
        big->L = Merge(small, big->L);
        big->recalc();

        return big;
    }
}

pair<TreapNode*, TreapNode*> SplitSz(TreapNode *T, int sz)
{
    if(T == nullptr)
    {
        return {nullptr, nullptr};
    }

    int leftTreeSz = ((T->L == nullptr) ? 0 : T->L->sz);
    if(leftTreeSz + 1 <= sz)
    {
        auto splitResult = SplitSz(T->R, sz - (leftTreeSz + 1));

        T->R = splitResult.first;
        T->recalc();

        return {T, splitResult.second};
    }
    else
    {
        auto splitResult = SplitSz(T->L, sz);

        T->L = splitResult.second;
        T->recalc();

        return {splitResult.first, T};
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, Q;
    string s;

    cin >> n >> Q;
    cin >> s;

    TreapNode *T = nullptr;
    for (char c : s)
    {
        T = Merge(T, new TreapNode(c));
    }

    while (Q--)
    {
        int l, r;
        cin >> l >> r;

        auto splitRes1 = SplitSz(T, r);
        auto splitRes2 = SplitSz(splitRes1.first, l - 1);

        T = Merge(splitRes2.first, splitRes1.second);
        T = Merge(T, splitRes2.second);
    }

    T->println();
}
