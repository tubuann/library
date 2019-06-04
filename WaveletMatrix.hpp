#ifndef WaveletMatrix_hpp
#define WaveletMatrix_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

struct WaveletMatrix{
    const int high;
    const int size;
    
    vector<vector<bool>> Matrix; //下から上
    vector<vector<pair<int,int>>> Rank; //(0,1) [high][size] 自分より前
    vector<int> Mid; //0-origin
    
    WaveletMatrix(int high,int size,const vector<ll> &A):high(high),size(size),Matrix(high,vector<bool>(size)),Rank(high,vector<pair<int,int>>(size+1)),Mid(high){init(A);}
    
    void init(vector<ll> A){
        for(int i=high-1;i>=0;i--){
            pair<int,int> R={0,0};
            for(int t=0;t<size;t++){
                Matrix[i][t]=A[t]>>i&1;
                Rank[i][t]=R;
                if(Matrix[i][t]){R.S++;}
                else{R.F++;}
            }
            Rank[i][size]=R;
            vector<ll> N(size);
            int l=0;
            for(int t=0;t<size;t++){
                if((A[t]>>i&1)==0){N[l]=A[t]; l++;}
            }
            Mid[i]=l;
            for(int t=0;t<size;t++){
                if(A[t]>>i&1){N[l]=A[t]; l++;}
            }
            A=N;
        }
    }
    
    ll access(int n) const {return access(high-1,n);}
    
    ll access(int h,int n) const {
        if(h==0){return Matrix[h][n];}
        if(Matrix[h][n]){
            return (1LL<<h)|access(h-1,Mid[h]+Rank[h][n].S);
        }
        return access(h-1,Rank[h][n].F);
    }
    
    //[l,r)
    int rank(ll s,int l,int r){
        return rank(s,l,r,high-1);
    }
    
    //[l,r)
    int rank(ll s,int l,int r,int h){
        if(h==0){
            if(s&1){return Rank[h][r].S-Rank[h][l].S;}
            return Rank[h][r].F-Rank[h][l].F;
        }
        if(s>>h&1){
            return rank(s,Mid[h]+Rank[h][l].S,Mid[h]+Rank[h][r].S,h-1);
        }
        return rank(s,Rank[h][l].F,Rank[h][r].F,h-1);
    }
    
    //[l,r)
    ll range_min(int l,int r){return range_min(l,r,high-1);}
    
    //[l,r)
    ll range_min(int l,int r,int h){
        if(h==0){
            if(Rank[h][r].F-Rank[h][l].F==0){return 1;}
            return 0;
        }
        if(Rank[h][r].F-Rank[h][l].F==0){
            return (1LL<<h)|range_min(Mid[h]+Rank[h][l].S,Mid[h]+Rank[h][r].S,h-1);
        }
        return range_min(Rank[h][l].F,Rank[h][r].F,h-1);
    }
    
    //[l,r)
    ll range_max(int l,int r){return range_max(l,r,high-1);}
    
    //[l,r)
    ll range_max(int l,int r,int h){
        if(h==0){
            if(Rank[h][r].S-Rank[h][l].S==0){return 0;}
            return 1;
        }
        if(Rank[h][r].S-Rank[h][l].S==0){
            return range_max(Rank[h][l].F,Rank[h][r].F,h-1);
        }
        return (1LL<<h)|range_max(Mid[h]+Rank[h][l].S,Mid[h]+Rank[h][r].S,h-1);
    }
    
    //[s,t) [l,r)
    int range_count(ll s,ll t,int l,int r){return range_count(0,s,t,l,r,high-1);}
    
    //[s,t) [l,r)
    int range_count(ll w,ll s,ll t,int l,int r,int h){
        if(r<=l || t<=s){return 0;}
        if(s<=w && (w+(1LL<<(h+1)))<=t){return r-l;}
        if(s>=(w+(1LL<<(h+1))) || w>=t){return 0;}
        int ret=0;
        if(h==0){
            if(s<=w && w<t){ret+=Rank[h][r].F-Rank[h][l].F;}
            if(s<=w+1 && w+1<t){ret+=Rank[h][r].S-Rank[h][l].S;}
            return ret;
        }
        ret+=range_count(w,s,t,Rank[h][l].F,Rank[h][r].F,h-1);
        ret+=range_count(w|(1LL<<h),s,t,Mid[h]+Rank[h][l].S,Mid[h]+Rank[h][r].S,h-1);
        return ret;
    }
    
    //[s,t) [l,r)
    ll range_min(ll s,ll t,int l,int r){return range_min(0,s,t,l,r,high-1);}
    
    //[s,t) [l,r)
    ll range_min(ll w,ll s,ll t,int l,int r,int h){
        if(r<=l || t<=s){return -1;}
        if(s<=w && (w+(1LL<<(h+1)))<=t){return range_min(l,r,h);}
        if(s>=(w+(1LL<<(h+1))) || w>=t){return -1;}
        ll ret=-1;
        if(h==0){
            if(s<=w && w<t && Rank[h][r].F-Rank[h][l].F>0){return 0;}
            if(s<=w+1 && w+1<t && Rank[h][r].S-Rank[h][l].S>0){return 1;}
            return -1;
        }
        ret=range_min(w,s,t,Rank[h][l].F,Rank[h][r].F,h-1);
        if(ret==-1){
            ret=range_min(w|(1LL<<h),s,t,Mid[h]+Rank[h][l].S,Mid[h]+Rank[h][r].S,h-1);
            if(ret==-1){return ret;}
            ret|=1LL<<h;
        }
        return ret;
    }
    
    //[s,t) [l,r)
    ll range_max(ll s,ll t,int l,int r){return range_max(0,s,t,l,r,high-1);}
    
    //[s,t) [l,r)
    ll range_max(ll w,ll s,ll t,int l,int r,int h){
        if(r<=l || t<=s){return -1;}
        if(s<=w && (w+(1LL<<(h+1)))<=t){return range_max(l,r,h);}
        if(s>=(w+(1LL<<(h+1))) || w>=t){return -1;}
        if(h==0){
            if(s<=w+1 && w+1<t && Rank[h][r].S-Rank[h][l].S>0){return 1;}
            if(s<=w && w<t && Rank[h][r].F-Rank[h][l].F>0){return 0;}
            return -1;
        }
        ll ret=-1;
        ret=range_max(w|(1LL<<h),s,t,Mid[h]+Rank[h][l].S,Mid[h]+Rank[h][r].S,h-1);
        if(ret==-1){
            ret=range_max(w,s,t,Rank[h][l].F,Rank[h][r].F,h-1);
        }
        else{ret|=1LL<<h;}
        return ret;
    }
};




#endif /*WaveletMatrix_hpp*/
