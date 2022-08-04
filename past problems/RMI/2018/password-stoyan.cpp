#include<iostream>
//#include "grader.cpp"

using namespace std;

int query(string s);

int letterCount[30];

string makeString(char c, int n)
{
    string output = "";
    for(int i = 0;i<n;i++)
    {
        output = output + c;
    }

    return output;
}

string Merge(string a, string b)
{
    int index = 0;
    while(true)
    {
        if(index==b.size()) break;

        a.insert(index, makeString(b[index], 1));
        if(query(a)!=a.size())
        {
            a.erase(index, 1);
            break;
        }
        else
        {
            index++;
        }
    }

    for(int i = index+1;i<=a.size();i++)
    {
        while(true)
        {
            if(index==b.size()) break;

            string s = "#";
            s[0] = b[index];
            a.insert(i, s);

            if(query(a)!=a.size())
            {
                a.erase(i, 1);
                break;
            }
            else
            {
                index++;
                i++;
            }
        }
    }

    return a;
}

string solve(int l, int r)
{
    if(l==r) return makeString('a'+l, letterCount[l]);

    string s1 = solve(l, (l+r)/2);
    string s2 = solve((l+r)/2+1, r);

    return Merge(s1, s2);
}

string guess(int n, int s)
{
    string answer = "";
    int l, r, mid;

    for(int i = 0;i<s;i++)
        letterCount[i] = query(makeString('a'+i, n));

    answer = solve(0, s-1);
    return answer;
}
