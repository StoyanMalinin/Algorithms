#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Rect
{
    int x1, x2, y;

    Rect(){}
    Rect(int x1, int x2, int y)
    {
        this->x1 = x1;
        this->x2 = x2;
        this->y = y;
    }
};

struct Zone
{
    int x1, x2;
    int64_t area;

    Zone()
    {
        this->area = 0;
    }
    Zone(int x1, int x2, int64_t area) : Zone()
    {
        this->x1 = x1;
        this->x2 = x2;
        this->area = area;
    }
};

vector <Zone>* eval(const vector <Rect>& v)
{
    vector <Zone> *ans = new vector<Zone>();

    struct Event
    {
        int x, h;
        bool type;

        Event(){}
        Event(int x, int h, bool type)
        {
            this->x = x;
            this->h = h;
            this->type = type;
        }
    };

    vector <Event> events;
    for(const Rect& r: v)
    {
        events.emplace_back(r.x1, r.y, false);
        events.emplace_back(r.x2, r.y, true);
    }

    sort(events.begin(), events.end(),
    [](const Event& A, const Event& B)
    {
        if(A.x!=B.x) return A.x<B.x;
        return A.type<B.type;
    });

    int cnt = 0;
    int lastX = 0;
    multiset <int> heights;

    for(const Event &e: events)
    {
        if(e.type==false)
        {
            cnt++;

            if(cnt==1)
            {
                //започва зона

                ans->emplace_back();
                ans->back().x1 = e.x;
            }
            else
            {
                ans->back().area += (e.x-lastX)*1LL*(*prev(heights.end()));
            }

            heights.insert(e.h);
        }
        else
        {
            cnt--;
            if(cnt==0)
            {
                //затваряме зона

                ans->back().x2 = e.x;
            }

            ans->back().area += (e.x-lastX)*1LL*(*prev(heights.end()));
            heights.erase(heights.find(e.h));
        }

        lastX = e.x;
    }

    return ans;
}

/*
В тази функция, ще изчислим как ще се слеят долните и горните зони.
Доста полезно наболюдение е, че няма да се слидват две съседни зони с еднакъв "знак" (теост две съседни положителни или отрицателни).
Това е така, понеже ако допуснем, че две съседни положителни зони биха се слели сега, то те щяха да се слели и преди.
Затова тук ще използваме по-трудно за изпълнение условие за сливане на зони - а именно, че интервалите трябва да се покриват за повече от само крайчетата си.
На по-човешки език казано, зоните [1, 2] и [2, 3] няма да се обединят.
Правим това, понеже условието е правоъгълниците да се докосват само в една точка. Пък ние знаем, че ако се получи гореописаната ситуация,
то те се докосват точно така, понеже са с различен "знак".
По тази причина sweep line-а тук ще е малко по различен.
Ние тук все едно ще пресичаме интервали от вида (a, b), тоест без краища.
*/
void mergeZones(const vector <Zone>& z1, const vector <Zone>& z2, int& zonesCnt, int64_t& sumArea, int64_t& maxArea)
{
    /*
    смятаме така сумарното лице,
    понеже от отделните зони правоъгълниците се пресичат най-много в точка,
    която е с лице 0.
    */
    sumArea = 0;
    for(const Zone& z: z1) sumArea += z.area;
    for(const Zone& z: z2) sumArea += z.area;

    struct Event
    {
        int x;
        int64_t area;

        bool type;

        Event(){}
        Event(int x, int64_t area, bool type)
        {
            this->x = x;
            this->area = area;
            this->type = type;
        }
    };

    vector <Event> events;
    for(const Zone& z: z1)
    {
        cout << "z1: " << z.x1 << " " << z.x2 << " -> " << z.area << '\n';

        events.emplace_back(z.x1, z.area, false);
        events.emplace_back(z.x2, z.area, true);
    }
    for(const Zone& z: z2)
    {
        cout << "z2: " << z.x1 << " " << z.x2 << " -> " << z.area << '\n';

        events.emplace_back(z.x1, z.area, false);
        events.emplace_back(z.x2, z.area, true);
    }

    sort(events.begin(), events.end(),
    [](const Event& A, const Event& B)
    {
        if(A.x!=B.x) return A.x<B.x;
        return A.type>B.type; //тук функцията е различна, понеже един вид пресичаме отворени интервали
    });

    maxArea = 0;
    zonesCnt = 0;

    int cnt = 0;
    int64_t currArea = 0;
    for(const Event& e: events)
    {
        if(e.type==false)
        {
            cnt++;
            if(cnt==1)
            {
                zonesCnt++;
                //открили сме нова зона
            }

            currArea += e.area;
            if(currArea>maxArea)
                maxArea = max(maxArea, currArea);
        }
        else
        {
            cnt--;
            if(cnt==0)
            {
                //зона се затваря
                currArea = 0;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector <Rect> positive, negative;

    int n;
    cin >> n;
    for(int i = 0;i<n;i++)
    {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if(y1>0 || y2>0)
            positive.emplace_back(x1, x2, max(y1, y2));
        else
            negative.emplace_back(x1, x2, -min(y1, y2));
    }

    vector <Zone> *zones1 = eval(positive);
    vector <Zone> *zones2 = eval(negative);

    int zonesCnt = 0;
    int64_t maxArea = 0, sumArea = 0;

    mergeZones(*zones1, *zones2, zonesCnt, sumArea, maxArea);

    cout << zonesCnt << '\n' << sumArea << '\n' << maxArea << '\n';
}
