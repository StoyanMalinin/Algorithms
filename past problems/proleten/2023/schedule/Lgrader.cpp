#include<iostream>
#include<vector>

#include "schedule.cpp"

using namespace std;

static int _n,_m,_a,_b,_q,_type;
static vector< pair<int,int> > _e;

extern void init(int, vector< pair<int,int> >);
extern void close (int,int);
extern bool question(int,int);

int main(){

    //ios_base::sync_with_stdio(0);
    //cin.tie(0);
    //cout.tie(0);

    cin>>_n>>_m;
    for(int i=1;i<=_m;i++){
        cin>>_a>>_b;
        _e.push_back({_a,_b});
    }

    init(_n,_e);

    cin>>_q;
    for(int i=1;i<=_q;i++){
        cin>>_type>>_a>>_b;
        if(_type==1){
            if(question(_a,_b))cout<<"1";
            else cout<<"0";
        }else{
            close(_a,_b);
        }
    }

    cout<<"\n";

    return 0;
}
/*
7 6
1 2
1 3
1 4
4 6
4 5
6 7
*/
