#include<iostream>
#include<random>

using namespace std;

mt19937 rnd(69420);

struct Treap
{
    int x;
    int cnt;

    int length;
    int priority;
    Treap *L, *R;

    Treap(){}
    Treap(int x)
    {
        this->x = x;
        this->cnt = 1;
        this->length = 1;

        this->priority = rnd();
        this->L = nullptr;
        this->R = nullptr;
    }

    void recalc()
    {
        this->length = this->cnt;
        if(this->L!=nullptr) this->length += this->L->length;
        if(this->R!=nullptr) this->length += this->R->length;
    }

    int query(int x)
    {
        if(this->x >= x)
        {
            return ((this->L!=nullptr)?this->L->query(x):0) + this->cnt + ((this->R!=nullptr)?this->R->length:0);
        }
        else
        {
            return ((this->R!=nullptr)?this->R->query(x):0);
        }
    }
};

Treap *Merge(Treap *small, Treap *big)
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

pair <Treap*, Treap*> Split(Treap *T, int k)
{
    if(T==nullptr) return {nullptr, nullptr};

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

void addElement(Treap *&T, int x)
{
    auto help = Split(T, x);
    auto help1 = Split(help.first, x-1);

    if(help1.second!=nullptr)
    {
        help1.second->cnt++;
        help1.second->recalc();

        T = Merge(help1.first, help1.second);
        T = Merge(T, help.second);
    }
    else
    {
        T = Merge(help1.first, new Treap(x));
        T = Merge(T, help.second);
    }
}

void removeElement(Treap *&T, int x)
{
    auto help = Split(T, x);
    auto help1 = Split(help.first, x-1);

    if(help1.second->cnt!=1)
    {
        help1.second->cnt--;
        help1.second->recalc();

        T = Merge(help1.first, help1.second);
        T = Merge(T, help.second);
    }
    else
    {
        T = Merge(help1.first, help.second);
    }
}

int main()
{
    Treap *T = nullptr;

    addElement(T, 1);
    addElement(T, 2);
    addElement(T, 3);
    addElement(T, 1);
    addElement(T, 1);
    removeElement(T, 1);

    cout << T->length << '\n';
}

