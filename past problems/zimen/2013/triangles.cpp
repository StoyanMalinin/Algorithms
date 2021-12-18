//Separating Axis Theorem

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

const double PI = acos(-1);
const double eps = 0.00000001;

double degToRad(double x)
{
    return (x/180)*PI;
}

double radToDeg(double x)
{
    return (x/PI)*180;
}

struct Vector2
{
    double x, y;

    Vector2(){}
    Vector2(double x, double y) : x(x), y(y) {}

    double mag2()
    {
        return x*x + y*y;
    }

    double mag()
    {
        return sqrt(x*x + y*y);
    }

    Vector2 normalized();
    Vector2 rotated(double ang)
    {
        return Vector2(x*cos(ang) - y*sin(ang), x*sin(ang) + y*cos(ang));
    }
};

Vector2 operator +(const Vector2& A, const Vector2& B)
{
    return Vector2(A.x+B.x, A.y+B.y);
}

Vector2 operator -(const Vector2& A)
{
    return Vector2(-A.x, -A.y);
}

Vector2 operator -(const Vector2& A, const Vector2& B)
{
    return Vector2(A.x-B.x, A.y-B.y);
}

Vector2 operator *(const Vector2& A, const double a)
{
    return Vector2(A.x*a, A.y*a);
}

Vector2 operator /(const Vector2& A, const double a)
{
    return Vector2(A.x/a, A.y/a);
}

Vector2 operator *(const double a, const Vector2& A)
{
    return Vector2(A.x*a, A.y*a);
}

Vector2 Vector2::normalized()
{
    return (*this)/mag();
}

double calcArea(const Vector2& A, const Vector2& B, const Vector2& C)
{
    return ((A.x*B.y + A.y*C.x + B.x*C.y) - (A.y*B.x + A.x*C.y + B.y*C.x))*0.5;
}

struct Polygon
{
    vector <Vector2> v;

    Polygon(){}
    Polygon(vector <Vector2> v)
    {
        this->v = v;
    }
};

bool operator <(Vector2 A, Vector2 B)
{
    if(abs(A.x-B.x)>eps) return A.x+eps<B.x;
    return A.y+eps<B.y;
}

bool operator >(Vector2 A, Vector2 B)
{
    if(abs(A.x-B.x)>eps) return A.x+eps>B.x;
    return A.y+eps>B.y;
}

struct Line
{
    //Ax + By + C = 0;
    double A, B, C;

    Line(){}
    Line(Vector2 P1, Vector2 P2)
    {
        this->A = P1.y - P2.y;
        this->B = P2.x - P1.x;
        this->C = P1.y*(P1.x-P2.x) - P1.x*(P1.y-P2.y);
    }

    double getY(double x) const
    {
        return (-C-A*x)/B;
    }

    pair <Vector2, Vector2> sample2() const
    {
        if(abs(B)>eps) return {Vector2(1, getY(1)), Vector2(2, getY(2))};
        else
        {
            double x = -C/A;
            return {Vector2(x, 1), Vector2(x, 2)};
        }
    }
};

Vector2 intersect(const Line& l1, const Line& l2)
{
    if(abs(l1.A)>eps) //l1.A != 0
    {
        double y = (l2.A*l1.C - l2.C*l1.A)/(l1.A*l2.B - l1.B*l2.A);
        double x = (-l1.C-l1.B*y)/l1.A;

        return Vector2(x, y);
    }
    else
    {
        double x = (l2.B*l1.C - l1.B*l2.C)/(l1.B*l2.A - l2.B*l1.A);
        double y = (-l1.C-l1.A*x)/l1.B;

        return Vector2(x, y);
    }
}

Vector2 project(const Line &l, const Vector2& P)
{
    pair <Vector2, Vector2> a = l.sample2();

    Vector2 v = a.first - a.second;
    v = v.rotated(PI/2);

    Vector2 P1 = P + v;
    Line l1(P, P1);

    return intersect(l, l1);
}

void readTriangle(Polygon &T)
{
    int x, y;

    cin >> x >> y;
    T.v.emplace_back(x,  y);

    cin >> x >> y;
    T.v.emplace_back(x,  y);

    cin >> x >> y;
    T.v.emplace_back(x,  y);
}

bool between(Vector2 A, Vector2 B, Vector2 X)
{
    if(min(A.x, B.x)-eps<=X.x && X.x<=max(A.x, B.x)+eps
       && min(A.y, B.y)-eps<=X.y && X.y<=max(A.y, B.y)+eps)
    {
        return true;
    }

    return false;
}

bool intersect(const Polygon &p1, const Polygon &p2)
{
    const Polygon* p = &p1;
    for(int iter = 0;iter<2;iter++)
    {
        for(int i = 0;i<(*p).v.size();i++)
        {
            Vector2 A = (*p).v[i];
            Vector2 B = (*p).v[(i+1)%(*p).v.size()];
            Line l(A, B);

            Vector2 min1 = project(l, p1.v[0]), max1 = project(l, p1.v[0]);
            for(int j = 1;j<p1.v.size();j++)
            {
                Vector2 P = project(l, p1.v[j]);
                min1 = min(min1, P);
                max1 = max(max1, P);
            }

            Vector2 min2 = project(l, p2.v[0]), max2 = project(l, p2.v[0]);
            for(int j = 1;j<p2.v.size();j++)
            {
                Vector2 P = project(l, p2.v[j]);
                min2 = min(min2, P);
                max2 = max(max2, P);
            }

            if(!(between(min1, max1, min2)==true || between(min2, max2, min1)==true))
            {
                return false;
            }

            /////////////////////////////////

            bool positiveArea[2] = {false, false};
            bool zeroArea[2] = {false, false};
            bool negativeArea[2] = {false, false};

            for(int j = 0;j<p1.v.size();j++)
            {
                double S = calcArea(A, B, p1.v[j]);

                if(S<-eps) negativeArea[0] = true;
                else if(S>+eps) positiveArea[0] = true;
                else zeroArea[0] = true;
            }

            for(int j = 0;j<p2.v.size();j++)
            {
                double S = calcArea(A, B, p2.v[j]);

                if(S<-eps) negativeArea[1] = true;
                else if(S>+eps) positiveArea[1] = true;
                else zeroArea[1] = true;
            }

            if(positiveArea[0]!=negativeArea[0] && positiveArea[1]!=negativeArea[1]
               && positiveArea[0]!=positiveArea[1] && zeroArea[0]!=zeroArea[1])
            {
                return false;
            }
        }

        p = &p2;
    }

    return true;
}

int main()
{
    Polygon T, T1, T2, T3, T4;

    readTriangle(T);
    readTriangle(T1);
    readTriangle(T2);
    readTriangle(T3);
    readTriangle(T4);

    cout << intersect(T, T1) << intersect(T, T2) << intersect(T, T3) << intersect(T, T4) << '\n';
}
