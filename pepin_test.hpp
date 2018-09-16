#ifndef pepin_test_hpp
#define pepin_test_hpp

#include<bits/stdc++.h>
#include "Long.hpp"
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

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



#endif /*pepin_test_hpp*/
