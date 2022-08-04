#include "prize.h"

#include <iostream>
#include <vector>

#ifdef _LOCAL_
#include "grader.cpp"
#endif // _LOCAL_

using namespace std;

int solve(int l, int r, vector <int> lRes, vector <int> rRes)
{
    if(lRes==rRes) return -1;
    if(l+1>=r) return -1;

    int mid = (l+r)/2;
    vector <int> midRes = ask(mid);

    if(midRes==vector <int>{0, 0}) return mid;
    else if(l==r) return -1;

    int solL = solve(l, mid, lRes, midRes);
    if(solL!=-1) return solL;

    int solR = solve(mid, r, midRes, rRes);
    return solR;
}

int find_best(int n)
{
    vector <int> lRes = ask(0);
    vector <int> rRes = ask(n-1);

    if(lRes==vector <int>{0, 0}) return 0;
    if(rRes==vector <int>{0, 0}) return n-1;

    return solve(0, n-1, lRes, rRes);
}
