#include <iostream>
#include <random>
#include <set>

using namespace std;

mt19937 rnd(22);
const int inf = 1e9 + 5;

struct TreapNode
{
    int x;
    int sz;
    int64_t sum;
    bool reverse;

    int priority;
    TreapNode *L, *R;

    TreapNode(int x)
    {
        this->x = x;
        this->sz = 1;
        this->sum = x;
        this->reverse = false;

        this->priority = rnd();
        this->L = this->R = nullptr;
    }

    void recalc()
    {
        if (reverse)
        {
            swap(L, R);

            if (L != nullptr)
            {
                L->reverse ^= 1;
            }
            if (R != nullptr)
            {
                R->reverse ^= 1;
            }

            reverse = false;
        }

        sz = 1;
        sum = x;
        if (L != nullptr)
        {
            sz += L->sz;
            sum += L->sum;
        }
        if (R != nullptr)
        {
            sz += R->sz;
            sum += R->sum;
        }
    }
};

TreapNode *Merge(TreapNode *small, TreapNode *big)
{
    if(small == nullptr) return big;
    if(big == nullptr) return small;

    big->recalc();
    small->recalc();

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

    T->recalc();

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
    cin >> n >> Q;

    TreapNode *T = nullptr;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;

        T = Merge(T, new TreapNode(x));
    }

    while (Q--)
    {
        int type, l, r;
        cin >> type >> l >> r;

        if (type == 1)
        {
            auto splitRes1 = SplitSz(T, r);
            auto splitRes2 = SplitSz(splitRes1.first, l - 1);

            splitRes2.second->reverse ^= 1; //reverse

            T = Merge(splitRes2.first, splitRes2.second);
            T = Merge(T, splitRes1.second);
        }
        else
        {
            auto splitRes1 = SplitSz(T, r);
            auto splitRes2 = SplitSz(splitRes1.first, l - 1);

            cout << splitRes2.second->sum << '\n';

            T = Merge(splitRes2.first, splitRes2.second);
            T = Merge(T, splitRes1.second);
        }
    }
}
