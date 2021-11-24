#include<bits/stdc++.h>

using namespace std;

struct Event
{
    int t;
    bool type;
    /*
    false - влиза
    true - излиза
    */

    Event(){}
    Event(int t, bool type)
    {
        this->t = t;
        this->type = type;
    }
};

bool operator <(const Event& A, const Event& B)
{
    if(A.t!=B.t) return A.t<B.t;
    return A.type<B.type;
}

class Solution{

	public:
	vector<int> findMaxGuests(int Entry[], int Exit[], int N)
	{
        vector <Event> v;
        for(int i = 0;i<N;i++)
        {
            v.push_back(Event(Entry[i], false));
            v.push_back(Event(Exit[i], true));
        }
        sort(v.begin(), v.end());

        int cnt = 0;
        int maxCnt = 0, bestTime = 0;

        for(const Event& e: v)
        {
            if(e.type==false)
            {
                cnt++;
                if(cnt>maxCnt)
                {
                    maxCnt = cnt;
                    bestTime = e.t;
                }
            }
            else
            {
                cnt--;
            }
        }

        return vector <int>({maxCnt, bestTime});
	}
};

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,i;
        cin>>n;
        int entry[n],exit1[n];
        for(i=0;i<n;i++)
        cin>>entry[i];
        for(i=0;i<n;i++)
        cin>>exit1[i];
        Solution obj;

	    vector<int> p = obj.findMaxGuests(entry, exit1, n);
	    cout<<p[0]<<' '<<p[1];
	    cout<<"\n";
    }
    return 0;
}
