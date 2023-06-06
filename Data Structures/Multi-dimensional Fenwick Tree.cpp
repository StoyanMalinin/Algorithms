#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

template <typename Type, int... Args>
struct BIT
{
    Type value = 0;
    void Update(Type change)
    {
        value += change;
    }

    Type Query()
    {
        return value;
    }
};

template <typename Type, int N, int... Ns>
struct BIT <Type, N, Ns...>
{
    BIT <Type, Ns...> fenwickTree[N+1];

    template <typename... Args>
    void Update(int pos, Args... args)
    {
        while (pos <= N)
        {
            fenwickTree[pos].Update(args...);
            pos += (pos&(-pos));
        }
    }

    template <typename... Args>
    Type Query(int L, int R, Args... args)
    {

        Type ans = 0;
        while (R)
        {
            ans += fenwickTree[R].Query(args...);
            R -= (R&(-R));
        }

        L--;
        while (L)
        {
            ans -= fenwickTree[L].Query(args...);
            L -= (L&(-L));
        }

        return ans;
    }

};

//creates 3 dimensional fenwick tree
//number of arguments
BIT <int, 100, 100, 100> fenwickTree;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;

        if (type == 1) //Update point with coordinates (x, y, z)
        {
            int x, y, z, change;
            cin >> x >> y >> z >> change;

            fenwickTree.Update(x, y, z, change);
        }

        else
        {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1;
            cin >> x2 >> y2 >> z2;

            //return sum of all elements enclosed in cube with corners (x1, y1, z1) and (x2, y2, z2)
            cout << fenwickTree.Query(x1, x2, y1, y2, z1, z2) << endl;
        }
    }

    return 0;
}
