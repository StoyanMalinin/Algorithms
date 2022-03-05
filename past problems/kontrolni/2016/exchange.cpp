#include<iostream>
#include<cstring>
#include<map>

using namespace std;

struct number
{
    int arr[45];
    int length;
};

int s, n;
int a[205], b[205];

bool calculated[2005][205];
number memo[2005][205];
int n0[1] = {0}, n1[1] = {1};

void memoPrepare()
{
    for(int i = 0;i<=s;i++)
    {
        for(int j = 0;j<n;j++)
        {
            memo[i][j].length = 1;
            memset(memo[i][j].arr, false, sizeof(memo[i][j].arr));
        }
    }
}

void add(number &A, number B)
{
    if(A.length<B.length)
    {
        for(int i = A.length;i<B.length;i++)
            A.arr[i] = 0;

        A.length = B.length;
    }
    else
    {
        for(int i = B.length;i<A.length;i++)
            B.arr[i] = 0;
    }


    int next = 0;
    for(int i = 0;i<A.length;i++)
    {
        A.arr[i] = A.arr[i] + B.arr[i] + next;

        next = A.arr[i]/10;
        A.arr[i] = A.arr[i]%10;
    }
    if(next!=0) {A.arr[A.length] = next;A.length++;}
}

number createSum(int sum, int index)
{
    number answer;
    if(sum==0)
    {
        answer.length = 1;
        for(int i = 0;i<answer.length;i++)
            answer.arr[i] = n1[i];

        return answer;
    }
    if(index==n)
    {
        answer.length = 1;
        for(int i = 0;i<answer.length;i++)
            answer.arr[i] = n0[i];

        return answer;
    }
    if(calculated[sum][index]==true) return memo[sum][index];
    else
    {
        answer.length = 1;
        memset(answer.arr, false, sizeof(answer.arr));

        for(int i = 0;i<=b[index];i++)
        {
            if(sum-i*a[index]<0) break;
            add(answer, createSum(sum-i*a[index], index+1));
        }


        /*
        cout << sum << " " << index << endl;
        cout << "-----";
        for(int i = answer.length-1;i>=0;i--)
            cout << answer.arr[i];
        cout << '\n';
        */

       // system("PAUSE");


    }

    memo[sum][index] = answer;
    calculated[sum][index] = true;

    return memo[sum][index];
}

int length;
map <int, int> coins;
map <int, int>:: iterator it;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s;
    cin >> n;
    for(int i = 0;i<n;i++) cin >> a[i];
    for(int i = 0;i<n;i++)
    {
        cin >> b[i];
        coins[ a[i] ] += b[i];
    }

    n = 0;
    for(it = coins.begin();it!=coins.end();it++)
    {
        a[n] = (*it).first;
        b[n] = (*it).second;

        n++;
    }
    //memoPrepare();


    /*
    number A, B;
    A.length = 1;A.arr[0] = 1;
    B.length = 2;B.arr[0] = 9;B.arr[1] = 6;

    add(A, B);
    cout << A.arr[1] << A.arr[0] << endl;
    */



    createSum(s, 0);

    number answer;
    answer.arr[0] = 0;answer.length = 1;

    for(int i = memo[s][0].length-1;i>=0;i--)
        cout << memo[s][0].arr[i];
    cout << '\n';

}
/*
50
3
20 10 5
1 2 3

50
3
20 10 5
10 10 10

5
3
1 4 5
100 100 100
*/
