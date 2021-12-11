#include <iostream>
#include <cmath>
#include <set>

using namespace std;

const int MAXN = 1005;
const double PI = acos(-1);
const double eps = 0.000001;

struct Vector2
{
    double x, y;

    Vector2(){}
    Vector2(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    double mag2() const
    {
        return x*x + y*y;
    }

    double mag() const
    {
        return sqrt(mag2());
    }

    Vector2 normalized();
    Vector2 rotated(double angle)
    {
        return Vector2(x*cos(angle) - y*sin(angle), x*sin(angle) + y*cos(angle));
    }
};

Vector2 operator +(const Vector2& A, const Vector2& B)
{
    return Vector2(A.x+B.x, A.y+B.y);
}

Vector2 operator -(const Vector2& A, const Vector2& B)
{
    return Vector2(A.x-B.x, A.y-B.y);
}

Vector2 operator *(const Vector2& A, double a)
{
    return Vector2(A.x*a, A.y*a);
}

Vector2 operator /(const Vector2& A, double a)
{
    return Vector2(A.x/a, A.y/a);
}

Vector2 Vector2::normalized()
{
    return (*this)/mag();
}

bool operator <(const Vector2& A, const Vector2& B)
{
    if(abs(A.x-B.x)>eps) return A.x+eps<B.x;
    return A.y+eps<B.y;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Vector2 a[MAXN];
    set <Vector2> s;

    for(int i = 0;i<n;i++)
    {
        int x, y;
        cin >> x >> y;

        a[i] = Vector2(x, y);
        s.insert(a[i]);
    }

    int cnt = 0;
    for(int i = 0;i<n;i++)
    {
        for(int j = i+1;j<n;j++)
        {
            Vector2 mid = (a[i]+a[j])/2;
            Vector2 dir = a[j] - mid;

            Vector2 C = mid + dir.rotated(PI/2);
            Vector2 D = mid + dir.rotated(-PI/2);

            if(s.count(C)==true && s.count(D)==true)
            {
                cnt++;
            }
        }
    }

    cout << cnt/2 << '\n';
}
