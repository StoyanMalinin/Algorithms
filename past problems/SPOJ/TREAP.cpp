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
    int minDiff;
    int front, back;

    int priority;
    TreapNode *L, *R;

    TreapNode(int x)
    {
        this->x = x;
        this->sz = 1;

        this->minDiff = inf;
        this->front = this->back = x;

        this->priority = rnd();
        this->L = this->R = nullptr;
    }

    void recalc()
    {
        sz = 1;
        front = back = x;
        if (L != nullptr)
        {
            sz += L->sz;
            front = L->front;
        }
        if (R != nullptr)
        {
            sz += R->sz;
            back = R->back;
        }

        minDiff = inf;
        if (L != nullptr)
        {
            minDiff = min(minDiff, L->minDiff);
            minDiff = min(minDiff, x - L->back);
        }
        if (R != nullptr)
        {
            minDiff = min(minDiff, R->minDiff);
            minDiff = min(minDiff, R->front - x);
        }
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

pair<TreapNode*, TreapNode*> Split(TreapNode *T, int k)
{
    if(T == nullptr)
    {
        return {nullptr, nullptr};
    }

    if(T->x <= k)
    {
        auto splitResult = Split(T->R, k);

        T->R = splitResult.first;
        T->recalc();

        return {T, splitResult.second};
    }
    else
    {
        auto splitResult = Split(T->L, k);

        T->L = splitResult.second;
        T->recalc();

        return {splitResult.first, T};
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

void addElement(TreapNode *&T, int x)
{
    auto splitRes = Split(T, x);

    T = Merge(splitRes.first, new TreapNode(x));
    T = Merge(T, splitRes.second);
}

void removeElement(TreapNode *&T, int x)
{
    auto splitRes1 = Split(T, x);
    auto splitRes2 = Split(splitRes1.first, x - 1);

    T = Merge(splitRes2.first, splitRes1.second);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> s;
    TreapNode *T = nullptr;

    int Q;
    cin >> Q;

    while (Q--)
    {
        char type;
        cin >> type;

        if (type == 'I')
        {
            int x;
            cin >> x;

            if (!s.count(x))
            {
                addElement(T, x);
                s.insert(x);
            }
        }
        else if (type == 'D')
        {
            int x;
            cin >> x;

            if (s.count(x))
            {
                removeElement(T, x);
                s.erase(x);
            }
        }
        else if (type == 'N')
        {
            int l, r;
            cin >> l >> r;

            if (l >= r)
            {
                cout << "-1" << '\n';
            }
            else
            {
                auto splitRes1 = SplitSz(T, r + 1);
                auto splitRes2 = SplitSz(splitRes1.first, l);

                cout << splitRes2.second->minDiff << '\n';

                T = Merge(splitRes2.first, splitRes2.second);
                T = Merge(T, splitRes1.second);
            }
        }
        else
        {
            int l, r;
            cin >> l >> r;

            if (l >= r)
            {
                cout << "-1" << '\n';
            }
            else
            {
                auto splitRes1 = SplitSz(T, r + 1);
                auto splitRes2 = SplitSz(splitRes1.first, l);

                cout << splitRes2.second->back - splitRes2.second->front << '\n';

                T = Merge(splitRes2.first, splitRes2.second);
                T = Merge(T, splitRes1.second);
            }
        }
    }
}
