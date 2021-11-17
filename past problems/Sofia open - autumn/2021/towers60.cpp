#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 2000;
const int64_t mod = 1e9 + 7;

int64_t dp[MAXN+5][MAXN+5][2];

int main()
{
    int n;
    cin >> n;

    //���� ����� ���� �����, �� �� "�������" ��������
    //������ �, �� ������� ����� ���������� ��������� �� ��� ���� (-1)-���� ����
    //���� �� �� ���� ��� ��������� �� ������ ��������
    //�������� - ����� ���� �� � ������ �� 0, ������ ��� ������ �� ������ � "������" ����
    //������ (-1)-���� �� � 0
    dp[0][0][0] = 1;
    dp[0][MAXN+1][1] = 1;

    int64_t ans = 0;
    for(int s = 1;s<=n;s++)
    {
        for(int h = 1;h<=s;h++)
        {
            //��� ��������� �� ������� �� �� ��� ����� � ���-�, ������ ����� �� � ���� ������� � ��������� ���������
            //��� ������ ������ �� �� �� �������� ��-�����

            //0
            for(int h1 = h+1;h1<=MAXN+1;h1++) dp[s][h][0] += dp[s-h][h1][1];

            //1
            for(int h1 = 0;h1<h;h1++) dp[s][h][1] += dp[s-h][h1][0];

            dp[s][h][0] %= mod;
            dp[s][h][1] %= mod;

            if(s==n)
                ans = (ans + dp[s][h][0] + dp[s][h][1])%mod;
        }
    }

    //����� 1 �� ��������, ������ ����� �������� � ������� 1 ��� ����
    cout << (ans - 1 + mod)%mod << '\n';
}
