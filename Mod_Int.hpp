#ifndef Mod_Int_hpp
#define Mod_Int_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
#define F first
#define S second



template<long long int mod=1000000007>
struct Mod_Int{
    typedef long long int ll;
    typedef pair<ll,ll> pll;
    typedef Mod_Int<mod> M;
    ll a;
    
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
    
    Mod_Int(ll A):a(A){
        a%=mod;
        if(a<0){a+=mod;}
    }
    
    Mod_Int(const M &b):a(b.a){}
    
    M & operator += (const M &b){
        a+=b.a;
        if(a>=mod){a-=mod;}
        return *this;
    }
    
    M operator + (const M &b) const {
        M c=*this;
        return c+=b;
    }
    
    M & operator -= (const M &b){
        a-=b.a;
        if(a<0){a+=mod;}
        return *this;
    }
    
    M operator - (const M &b) const {
        M c=*this;
        return c-=b;
    }
    
    M & operator *= (const M &b){
        (a*=b.a)%=mod;
        return *this;
    }
    
    M operator * (const M &b) const {
        M c=*this;
        return c*=b;
    }
    
    M & operator /= (const M &b){
        (a*=R(b.a))%=mod;
        return *this;
    }
    
    M operator / (const M &b) const {
        M c=*this;
        return c/=b;
    }
    
    M & mod_pow_equal(ll x){
        ll ans=1;
        while(x>0){
            if(x&1){ans*=a; ans%=mod;}
            a*=a;
            a%=mod;
            x>>=1;
        }
        a=ans;
        return *this;
    }
    
    M & mod_pow(ll x){
        M c(a);
        return c.mod_pow_equal(x);
    }
    
    bool operator == (const M &b) const {return a==b.a;}
    
    bool operator != (const M &b) const {return a!=b.a;}
    
    bool operator <= (const M &b) const {return a<=b.a;}
    
    bool operator < (const M &b) const {return a<b.a;}
    
    bool operator > (const M &b) const {return a>b.a;}
    
    bool operator >= (const M &b) const {return a>=b.a;}
    
    M & operator = (const M &b){
        a=b.a;
        return *this;
    }
    
    M & operator = (const ll &b){
        (a=b)%=mod;
        if(a<0){a+=mod;}
        return *this;
    }
};


#endif /*Mod_Int_hpp*/
