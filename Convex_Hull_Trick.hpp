#ifndef Comvex_Hull_Trick_hpp
#define Comvex_Hull_Trick_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
#define F first
#define S second


/*
 O(QlogN+N)
 追加する直線の傾きが狭義単調減少であること
 maxを求めるときは値と傾きに-1をかけること
 */
template<typename T>
class Comvex_Hull_Trick{
private:
    typedef pair<T,T> line; //y切片,傾き
    deque<line> D;
    
    inline T point(const line &L,const T &x) const {return L.F+L.S*x;}
    
    inline bool is_need(const line &A,const line &B,const line &C) const {
        return (C.F-A.F)*(A.S-B.S)>(B.F-A.F)*(A.S-C.S);
    }
    
public:
    Comvex_Hull_Trick(){}
    
    void add_line(const line &L){
        while(!D.empty() && D.back().S==D.back().S){L.F=min(L.F,D.back().F); D.pop_back();}
        while(D.size()>=2 && !is_need(D[D.size()-2],D.back(),L)){D.pop_back();}
        D.push_back(L);
    }
    
    T search(const T &x) const {
        ll l=0;
        ll r=D.size()-1;
        while(l+1<r){
            ll m=l+(r-l)/2;
            if(point(D[m],x)<point(D[m+1],x)){r=m;}
            else{l=m+1;}
        }
        for(ll i=l;i<r;i++){
            if(point(D[i],x)<point(D[i+1],x)){return point(D[i],x);}
        }
        return point(D[r],x);
    }
    
    pair<T,T> search_line(const T &x) const {
        ll l=0;
        ll r=D.size()-1;
        while(l+1<r){
            ll m=l+(r-l)/2;
            if(point(D[m],x)<point(D[m+1],x)){r=m;}
            else{l=m+1;}
        }
        for(ll i=l;i<r;i++){
            if(point(D[i],x)<point(D[i+1],x)){return D[i];}
        }
        return D[r];
    }
    
    pair<T,T> back() const {return D.back();}
    
    unsigned long size() const {return D.size();}
    
    bool empty() const {return D.empty();}
};



#endif /*Comvex_Hull_Trick_hpp*/
