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



#endif /*string_hash_hpp*/
