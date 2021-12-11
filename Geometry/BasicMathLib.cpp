#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = acos(-1);

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

int main()
{
    Vector2 v(1, 0);

    v = v.rotated(degToRad(90));
    cout << fixed << setprecision(5) << v.x << " " << v.y << '\n';
}
