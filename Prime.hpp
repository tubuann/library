#ifndef Prime_hpp
#define Prime_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

class Prime{
private:
  typedef unsigned long ul;
  typedef unsigned long long int ull;
  typedef long long int ll;
  typedef pair<ll,ll> pll;
  #define F first
  #define S second
  const ll MOD=1000000007;
  
public:
  bool is_prime(ll p){
    assert(p>0);
    if(p==1){return false;}
    for(int i=2;i*i<=p;i++){
      if(p%i==0){return false;}
    }
    return true;
  }

  vector<bool> Sieve_of_Eratosthenes(ll mx){
    vector<bool> sieve(mx+1,true);
    sieve[0]=sieve[1]=false;
    for(ul i=2;i*i<=mx;i++){
      if(!sieve[i]){continue;}
      for(ul t=2;i*t<=mx;t++){
	sieve[i*t]=false;
      }
    }
    return sieve;
  }

  ll mod_pow(ll a,ll x,ll mod){
    a%=mod;
    ll ans=1;
    for(int i=0;i<63;i++){
      if(x>>i&1){ans*=a; ans%=mod;}
      a*=a;
      a%=mod;
    }
    return ans;
  }

  ll gcd(ll a,ll b){
    if(a%b==0){return b;}
    return gcd(b,a%b);
  }

  ll lcm(ll a,ll b){
    return a/gcd(a,b)*b;
  }

  pll Ex_Euc(ll a,ll b){
    if(b==0){return {1,0};}
    pll ret=Ex_Euc(b,a%b);
    ret.F-=a/b*ret.S;
    return {ret.S,ret.F};
  }

  ll Phi(ll a){
    ll ans=a;
    vector<ll> p;
    for(ll i=2;i*i<=a;i++){
      if(a%i==0){
	p.push_back(i);
	while(a%i==0){
	  a/=i;
	}
      }
    }
    if(a!=1){p.push_back(a);}
    for(int i=0;i<p.size();i++){
      ans/=p[i];
      ans*=p[i]-1;
    }
    return ans;
  }

  ll order(ll a,ll mod){
    assert(mod>1);
    a%=mod;
    if(a<0){a+=mod;}
    assert(a!=0);
    assert(gcd(a,mod)==1);
    ll phi=Phi(mod);
    ll k=phi;
    assert(mod_pow(a,phi,mod)==1);
    for(ll i=2;i*i<=k;i++){
      while(k%i==0){
	if(mod_pow(a,phi/i,mod)==1){phi/=i;}
	k/=i;
      }
    }
    if(k!=1 && mod_pow(a,phi/k,mod)==1){phi/=k;}
    return phi;
  }
};



#endif /*Prime_hpp*/
