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

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_3_B"
//#define ERROR "0.00000001"


int main(){
    cout<<fixed<<setprecision(12);
    ll q;
    cin>>q;
    ll n=q;
    vector<P> poly;
    while(q--){
        D x1,y1;
        cin>>x1>>y1;
        P a={x1,y1};
        poly.push_back(a);
    }
    poly.push_back(P(pol[0]));
    poly.push_back(P(pol[1]));
    bool jd=true;
    for(int i=1;i+1<(int)poly.size();i++){
      jd&=cross(poly[i]-poly[i-1],poly[i+1]-poly[i])>EPS;
    }
    cout<<jd<<endl;
    
    return 0;
}
