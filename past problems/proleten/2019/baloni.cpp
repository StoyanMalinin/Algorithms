#include<iostream>
#include<random>

using namespace std;

const int MAXN = 2e5 + 5;

mt19937 rnd(6942069LL);

struct Treap
{
    int groupSize;
    int groupColor;

    int length;
    int groupsCount;

    int priority;
    Treap *L, *R;

    Treap(){}
    Treap(int groupSize, int groupColor)
    {
        this->groupSize = groupSize;
        this->groupColor = groupColor;

        this->length = this->groupSize;
        this->groupsCount = 1;

        this->priority = rnd();
        this->L = nullptr;
        this->R = nullptr;
    }

    void recalc()
    {
        this->groupsCount = 1;
        this->length = this->groupSize;
        if(this->L!=nullptr)
        {
            this->length += this->L->length;
            this->groupsCount += this->L->groupsCount;
        }
        if(this->R!=nullptr)
        {
            this->length += this->R->length;
            this->groupsCount += this->R->groupsCount;
        }
    }

    int groupIndex()
    {
        if(this->L!=nullptr) return this->L->groupsCount;
        return 0;
    }

    int getGroup(int index, int skipped)
    {
        if(this->L!=nullptr)
        {
            if(this->L->length > index)
            {
                return this->L->getGroup(index, skipped);
            }
            else if(this->L->length + this->groupSize > index)
            {
                return this->groupIndex() + skipped;
            }
            else
            {
                return this->R->getGroup(index - this->groupSize - this->L->length, skipped + this->L->groupsCount + 1);
            }
        }
        else
        {
            if(this->groupSize > index) return this->groupIndex() + skipped;
            return this->R->getGroup(index - this->groupSize, skipped+1);
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
    if(k==0) return {nullptr, T};

    if(T->L!=nullptr)
    {
        if(T->L->groupsCount>=k)
        {
            auto splitResult = Split(T->L, k);

            T->L = splitResult.second;
            T->recalc();

            return {splitResult.first, T};
        }
        else
        {
            auto splitResult = Split(T->R, k-T->L->groupsCount-1);

            T->R = splitResult.first;
            T->recalc();

            return {T, splitResult.second};
        }
    }
    else
    {
        auto splitResult = Split(T->R, k-1);

        T->R = splitResult.first;
        T->recalc();

        return {T, splitResult.second};
    }
}

int n;
int a[MAXN];

Treap *T = nullptr;

void Init()
{
    for(int i = 0;i<n;)
    {
        int indexSave = i;
        for(;i<n;i++)
        {
            if(a[i]!=a[indexSave]) break;
        }

        T = Merge(T, new Treap(i-indexSave, a[indexSave]));
    }
}

void operation1(int index)
{
    int groupIndex = T->getGroup(index, 0);

    auto help = Split(T, groupIndex+1);
    auto help1 = Split(help.first, groupIndex);

    if(help1.second->groupSize==1)
    {
        auto help2 = Split(help.second, 1);
        auto help3 = Split(help1.first, ((help1.first==nullptr)?1:help1.first->groupsCount) - 1 );

        if(help2.first!=nullptr && help3.second!=nullptr)
        {
            if(help2.first->groupColor==help3.second->groupColor)
            {
                int newLength = help2.first->groupSize + help3.second->groupSize;

                T = Merge(help3.first, new Treap(newLength, help2.first->groupColor));
                T = Merge(T, help2.second);

                return;
            }
        }

        help.second = Merge(help2.first, help2.second);
        help1.first = Merge(help3.first, help3.second);

        T = Merge(help1.first, help.second);
    }
    else
    {
        help1.second->groupSize--;
        help1.second->recalc();

        T = Merge(help1.first, help1.second);
        T = Merge(T, help.second);
    }
}

void operation2(int index, int color)
{
    if(T==nullptr)
    {
        T = new Treap(1, color);
        return;
    }
    if(index==T->length)
    {
        auto help = Split(T, T->groupsCount - 1);

        if(help.second->groupColor==color)
        {
            help.second->groupSize++;
            help.second->recalc();

            T = Merge(help.first, help.second);
        }
        else
        {
            T = Merge(help.first, help.second);
            T = Merge(T, new Treap(1, color));
        }

        return;
    }

    int group = T->getGroup(index, 0);

    auto help = Split(T, group+1);
    auto help1 = Split(help.first, group);

    Treap *L, *Mid, *R;

    L = help1.first;
    Mid = help1.second;
    R = help.second;

    //inside
    if( ((L==nullptr)?0:L->length) < index && index < ((L==nullptr)?0:L->length) + Mid->length )
    {
        if(color==Mid->groupColor)
        {
            Mid->groupSize++;
            Mid->recalc();

            T = Merge(L, Mid);
            T = Merge(T, R);

            return;
        }
        else
        {
            int len1 = index - ((L==nullptr)?0:L->length);

            T = L;
            if(len1>0) T = Merge(T, new Treap(len1, Mid->groupColor));
            T = Merge(T, new Treap(1, color));
            if(Mid->groupSize-len1>0) T = Merge(T, new Treap(Mid->groupSize-len1, Mid->groupColor));
            T = Merge(T, R);
        }
    }
    else
    {
        auto help2 = Split(L, ((L==nullptr)?1:L->groupsCount) - 1);
        if(help2.second!=nullptr && help2.second->groupColor==color)
        {
            help2.second->groupSize++;
            help2.second->recalc();

            T = Merge(help2.first, help2.second);
            T = Merge(T, Mid);
            T = Merge(T, R);

            return;
        }
        L = Merge(help2.first, help2.second);

        if(Mid->groupColor==color)
        {
            Mid->groupSize++;
            Mid->recalc();

            T = Merge(L, Mid);
            T = Merge(T, R);

            return;
        }
        if(Mid->groupColor!=color)
        {
            T = Merge(L, new Treap(1, color));
            T = Merge(T, Mid);
            T = Merge(T, R);

            return;
        }
    }
}

void operation3(int index, int color)
{
    if(T==nullptr)
    {
        T = new Treap(1, color);
        return;
    }
    if(T->length==1)
    {
        T = new Treap(1, color);
        return;
    }

    operation1(index);
    operation2(index, color);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    int type, index, color;

    cin >> n;
    for(int i = 0;i<n;i++)
    {
        cin >> a[i];
    }
    Init();

    cin >> Q;
    while(Q--)
    {
        cin >> type;
        if(type==1)
        {
            cin >> index;
            operation1(index-1);
        }
        else if(type==2)
        {
            cin >> index >> color;
            operation2(index-1, color);
        }
        else if(type==3)
        {
            cin >> index >> color;
            operation3(index-1, color);
        }
        else
        {
            cout << ((T==nullptr)?0:T->groupsCount) << '\n';
        }
    }
}
