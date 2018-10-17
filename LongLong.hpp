#ifndef LongLong_hpp
#define LongLong_hpp

#include "Mod_Int.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second



class LongLong{
private:
    typedef LongLong LL;
    typedef long long int ll;
    typedef unsigned long long int ull;
    typedef unsigned long ul;
    static const ull MX=1LL<<32;
    static const ull I=MX-1;
    static const ull MI=(1LL<<16)-1;
    static const ll Inv=827676002;
    static const ll A=2281701377;
    bool sign;
    deque<ull> N;
    
    
    
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
    
    
    inline int Sign() const {
        int ret=sign?1:-1;
        if(N.size()==0){ret=0;}
        return ret;
    }
    
    inline void clean(){
        while(N.size()>0 && N[N.size()-1]==0){N.pop_back();}
    }
    
    inline ull node(const ul &i) const {
        assert(i<N.size());
        return (const ull)N[i];
    }
    
    inline ul Size() const {return N.size();}
    
    inline LL reverse() const {return LL(N,!sign);}
    
    inline void resize(ul i){N.resize(i);}
    
public:
    LongLong(const deque<ull> &N={},const bool &sign=true):N(N),sign(sign){clean();}
    
    LongLong(ll n):N({}),sign(true){
        if(n==0){return;}
        if(n<0){n=std::abs(n); sign=false;}
        N.resize(2);
        N[0]=n&I;
        N[1]=n>>32;
        clean();
    }
    
    LongLong(string s):N({}),sign(true){
        std::reverse(s.begin(),s.end());
        bool f=true;
        if(s[s.size()-1]=='-'){s.pop_back(); f=false;}
        LongLong k(1);
        for(ul i=0;i<s.size();i++){
            s[i]-='0';
            if(s[i]){
                (*this)+=k*s[i];
            }
            k*=10;
        }
        sign=f;
    }
    
    ul size(){return N.size();}
    
    bool operator [] (ul K) const {
        ul k=K/32;
        K%=32;
        return N[k]>>K&1;
    }
    
    LongLong & operator = (const LL &L){
        N=L.N;
        sign=L.sign;
        return *this;
    }
    
    bool operator < (const LL &L) const {
        int Ls=L.Sign();
        int Ts=Sign();
        if(Ts<Ls){return true;}
        if(Ts>Ls){return false;}
        if(Ls==0){return false;}
        if(Ls==1){
            if(N.size()<L.Size()){return true;}
            if(N.size()>L.Size()){return false;}
            for(int i=(int)N.size()-1;i>=0;i--){
                if(node(i)<L.node(i)){return true;}
                if(node(i)>L.node(i)){return false;}
            }
            return false;
        }
        if(N.size()<L.Size()){return false;}
        if(N.size()>L.Size()){return true;}
        for(int i=(int)N.size()-1;i>=0;i--){
            if(node(i)<L.node(i)){return false;}
            if(node(i)>L.node(i)){return true;}
        }
        return false;
    }
    
    bool operator > (const LL &L) const {
        return L<*this;
    }
    
    bool operator == (const LL &L) const {
        int Ls=L.Sign();
        int Ts=Sign();
        if(Ls!=Ts){return false;}
        if(Ls==0){return true;}
        if(L.Size()!=N.size()){return false;}
        for(ul i=0;i<N.size();i++){
            if(node(i)!=L.node(i)){return false;}
        }
        return true;
    }
    
    bool operator != (const LL &L) const {
        return !(*this==L);
    }
    
    bool operator <= (const LL &L) const {
        int Ls=L.Sign();
        int Ts=Sign();
        if(Ts<Ls){return true;}
        if(Ts>Ls){return false;}
        if(Ls==0){return true;}
        if(Ls==1){
            if(N.size()<L.Size()){return true;}
            if(N.size()>L.Size()){return false;}
            for(int i=(int)N.size()-1;i>=0;i--){
                if(node(i)<L.node(i)){return true;}
                if(node(i)>L.node(i)){return false;}
            }
            return true;
        }
        if(N.size()<L.Size()){return false;}
        if(N.size()>L.Size()){return true;}
        for(int i=(int)N.size()-1;i>=0;i--){
            if(node(i)<L.node(i)){return false;}
            if(node(i)>L.node(i)){return true;}
        }
        return true;
    }
    
    bool operator >= (const LL &L) const {
        return L<=*this;
    }
    
    LongLong & operator <<= (ul K){
        ul k=K/32;
        K%=32;
        while(k--){
            N.push_front(0);
        }
        if(K==0){return *this;}
        N.resize(N.size()+1);
        for(ll i=N.size()-2;i>=0;i--){
            N[i]<<=K;
            N[i+1]+=N[i]>>32;
            N[i]&=I;
        }
        clean();
        return *this;
    }
    
    LongLong operator << (ul K) const {
        LongLong ret(N,sign);
        return ret<<=K;
    }
    
    LongLong & operator >>= (ul K){
        ul k=K/32;
        K%=32;
        while(N.size()>0 && k--){
            N.pop_front();
        }
        if(N.size()==0 || K==0){return *this;}
        N[0]>>=K;
        ull key=1; key<<=K; key--;
        for(ul i=1;i<N.size();i++){
            N[i-1]|=(N[i]&key)<<(32-K);
            N[i]>>=K;
        }
        clean();
        return *this;
    }
    
    LongLong operator >> (ul k) const {
        LongLong ret(N,sign);
        return ret>>=k;
    }
    
    LongLong & operator &= (const LongLong &L){
        ul S=min(N.size(),L.Size());
        N.resize(S);
        for(ul i=0;i<S;i++){
            N[i]&=L.node(i);
        }
        clean();
        return *this;
    }
    
    LongLong operator & (const LongLong &L) const {
        LongLong ret(N,sign);
        return ret&=L;
    }
    
    LongLong & operator |= (const LongLong &L){
        N.resize(N.size(),L.Size());
        for(ul i=0;i<L.Size();i++){
            N[i]|=L.node(i);
        }
        clean();
        return *this;
    }
    
    LongLong operator | (const LongLong &L) const {
        LL ret(N,sign);
        return ret|=L;
    }
    
    LongLong operator xor (const LL &L) const {
        LL ret(N,sign);
        ret.N.resize(max(ret.Size(),L.Size()));
        for(ul i=0;i<L.Size();i++){
            ret.N[i]=ret.node(i) xor L.node(i);
        }
        ret.clean();
        return ret;
    }
    
    LongLong & operator += (const LL &L){
        int Ls=L.Sign();
        int Ts=Sign();
        if(Ls==0){return *this;}
        if(Ts==0){N=L.N; sign=L.sign; return *this;}
        if(Ts>0 && Ls>0){
            N.resize(max(N.size(),L.Size())+1);
            for(ul i=0;i<L.Size();i++){
                N[i]+=L.node(i);
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            for(ul i=L.Size();i<N.size()-1;i++){
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            clean();
            return *this;
        }
        if(Ts<0 && Ls<0){
            N.resize(max(N.size(),L.Size())+1);
            for(ul i=0;i<L.Size();i++){
                N[i]+=L.node(i);
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            for(ul i=L.Size();i<N.size()-1;i++){
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            clean();
            return *this;
        }
        if(Ts>0 && Ls<0){
            if(*this>=L.abs()){
                bool k=false;
                for(ul i=0;i<L.Size();i++){
                    N[i]+=MX;
                    N[i]-=L.node(i)+k;
                    k=false;
                    if(N[i]<MX){k=true;}
                    else{N[i]-=MX; k=false;}
                }
                for(ul i=L.Size();i<N.size() && k;i++){
                    if(N[i]==0){N[i]=I; continue;}
                    N[i]-=1; k=false;
                }
                clean();
                return *this;
            }
            else{
                bool k=false;
                N.resize(L.Size());
                for(ul i=0;i<N.size();i++){
                    N[i]=MX+L.node(i)-N[i]-k;
                    k=false;
                    if(N[i]<MX){k=true;}
                    else{N[i]-=MX; k=false;}
                }
                sign=false;
                clean();
                return *this;
            }
        }
        if((*this).abs()>=L){
            bool k=false;
            for(ul i=0;i<L.Size();i++){
                N[i]+=MX;
                N[i]-=L.node(i)+k;
                k=false;
                if(N[i]<MX){k=true;}
                else{N[i]-=MX; k=false;}
            }
            for(ul i=L.Size();i<N.size() && k;i++){
                if(N[i]==0){N[i]=I; continue;}
                N[i]-=1; k=false;
            }
            clean();
            return *this;
        }
        bool k=false;
        N.resize(L.Size());
        for(ul i=0;i<N.size();i++){
            N[i]=MX+L.node(i)-N[i]-k;
            k=false;
            if(N[i]<MX){k=true;}
            else{N[i]-=MX; k=false;}
        }
        sign=true;
        clean();
        return *this;
    }
    
    LongLong operator + (const LL &L) const {
        LL ret(N,sign);
        return ret+=L;
    }
    
    LongLong & operator -= (const LL &L){
        int Ls=L.Sign();
        int Ts=Sign();
        if(Ls==0){return *this;}
        if(Ts==0){N=L.N; sign=!L.sign; return *this;}
        if(Ts>0 && Ls<0){
            N.resize(max(N.size(),L.Size())+1);
            for(ul i=0;i<L.Size();i++){
                N[i]+=L.node(i);
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            for(ul i=L.Size();i<N.size()-1;i++){
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            clean();
            return *this;
        }
        if(Ts<0 && Ls>0){
            N.resize(max(N.size(),L.Size())+1);
            for(ul i=0;i<L.Size();i++){
                N[i]+=L.node(i);
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            for(ul i=L.Size();i<N.size()-1;i++){
                N[i+1]+=N[i]>>32;
                N[i]&=I;
            }
            clean();
            return *this;
        }
        if(Ts>0 && Ls>0){
            if(*this>=L){
                bool k=false;
                for(ul i=0;i<L.Size();i++){
                    N[i]+=MX;
                    N[i]-=L.node(i);
                    N[i]-=k; k=false;
                    if(N[i]>=MX){N[i]-=MX;}
                    else{k=true;}
                }
                for(ul i=L.Size();i<N.size() && k;i++){
                    if(N[i]==0){N[i]=I; continue;}
                    N[i]-=1; k=false;
                }
                clean();
                return *this;
            }
            else{
                int k=0;
                N.resize(L.Size());
                for(ul i=0;i<N.size();i++){
                    N[i]=MX+L.node(i)-N[i];
                    if(k){N[i]--; k=0;}
                    if(N[i]<MX){k=1;}
                    else{N[i]-=MX;}
                }
                sign=false;
                clean();
                return *this;
            }
        }
        if((*this)<=L){
            bool k=false;
            for(ul i=0;i<L.Size();i++){
                N[i]+=MX;
                N[i]-=L.node(i);
                N[i]-=k; k=false;
                if(N[i]<MX){k=true;}
                else{N[i]-=MX;}
            }
            for(ul i=L.Size();i<N.size() && k;i++){
                if(N[i]==0){N[i]=I; continue;}
                N[i]-=1; k=false;
            }
            clean();
            return *this;
        }
        bool k=false;
        N.resize(L.Size());
        for(ul i=0;i<N.size();i++){
            N[i]=MX+L.node(i)-N[i]-k;
            k=false;
            if(N[i]<MX){k=true;}
            else{N[i]-=MX; k=false;}
        }
        sign=true;
        clean();
        return *this;
    }
    
    LongLong operator - (const LL &L) const {
        LL ret(N,sign);
        return ret-=L;
    }
    
    LongLong & operator *= (const LL &L){
        if(!L.sign){sign=!sign;}
        if(*this==0){return *this;}
        if(L==0){N.clear(); return *this;}
        if(L.N.size()==1 && L.N[0]==1){return *this;}
        NTT<2281701377,3> ntt1;
        NTT<2483027969,3> ntt2;
        vector<Mod_Int<2281701377>> a1(N.size()*2);
        vector<Mod_Int<2483027969>> a2(N.size()*2);
        vector<Mod_Int<2281701377>> b1(L.N.size()*2);
        vector<Mod_Int<2483027969>> b2(L.N.size()*2);
        for(int i=0;i<N.size();i++){
            a1[i*2]=N[i]&MI;
            a1[i*2+1]=N[i]>>16;
            a2[i*2]=N[i]&MI;
            a2[i*2+1]=N[i]>>16;
        }
        for(int i=0;i<L.N.size();i++){
            b1[i*2]=L.N[i]&MI;
            b1[i*2+1]=L.N[i]>>16;
            b2[i*2]=L.N[i]&MI;
            b2[i*2+1]=L.N[i]>>16;
        }
        ntt1.Multiplication(a1,b1);
        ntt2.Multiplication(a2,b2);
        N.resize(a1.size()/2+5);
        for(int i=0;i<N.size();i++){N[i]=0;}
        for(ul i=0;i<a1.size();i+=2){
            ll k=a1[i].a;
            (a2[i]-=k)*=Inv;
            k+=a2[i].a*A;
            N[i>>1]+=k&I;
            N[(i>>1)+1]+=k>>32;
        }
        for(ul i=1;i<a1.size();i+=2){
            ull k=a1[i].a;
            (a2[i]-=k)*=Inv;
            k+=a2[i].a*=A;
            N[i>>1]+=(k&MI)<<16;
            N[(i>>1)+1]+=(k>>16)&I;
            N[(i>>1)+2]+=k>>48;
        }
        for(ul i=0;i+1<N.size();i++){
            N[i+1]+=N[i]>>32;
            N[i]&=I;
        }
        clean();
        return *this;
    }
    
    LongLong operator * (const LL &L) const {
        LongLong ret(*this);
        return ret*=L;
        /*
         ret.resize(N.size()+L.Size()+2);
         for(ul i=0;i<N.size();i++){
         for(ul t=0;t<L.Size();t++){
         ull d=N[i]*L.node(t);
         ret.N[i+t+1]+=d>>32;
         ret.N[i+t]+=d&I;
         }
         }
         for(ul i=0;i<ret.Size()-1;i++){
         ret.N[i+1]+=ret.N[i]>>32;
         ret.N[i]&=I;
         }
         ret.clean();
         int s=sign; s+=L.sign;
         ret.sign=s%2;
         ret.sign=!ret.sign;
         return ret;
         */
    }
    
    LongLong & operator %= (LL L){
        assert(L!=0);
        bool s=sign; if(!L.sign){s=!s; L.sign=true;}
        sign=true;
        if((*this)<L){sign=s; return *this;}
        ul d=N.size()-L.Size()+1;
        for(ll i=d*32;i>=0;i--){
            if((*this>>i)>=L){(*this)-=(L<<i);}
        }
        sign=s;
        return *this;
    }
    
    LongLong operator % (const LL &L) const {
        LongLong ret(N,sign);
        return ret%=L;
    }
    
    LongLong operator /= (const LL &L){
        N=((*this)/L).N;
        if(!L.sign){sign=!sign;}
        return *this;
    }
    
    LongLong operator / (LL L) const {
        assert(L!=0);
        LL ret;
        LL k(1);
        LL A(N,sign);
        bool s=A.sign; if(!L.sign){s=!s; L.sign=true;}
        A.sign=true;
        if(A<L){return 0;}
        ul d=A.Size()-L.Size()+1;
        for(ll i=d*32;i>=0;i--){
            if((A>>i)>=L){A-=(L<<i); ret+=(k<<i);}
        }
        ret.sign=s;
        return ret;
    }
    
    LongLong abs() const {return LL(N,true);}
    
    ll to_longlong() const {
        ll ret=0;
        ll k=1;
        for(ul i=0;i<N.size();i++){
            ret+=k*N[i];
            k<<=32;
        }
        if(!sign){ret*=-1;}
        return ret;
    }
    
    ull to_unsignedlonglong() const {
        ull ret=0;
        ull k=1;
        for(ul i=0;i<N.size();i++){
            ret+=k*N[i];
            k<<=32;
        }
        return ret;
    }
    
    string to_string() const {
        string s;
        pair<vector<ull>,bool> ret=to_vector(10);
        for(ul i=0;i<ret.F.size();i++){
            s.push_back('0'+ret.F[i]);
        }
        if(s.size()==0){s.push_back('0');}
        if(!ret.S && s[s.size()-1]!='0'){s.push_back('-');}
        std::reverse(s.begin(),s.end());
        return s;
    }
    
    //left::small right::big
    pair<vector<ull>,bool> to_vector(const LL &x) const {
        vector<ull> ret;
        LL L(N,true);
        while(L>0){
            ret.push_back((L%x).to_unsignedlonglong());
            L/=x;
        }
        return {ret,sign};
    }
    
    void bit(){
        for(ul i=0;i<N.size();i++){
            for(ul t=0;t<32;t++){
                cout<<(*this)[i*32+t];
            }
        }
        cout<<endl;
    }
};




#endif /*LongLong_hpp*/
