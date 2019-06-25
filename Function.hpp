#ifndef Function_hpp
#define Function_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

namespace Convolution{
    /*
     Aのサイズは2^nとなっていること。
     
     R_k=sum_(i&j=k),A_i B_j
     R=mobius(zeta(A),zeta(B))
     上位集合の畳み込みの積をとって逆変換
     
     R_k=sum_(i|j=k),A_i B_j
     R=mobius(zeta(A),zeta(B))
     下位集合の畳み込みの積をとって逆変換
     */
    
    //R_i=sum_(j in i),A_j
    //下位集合の畳み込み　上位集合の畳み込みはif文のなかの等号の左右を反対にする。
    template<typename T>
    vector<T> zeta(const vector<T> &A,int n){
        vector<T> ret=A;
        for(int i=1;i<1<<n;i<<=1){
            for(int j=0;j<1<<n;j++){
                if((j&i)==0){ret[j|i]+=ret[j];}
            }
        }
        return ret;
    }
    
    //R_i=sum_(j in i),(-1)^(|i\j|) A_j
    //ゼータ変換の逆変換
    template<typename T>
    vector<T> mobius(const vector<T> &A,int n){
        vector<T> ret=A;
        for(int i=1;i<1<<n;i<<=1){
            for(int j=0;j<1<<n;j++){
                if((j&i)==0){ret[j|i]-=ret[j];}
            }
        }
        return ret;
    }
    
    //R_i=sum_(j),(-1)^(|i&j|) A_j
    //オーバーフローに注意,sqrt(|A|)で割ると直交かつ対称な変換になる
    template<typename T>
    vector<T> hadamard(const vector<T> &A,int n){
        vector<T> ret=A;
        for(int i=1;i<1<<n;i<<=1){
            for(int j=0;j<1<<n;j++){
                if((i&j)==0){
                    T P=ret[j],Q=ret[j|i];
                    ret[j]=P+Q;
                    ret[j|i]=P-Q;
                }
            }
        }
        return ret;
    }
    
    //R_i=sum_(j),r^(ij) A_j
    //オーバーフローに注意,sqrt(|A|)で割るとユニタリかつエルミートな変換になる,rは1の原始|A|乗根
    template<typename T>
    vector<T> fourier(const vector<T> &A,int n,T r){
        vector<T> ret=A;
        vector<T> E(1<<n,1);
        for(int i=1;i<1<<n;i++){E[i]=E[i-1]*r;}
        for(int i=0,j=1;j<1<<n;j++){
            for(int k=1<<(n-1);k>(i^=k);k>>=1);
            if(i>j){swap(ret[i],ret[j]);}
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<1<<n;j+=2<<i){
                for(int k=0;k<1<<i;k++){
                    T P=ret[j|k],Q=ret[j|1<<i|k]*E[(1<<n-i-1)*k];
                    ret[j|k]=P+Q;
                    ret[j|1<<i|k]=P-Q;
                }
            }
        }
        return ret;
    }
};

using namespace Convolution;



namespace Monotone_Minima{
    //argmin(cul(i,*))<=argmin(cul(j,*)) for(i<j)
    //を満たすn行m列の行列で、各行の最小値を求め、そのindexを返す。
    template<typename T>
    vector<int> argmin(function<T(int,int)> cul,int n,int m,function<bool(T,T)> comp=less<T>()){
        vector<int> ret(n,-1);
        int i=2;
        while(i<n){i<<=1;}
        while(i>>=1){
            for(int j=0;j<n;j+=i){
                if(ret[j]!=-1){continue;}
                int l=(j-i>=0 && ret[j-i]!=-1?ret[j-i]:0),r=(j+i<n && ret[j+i]!=-1?ret[j+i]+1:m);
                T a=cul(j,l);
                ret[j]=l;
                for(int k=l+1;k<r;k++){
                    if(comp(cul(j,k),a)){
                        a=cul(j,k);
                        ret[j]=k;
                    }
                }
            }
        }
        return ret;
    }
    
    //f(i,k)+f(j,l)<=f(i,l)+f(j,k) for(i<=j,k<=l)
    //を満たすn行n列の行列Aに対して、
    //dp[i]=min_{j<i} dp[j]+A_{i,j}
    //を求める。
    template<typename T>
    vector<T> divide_and_conquer(function<T(int,int)> cul,int n,T e=T(),function<bool(T,T)> comp=less<T>()){
        vector<T> ret(n,e);
        for(int i=1;i<n;i++){ret[i]=ret[0]+cul(i,0);}
        for(int i=1;i<n;i++){
            int j=i&(-i);
            int k=i-j;
            auto fnc=[&](int a,int b){return ret[k+b]+cul(i+a,k+b);};
            vector<int> am=argmin<T>(fnc,min(j,n-i),j,comp);
            for(int s=0;s<j && i+s<n;s++){
                T a=fnc(s,am[s]);
                if(comp(a,ret[i+s])){ret[i+s]=a;}
            }
        }
        return ret;
    }
}

using namespace Monotone_Minima;

#endif /*Function_hpp*/
