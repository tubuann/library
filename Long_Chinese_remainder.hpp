#ifndef Long_Chinese_remainder_hpp
#define Long_Chinese_remainder_hpp

#include "Long.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

class Long_Chinese_remainder{
private:
  typedef pair<Long,Long> pll;
  typedef unsigned long ul;
  vector<Long> mod;
  vector<Long> a;
  Long M;

  Long gcd(Long a,Long b){
    if(a%b==0){return b;}
    return gcd(b,a%b);
  }

  pll Ex_gcd(Long a,Long b){
    if(b==0){return {1,0};}
    pll A=Ex_gcd(b,a%b);
    swap(A.F,A.S);
    A.S=A.S-a/b*A.F;
    return {A.F,A.S};
  }

public:
  Long_Chinese_remainder(vector<Long> m={},vector<Long> A={}){
    assert(m.size()==A.size());
    M=1;
    for(int i=0;i<m.size();i++){
      assert(gcd(M,m[i])==1);
      M=M*m[i];
      A[i]=A[i]%m[i];
    }
    a=A;
    mod=m;
  }

  void add(Long m,Long A){
    assert(gcd(M,m)==1);
    M=M*m;
    mod.push_back(m);
    a.push_back(A);
  }

  Long solve(){
    Long ans=0;
    for(ul i=0;i<mod.size();i++){
      pll k=Ex_gcd(mod[i],M/mod[i]);
      ans=ans+M/mod[i]*k.S*a[i];
      ans=ans%M;
    }
    return ans;
  }

  Long Mod(){return M;}
};




#endif /*Long_Chinese_remainder_hpp*/
