//Решение - Мартин

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

const long long inf = 1e18;

pair <long long, long long> extendedEuclid(long long a, long long b)
{
    // A = A*x1 + B*y1
    // B = A*x2 + B*y2
    long long x1 = 1, y1 = 0;
    long long x2 = 0, y2 = 1;

    long long r, q, temp;

    while (b)
    {
        r = a%b;
        q = a/b;
        a = b;
        b = r;

        temp = x1 - q*x2;
        x1 = x2;
        x2 = temp;

        temp = y1 - q*y2;
        y1 = y2;
        y2 = temp;
    }

    return {x1, y1};
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    //A*x + B*y = C
    //x и y - брой скокове от съответния вид

    long long A, B, C;
    cin >> A >> B >> C;

    if (C < 0)//отърваме се от 4тия случай, където x0 < 0 и y0 < 0
        C = -C;

    long long d = __gcd(A, B); //вградена функция за намиране на НОД на две числа
    if (C%d != 0)
    {
        cout << "Impossible" << endl;
        return 0;
    }

    A /= d;
    B /= d;
    C /= d;

    pair <long long, long long> ansEquation = extendedEuclid(A, B);

    long long x0 = ansEquation.first * C;
    long long y0 = ansEquation.second * C;

    long long ans = inf;
    long long temp = inf, k1, k2;

    long long firstK = -(x0/B);
    long long secondK = y0/A;

    if (x0%B != 0 && firstK > 0)
        firstK++;
    if (y0%A != 0 && secondK < 0)
        secondK--;

    //--------------- 1 случай ------------------------
    //x_ans >= 0 && y_ans >= 0
    //k >= -x0/B, k <= y0/A

    // Тъй като имаме = в двете неравенства и ако получим дробен резултат
    // в двете неравенства, закръгляме съответно нагоре или надолу

    // x_ans + y_ans = x0 + y0 + min_k*(B-A)

    k1 = ceil (double(-x0)/double(B));
    k2 = floor(double(y0) / double(A));

    if (k1 <= k2)
        temp = x0 + y0 + min(k1, k2)*(B-A);

    if (temp >= 0)
        ans = min(ans, temp);



    //--------------- 2 случай ------------------------
    //x_ans < 0 && y_ans >= 0
    //k < -x0/B, k <= y0/A

    // -x_ans + y_ans = -x0 + y0 - max_k*(B+A)

    k1 = ceil (double(-x0)/double(B)) - 1;
    k2 = floor(double(y0) / double(A));


    temp = -x0 + y0 - max(k1, k2)*(B+A); //поради грешка в тестовете вместо max(k1, k2) ще трябва да се запише min(k1, k2)
    if (temp >= 0)
        ans = min(ans, temp);

    //--------------- 3 случай ------------------------
    //x_ans >= 0 && y_ans < 0
    //k >= -x0/B, k > y0/A

    // x_ans - y_ans = x0 - y0 + min_k*(B+A)

    k1 = ceil (double(-x0)/double(B));
    k2 = floor(double(y0) / double(A))+1;

    temp = x0 - y0 + min(k1, k2)*(B+A); //поради грешка в тестовете вместо min(k1, k2) ще трябва да се запише max(k1, k2)
    if (temp >= 0)
        ans = min(ans, temp);


    cout << ans << endl;

    return 0;
}
