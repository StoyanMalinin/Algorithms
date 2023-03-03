#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<set>

using namespace std;

const int MAXN = 1e5;

struct FenwickTree
{
    int tree[MAXN * 2 + 5];

    FenwickTree()
    {
        memset(this->tree, 0, sizeof(this->tree));
    }

    void update(int index, int value)
    {
        index++;
        while (index < MAXN*2 + 5)
        {
            tree[index] += value;
            index += index&(-index);
        }
    }

    int query(int index)
    {
        int sum = 0;

        index++;
        while (index>0)
        {
            sum += tree[index];
            index -= index&(-index);
        }

        return sum;
    }
};

FenwickTree *T = new FenwickTree();
queue <int> leftShoes[MAXN + 5], rightShoes[MAXN + 5];

int calcValue(int leftShoeInd, int rightShoeInd)
{
    int val = leftShoeInd + (rightShoeInd - 1);
    if (leftShoeInd > rightShoeInd) val++;

    return val;
}

int64_t count_swaps(vector <int> s)
{
    set <int> allIndexes;
    for (int i = 0;i<s.size();i++)
    {
        allIndexes.insert(i);

        if (s[i] < 0) leftShoes[ -s[i] ].push(i);
        else rightShoes[ s[i] ].push(i);
    }

    int64_t answer = 0;
    for (int index = 0; index < s.size(); index += 2)
    {
        int bestIndex = -1;
        int leftShoeFakeInd, rightShoeFakeInd;

        bestIndex = abs(s[*allIndexes.begin()]);
        allIndexes.erase(leftShoes[bestIndex].front());
        allIndexes.erase(rightShoes[bestIndex].front());

        leftShoeFakeInd = leftShoes[bestIndex].front() - T->query(leftShoes[bestIndex].front());
        rightShoeFakeInd = rightShoes[bestIndex].front() - T->query(rightShoes[bestIndex].front());

        T->update(leftShoes[bestIndex].front(), 1);
        T->update(rightShoes[bestIndex].front(), 1);

        leftShoes[bestIndex].pop();
        rightShoes[bestIndex].pop();

        answer += calcValue(leftShoeFakeInd, rightShoeFakeInd);
    }

    return answer;
}
