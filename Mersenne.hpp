#ifndef Mersenne_hpp
#define Mersenne_hpp

#include "LongLong.hpp"
#include "Long.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef LongLong LL;
#define F first
#define S second

bool prime(ll p){
  assert(p>0);
  if(p==1){return false;}
  for(int i=2;i*i<=p;i++){
    if(p%i==0){return false;}
  }
  return true;
}

bool Lucas_test(ll n){
  assert(n%4==3);
  assert(n>=1);
  if(!prime(n)){return false;}
  Long s(3);
  Long mp(1);
  Long d(2);
  mp=mp<<n;
  mp=mp-1;
  for(ll i=1;i<n-1;i++){
    s=s*s-d;
    s=s%mp;
  }
  if(s==Long(0)){return true;}
  return false;
}

bool Lucas_Lehmer_test(ll n){
    assert(n>=1);
    if(!prime(n)){return false;}
    if(n==2){return true;}
    LL s(4);
    LL m(1);
    m<<=n;
    m-=1;
    for(ll i=1;i<n-1;i++){
        s*=s;
        s=(s&m)+(s>>n);
        if(s>=m){s-=m;}
        s-=2;
    }
    if(s==0){return true;}
    return false;
}

bool is_perfect(LL a){
    assert(a[0]==0 && a>0);
    ll p=0;
    for(ll i=0;i<a.size()*32 && a[i]==0;i++){p++;}
    a>>=p;
    p++;
    if(a!=(LL(1)<<p)-1){return false;}
    return Lucas_Lehmer_test(p);
}



#endif /*Mersenne_hpp*/
