#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5;

int n;
int64_t m;
int64_t a[MAXN+5];

int64_t pref[MAXN + 5], suff[MAXN + 5];

struct Answer
{
    int len, ind;

    Answer(int len, int ind) : len(len), ind(ind) {}
};

Answer getBestAnswer(const Answer &a1, const Answer &a2)
{
    if (a1.len > a2.len) return a1;
    if (a1.len < a2.len) return a2;

    if (a1.ind < a2.ind) return a1;
    return a2;
}

Answer solve(int l, int r)
{
    if (r - l + 1 < 1)
    {
        return Answer(0, -1);
    }
    if (r - l + 1 == 1)
    {
        if (a[l] <= m) return Answer(1, l);
        return Answer(0, -1);
    }

    int mid = (l + r) / 2;
    Answer ans = getBestAnswer(solve(l, mid), solve(mid + 1, r));

    vector <int> optPref, optSuff;

    int64_t sum = 0;
    for (int i = mid; i >= l; i--)
    {
        sum += a[i];
        suff[i] = sum;

        while (!optSuff.empty() && sum <= suff[optSuff.back()])
        {
            optSuff.pop_back();
        }
        optSuff.push_back(i);
    }

    sum = 0;
    for (int i = mid + 1; i <= r; i++)
    {
        sum += a[i];
        pref[i] = sum;

        while (!optPref.empty() && sum <= pref[optPref.back()])
        {
            optPref.pop_back();
        }
        optPref.push_back(i);
    }

    int ptr = optSuff.size() - 1;
    for (int i : optPref)
    {
        while (ptr >= 0 && suff[optSuff[ptr]] + pref[i] > m)
        {
            ptr--;
        }

        if (ptr >= 0)
        {
            ans = getBestAnswer(ans,
                                Answer((mid - optSuff[ptr] + 1) + (i - (mid + 1) + 1), optSuff[ptr]));
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    Answer ans = solve(0, n - 1);
    cout << ans.len << " " << ans.ind + 1 << '\n';
}
