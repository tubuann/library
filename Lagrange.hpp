#ifndef Lagrange_hpp
#define Lagrange_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

/*
 ラグランジュの補間多項式
 N+1個の異なる点からN次多項式を復元する
 */
template<typename T>
struct Lagrange{
    //pair<T,T>=(x,y)
    int N;
    vector<pair<T,T>> pts;
    vector<T> frc;
    bool made;
    
    Lagrange(const vector<pair<T,T>> &PT):pts(PT),frc(PT.size(),1),N(PT.size()),made(false){}
    
    //前計算、O(N^2)
    void make_frc(){
        made=true;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i!=j){frc[i]*=pts[i].F-pts[j].F;}
            }
        }
        for(auto &I:frc){I=T(1)/I;}
    }
    
    //x座標が等差数列になっているとき、前計算をO(N)で行う
    void make_frc_arithmetic(){
        made=true;
        T lf=1;
        vector<T> mul(N,1);
        for(int i=N-2;i>=0;i--){mul[i]=(pts[i].F-pts.back().F)*mul[i+1];}
        for(int i=0;i<N;i++){
            frc[i]=lf*mul[i];
            if(i+1!=N){lf*=pts[i+1].F-pts.front().F;}
        }
        for(auto &I:frc){I=T(1)/I;}
    }
    
    //x座標が等比数列になっているとき、前計算をO(N)で行う
    void make_frc_geometric(){
        made=true;
        if(N<=1){return;}
        T lf=1,r=pts[1].F/pts[0].F,inv=pts[0].F/pts[1].F,k=1,k2=1;
        vector<T> mul(N,1);
        for(int i=N-2;i>=0;i--){mul[i]=(pts[i].F-pts.back().F)*mul[i+1]*k; k*=inv;}
        for(int i=0;i<N;i++){
            frc[i]=lf*mul[i];
            if(i+1!=N){lf*=k2*(pts[i+1].F-pts.front().F); k2*=r;}
        }
        for(auto &I:frc){I=T(1)/I;}
    }
    
    //O(N)でxでの値を復元する
    T cul(T x){
        if(!made){make_frc();}
        T lf=1,ret=0;
        vector<T> mul(N+1,1);
        for(int i=N-1;i>0;i--){mul[i]=mul[i+1]*(x-pts[i].F);}
        for(int i=0;i<N;i++){
            ret+=pts[i].S*lf*mul[i+1]*frc[i];
            lf*=x-pts[i].F;
        }
        return ret;
    }
};


#endif /*Lagrange_hpp*/
