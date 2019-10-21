#include<bits/stdc++.h>
#include "../../ICPC/Geometry_Complex.hpp"
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
typedef long double D;
typedef complex<D> P;
#define F first
#define S second
const ll MOD=1000000007;
//const ll MOD=998244353;



template<typename T,typename U>istream & operator >> (istream &i,pair<T,U> &A){i>>A.F>>A.S; return i;}
template<typename T>istream & operator >> (istream &i,vector<T> &A){for(auto &I:A){i>>I;} return i;}
template<typename T,typename U>ostream & operator << (ostream &o,const pair<T,U> &A){o<<A.F<<" "<<A.S; return o;}
template<typename T>ostream & operator << (ostream &o,const vector<T> &A){ll i=A.size(); for(auto &I:A){o<<I<<(--i?" ":"");} return o;}

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A"

int main(){
    Geometry<ll> G;
    ll q;
    cin>>q;
    while(q--){
    ll x,y;
    ll xd,yd;
    cin>>x>>y>>xd>>yd;
    x-=xd;
    y-=yd;
    ll x2,y2;
    cin>>x2>>y2>>xd>>yd;
    x2-=xd;
    y2-=yd;
    if(G.dot({x,y},{x2,y2})==0){cout<<1<<endl;}
    else if(G.cross({x,y},{x2,y2})==0){cout<<2<<endl;}
    else{cout<<0<<endl;}
    }
    
    return 0;
}
