#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;

const int inf = 1e9 + 5;

struct Event
{
    int pos, h;
    bool type;

    Event(){}
    Event(int pos, int h, bool type) : pos(pos), h(h), type(type) {}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, h, k;
    vector <Event> events;

    cin >> n >> s >> h >> k;
    for(int i = 0;i<n;i++)
    {
        int l, r, t;
        cin >> l >> r >> t;

        events.emplace_back(l, t, false);
        events.emplace_back(r+1, t, true);
    }
    events.emplace_back(1, 0, false);
    events.emplace_back(s+1, 0, true);
    sort(events.begin(), events.end(),
    [](const Event& A, const Event& B)
    {
        if(A.pos!=B.pos) return A.pos<B.pos;
        return A.type<B.type;
    });

    set <int64_t> importantHeights = {h};
    map <int64_t, list <pair <int, int>>> height2Segments;

    int64_t currH = 0;
    for(int i = 0;i<events.size();i++)
    {
        if(events[i].type==false) currH += events[i].h;
        else currH -= events[i].h;

        if(i!=events.size()-1 && events[i].pos<=events[i+1].pos-1 && h-currH>0)
        {
            importantHeights.insert(h-currH);
            height2Segments[h-currH].push_back({events[i].pos, events[i+1].pos-1});
        }
    }

    int64_t ans = 0;
    int64_t segmentCoverVal = (s+k-1)/k, lastH = h;
    set <pair <int, int>> segments = {make_pair(1, s)};
    for(auto hIt = importantHeights.rbegin();hIt!=importantHeights.rend();hIt++)
    {
        ans += (lastH-*hIt)*segmentCoverVal;

        list <pair <int, int>> &l = height2Segments[*hIt];
        for(pair <int, int> item: l)
        {
            auto it = prev(segments.upper_bound({item.first, inf}));

            pair <int, int> seg = *it;
            segmentCoverVal -= (seg.second-seg.first+1+k-1)/k;
            segments.erase(it);

            if(seg.first<=item.first-1)
            {
                segments.insert({seg.first, item.first-1});
                segmentCoverVal += ((item.first-1)-seg.first+1+k-1)/k;
            }
            if(item.second+1<=seg.second)
            {
                segments.insert({item.second+1, seg.second});
                segmentCoverVal += (seg.second-(item.second+1)+1+k-1)/k;
            }
        }

        lastH = *hIt;
    }
    ans += (lastH-0)*segmentCoverVal;

    cout << ans << '\n';
}
