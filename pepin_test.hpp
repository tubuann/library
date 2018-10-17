#ifndef pepin_test_hpp
#define pepin_test_hpp

#include<bits/stdc++.h>
//#include "Long.hpp"
#include "LongLong.hpp"
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

typedef LongLong LL;

//モンゴメリ乗算
//ret*N=-1 mod 1<<A
void IN(const ll &A,const LL &N,LL &ret){
    ret=0;
    LL t(0);
    LL I(1);
    for(int i=0;i<A;i++){
        if(t[0]==0){
            t+=N;
            ret+=I;
        }
        t>>=1;
        I<<=1;
    }
}

bool pepin_test(ll n){
    assert(n>=0);
    if(n==0){return true;}
    ll A=1LL<<n;
    LL l=1; l<<=A; l+=1;
    ll B=A; B++;
    LL I(1); I<<=B;
    LL a(3); a<<=B;
    for(int i=2;i>=0;i--){if(a>=(l<<i)){a-=(l<<i);}}
    I-=1;
    LL inv;
    IN(B,l,inv);
    LL x(l); x>>=1;
    for(ll i=0;i<A-1;i++){
        a*=a;
        (a+=((a*inv)&=I)*=l)>>=B;
        if(a>=l){a-=l;}
    }
    (a+=((a*inv)&=I)*=l)>>=B;
    if(a>=l){a-=l;}
    return a==(l-=1);
}



/*
LL mod_pow(LL a,LL x,const LL &mod){
    LL ret=1;
    while(x>0){
        if(x[0]){(ret*=a)%=mod;}
        (a*=a)%=mod;
        x>>=1;
    }
    return ret;
}

bool pepin_test(ll n){
    assert(n>=0);
    if(n==0){return true;}
    ll A=(ll)1<<n;
    LL l=1; l<<=A; l+=1;
    LL a=3;
    if(mod_pow(a,l>>1,l)==l-1){return true;}
    return false;
}
*/

/*
bool pepin_test(ll n){
  assert(n>=0);
  if(n==0){return true;}
  ll A=(ll)1<<n;
  vector<ll> s={1};
  for(ll i=0;i<A;i++){
    s.push_back(0);
  }
  Long l(s,true,2);
  l=Long(1)+l;
  Long a(3);
  if(a.mod_pow(l>>1,l)==l-Long(1)){return true;}
  return true;
}
*/


#endif /*pepin_test_hpp*/
