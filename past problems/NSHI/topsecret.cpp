
#include "topsecret.h"
#include <bits/stdc++.h>

int find_position(int N, int Q)
{
    using namespace std;

    bool used[N+10];
    for (int i = 0; i < N+5; i++)
        used[i] = false;

    int l = 0, r = N;

    while (l < r)
    {
        int mid = (l+r+1)/2;

        vector <int> left, rightOrEqual;

        for (int i = 0; i < N; i++)
        {
            if (!used[i])
            {

                bool f = is_less(i, mid);
                if (f == true)
                    left.push_back(i);
                else
                    rightOrEqual.push_back(i);
            }
        }

        if (left.size() < mid-l)
        {

            for (int i:rightOrEqual)
                used[i] = true;

            r = mid-1;
        }

        else
        {
            for (int i:left)
                used[i] = true;

            l = mid;
        }

    }
    return r;
}
