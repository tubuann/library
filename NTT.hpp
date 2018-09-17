#ifndef NTT_hpp
#define NTT_hpp

#include "LongLong.hpp"
#include "Garner.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

//LongLong
class NTT{
private:
  typedef LongLong LL;
  vector<LL> primes;
  void F(LL &,const LL &,const LL &);
    
public:
  NTT(const vector<LL> &primes={1000002139,1000002149,1000002161,1000002173,1000002187,1000002193,1000002233,1000002239,1000002277,1000002307,1000002359,1001432189,1001432219}):primes(primes){}
    
  LL solve(const LL &a,const LL &b,const LL &mod){
    vector<LL> A(primes.size()),B(primes.size());
    for(int i=0;i<primes.size();i++){
      A[i]=a%primes[i];
      B[i]=b%primes[i];
    }
    for(int i=0;i<primes.size();i++){
      F(A[i],B[i],primes[i]);
    }
    return Garner(A,primes)%mod;
  }
};



//long long
class NTTll{
private:
  typedef long long int ll;
  vector<ll> primes;
  void F(ll &,const ll &,const ll &);
    
public:
  NTTll(const vector<ll> &primes={1000002139,1000002149,1000002161,1000002173,1000002187,1000002193,1000002233,1000002239,1000002277,1000002307,1000002359,1001432189,1001432219}):primes(primes){}
    
  ll solve(const ll &a,const ll &b,const ll &mod){
    vector<ll> A(primes.size()),B(primes.size());
    for(int i=0;i<primes.size();i++){
      A[i]=a%primes[i];
      B[i]=b%primes[i];
    }
    for(int i=0;i<primes.size();i++){
      F(A[i],B[i],primes[i]);
    }
    return Garnerll(A,primes,mod);
  }
};



#endif /*NTT_hpp*/

//LongLong
/*
//sum
void NTT::F(LL &a,const LL &b,const LL &mod){
    a+=b;
    a%=mod;
}
*/

//long long
/*
//sum
void NTTll::F(ll &a,const ll &b,const ll &mod){
    a+=b;
    a%=mod;
}
*/