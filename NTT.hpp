#ifndef NTT_hpp
#define NTT_hpp

#include "Mod_Int.hpp"
#include "Garner.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

//2^25*5+1
template<long long mod=167772161,long long primitive_root=3>
class NTT{
private:
    typedef Mod_Int<mod> Int;
    
    ll bit_size(ll a){
        for(int i=0;i<63;i++){
            if(a<=(1LL<<i)){return 1LL<<i;}
        }
        return -1;
    }
    
    //係数,x1,答え
    vector<Int> & FFT(const vector<Int> &a,ll s,ll d,Int x,vector<Int> &ret){
        if(d==a.size()){
            ret[0]=a[s];
            return ret;
        }
        ll size=a.size()/d/2;
        vector<Int> A(size);
        vector<Int> B(size);
        FFT(a,s,d*2,x*x,A);
        FFT(a,s+d,d*2,x*x,B);
        Int k(1);
        for(int i=0;i<ret.size();i++,k*=x){
            ret[i]=A[i%size]+B[i%size]*k;
        }
        return ret;
    }
    
public:
    vector<Int> & FFT(vector<Int> &a,vector<Int> &ret){
        ll S=a.size();
        ll size=bit_size(a.size());
        a.resize(size,0);
        ret.resize(size);
        a.resize(S);
        return FFT(a,0,1,Int(primitive_root).mod_pow_equal((mod-1)/size),ret);
    }
    
    vector<Int> & test(vector<Int> a,vector<Int> &ret){
        const ll size=bit_size(a.size());
        a.resize(size,0);
        ret.resize(size);
        Int R(primitive_root); R.mod_pow_equal((mod-1)/size);
        FFT(a,0,1,R,ret);
        FFT(ret,0,1,R,a);
        ll t=0;
        for(int i=0;i<a.size();i++,t--){
            if(t<0){t+=size;}
            ret[i]=a[t]/size;
        }
        return ret;
    }
    
    vector<Int> & Multiplication(vector<Int> &a,vector<Int> &b,vector<Int> &ret){
        ll asize=a.size(),bsize=b.size();
        ll size=bit_size(asize+bsize);
        vector<Int> A(size),B(size);
        a.resize(size,0);
        b.resize(size,0);
        ret.resize(size);
        Int R(primitive_root); R.mod_pow_equal((mod-1)/size);
        FFT(a,0,1,R,A);
        FFT(b,0,1,R,B);
        for(int i=0;i<size;i++){A[i]*=B[i];}
        FFT(A,0,1,R,B);
        ll t=0;
        for(int i=0;i<size;i++,t--){
            if(t<0){t+=size;}
            ret[i]=B[t]/size;
        }
        a.resize(asize);
        b.resize(bsize);
        return ret;
    }
};




//a.size()+b.size()<2^23 8*10^6<2^23
vector<ll> & NTT_Multiplication(const vector<ll> &a,const vector<ll> &b,const ll &mod,vector<ll> &ret){
    NTT<167772161,3> ntt1;
    NTT<469762049,3> ntt2;
    NTT<1224736769,3> ntt3;
    vector<Mod_Int<167772161>> a1(a.size());
    vector<Mod_Int<469762049>> a2(a.size());
    vector<Mod_Int<1224736769>> a3(a.size());
    vector<Mod_Int<167772161>> b1(a.size());
    vector<Mod_Int<469762049>> b2(a.size());
    vector<Mod_Int<1224736769>> b3(a.size());
    vector<Mod_Int<167772161>> ret1(a.size());
    vector<Mod_Int<469762049>> ret2(a.size());
    vector<Mod_Int<1224736769>> ret3(a.size());
    for(int i=0;i<a.size();i++){
        a1[i]=a[i]; a2[i]=a[i]; a3[i]=a[i];
    }
    for(int i=0;i<b.size();i++){
        b1[i]=b[i]; b2[i]=b[i]; b3[i]=b[i];
    }
    ntt1.Multiplication(a1,b1,ret1);
    ntt2.Multiplication(a2,b2,ret2);
    ntt3.Multiplication(a3,b3,ret3);
    ret.resize(ret1.size());
    for(int i=0;i<ret1.size();i++){
        ret[i]=Garnerll({ret1[i].a,ret2[i].a,ret3[i].a},{167772161,469762049,1224736769},mod);
    }
    return ret;
}




#endif /*NTT_hpp*/


