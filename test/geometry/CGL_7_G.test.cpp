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

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G"
#define ERROR "0.00001"

int main(){
    cout<<fixed<<setprecision(12);
    pair<P,D> c1,c2;
    cin>>c1>>c2;
    vector<pair<P,P>> ans=tangentCC(c1,c2);
    sort(ans.begin(),ans.end(),[&](const pair<P,P> &s1,const pair<P,P> &s2){return s1.F==s2.F?comp(s1.S,s2.S):comp(s1.F,s2.F);});
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    for(auto &I:ans){
        if(abs(I.F-I.S)>EPS){
            assert(abs(distLP(I.F,I.S,c1.F)-c1.S)<EPS);
            assert(abs(distLP(I.F,I.S,c2.F)-c2.S)<EPS);
        }
        else{
            assert(abs(abs(I.F-c1.F)-c1.S)<EPS);
            assert(abs(abs(I.F-c2.F)-c2.S)<EPS);
        }
        cout<<fixed<<setprecision(12)<<I.F.real()<<" "<<I.F.imag()<<endl;
    }
    
    return 0;
}
