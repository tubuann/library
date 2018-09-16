#ifndef Chinese_remainder_theorem_hpp
#define Chinese_remainder_theorem_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second

class Chinese_remainder_theorem{
private:
  vector<ll> mod;
  vector<ll> a;
  ll M;

  ll gcd(ll a,ll b){
    if(a%b==0){return b;}
    return gcd(b,a%b);
  }

  pll Ex_gcd(ll a,ll b){
    if(b==0){return {1,0};}
    pll A=Ex_gcd(b,a%b);
    swap(A.F,A.S);
    A.S-=a/b*A.F;
    return {A.F,A.S};
  }

public:
  Chinese_remainder_theorem(vector<ll> m={},vector<ll> a={}):a(a){
    assert(m.size()==a.size());
    M=1;
    for(int i=0;i<m.size();i++){
      assert(gcd(M,m[i])==1);
      M*=m[i];
    }
    mod=m;
  }

  void add(ll m,ll A){
    assert(gcd(M,m)==1);
    M*=m;
    mod.push_back(m);
    a.push_back(A);
  }

  ll solve(){
    ll ans=0;
    for(int i=0;i<mod.size();i++){
      pll k=Ex_gcd(mod[i],M/mod[i]);
      ans+=a[i]%mod[i]*M/mod[i]*k.S;
      ans%=M;
    }
    return ans;
  }

  ll Mod(){return M;}
};




#endif /*Chinese_remainder_theorem_hpp*/
