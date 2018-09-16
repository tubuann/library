#ifndef Lagrange_polynomial_hpp
#define Lagrange_polynomial_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T>
class Lagrange_polynomial{
private:
  typedef unsigned long ul;
  typedef pair<T,T> point;
  vector<point> P;

public:
  Lagrange_polynomial(vector<point> P={}):P(P){}

  void add_point(point a){P.push_back(a);}

  void add_point(vector<point> a){
    for(int i=0;i<a.size();i++){
      P.push_back(a[i]);
    }
  }

  T F(T x){
    assert(P.size()>1);
    T ret=0;
    for(ul i=0;i<P.size();i++){
      T a=P[i].S;
      for(ul t=0;t<P.size();t++){
	if(i==t){continue;}
	a*=x-P[t].F;
	assert(P[i].F!=P[t].F);
	a/=P[i].F-P[t].F;
      }
      ret+=a;
    }
    return ret;
  }

  bool judge(T x,T y){
    return F(x)==y;
  }
};



#endif /*Lagrange_polynomial_hpp*/
