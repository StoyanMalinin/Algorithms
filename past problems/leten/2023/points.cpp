#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 5e5 + 50;

struct Segment
{
    int x, y1, y2, type;
    Segment(){}
    Segment(int x, int y1, int y2, int type)
        :x(x), y1(y1), y2(y2), type(type){}

    inline bool operator< (const Segment other)
    {
        if (x != other.x)
            return x < other.x;

        return type < other.type;
    }
};

int n, k;
vector <Segment> segments;
set <int> yCoordinates;
map <int, int> compressedY;

struct FenwickTree
{
    int n, tree[3 * MAXN];
    FenwickTree(int n)
        :n(n)
    {
        memset(tree, 0, sizeof(tree));
    }

    void AddPoint(int q)
    {
        if (q <= 0)
            return;

        while(q <= n)
        {
            tree[q]++;
            q += q&(-q);
        }
    }

    int GetPrefix(int index)
    {
        int sum = 0;
        while (index)
        {
            sum += tree[index];
            index -= index&(-index);
        }

        return sum;
    }

    inline int Query(int ql, int qr)
    {
        return GetPrefix(qr) - GetPrefix(ql-1);
    }
};


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> k;

    int startTime = clock();
    segments.reserve(3*n);
    int x, y, newX, newY, x1, y1, x2, y2;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;

        newX = x-y;
        newY = x+y;

        x1 = newX - k;
        y1 = newY - k;
        x2 = newX + k;
        y2 = newY + k;

        segments.emplace_back(x1, y1, y2, -1);
        segments.emplace_back(newX, newY, newY, 0);
        segments.emplace_back(x2, y1, y2, +1);

        yCoordinates.insert(newY);
        yCoordinates.insert(y1);
        yCoordinates.insert(y2);
    }

    int k = 1;
    for (auto it = yCoordinates.begin(); it != yCoordinates.end(); it++, k++)
        compressedY[*it] = k;

    for (Segment &s:segments)
    {
        s.y1 = compressedY[s.y1];
        s.y2 = compressedY[s.y2];
    }

    sort(segments.begin(), segments.end());
    int endTime = clock();

    cout << "initTime: " << endTime - startTime << '\n';

    int64_t ans = 0;
    FenwickTree tree(yCoordinates.size());

    for (const Segment &s : segments)
    {
        if (s.type == 0)
            tree.AddPoint(s.y1);

        if (s.type == -1)
            ans -= tree.Query(s.y1, s.y2);

        if (s.type == +1)
            ans += tree.Query(s.y1, s.y2);
    }

    cout << (ans-n)/2 << endl;

    return 0;
}
