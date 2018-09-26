#ifndef Largest_Rectangle_hpp
#define Largest_Rectangle_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second

ll Largest_Rectangle_inHistogram(const vector<ll> &A){
    ll mx=0;
    stack<pll> s;
    for(ll i=0;i<A.size();i++){
        ll mi=i;
        while(!s.empty() && s.top().F>A[i]){
            pll w=s.top(); s.pop();
            mx=max(mx,w.F*(i-w.S));
            mi=w.S;
        }
        s.push({A[i],mi});
    }
    while(!s.empty()){
        pll w=s.top(); s.pop();
        mx=max(mx,w.F*((ll)A.size()-w.S));
    }
    return mx;
}


ll Largest_Rectangle(const vector<vector<bool>> &A){
    vector<vector<ll>> a(A.size(),vector<ll>(A[0].size(),0));
    ll count;
    for(int i=0;i<A[0].size();i++){
        count=0;
        for(ll h=0;h<A.size();h++){
            if(A[h][i]){count++;}
            else{count=0;}
            a[h][i]=count;
        }
    }
    ll mx=0;
    stack<pll> s;
    for(int i=0;i<A.size();i++){
        for(int t=0;t<A[0].size();t++){
            ll mi=t;
            while(!s.empty() && s.top().F>a[i][t]){
                pll w=s.top(); s.pop();
                mx=max(mx,w.F*(t-w.S));
                mi=w.S;
            }
            s.push({a[i][t],mi});
        }
        while(!s.empty()){
            pll w=s.top(); s.pop();
            mx=max(mx,w.F*((ll)A[0].size()-w.S));
        }
    }
    return mx;
}

ll Largest_Square(const vector<vector<bool>> &A){
    vector<vector<ll>> a(A.size(),vector<ll>(A[0].size(),0));
    ll count;
    for(int i=0;i<A[0].size();i++){
        count=0;
        for(ll h=0;h<A.size();h++){
            if(A[h][i]){count++;}
            else{count=0;}
            a[h][i]=count;
        }
    }
    ll mx=0;
    stack<pll> s;
    for(int i=0;i<A.size();i++){
        for(int t=0;t<A[0].size();t++){
            ll mi=t;
            while(!s.empty() && s.top().F>a[i][t]){
                pll w=s.top(); s.pop();
                ll x=min(w.F,t-w.S);
                mx=max(mx,x*x);
                mi=w.S;
            }
            s.push({a[i][t],mi});
        }
        while(!s.empty()){
            pll w=s.top(); s.pop();
            ll x=min(w.F,(ll)A[0].size()-w.S);
            mx=max(mx,x*x);
        }
    }
    return mx;
}



#endif /*Largest_Rectangle_hpp*/
