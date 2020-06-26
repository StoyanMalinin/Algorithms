#include<iostream>
#include<cstring>
#include<queue>

using namespace std;

const int MAXN = 2e5 + 5;

struct Trie
{
    int ending = 0, depth = 0;
    Trie *parent, *root;
    char lastChar = '#';

    Trie *children[30];
    Trie *successLink, *failLink;

    Trie()
    {
        this->depth = 0;
        this->ending = 0;
        this->lastChar = '#';

        this->root = this;
        this->parent = nullptr;

        this->successLink = this->failLink = false;
        for(char c = 'a';c<='z';c++) this->children[c-'a'] = nullptr;
    }
    Trie(Trie *parent, Trie *root)
    {
        this->depth = 0;
        this->ending = 0;
        this->lastChar = '#';

        this->root = root;
        this->parent = parent;

        this->successLink = this->failLink = false;
        for(char c = 'a';c<='z';c++) this->children[c-'a'] = nullptr;
    }

    void addString(string &s, int ind = 0)
    {
        this->depth = ind;
        if(ind==s.size())
        {
            this->ending++;
            return;
        }

        if(this->children[ s[ind] - 'a' ]==nullptr)
        {
            this->children[ s[ind] - 'a' ] = new Trie(this, this->root);
            this->children[ s[ind] - 'a' ]->lastChar = s[ind];
        }

        this->children[ s[ind] - 'a' ]->addString(s, ind+1);
    }

    void bfs()
    {
        queue <Trie*> q;
        q.push(this);

        while(q.empty()==false)
        {
            Trie *x = q.front();q.pop();

            for(char c = 'a';c<='z';c++)
            {
                if(x->children[c-'a']!=nullptr) q.push(x->children[c-'a']);
            }
            if(x->parent==nullptr)
            {
                x->failLink = root;
                x->successLink = nullptr;

                continue;
            }

            x->failLink = x->parent->failLink;
            while(x->failLink!=root && x->failLink->children[x->lastChar-'a']==nullptr)
                x->failLink = x->failLink->failLink;

            if(x->failLink->children[x->lastChar-'a']!=nullptr && x->failLink->children[x->lastChar-'a']!=x)
                x->failLink = x->failLink->children[x->lastChar-'a'];
            else
                x->failLink = root;

            if(x->failLink->ending>0) x->successLink = x->failLink;
            else x->successLink = x->failLink->successLink;
        }
    }

    void printTrie()
    {
        cout << this << " " << lastChar << " " << depth << " || " << failLink << " " << successLink << '\n';
        for(char c = 'a';c<='z';c++)
        {
            if(children[c-'a']!=nullptr) children[c-'a']->printTrie();
        }
    }

    Trie *extend(char c)
    {
        Trie *ans = this;
        while(ans!=root && ans->children[c-'a']==nullptr) ans = ans->failLink;

        if(ans->children[c-'a']!=nullptr) return ans->children[c-'a'];
        return root;
    }
};

Trie *T;

int n;
string s[MAXN], t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    T = new Trie();
    cin >> t;

    cin >> n;
    for(int i =0;i<n;i++)
    {
        cin >> s[i];
        T->addString(s[i]);
    }
    T->bfs();
}

