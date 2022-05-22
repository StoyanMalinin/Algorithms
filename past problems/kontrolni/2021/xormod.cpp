#include <iostream>

using namespace std;

const int MAX_BIT = 62;

void solveTestcase()
{
    int64_t a, n;
    cin >> a >> n;

    int64_t b = 0;
    for(int bit = MAX_BIT;bit>=0;bit--)
    {
        //set to 0
        int64_t lowerBound = (a^b)&(~((1LL<<bit)-1));
        int64_t upperBound = (a^b)|((1LL<<bit)-1);

        int64_t x = lowerBound;
        if(x%n!=0) x += n - x%n;

        //then set to 1
        if(!(x<=upperBound)) b |= (1LL<<bit);
    }

    cout << b << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--) solveTestcase();
}
