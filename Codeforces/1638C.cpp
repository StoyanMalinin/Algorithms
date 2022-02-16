#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

const int MAXN = 1e5;
const int inf = 1e9 + 5;

int n;
int a[MAXN+5];

void solveTestcase()
{
    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];

    set <int> s;
    for(int i = n-1;i>=0;i--)
    {
        int minVal = a[i];
        while(s.empty()==false && *s.begin()<a[i])
        {
            minVal = min(minVal, *s.begin());
            s.erase(s.begin());
        }

        s.insert(minVal);
    }

    cout << s.size() << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--) solveTestcase();
}
