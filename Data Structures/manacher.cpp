#include<iostream>

using namespace std;

const int MAXN = 1e5 + 5;

int d1[MAXN], d2[MAXN];
void manacher(string &s, int *d1, int *d2)
{
    int n = s.size();

    //odd
    for(int i = 0, l = 0, r = -1;i<n;i++)
    {
        int len = ((i>r)?1:min(d1[l+r-i], r-i+1));
        while(i-len>=0 && i+len<n && s[i-len]==s[i+len]) len++;

        d1[i] = len;
        if(i+len-1>r)
        {
            l = i - len + 1;
            r = i + len - 1;
        }

        cout << "d1[" <<  i << "] = " << d1[i] << '\n';
    }

    cout << '\n';

    //even
    for(int i = 0, l = 0, r = -1;i<n;i++)
    {
        int len = ((i+1>r)?0:min(d2[l+r-i-1], r-i));
        while(i-len>=0 && i+1+len<n && s[i-len]==s[i+1+len]) len++;

        d2[i] = len;
        if(i+1+len-1>r)
        {
            l = i - len + 1;
            r = i + 1 + len - 1;
        }

        cout << "d2[" <<  i << "] = " << d2[i] << '\n';
    }
}

int main()
{
    string s;
    cin >> s;

    manacher(s, d1, d2);
}
