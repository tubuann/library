#ifndef DLP_hpp
#define DLP_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T=long long>
struct BSGS{
    ll Or;
    ll M_SIZE=100000;
    T mod;
    unordered_map<T,T> M;
    T Root;
    T Inv;
    
    void build(){
        T e=1;
        for(int i=0;i<M_SIZE && M.count(e)==0;i++,e=e*Root%mod){M[e]=i;}
        Inv=mod_pow(R(Root),M_SIZE);
    }
    
    pll Ex_gcd(ll a,ll b){
        if(b==0){return {1,0};}
        pll ret=Ex_gcd(b,a%b);
        ret.F-=a/b*ret.S;
        return {ret.S,ret.F};
    }
    
    ll mod_pow(ll a,ll x){
        a%=mod;
        ll ans=1;
        while(x>0){
            if(x&1){ans*=a; ans%=mod;}
            a*=a;
            a%=mod;
            x>>=1;
        }
        return ans;
    }
    
    ll R(ll a){
        ll ret=Ex_gcd(a,mod).F;
        ret%=mod;
        if(ret<0){ret+=mod;}
        return ret;
    }
    
    ll LOG(T a){
        for(ll I=0;I<Or;I+=M_SIZE,a=a*Inv%mod){if(M.count(a)){return (I+M[a])%Or;}}
        return -1;
    }
};

struct Pohlig_Hellman{
    ll mod;
    ll Phi;
    vector<ll> E;
    vector<ll> Inv;
    vector<BSGS<ll>> P;
    ll Root;
    ll M_SIZE;
    
    void build(){
        ll K=Phi;
        ll A=1;
        for(ll i=2;i*i<=K;i++){
            ll k=1;
            while(K%i==0){K/=i; k*=i;}
            if(k!=1){
                E.push_back(k);
                Inv.push_back(R(A,k));
                A*=k;
                P.push_back(BSGS<ll>());
                P.back().Or=k;
                P.back().M_SIZE=min(M_SIZE,k);
                P.back().mod=mod;
                P.back().Root=mod_pow(Root,Phi/k);
                P.back().build();
            }
        }
        if(K!=1){
            E.push_back(K);
            Inv.push_back(R(A,K));
            P.push_back(BSGS<ll>());
            P.back().Or=K;
            P.back().M_SIZE=min(M_SIZE,K);
            P.back().mod=mod;
            P.back().Root=mod_pow(Root,Phi/K);
            P.back().build();
        }
    }
    
    pll Ex_gcd(ll a,ll b){
        if(b==0){return {1,0};}
        pll ret=Ex_gcd(b,a%b);
        ret.F-=a/b*ret.S;
        return {ret.S,ret.F};
    }
    
    ll mod_pow(ll a,ll x){
        a%=mod;
        ll ans=1;
        while(x>0){
            if(x&1){ans*=a; ans%=mod;}
            a*=a;
            a%=mod;
            x>>=1;
        }
        return ans;
    }
    
    ll R(ll a,ll mod){
        ll ret=Ex_gcd(a,mod).F;
        ret%=mod;
        if(ret<0){ret+=mod;}
        return ret;
    }
    
    ll gcd(ll a,ll b){
        while(a%b!=0){
            a%=b;
            swap(a,b);
        }
        return b;
    }
    
    ll LOG(ll a){
        ll ans=0;
        ll M=1;
        for(int i=0;i<E.size();i++){
            ll A=P[i].LOG(mod_pow(a,Phi/E[i]));
            assert(A!=-1);
            (A-=ans)%=E[i];
            if(A<0){A+=E[i];}
            (A*=Inv[i])%=E[i];
            ans+=A*M;
            M*=E[i];
        }
        return ans;
    }
    
    ll Order(ll a){
        ll ret=Phi;
        for(int i=0;i<E.size();i++){
            ll A=P[i].LOG(mod_pow(a,Phi/E[i]));
            assert(A!=-1);
            if(A==0){A+=E[i];}
            ret/=gcd(E[i],A);
        }
        return ret;
    }
};



#endif /*DLP_hpp*/
