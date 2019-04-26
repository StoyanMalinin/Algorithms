#include<iostream>
#include<cstring>

using namespace std;

const int MAXN = 1005;

struct fenwick1D
{
    int n;
    long long tree[MAXN];

    fenwick1D(){}
    fenwick1D(int n)
    {
        this->n = n;
        memset(this->tree, 0, sizeof(this->tree));
    }

    void update(int index, long long value)
    {
        if(index<=0) return;
        while(index<=this->n)
        {
            this->tree[index] += value;
            index += index&(-index);
        }
    }

    long long getPrefix(int index)
    {
        long long result = 0;
        while(index>0)
        {
            result += this->tree[index];
            index -= index&(-index);
        }

        return result;
    }

    long long query(int l, int r)
    {
        return getPrefix(r) - getPrefix(l-1);
    }
};

struct fenwick2D
{
    int n;
    fenwick1D *tree[MAXN];

    fenwick2D(){}
    fenwick2D(int n, int m)
    {
        this->n = n;
        for(int i = 0;i<=n+1;i++)
        {
            this->tree[i] = new fenwick1D(m);
        }
    }

    void update(int x, int y, long long value)
    {
        if(x<=0) return;
        while(x<=this->n)
        {
            this->tree[x]->update(y, value);
            x += x&(-x);
        }
    }

    long long query(int x, int y)
    {
        long long result = 0;
        while(x>0)
        {
            result += this->tree[x]->getPrefix(y);
            x -= x&(-x);
        }

        return result;
    }
};

int main()
{

}
