#include<iostream>
#include<vector>

using namespace std;

const int MAXN = 1e5 + 5;
const pair <long long, long long> key = {29, 31};
const pair <long long, long long> mod = {1e9+7, 1e9+9};
pair <long long, long long> keyP[MAXN];

struct Hash
{
    int len;
    pair <long long, long long> x;

    Hash()
    {
        this->len = 0;
        this->x = {0, 0};
    }
    Hash(char c)
    {
        this->len = 1;
        this->x = {c-'a'+1, c-'a'+1};
    }

    void addChar(char c)
    {
        len++;
        x.first = (x.first*key.first + (c-'a'+1))%mod.first;
        x.second = (x.second*key.second + (c-'a'+1))%mod.second;
    }
};

Hash operator +(Hash A, Hash B)//x + y = xy
{
    A.len += B.len;
    A.x.first = (A.x.first*keyP[B.len].first + B.x.first)%mod.first;
    A.x.second = (A.x.second*keyP[B.len].second + B.x.second)%mod.second;

    return A;
}

Hash operator -(Hash A, Hash B) //xy - x = y
{
    A.x.first = (A.x.first - B.x.first*keyP[A.len-B.len].first + mod.first*mod.first)%mod.first;
    A.x.second = (A.x.second - B.x.second*keyP[A.len-B.len].second + mod.second*mod.second)%mod.second;
    A.len -= B.len;

    return A;
}

bool operator ==(Hash A, Hash B)
{
    if(A.len==B.len && A.x==B.x) return true;
    return false;
}

struct String
{
    int n;
    string s;

    vector <Hash> h;

    void InitString()
    {
        h.resize(n);

        h[0] = Hash(s[0]);
        for(int i = 1;i<n;i++)
        {
            h[i] = h[i-1];
            h[i].addChar(s[i]);
        }
    }

    String(){}
    String(string s)
    {
        this->n = s.size();
        this->s = s;

        InitString();
    }

    void readString()
    {
        cin >> this->s;
        this->n = this->s.size();

        InitString();
    }

    Hash getSegment(int l, int r)
    {
        if(l==0) return h[r];
        return h[r] - h[l-1];
    }
};

void Init()
{
    keyP[0] = {1, 1};
    for(int i = 1;i<MAXN;i++)
    {
        keyP[i].first = (keyP[i-1].first*key.first)%mod.first;
        keyP[i].second = (keyP[i-1].second*key.second)%mod.second;
    }
}

int main()
{
    Init();
}


