#ifndef string_hash_hpp
#define string_hash_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second


class string_hash{
private:
    typedef long long int ll;
    typedef unsigned long long int ull;
    typedef unsigned long ul;
    typedef vector<ull> Hash;
    
    const ull mod;
    const ull roll;
    Hash H;
    string W;
    
    ull mod_pow(ull a,ull x){
        a%=mod;
        ll ans=1;
        while(x>0){
            if(x&1){ans*=a; ans%=mod;}
            a*=a; a%=mod;
            x>>=1;
        }
        return ans;
    }
    
    pll Ex_gcd(ll a,ll b){
        if(b==0){return {1,0};}
        pll ret=Ex_gcd(b,a%b);
        ret.F-=a/b*ret.S;
        return {ret.S,ret.F};
    }
    
    ull R(ull a){
        ll ret=Ex_gcd(a,mod).F;
        ret%=mod;
        if(ret<0){ret+=mod;}
        return ret;
    }
    
    void mk_hash(){
        H[0]=W[0];
        for(int i=1;i<H.size();i++){
            H[i]=H[i-1]*roll%mod+W[i];
            H[i]%=mod;
        }
    }
    
public:
    //乱数を使って初期化するべき?
    string_hash(const string &W={},ull mod=1000000007,ull roll=65537):W(W),mod(mod),roll(roll),H(W.size()){
        mk_hash();
    }
    
    void push_back(const string &A){
        ull d=H.size();
        H.resize(d+A.size());
        W.resize(d+A.size());
        for(ull i=d;i<H.size();i++){
            W[i]=A[i-d];
            H[i]=W[i];
            if(i!=0){
                H[i]+=H[i-1]*roll%mod;
            }
            H[i]%=mod;
        }
    }
    
    void push_back(char c){
        W.push_back(c);
        H.push_back(c);
        if(H.size()==1){return;}
        H[H.size()-1]+=H[H.size()-2]*roll%mod;
        H[H.size()-1]%=mod;
    }
    
    unsigned long size() const {return W.size();}
    
    const ull & MOD() const {return mod;}
    
    const ull & ROLL() const {return roll;}
    
    ull & operator [] (const ul &s){
        assert(s<H.size());
        return H[s];
    }
    
    bool operator == (string_hash &S) const {
        return S.size()==H.size() && H[H.size()-1]==S[H.size()-1];
    }
    
    //共通の長さ、初めて違う文字のインデックス
    unsigned long same(string_hash &W) const {
        ul r=min(H.size(),W.size())-1;
        if(H[r]==W[r]){return r+1;}
        ul l=0;
        while(r-l>3){
            ul m=l+(r-l)/2;
            if(W[m]!=H[m]){r=m;}
            else{l=m+1;}
        }
        for(ul i=l;i<r;i++){
            if(W[i]!=H[i]){return i;}
        }
        return r;
    }
    
    //[l,r)
    ull hash(ul l,ul r){
        assert(l<r && r<=H.size());
        if(l==0){return H[r-1];}
        return (mod+H[r-1]-H[l-1]*mod_pow(roll,r-l)%mod)%mod;
    }
    
    ull merge_hash(ull hash,ul Long){
        return (H[H.size()-1]*mod_pow(roll,Long)%mod+hash)%mod;
    }
};



template<typename T>
class vector_hash{
private:
    typedef long long int ll;
    typedef unsigned long long int ull;
    typedef unsigned long ul;
    typedef vector<ull> Hash;
    
    const ull mod;
    const ull roll;
    Hash H;
    vector<T> W;
    
    ull mod_pow(ull a,ull x){
        a%=mod;
        ll ans=1;
        while(x>0){
            if(x&1){ans*=a; ans%=mod;}
            a*=a; a%=mod;
            x>>=1;
        }
        return ans;
    }
    
    pll Ex_gcd(ll a,ll b){
        if(b==0){return {1,0};}
        pll ret=Ex_gcd(b,a%b);
        ret.F-=a/b*ret.S;
        return {ret.S,ret.F};
    }
    
    ull R(ull a){
        ll ret=Ex_gcd(a,mod).F;
        ret%=mod;
        if(ret<0){ret+=mod;}
        return ret;
    }
    
    void mk_hash(){
        H[0]=W[0]%mod;
        for(int i=1;i<H.size();i++){
            H[i]=H[i-1]*roll%mod+W[i]%mod;
            H[i]%=mod;
        }
    }
    
public:
    //乱数を使って初期化するべき?
    vector_hash(const vector<T> &W={},ull mod=1000000007,ull roll=65537):W(W),mod(mod),roll(roll),H(W.size()){
        mk_hash();
    }
    
    void push_back(const vector<T> &A){
        ull d=H.size();
        H.resize(d+A.size());
        W.resize(d+A.size());
        for(ull i=d;i<H.size();i++){
            W[i]=A[i-d];
            H[i]=W[i]%mod;
            if(i!=0){
                H[i]+=H[i-1]*roll%mod;
            }
            H[i]%=mod;
        }
    }
    
    void push_back(T c){
        W.push_back(c);
        H.push_back(c)%mod;
        if(H.size()==1){return;}
        H[H.size()-1]+=H[H.size()-2]*roll%mod;
        H[H.size()-1]%=mod;
    }
    
    unsigned long size() const {return W.size();}
    
    const ull & MOD() const {return mod;}
    
    const ull & ROLL() const {return roll;}
    
    T & operator [] (const ul &s){
        assert(s<H.size());
        return H[s];
    }
    
    bool operator == (vector_hash &S) const {
        return S.size()==H.size() && H[H.size()-1]==S[H.size()-1];
    }
    
    //共通の長さ、初めて違う文字のインデックス
    unsigned long same(vector_hash &W) const {
        ul r=min(H.size(),W.size())-1;
        if(H[r]==W[r]){return r+1;}
        ul l=0;
        while(r-l>3){
            ul m=l+(r-l)/2;
            if(W[m]!=H[m]){r=m;}
            else{l=m+1;}
        }
        for(ul i=l;i<r;i++){
            if(W[i]!=H[i]){return i;}
        }
        return r;
    }
    
    //[l,r)
    ull hash(ul l,ul r){
        assert(l<r && r<=H.size());
        if(l==0){return H[r-1];}
        return (mod+H[r-1]-H[l-1]*mod_pow(roll,r-l)%mod)%mod;
    }
    
    ull merge_hash(ull hash,ul Long){
        return (H[H.size()-1]*mod_pow(roll,Long)%mod+hash)%mod;
    }
};





/*
class string_hash{
private:
    typedef unsigned long long int ull;
    typedef unsigned long ul;
    const ull mod;
    const ull B;
    string S;
    vector<ull> H;
    
    ull mod_pow(const ull &a,ull x,const ull &mod) const {
        if(a==0){return 0;}
        ull ret=1;
        ull k=a;
        while(x>0){
            if(x&1){ret*=k; ret%=mod;}
            k*=k; k%=mod;
            x>>=1;
        }
        return ret;
    }
    
    vector<ull> hash(const string &s) const {
        ull h=0;
        vector<ull> ret(s.size());
        for(int i=0;i<s.size();i++){
            h+=s[i]; //"NULL"を文字として数えるなら+1をする
            h*=B;
            h%=mod;
            ret[i]=h;
        }
        return ret;
    }
    
    vector<ull> & hash(const string &s,vector<ull> &ret) const {
        ret.resize(s.size());
        ull h=0;
        for(int i=0;i<s.size();i++){
            h+=s[i]; //"NULL"を文字として数えるなら+1をする
            h*=B;
            h%=mod;
            ret[i]=h;
        }
        return ret;
    }
    
public:
    string_hash(const string &S={},const ull &mod=1000000007,const ull &B=65537):S(S),mod(mod),B(B){
        hash(S,H);
    }
    
    unsigned long size() const {return H.size();}
    
    const ull & operator [] (const unsigned long &s) const {
        assert(s<H.size());
        return H[s];
    }
    
    const ull & MOD() const {return mod;}
    
    const ull & ROLL() const {return B;}
    
    //共通の長さ、初めて違う文字のインデックス
    unsigned long same(const string_hash &W) const {
        ul r=min(H.size(),W.size());
        ul l=0;
        while(r-l>5){
            ul m=l+(r-l)/2;
            if(W[m]!=H[m]){r=m+1;}
            else{l=m;}
        }
        for(ul i=l;i<r;i++){
            if(W[i]!=H[i]){return i;}
        }
        return r;
    }
    
    ull merge_hash(const string_hash &W) const {
        assert(W.MOD()==mod && W.ROLL()==B);
        ull k=W[W.size()-1]*mod_pow(B,H.size(),mod);
        k%=mod;
        if(H.size()!=0){
            k+=H[H.size()-1];
            k%=mod;
        }
        return k;
    }
    
    ull merge_hash(const ull &hs) const {
        ull k=hs*mod_pow(B,H.size(),mod);
        k%=mod;
        if(H.size()!=0){
            k+=H[H.size()-1];
            k%=mod;
        }
        return k;
    }
    
    bool operator == (const string_hash &W) const {
        assert(W.MOD()==mod && W.ROLL()==B);
        return W.size()==H.size() && (W.size()==0 || W[W.size()-1]==H[H.size()-1]);
    }
};
*/


#endif /*string_hash_hpp*/
