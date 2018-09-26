#ifndef comb_hpp
#define comb_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second

class comb{
private:
    ll mod;
    ll mx;
    vector<ll> F;
    
public:
    comb(ll mod=1000000007,ll mx=100000):mod(mod),mx(mx){
        mk_F();
    }
    
    ll mod_pow(ll a,ll x){
        a%=mod;
        ll ans=1;
        for(int i=0;i<63;i++){
            if(x>>i&1){ans*=a; ans%=mod;}
            a*=a;
            a%=mod;
        }
        return ans;
    }
    
    pll Ex_gcd(ll a,ll b){
        if(b==0){return {1,0};}
        pll ret=Ex_gcd(b,a%b);
        ret.F-=a/b*ret.S;
        return {ret.S,ret.F};
    }
    
    ll prime_R(ll a){
        return mod_pow(a,mod-2);
    }
    
    ll R(ll a){
        ll ret=Ex_gcd(a,mod).F;
        ret%=mod;
        if(ret<0){ret+=mod;}
        return ret;
    }
    
    void mk_F(){
        F={1};
        ll a=1;
        for(ll i=1;i<=mx;i++){
            a*=i;
            a%=mod;
            F.push_back(a);
        }
    }
    
    ll c(ll n,ll k){
        if(n<k){return 0;}
        if(n==k || k==0){return 1;}
        return F[n]*R(F[n-k])%mod*R(F[k])%mod;
    }
    
    //mod must be prime
    ll Lucas_C(ll n,ll m){
        ll ret=1;
        while(n>0 || m>0){
            ret*=c(n%mod,m%mod);
            ret%=mod;
            n/=mod; m/=mod;
        }
        return ret;
    }
    
    ll Stirling(ll n,ll k){
        ll ret=0;
        for(ll i=1;i<=k;i++){
            if((k-i)%2){ret-=c(k,i)*mod_pow(i,n)%mod;}
            else{ret+=c(k,i)*mod_pow(i,n)%mod;}
            ret%=mod;
        }
        ret*=R(F[k]);
        ret%=mod;
        if(ret<0){ret+=mod;}
        return ret;
    }
    
    ll Bell(ll n,ll k){
        ll ret=0;
        for(ll i=1;i<=k;i++){ret+=Stirling(n,i); ret%=mod;}
        return ret;
    }
};



#endif /*comb_hpp*/
