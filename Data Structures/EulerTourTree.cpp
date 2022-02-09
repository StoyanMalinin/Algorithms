#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <set>

using namespace std;

const int MAXN = 1e6 + 4e5 + 5;

mt19937 rnd(22);

struct EulerTourTree
{
    struct TreapNode
    {
        //treap info
        int length;
        TreapNode *L, *R, *parent;
        int priority;

        //abstract info
        int node, treeSize;
        bool isFirst;

        TreapNode()
        {
            this->L = nullptr;
            this->R = nullptr;
            this->parent = nullptr;
            this->priority = rnd();
        }
        TreapNode(int node) : TreapNode()
        {
            this->node = node;
            this->length = 1;
        }
        TreapNode(int node, bool isFirst) : TreapNode(node)
        {
            this->isFirst = isFirst;
            this->treeSize = isFirst;
        }

        void recalc()
        {
            length = 1;
            treeSize = isFirst;

            if(L!=nullptr)
            {
                length += L->length;
                treeSize += L->treeSize;

                L->parent = this;
            }
            if(R!=nullptr)
            {
                length += R->length;
                treeSize += R->treeSize;

                R->parent = this;
            }
        }

        int getInd(bool toAdd = true)
        {
            recalc();

            if(toAdd==true)
            {
                if(parent==nullptr) return ((L==nullptr)?0:L->length);
                return 1 + ((L==nullptr)?0:L->length) + parent->getInd((parent->R==this));
            }
            else
            {
                if(parent==nullptr) return -1;
                return parent->getInd((parent->R==this));
            }
        }

        TreapNode *getRoot()
        {
            if(parent==nullptr) return this;
            return parent->getRoot();
        }

        void print()
        {
            if(L!=nullptr) L->print();
            cout << "{" << node <<  "}, ";
            if(R!=nullptr) R->print();
        }

        TreapNode *getLeftmost()
        {
            if(L==nullptr) return this;
            return L->getLeftmost();
        }
    };

    TreapNode* Merge(TreapNode *small, TreapNode *big)
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

    pair <TreapNode*, TreapNode*> SplitSz(TreapNode *T, int sz)
    {
        if(T==nullptr) return {nullptr, nullptr};

        if(((T->L==nullptr)?0:T->L->length)+1<=sz)
        {
            auto splitRes = SplitSz(T->R, sz-((T->L==nullptr)?0:T->L->length)-1);

            T->R = splitRes.first;
            T->recalc();

            if(splitRes.second!=nullptr)
                splitRes.second->parent = nullptr;

            return {T, splitRes.second};
        }
        else
        {
            auto splitRes = SplitSz(T->L, sz);

            T->L = splitRes.second;
            T->recalc();

            if(splitRes.first!=nullptr)
                splitRes.first->parent = nullptr;

            return {splitRes.first, T};
        }
    }

    int n;
    int parent[MAXN];
    pair <TreapNode*, TreapNode*> ptr[MAXN];

    EulerTourTree(){}
    EulerTourTree(int n)
    {
        this->n = n;
        for(int x = 0;x<=n;x++)
        {
            this->parent[x] = -1;

            this->ptr[x].first = new TreapNode(x, true);
            this->ptr[x].second = new TreapNode(x, false);

            Merge(this->ptr[x].first, this->ptr[x].second);
        }
    }

    void disconnectNode(int x)
    {
        if(parent[x]==-1) return;
        parent[x] = -1;

        TreapNode *T = ptr[x].first->getRoot();

        int l = ptr[x].first->getInd();
        int r =  ptr[x].second->getInd();

        auto help1 = SplitSz(T, r+1);
        auto help2 = SplitSz(help1.first, l);

        T = Merge(help2.first, help1.second);
    }

    void connectNode(int u, int par)
    {
        TreapNode *T = ptr[par].first->getRoot();
        parent[u] = par;

        auto help = SplitSz(T, ptr[par].first->getInd()+1);

        T = Merge(help.first, ptr[u].first->getRoot());
        T = Merge(T, help.second);
    }

    int getTreeSize(int x)
    {
        TreapNode *T = ptr[x].first->getRoot();

        int l = ptr[x].first->getInd();
        int r = ptr[x].second->getInd();

        auto help1 = SplitSz(T, r+1);
        auto help2 = SplitSz(help1.first, l);

        int treeSize = help2.second->treeSize;
        T = Merge(help2.first, help2.second);
        T = Merge(T, help1.second);

        return treeSize;
    }

    int getRoot(int x)
    {
        return ptr[x].first->getRoot()->getLeftmost()->node;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    EulerTourTree T(10);

    cout << T.getTreeSize(1) << " == " << "1" << '\n';

    T.connectNode(2, 1);
    T.connectNode(3, 2);
    cout << T.getTreeSize(1) << " == " << "3" << '\n';
    cout << T.getTreeSize(2) << " == " << "2" << '\n';

    T.connectNode(4, 2);
    cout << T.getTreeSize(1) << " == " << "4" << '\n';
    cout << T.getTreeSize(2) << " == " << "3" << '\n';
    cout << T.getTreeSize(3) << " == " << "1" << '\n';

    T.disconnectNode(2);
    cout << T.getTreeSize(1) << " == " << "1" << '\n';
    cout << T.getTreeSize(2) << " == " << "3" << '\n';
}
/*
5 5 2
1 5 1
2 5 5
*/
