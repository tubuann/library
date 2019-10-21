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

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C"
//#define ERROR "0.00000001"

int main(){
    cout<<fixed<<setprecision(12);
    ll n;
    cin>>n;
    vector<P> A(n);
    for(auto &I:A){cin>>I;}
    ll q;
    cin>>q;
    while(q--){
        P p1,p2;
        cin>>p1>>p2;
        vector<P> B=convexcut(A,p1,p2);
        cout<<fixed<<setprecision(12)<<area(B)<<endl;
    }
    
    return 0;
}
