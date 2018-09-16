#ifndef seisuu_hpp
#define seisuu_hpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
const ll E=1e18+7;
const ll MOD=1000000007;
#define F first
#define S second



ll mod_pow(ll a,ll x){
    ll ans=1;
    for(int i=0;i<63;i++){
        if(x>>i&1){ans*=a; ans%=MOD;}
        a*=a;
        a%=MOD;
    }
    return ans;
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

ll R(ll a){
    return mod_pow(a,MOD-2);
}

ll factorial(ll n){
    ll ret=1;
    for(int i=2;i<=n;i++){
        ret*=i%MOD;
        ret%=MOD;
    }
    return ret;
}

ll c(ll n,ll k){
  if(n<k){return 0;}
    return factorial(n)*R(factorial(n-k))%MOD*R(factorial(k))%MOD;
}

ll Lucas_C(ll n,ll m,ll p){
  ll ret=1;
  while(n>0 || m>0){
    ret*=c(n%p,m%p);
    ret%=p;
    n/=p; m/=p;
  }
  return ret;
}

ll gcd(ll a,ll b){
  if(a%b==0){return b;}
  return gcd(b,a%b);
}

ll lcm(ll a,ll b){
  return a/gcd(a,b)*b;
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
  assert(mod>0);
  a%=mod;
  if(a<0){a+=mod;}
  assert(gcd(a,mod)==1);
  assert(a!=0);
  if(a==1){return 1;}
  ll phi=Phi(mod);
  assert(mod_pow(a,phi,mod)==1);
  for(ll i=2;i*i<=phi;i++){
    while(phi%i==0 && mod_pow(a,phi/i,mod)==1){phi/=i;}
  }
  return phi;
}

pll Ex_Euc(ll a,ll b){
  if(b==0){return {1,0};}
  pll ret=Ex_Euc(b,a%b);
  ret.F-=a/b*ret.S;
  return {ret.S,ret.F};
}

bool prime(ll p){
  for(int i=2;i*i<=p;i++){
    if(p%i==0){return false;}
  }
  return true;
}

vector<ll> mk_prime(ll mx){
  vector<ll> p={2};
  for(int i=3;i<=mx;i++){
    bool j=true;
    for(int t=0;p[t]*p[t]<=i;t++){
      if(i%p[t]==0){j=false; break;}
    }
    if(j){p.push_back(i);}
  }
  return p;
}


ll Stirling(ll n,ll k){
  ll ret=0;
  for(ll i=1;i<=k;i++){
    if((k-i)%2){ret-=c(k,i)*mod_pow(i,n)%MOD;}
    else{ret+=c(k,i)*mod_pow(i,n)%MOD;}
    ret%=MOD;
  }
  ret*=R(factorial(k));
  ret%=MOD;
  if(ret<0){ret+=MOD;}
  return ret;
}

//高速化したい場合はfactorialをメモ化する
ll Bell(ll n,ll k){
  ll ret=0;
  for(ll i=1;i<=k;i++){ret+=Stirling(n,i); ret%=MOD;}
  return ret;
}


vector<vector<ll>> mk_c(){
  ll mx=50;
  vector<vector<ll>> c(mx+1,vector<ll>(mx+1,0));
  for(ll i=0;i<=mx;i++){
    c[i][i]=1;
    c[i][0]=1;
    for(ll t=1;t<i;t++){
      c[i][t]=c[i-1][t-1]+c[i-1][t];
    }
  }
  return c;
}

#endif /*seisuu_hpp*/
