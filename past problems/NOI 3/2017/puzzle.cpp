#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 5e4;
const int64_t mod = 1e9 + 7;

int getMatchingSide(int side)
{
    if (side == 0) return 0;
    if (side == 1) return 2;
    if (side == 2) return 1;

    return -1;
}

struct State
{
    int64_t cnt[3][3];

    State()
    {
        memset(cnt, 0, sizeof(cnt));
    }
};

State mergeState(const State &s1, const State &s2)
{
    State res;
    for (int side1 = 0; side1 < 3; side1++)
    {
        for (int side2 = 0; side2 < 3; side2++)
        {
            int side3 = getMatchingSide(side2);
            for (int side4 = 0; side4 < 3; side4++)
            {
                res.cnt[side1][side4] = (res.cnt[side1][side4]
                                         + s1.cnt[side1][side2] * s2.cnt[side3][side4]) % mod;
            }
        }
    }

    return res;
}

struct SegmentTreeNode
{
    State s;

    int l, r;
    SegmentTreeNode *L, *R;

    SegmentTreeNode() : L(nullptr), R(nullptr) {}
    SegmentTreeNode(int l, int r)
    {
        this->l = l;
        this->r = r;
        this->L = nullptr;
        this->R = nullptr;
    }

    void recalc()
    {
        s = mergeState(L->s, R->s);
    }

    void build()
    {
        if (l == r)
        {
            return;
        }

        L = new SegmentTreeNode(l, (l + r) / 2);
        R = new SegmentTreeNode((l + r) / 2 + 1, r);

        L->build();
        R->build();
    }

    void updatePiece(int ind, pair <int, int> piece, int change)
    {
        if (ind == l && l == r)
        {
            s.cnt[piece.first][piece.second] = (s.cnt[piece.first][piece.second] + change + mod) % mod;
            return;
        }
        if (ind < l || r < ind)
        {
            return;
        }

        L->updatePiece(ind, piece, change);
        R->updatePiece(ind, piece, change);
        recalc();
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, Q;
    cin >> m >> n >> Q;

    SegmentTreeNode *T = new SegmentTreeNode(0, n - 1);
    T->build();

    for (int i = 0; i < m; i++)
    {
        int ind, s1, s2;
        cin >> ind >> s1 >> s2;
        ind--;s1--;s2--;

        T->updatePiece(ind, make_pair(s1, s2), +1);
    }

    cout << T->s.cnt[0][0] << '\n';

    while(Q--)
    {
        int type;
        int ind, s1, s2;
        cin >> type >> ind >> s1 >> s2;
        ind--;s1--;s2--;

        if (type==1)
        {
            T->updatePiece(ind, make_pair(s1, s2), +1);
        }
        else
        {
            T->updatePiece(ind, make_pair(s1, s2), -1);
        }

        cout << T->s.cnt[0][0] << '\n';
    }
}
