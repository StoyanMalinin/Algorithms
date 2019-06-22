#include<iostream>
#include<cstring>

using namespace std;

const int MAXN = 1e5 + 5;

struct fenwickTree
{
    int tree[MAXN], jump[MAXN];

    void Init()
    {
        memset(this->tree, 0, sizeof(this->tree));

        int curr = 1, p = 0;
        for(int i = 0;i<MAXN;i++)
        {
            if(curr*2<i)
            {
                p++;
                curr *= 2;
            }

            jump[i] = p;
        }
    }

    void update(int index, int value)
    {
        while(index<MAXN)
        {
            this->tree[index] += value;
            index += index&(-index);
        }
    }

    int rsq(int index)
    {
        int sum = 0;
        while(index>0)
        {
            sum += this->tree[index];
            index -= index&(-index);
        }

        return sum;
    }

    int query(int l, int r)
    {
        return rsq(r) - rsq(l-1);
    }

    int findElement(int l, int r, int index)
    {
        if(l==r) return l;
        int free = (1LL<<this->jump[r-l+1]) - this->tree[ l + (1LL<<this->jump[r-l+1]) - 1 ];

        if(free>=index) return findElement(l, l+(1LL<<this->jump[r-l+1])-1, index);
        return findElement(l+(1LL<<this->jump[r-l+1]), r, index-free);
    }
};

int main()
{

}
