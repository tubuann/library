#ifndef CPP_hpp
#define CPP_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

class CPP{
private:
    ll v;
    vector<pair<pll,ll>> edge; //to,cost
    ll sum;
    vector<ll> count;
    const ll INF=1e18;
    
public:
    CPP(ll v):v(v),sum(0),count(vector<ll>(v,0)){}
    
    void add_edge(ll from,ll to,ll cost){
        edge.push_back({{from,to},cost});
        sum+=cost;
        count[from]++;
        count[to]++;
    }
    
    ll solve(){
        ll ret=sum;
        vector<ll> n;
        for(int i=0;i<v;i++){
            if(count[i]%2==1){n.push_back(i);}
        }
        if(n.size()==0){return ret;}
        vector<vector<ll>> A(v,vector<ll>(v,INF));
        for(int i=0;i<v;i++){A[i][i]=0;}
        for(int i=0;i<edge.size();i++){
            A[edge[i].F.F][edge[i].F.S]=min(A[edge[i].F.F][edge[i].F.S],edge[i].S);
            A[edge[i].F.S][edge[i].F.F]=A[edge[i].F.F][edge[i].F.S];
        }
        for(int i=0;i<v;i++){
            for(int t=0;t<v;t++){
                for(int h=0;h<v;h++){
                    A[t][h]=min(A[t][i]+A[i][h],A[t][h]);
                }
            }
        }
        vector<ll> dp(1LL<<n.size(),INF);
        priority_queue<pll,vector<pll>,greater<pll>> q; //cost,where
        q.push({0,0});
        dp[0]=0;
        while(!q.empty()){
            pll w=q.top(); q.pop();
            if(dp[w.S]!=w.F){continue;}
            for(int i=0;i<n.size();i++){
                if(w.S>>i&1){continue;}
                for(int t=i+1;t<n.size();t++){
                    if(w.S>>t&1){continue;}
                    pll New={w.F,w.S};
                    New.S|=1LL<<i;
                    New.S|=1LL<<t;
                    New.F+=A[n[i]][n[t]];
                    if(dp[New.S]>New.F){
                        dp[New.S]=New.F;
                        q.push(New);
                    }
                }
            }
        }
        return ret+dp[(1LL<<n.size())-1];
    }
};




#endif /*CPP_hpp*/
