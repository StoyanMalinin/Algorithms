#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 0.00000001;

struct Vector2
{
    double x, y;

    Vector2(){}
    Vector2(double x, double y) : x(x), y(y) {}
};

bool operator <(Vector2 A, Vector2 B)
{
    if(abs(A.x-B.x)>eps) return A.x+eps<B.x;
    return A.y+eps<B.y;
}

double calcArea(const Vector2& A, const Vector2& B, const Vector2& C)
{
    return ((A.x*B.y + A.y*C.x + B.x*C.y) - (A.y*B.x + A.x*C.y + B.y*C.x))*0.5;
}

double getDist2(Vector2 A, Vector2 B)
{
    return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}

vector <Vector2> hull;
void calcConvexHull(vector <Vector2> &v)
{
    for(int i = 1;i<v.size();i++)
    {
        if(v[i]<v[0])
            swap(v[i], v[0]);
    }

    sort(v.begin()+1, v.end(),
    [&](Vector2 A, Vector2 B)
    {
        double S = calcArea(v[0], A, B);
        if(S>eps) return true;//положително ориентирани
        if(S<-eps) return false;//отрицателно ориентирани

        return getDist2(v[0], A) < getDist2(v[0], B);//колинерани => сравняваме по разстояние
    });

    hull.push_back(v[0]);
    for(int i = 1;i<v.size();i++)
    {
        while(hull.size()>=2 && calcArea(hull[hull.size()-2], hull[hull.size()-1], v[i])<=0)
            hull.pop_back();
        hull.push_back(v[i]);
    }

    cout << "Convex hull: " << '\n';
    for(Vector2 p: hull)
        cout << p.x << " " << p.y << '\n';
}


int main()
{
    vector <Vector2> v;

    int n;
    cin >> n;

    for(int i = 0;i<n;i++)
    {
        int x, y;
        cin >> x >> y;

        v.push_back(Vector2(x, y));//v.emplace_back(x, y);
    }

    calcConvexHull(v);
}
/*
11
1 1
4 2
3 3
2 2
6 3
4 0
1 3
3 4
4 4
5 4
8 0
*/
