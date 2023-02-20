#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 5000;
const int MAXR = 100;
const int H_CNT = 1;
const int64_t mod[H_CNT] = {(int64_t) 1e9 + 7};//, (int64_t) 1e9 + 9};
const int64_t key[H_CNT] = {29};//, 31};
int64_t keyPow[H_CNT][MAXN+5];

int n, m, r, c;
char pattern[MAXR+5][MAXR+5];
char input[MAXR+5][MAXN+5];

void init1()
{
    for (int h = 0; h < H_CNT; h++)
    {
        keyPow[h][0] = 1;
    }
    for (int i = 1; i <= MAXN; i++)
    {
        for(int h = 0; h < H_CNT; h++)
        {
            keyPow[h][i] = (keyPow[h][i - 1] * key[h]) % mod[h];
        }
    }
}

struct Hash
{
    int len;
    int h[H_CNT];

    Hash()
    {
        this->len = 0;
        memset(this->h, 0, sizeof(this->h));
    }

    bool operator ==(const Hash& other)
    {
        if (len != other.len)
        {
            return false;
        }
        for (int i = 0; i < H_CNT; i++)
        {
            if (h[i] != other.h[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator !=(const Hash& other)
    {
        return !(*this == other);
    }

    void pushBack(char c)
    {
        len++;
        for (int i = 0; i < H_CNT; i++)
        {
            h[i] = (h[i] * key[i] + (c - 'a')) % mod[i];
        }
    }

    void popFront(char c)
    {
        for (int i = 0; i < H_CNT; i++)
        {
            h[i] = (h[i] - (c - 'a') * keyPow[i][len - 1] + mod[i] * mod[i]) % mod[i];
        }
        len--;
    }
};

Hash inputHash[MAXN + 5];
int cancelPattern[MAXR+5];
Hash patternHash[MAXR + 5];

void init2()
{
    int len = 0;
    cancelPattern[0] = 0;
    for (int i = 1; i < c; i++)
    {
        while (len != 0 && patternHash[i] != patternHash[len])
        {
            len = cancelPattern[len - 1];
        }

        if (patternHash[i] == patternHash[len])
        {
            len++;
        }
        cancelPattern[i] = len;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init1();

    int ans = 0;

    cin >> r >> c;
    for (int i = 0; i < r; i++)
    {
        cin >> pattern[i];
        for (int j = 0; j < c; j++)
        {
            patternHash[j].pushBack(pattern[i][j]);
        }
    }

    init2();

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        if (i - r >= 0)
        {
            for (int j = 0; j < m; j++)
            {
                inputHash[j].popFront(input[(i - r) % r][j]);
            }
        }

        cin >> input[i % r];
        for (int j = 0; j < m; j++)
        {
            inputHash[j].pushBack(input[i % r][j]);
        }

        if (i + 1 >= r)
        {
            int len = 0;
            for (int j = 0; j < m; j++)
            {
                while (len != 0 && inputHash[j] != patternHash[len])
                {
                    len = cancelPattern[len - 1];
                }

                if (inputHash[j] == patternHash[len])
                {
                    len++;
                    if (len == c)
                    {
                        ans++;
                        len = cancelPattern[len - 1];
                    }
                }
            }
        }
    }

    cout << ans << '\n';
}
