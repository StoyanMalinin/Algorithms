#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int offset = 4*1e6;
int answer[2*offset+5];
int nearestLeft[2*offset+5];
int nearestRight[2*offset+5];
bool D[2*offset+5];

void fillArray(int n, int l, int p, int f)
{
    int8_t sign = 0;
    int a;

    sign = (f<=0?1:-1);
    a = sign*(l%p);
    answer[a+offset] = 1;

    int sum = l;
    for (int i = 1; i < n; i++)
    {
        sum = (sum+l)%p;
        a = sum*(i<f?-1:+1);

        answer[a+offset] = 1;
    }

    int i, j;
    int left = -3*offset, right = 3*offset;
    for (int i = 0, j = 2*offset-1; i < 2*offset; i++, j--)
    {
        if (answer[i] == 1)
            left = i;

        if (answer[j] == 1)
            right = j;

        nearestRight[j] = right;
        nearestLeft[i] = left;
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, l, p, f;
    int m, r, q, g;
    int8_t sign = 0;

    cin >> n >> l >> p >> f;
    cin >> m >> r >> q >> g;

    fillArray(n, l, p, f);
    //fillArray(b, m, r, q, g);

    int diff = 0, left, right;

    sign = (g<=0?1:-1);
    int b = sign*(r%q);
    int MIN = 0;

    left = nearestLeft[b+offset];
    right = nearestRight[b+offset];

    MIN = min(abs(right - b - offset),abs(left - b - offset));

    D[MIN + offset] = true;

    int br = 1, sum = r;
    for (int i = 1; i < m; i++)
    {
        sum = (sum + r)%q;
        b = sum*((i<g)?-1:+1);

        left = nearestLeft[b+offset];
        right = nearestRight[b+offset];

        MIN = min(right - b - offset,b - left + offset);
        if (D[MIN+offset] == false)
        {
            br++;
            D[MIN+offset] = true;
        }
    }

    bool first = true;
    cout << br << endl;
    for (int i = 2*offset+1; i >= 0; i--)
    {
        if (D[i] == true)
        {
            if (first == true)
                cout << i-offset;
            else
                cout << " " << i-offset;

            first = false;
        }
    }
    cout << endl;

    return 0;
}
