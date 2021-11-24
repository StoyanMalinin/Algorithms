#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int inf = 1e9 + 5;

struct Event
{
    int t;
    bool type;
    /*
    false - влиза
    true - излиза
    */

    Event(){}
    Event(int t, bool type)
    {
        this->t = t;
        this->type = type;
    }
};

bool operator <(const Event& A, const Event& B)
{
    if(A.t!=B.t) return A.t<B.t;
    return A.type>B.type;
}

int main()
{
    vector <Event> v;

    int n;
    cin >> n;
    for(int i = 0;i<n;i++)
    {
        int a, b;
        cin >> a >> b;

        v.push_back({a, false});
        v.push_back({b, true});
    }

    sort(v.begin(), v.end());

    int cnt = 0;
    int maxCnt = 0;
    for(const Event& e: v)
    {
        if(e.type==false)
        {
            cnt++;
            maxCnt = max(maxCnt, cnt);
        }
        else
        {
            cnt--;
        }
    }

    cnt = 0;
    int lastTime = inf;

    set <int> boundry;
    int cntCovered = 0;

    for(const Event& e: v)
    {
        if(cnt==maxCnt)
        {
            boundry.insert(e.t);
            boundry.insert(lastTime);

            if(lastTime!=inf && e.t!=lastTime)
                cntCovered += e.t - lastTime - 1;
        }

        if(e.type==false)
        {
            cnt++;
        }
        else
        {
            cnt--;
        }

        lastTime = e.t;
    }

    cout << cntCovered + boundry.size() << '\n';
}
