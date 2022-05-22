#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

constexpr int MAXN = 3e5+50;

int LOG2(int value)
{
    return 31 - __builtin_clz(value);
}
class Information
{

public:
    Information(){}
    Information(int inpGCD, int inpMIN)
        :m_gcd(inpGCD), m_min(inpMIN){}
    ~Information(){}

    bool isValid()
    {
        return m_gcd == m_min;
    }
    friend Information min (const Information& a, const Information& b)
    {
        return Information(__gcd(a.m_gcd, b.m_gcd), min(a.m_min, b.m_min));
    }

    friend ostream& operator<< (ostream& output, const Information& a)
    {
        output << "(" << a.m_gcd << ", " << a.m_min << ")";
        return output;
    }

    void operator= (const int a)
    {
        m_gcd = m_min = a;
    }


private:
    int m_gcd, m_min;
};

template <typename Type, int tableSize, int LOGLIMIT>
class SparseTable
{
public:
    SparseTable(){}
    ~SparseTable(){}

    void Build(const int* input, int n)
    {
        for (int i = 0; i < n; i++)
            m_sparseTable[i][0] = input[i];

        for (int lg = 1; lg <= LOGLIMIT; lg++)
        {
            for (int i = 0; i < n; i++)
            {
                if (i + (1 << (lg-1)) > n-1)
                    m_sparseTable[i][lg] = m_sparseTable[i][lg-1];
                else
                    m_sparseTable[i][lg] = min(m_sparseTable[i][lg-1], m_sparseTable[i + (1 << (lg-1))][lg-1]);
            }
        }
    }

    Type Query(int left, int right) const
    {
        int L = LOG2(right-left+1);
        return min(m_sparseTable[left][L], m_sparseTable[right - (1 << L) + 1][L]);
    }

private:
    Type m_sparseTable[tableSize+5][LOGLIMIT+5];
};

bool check(const SparseTable <Information, MAXN, 20>* sparseTable, const int n, int length)
{
    for (int i = 0; i < n-length+1; i++)
    {
        Information info = sparseTable->Query(i, i+length-1);
        if (info.isValid() == true)
            return true;
    }

    return false;
}

void recoverPath(const SparseTable <Information, MAXN, 20>* sparseTable, vector <int>& answer, const int n, int length)
{
    for (int i = 0; i < n - length + 1; i++)
    {
        Information info = sparseTable->Query(i, i+length-1);
        if (info.isValid() == true)
            answer.push_back(i+1);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, a[MAXN];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    SparseTable <Information, MAXN, 20> *sparseTable = new SparseTable<Information, MAXN, 20>;
    sparseTable->Build(a, n);


    int left = 1, right = n;
    while (right - left > 1)
    {
        int mid = (right+left)/2;

        bool flag = check(sparseTable, n, mid);
        if (flag == true)
            left = mid;
        else
            right = mid-1;
    }

    vector <int> answer;
    int length;

    if (check(sparseTable, n, right) == true)
    {
        length = right;
        recoverPath(sparseTable, answer, n, right);
    }
    else if (check(sparseTable, n, left) == true)
    {
        length = left;
        recoverPath(sparseTable, answer, n, left);
    }

    int sz = answer.size();
    cout << sz << " " << length-1 << endl;
    if (sz == 0)
        return 0;
    cout << answer[0];
    for (int i = 1; i < sz; i++)
        cout << " " << answer[i];
    cout << endl;

    return 0;
}

/*
5
4 6 9 3 6
*/
