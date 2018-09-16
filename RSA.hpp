#ifndef RSA_hpp
#define RSA_hpp

#include "Long.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

class RSA{
private:
  typedef unsigned long ul;
  Long p,q;
  Long mod;
  Long key;
  Long rev;
  ul bit_size;
  random_device r;
  mt19937 mt;

  typedef pair<Long,Long> PLL;

  PLL Ex_Euc(Long a,Long b){
    if(b==0){return {1,0};}
    PLL ret=Ex_Euc(b,a%b);
    ret.F=ret.F-a/b*ret.S;
    return {ret.S,ret.F};
  }

  Long Rev(Long a,Long mod){
    PLL ret=Ex_Euc(a,mod);
    if(ret.F<0){
      ret.F=ret.F+mod;
    }
    return ret.F;
  }

  bool Miller_Rabin_test(Long P,ul k){
    if(!P[0] || P%3==0 || P%5==0 || P%7==0 || P%11==0 || P%13==0){return false;}
    Long N=P-1;
    Long D=N;
    ll s=0;
    int mx=1000000000;
    uniform_int_distribution<int> R(2,mx);
    while(D.size()>0 && D[0]==false){D=D>>1; s++;}
    for(ll i=0;i<k;i++){
      bool j=false;
      Long A=R(mt);
      A=A.mod_pow(D,P);
      if(A==1 || A==N){j=true;}
      for(int t=1;t<s && !j;t++){
	A=A.mod_pow(2,P);
	if(A==N){j=true;}
      }
      if(!j){return false;}
    }
    return true;
  }

  ll delta(){
    int mx=1000000;
    uniform_int_distribution<int> R(1,mx);
    ll d=R(mt);
    d*=mx;
    d+=R(mt);
    return d;
  }

public:
  RSA(Long p,Long q):p(p),q(q),mt(r()){
    mod=p*q;
    bit_size=mod.size()-1;
    Long phi=(p-1)*(q-1);
    key=65537;
    rev=Rev(key,phi);
    phi=0; p=0; q=0;
  }

  RSA(ul size,ul k=10):mt(r()){
    assert(size>=100);
    p=1;
    p=p<<(size/2);
    p=p+delta();
    while(1){
      if(Miller_Rabin_test(p,k)){break;}
      p=p+delta();
    }
    q=p+delta();
    while(1){
      if(Miller_Rabin_test(q,k)){break;}
      q=q+delta();
    }
    mod=p*q;
    bit_size=mod.size()-1;
    Long phi=(p-1)*(q-1);
    key=65537;
    rev=Rev(key,phi);
    phi=0; p=0; q=0;
  }

  RSA(Long mod,Long key,Long rev):mod(mod),key(key),rev(rev),mt(r()){
    bit_size=mod.size()-1;
  }
  
  ul size(){return bit_size;}

  void test(Long M){
    vector<Long> C=M_to_C(Decomposition(M));
    M=back_to_Long(C_to_M(C));
    cout<<M.to_string()<<endl;
  }

  void Rtest(Long M){
    vector<Long> C=C_to_M(Decomposition(M));
    M=back_to_Long(M_to_C(C));
    cout<<M.to_string()<<endl;
  }

  vector<Long> Decomposition(Long A){
    return A.to_bit_vector(bit_size).F;
  }

  Long back_to_Long(vector<Long> A){
    return Long(A,bit_size,true);
  }

  Long M_to_C_one(Long M){
    return M.mod_pow(key,mod);
  }

  Long C_to_M_one(Long C){
    return C.mod_pow(rev,mod);
  }

  vector<Long> M_to_C(vector<Long> M){
    for(int i=0;i<M.size();i++){
      M[i]=M_to_C_one(M[i]);
    }
    return M;
  }

  vector<Long> C_to_M(vector<Long> C){
    for(int i=0;i<C.size();i++){
      C[i]=C_to_M_one(C[i]);
    }
    return C;
  }
};



#endif /*RSA_hpp*/
