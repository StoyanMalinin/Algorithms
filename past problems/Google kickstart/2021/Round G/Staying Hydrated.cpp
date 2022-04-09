#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int getBestPos(const vector <pair <int, bool>> &v)
{
    int bestPos = -1;
    int64_t bestSum = numeric_limits<int64_t>::max();

    int64_t rightSum = 0, rightCnt = 0;
    int64_t leftSum = 0, leftCnt = 0;

    for(auto &item: v)
    {
        if(item.second==false)
        {
            rightCnt++;
            rightSum += item.first;
        }
    }

    for(auto &item: v)
    {
        if(item.second==false)
        {
            rightCnt--;
            rightSum -= item.first;
        }
        else
        {
            leftCnt++;
            leftSum += item.first;
        }

        int64_t posSum = 0;
        posSum += item.first*leftCnt - leftSum;
        posSum += rightSum - item.first*rightCnt;

        if(posSum<bestSum)
        {
            bestSum = posSum;
            bestPos = item.first;
        }
    }

    return bestPos;
}

void solveTestcase(int T)
{
    int n;
    cin >> n;

    vector <pair <int, bool>> vx, vy;
    for(int i = 0;i<n;i++)
    {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        vx.push_back({x1, false});
        vx.push_back({x2, true});

        vy.push_back({y1, false});
        vy.push_back({y2, true});
    }

    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    int bestX = getBestPos(vx);
    int bestY = getBestPos(vy);

    cout << "Case #" << T << ": " << bestX << " " << bestY << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for(int t = 1;t<=T;t++)
        solveTestcase(t);
}
