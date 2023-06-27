#include <iostream>
#include <random>

#include "sumquery.h"
#ifdef __LOCAL__
    #include "Lgrader.cpp"
#endif // __LOCAL__

using namespace std;

const int64_t mod = 1e9 + 7;

mt19937 rnd(22);

struct TreapNode
{
    int sz;
    int64_t x;
    int64_t sum, indexSum;

    int priority;
    TreapNode *L, *R;

    TreapNode(int64_t x)
    {
        this->x = x;
        this->sz = 1;
        this->sum = this->x % mod;
        this->indexSum = (1 * this->x) % mod;

        this->priority = rnd();
        this->L = this->R = nullptr;
    }

    void recalc()
    {
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
        sum %= mod;

        if (L != nullptr)
        {
            indexSum = L->indexSum;
            indexSum += (L->sz + 1) * (x % mod);
            if (R != nullptr)
            {
                indexSum += R->indexSum + R->sum * (L->sz + 1);
            }
        }
        else
        {
            indexSum = (1 * x) % mod;
            if (R != nullptr)
            {
                indexSum += R->indexSum + R->sum * (0 + 1);
            }
        }
        indexSum %= mod;
    }
};

TreapNode *Merge(TreapNode *small, TreapNode *big)
{
    if (small == nullptr) return big;
    if (big == nullptr) return small;

    if (small->priority > big->priority)
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

pair<TreapNode*, TreapNode*> Split(TreapNode *T, int64_t k)
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

void addElement(TreapNode *&T, int64_t x)
{
    auto splitRes = Split(T, x);

    T = Merge(splitRes.first, new TreapNode(x));
    T = Merge(T, splitRes.second);
}

void removeElement(TreapNode *&T, int64_t x)
{
    auto splitRes1 = Split(T, x);
    auto splitRes2 = Split(splitRes1.first, x - 1);

    T = Merge(splitRes2.first, splitRes1.second);
}

TreapNode *T = nullptr;

void init(int q)
{

}

void add_number(long long x)
{
    addElement(T, x);
}

void remove_number(long long x)
{
    removeElement(T, x);
}

int sum_query(int l, int r)
{
    auto splitRes1 = SplitSz(T, r + 1);
    auto splitRes2 = SplitSz(splitRes1.first, l);

    int64_t indexSum = splitRes2.second->indexSum;

    T = Merge(splitRes2.first, splitRes2.second);
    T = Merge(T, splitRes1.second);

    return indexSum;
}
/*
7
1 4
1 2
1 3
3 0 1
3 1 2
2 3
3 1 1
*/
