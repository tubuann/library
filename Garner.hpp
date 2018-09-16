#ifndef Garner_hpp
#define Garner_hpp

#include "LongLong.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

typedef LongLong LL;

//LongLong
void Ex_Euc(LL a,LL b,LL &x,LL &y){
  if(b==0){x=1; y=0; return;}
  Ex_Euc(b,a%b,y,x);
  y-=(a/b)*x;
}

LL Garner(const vector<LL> &a,const vector<LL> &m){
  assert(a.size()==m.size());
  LL M(1);
  LL ans(0);
  for(int i=0;i<a.size();i++){
    LL k=a[i]-ans;
    LL x,y;
    Ex_Euc(M,m[i],x,y);
    ans+=M*(x*k%m[i]);
    M*=m[i];
  }
  if(ans<0){ans+=M;}
  return ans;
}





//long long
void Ex_Eucll(ll a,ll b,ll &x,ll &y){
    if(b==0){x=1; y=0; return;}
    Ex_Eucll(b,a%b,y,x);
    y-=(a/b)*x;
}

ll Garnerll(const vector<ll> &a,const vector<ll> &m,const ll &mod){
    assert(a.size()==m.size());
    vector<ll> rmn(a.size(),0);
    vector<ll> LM(a.size(),1);
    ll ans=0;
    ll M=1;
    for(int i=0;i<a.size();i++){
        ll k=a[i]-rmn[i];
        k%=m[i];
        if(k<0){k+=m[i];}
        ll x,y;
        Ex_Eucll(LM[i],m[i],x,y);
        k*=x; k%=m[i];
        if(k<0){k+=m[i];}
        ans+=k*M;
        ans%=mod;
        for(int t=i+1;t<a.size();t++){
            rmn[t]+=LM[t]*k;
            rmn[t]%=m[t];
            LM[t]*=m[i];
            LM[t]%=m[t];
        }
        M*=m[i];
        M%=mod;
    }
    return ans;
}



#endif /*Garner_hpp*/
