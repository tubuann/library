#ifndef BigInt_hpp
#define BigInt_hpp

#include "Mod_Int.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<unsigned long long N=1000000000>
class BigInt{
public:
    typedef unsigned long long ull;
    
    template<long long mod=2483027969,long long primitive_root=3>
    class NTT{
    private:
        typedef Mod_Int<mod> Int;
        vector<Int> X;
        
        inline void mk_x(const ll &s){
            ll size=s/2;
            if(X.size()==size){return;}
            Int R(primitive_root); R.mod_pow_equal((mod-1)/s);
            X.resize(size);
            X[0]=1;
            for(int i=1;i<size;i++){(X[i]=X[i-1])*=R;}
        }
        
        void FFT(vector<Int> &a,const ll &size){
            for(int i=0,j=1;j+1<size;j++){
                for(ll k=size>>1;k>(i^=k);k>>=1);
                if(i>j){swap(a[i],a[j]);}
            }
            for(int i=1;i<size;i<<=1){
                for(int j=0;j<size;j+=i<<1){
                    for(int k=0;k<i;k++){
                        Int z=a[i+j+k]*X[size/i/2*k];
                        a[i+j+k]=a[j+k]-z;
                        a[j+k]+=z;
                    }
                }
            }
        }
        
    public:
        void Multiplication(vector<Int> &a,vector<Int> &b){
            ll size=1;
            while(size<a.size()+b.size()-1){size<<=1;}
            mk_x(size);
            a.resize(size,0);
            b.resize(size,0);
            FFT(a,size);
            FFT(b,size);
            for(int i=0;i<size;i++){b[i]*=a[i];}
            FFT(b,size);
            Int inv(1); inv/=size;
            (a[0]=b[0])*=inv;
            for(int i=1;i<size;i++){
                (a[i]=b[size-i])*=inv;
            }
        }
    };
    
    static const ull MX=N-1;
    
    deque<ull> A;
    bool sign;
    
    inline void clean(){
        while(A.size() && A.back()==0){A.pop_back();}
    }
    
    //greater than abs
    inline bool GTA(const BigInt<N> &B) const {
        if(A.size()!=B.size()){return A.size()>B.size();}
        for(int i=A.size()-1;i>=0;i--){
            if(A[i]!=B.A[i]){return A[i]>B.A[i];}
        }
        return false;
    }
    
    //greater than or equal abs
    inline bool GTEA(const BigInt<N> &B) const {
        if(A.size()!=B.size()){return A.size()>B.size();}
        for(int i=A.size()-1;i>=0;i--){
            if(A[i]!=B.A[i]){return A[i]>B.A[i];}
        }
        return true;
    }
    
    //less than abs
    inline bool LTA(const BigInt<N> &B) const {
        if(A.size()!=B.size()){return A.size()<B.size();}
        for(int i=A.size()-1;i>=0;i--){
            if(A[i]!=B.A[i]){return A[i]<B.A[i];}
        }
        return false;
    }
    
    ////less than or equal abs
    inline bool LTEA(const BigInt<N> &B) const {
        if(A.size()!=B.size()){return A.size()<B.size();}
        for(int i=A.size()-1;i>=0;i--){
            if(A[i]!=B.A[i]){return A[i]<B.A[i];}
        }
        return true;
    }
    
    //equal abs
    inline bool EA(const BigInt<N> &B) const {return A==B.A;}
    
    inline bool GTEA(const BigInt<N> &B,int a) const {
        if(A.size()!=B.size()+a){return A.size()>B.size()+a;}
        for(int i=(int)B.size()-1;i>=0;i--){
            if(A[i+a]!=B.A[i]){return A[i+a]>B.A[i];}
        }
        return true;
    }
    
    inline bool MNS(const BigInt<N> &B,int a){
        if(!GTEA(B,a)){return false;}
        bool k=false;
        for(int i=0;i<B.size();i++){
            A[i+a]+=N;
            A[i+a]-=B.A[i];
            if(k){A[i+a]--;}
            if(A[i+a]>=N){A[i+a]-=N; k=false;}
            else{k=true;}
        }
        if(k){
            for(ll i=B.size();i+a<A.size();i++){
                if(A[i+a]==0){A[i+a]=N-1;}
                else{A[i+a]--; break;}
            }
        }
        clean();
        return true;
    }
    
    
    
    
    BigInt(const deque<ull> &A,const bool &sign):A(A),sign(sign){clean();}
    
    BigInt(const BigInt<N> &C):A(C.A),sign(C.sign){}
    
    BigInt(ll a=0){
        sign=(a>=0);
        if(a<0){a*=-1;}
        while(a>0){A.push_back(a%N); a/=N;}
        clean();
    }
    
    //10進10000進変換
    BigInt(string s):A((s.size()+3)/4,0),sign(true){
        reverse(s.begin(),s.end());
        if(s.back()=='-'){sign=false; s.pop_back();}
        for(int i=0;i<s.size();i+=4){
            for(int t=0;t<4;t++){
                A[i/4]*=10;
                if(i+3-t>=s.size()){continue;}
                A[i/4]+=s[i+3-t]-'0';
            }
        }
        clean();
    }
    
    bool operator == (const BigInt<N> &B) const {
        return sign==B.sign && A==B.A;
    }
    
    bool operator > (const BigInt<N> &B) const {
        if(sign!=B.sign){return sign;}
        if(sign){return GTA(B);}
        return LTA(B);
    }
    
    bool operator < (const BigInt<N> &B) const {
        if(sign!=B.sign){return B.sign;}
        if(sign){return LTA(B);}
        return GTA(B);
    }
    
    bool operator >= (const BigInt<N> &B) const {
        if(sign!=B.sign){return sign;}
        if(sign){return GTEA(B);}
        return LTEA(B);
    }
    
    bool operator <= (const BigInt<N> &B) const {
        if(sign!=B.sign){return B.sign;}
        if(sign){return LTEA(B);}
        return GTEA(B);
    }
    
    BigInt<N>& operator = (const BigInt<N> &B){sign=B.sign; A=B.A; return *this;}
    
    BigInt<N>& operator <<= (int a){
        assert(a<32);
        for(auto &i:A){i<<=a;}
        for(int i=0;i<A.size();i++){
            if(i+1==A.size() && A[i]>=N){A.push_back(A[i]/N); A[i]%=N;}
            else if(A[i]>=N){A[i+1]+=A[i]/N; A[i]%=N;}
        }
        clean();
        return *this;
    }
    
    BigInt<N>& operator += (const BigInt<N> &B){
        if(sign==B.sign){
            while(A.size()<B.size()+1){A.push_back(0);}
            for(int i=0;i<B.size();i++){
                A[i]+=B.A[i];
                if(A[i]>=N){A[i+1]++; A[i]-=N;}
            }
            for(int i=B.size();i<A.size();i++){
                if(A[i]>=N){A[i+1]++; A[i]-=N;}
                else{break;}
            }
            clean();
            return *this;
        }
        else if(EA(B)){
            sign=true;
            A.clear();
            return *this;
        }
        else if(GTA(B)){
            bool k=false;
            for(int i=0;i<B.size();i++){
                A[i]+=N;
                A[i]-=B.A[i];
                if(k){A[i]--;}
                if(A[i]>=N){A[i]-=N; k=false;}
                else{k=true;}
            }
            if(k){
                for(ll i=B.size();i<A.size();i++){
                    if(A[i]==0){A[i]=N-1;}
                    else{A[i]--; break;}
                }
            }
            clean();
            return *this;
        }
        sign=B.sign;
        bool k=false;
        while(A.size()<B.size()){A.push_back(0);}
        for(int i=0;i<A.size();i++){
            A[i]=B.A[i]+N-A[i];
            if(k){A[i]--;}
            if(A[i]>=N){A[i]-=N; k=false;}
            else{k=true;}
        }
        clean();
        return *this;
    }
    
    BigInt<N>& operator -= (const BigInt<N> &B){
        if(sign!=B.sign){
            while(A.size()<B.size()+1){A.push_back(0);}
            for(int i=0;i<B.size();i++){
                A[i]+=B.A[i];
                if(A[i]>=N){A[i+1]++; A[i]-=N;}
            }
            for(int i=B.size();i<A.size();i++){
                if(A[i]>=N){A[i+1]++; A[i]-=N;}
                else{break;}
            }
            clean();
            return *this;
        }
        else if(EA(B)){
            sign=true;
            A.clear();
            return *this;
        }
        else if(GTA(B)){
            bool k=false;
            for(int i=0;i<B.size();i++){
                A[i]+=N;
                A[i]-=B.A[i];
                if(k){A[i]--;}
                if(A[i]>=N){A[i]-=N; k=false;}
                else{k=true;}
            }
            if(k){
                for(ll i=B.size();i<A.size();i++){
                    if(A[i]==0){A[i]=N-1;}
                    else{A[i]--; break;}
                }
            }
            clean();
            return *this;
        }
        sign=!sign;
        bool k=false;
        while(A.size()<B.size()){A.push_back(0);}
        for(int i=0;i<A.size();i++){
            A[i]=B.A[i]+N-A[i];
            if(k){A[i]--;}
            if(A[i]>=N){A[i]-=N; k=false;}
            else{k=true;}
        }
        clean();
        return *this;
    }
    
    
    //二乗にサイズをかけてもオーバーフローしないサイズにすること。
    BigInt<N>& operator *= (const BigInt<N> &B){
        if(!B.sign){sign=!sign;}
        if(A.size()==0){sign=true; return *this;}
        if(B.size()==0){A.clear(); sign=true; return *this;}
        if(B.A.size()==1 && B.A[0]==1){return *this;}
        NTT<2281701377,3> ntt1;
        NTT<2483027969,3> ntt2;
        vector<Mod_Int<2281701377>> a1(A.size());
        vector<Mod_Int<2483027969>> a2(A.size());
        vector<Mod_Int<2281701377>> b1(B.size());
        vector<Mod_Int<2483027969>> b2(B.size());
        for(int i=0;i<A.size();i++){
            a1[i]=A[i];
            a2[i]=A[i];
        }
        for(int i=0;i<B.size();i++){
            b1[i]=B.A[i];
            b2[i]=B.A[i];
        }
        ntt1.Multiplication(a1,b1);
        ntt2.Multiplication(a2,b2);
        A.resize(a1.size()+5);
        for(auto &i:A){i=0;}
        for(int i=0;i<a1.size();i++){
            A[i]=a1[i].a;
            (a2[i]-=A[i])*=827676002;
            A[i]+=a2[i].a*2281701377;
        }
        for(int i=0;i<A.size();i++){
            if(A[i]>=N && A.size()==i+1){A.push_back(A[i]/N); A[i]%=N;}
            else if(A[i]>=N){A[i+1]+=A[i]/N; A[i]%=N;}
        }
        clean();
        return *this;
    }
    
    BigInt<N>& operator /= (const BigInt<N> &B){
        if(LTA(B)){sign=true; A.clear(); return *this;}
        if(!B.sign){sign=!sign;}
        vector<ull> ans(1+A.size()-B.size(),0);
        vector<BigInt<N>> R(32,B);
        for(int i=1;i<32;i++){R[i]<<=i;}
        for(int i=(int)A.size()-(int)B.size();i>=0;i--){
            for(int j=31;j>=0;j--){
                if((ans[i]^(1LL<<j))>=N){continue;}
                ans[i]^=(MNS(R[j],i)?1LL<<j:0);
            }
        }
        A.resize(ans.size());
        for(int i=0;i<ans.size();i++){A[i]=ans[i];}
        clean();
        return *this;
    }
    
    BigInt<N>& operator %= (const BigInt<N> &B){
        if(!B.sign){sign=!sign;}
        if(LTA(B)){return *this;}
        vector<BigInt<N>> R(32,B);
        for(int i=1;i<32;i++){R[i]<<=i;}
        for(int i=(int)A.size()-(int)B.size();i>=0;i--){
            for(int j=31;j>=0;j--){
                if((1LL<<j)>=N){continue;}
                MNS(R[j],i);
            }
        }
        clean();
        return *this;
    }
    
    ll size() const {return A.size();}
};

string show(const BigInt<10000> &A){
    string ans(A.size()*4+10,'0');
    for(int i=0;i<A.size();i++){
        ll k=1;
        for(int t=0;t<4;t++){
            ans[i*4+t]+=(A.A[i]/k)%10;
            k*=10;
        }
    }
    while(ans.size()>1 && ans.back()=='0'){ans.pop_back();}
    if(A.sign==false){ans.push_back('-');}
    reverse(ans.begin(),ans.end());
    return ans;
}


#endif /*BigInt_hpp*/
