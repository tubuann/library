#ifndef Mod_Geometry_hpp
#define Mod_Geometry_hpp

#include "Mod_Int.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
#define F first
#define S second



template<long long int mod=1000000007>
struct Mod_Point{
    typedef Mod_Point<mod> M;
    typedef Mod_Int<mod> Int;
    Int x,y;
    
    Mod_Point(const M &b):x(b.x),y(b.y){}
    
    Mod_Point(const Int &x,const Int &y):x(x),y(y){}
    
    Mod_Point(ll x,ll y):x(x),y(y){}
    
    Mod_Point(pll p):x(p.F),y(p.S){}
    
    M & operator += (const M &V){
        x+=V.x; y+=V.y;
        return *this;
    }
    
    M operator + (const M &V) const {
        M c=*this;
        return c+=V;
    }
    
    M & operator -= (const M &V){
        x-=V.x; y-=V.y;
        return *this;
    }
    
    M operator - (const M &V) const {
        M c=*this;
        return c-=V;
    }
    
    bool operator == (const M &b) const {return x==b.x && y==b.y;}
    
    bool operator != (const M &b) const {return x!=b.x || y!=b.y;}
    
    Int slant(){
        if(x==0){return mod;}
        return y/x;
    }
};

template<long long int mod=1000000007>
struct Mod_Line{
    typedef Mod_Point<mod> P;
    typedef Mod_Int<mod> Int;
    typedef Mod_Line<mod> M;
    P s,t;
    
    Mod_Line(const P &s,const P &t):s(s),t(t){assert(s!=t);}
    
    Mod_Line(const Int &sx,const Int &sy,const Int &tx,const Int &ty):s(sx,sy),t(tx,ty){assert(s!=t);}
    
    Mod_Line(const M &b):s(b.s),t(b.t){}
    
    Mod_Line(const pll &s,const pll &t):s(s),t(t){}
    
    Int slant() const {
        Int x=t.x-s.x;
        Int y=t.y-s.y;
        if(x==0){return mod;}
        return y/x;
    }
    
    Int Y() const {
        Int s=slant();
        if(s==mod){return mod;}
        return s.y-s.x*s;
    }
    
    pair<Int,ll> equals() const {
        Int x=t.x-s.x;
        Int y=t.y-s.y;
        if(x==0){return {s.x,mod};}
        Int sl=y/x;
        return {s.y-s.x*sl,sl.a};
    }
    
    P operator * (const M &b){
        pair<Int,ll> A=equals(),B=b.equals();
        assert(A.S!=B.S);
        if(A.S==mod){
            return P(A.F,B.F+A.F*B.S);
        }
        if(B.S==mod){
            return P(B.F,A.F+B.F*Int(A.S));
        }
        Int x=(A.F-B.F)/((Int)B.S-A.S);
        return P(x,A.F+Int(A.S)*x);
    }
    
    bool operator == (const M& b) const {return equals()==b.equals();}
    
    bool operator != (const M& b) const {return equals()!=b.equals();}
};


#endif /*Mod_Int_hpp*/
