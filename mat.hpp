#ifndef mat_hpp
#define mat_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T>
class mat{
private:
  typedef unsigned long ul;
  ul n,m;
  vector<vector<T>> M;
    
public:
  mat(ul n=0,ul m=0):n(n),m(m){M.resize(n,vector<T>(m,T()));}
    
  mat(vector<vector<T>> M):M(M){
    n=M.size();
    m=M[0].size();
    for(int i=0;i<M.size();i++){
      assert(M[i].size()==m);
    }
  }
    
  vector<T> & operator [] (ul N){
    assert(N<n);
    return M[N];
  }
    
  mat operator + (mat a){
    assert(a.n==n);
    assert(a.m==m);
    for(int i=0;i<n;i++){
      for(int t=0;t<m;t++){
	a[i][t]+=M[i][t];
      }
    }
    return a;
  }
    
  mat operator - (mat a){
    assert(a.n==n);
    assert(a.m==m);
    for(int i=0;i<n;i++){
      for(int t=0;t<m;t++){
	a[i][t]=M[i][t]-a[i][t];
      }
    }
    return a;
  }
    
    
  mat operator * (T a){
    mat<T> ret(M);
    for(int i=0;i<n;i++){
      for(int t=0;t<m;t++){
	ret[i][t]*=a;
      }
    }
    return ret;
  }
    
  mat operator * (mat a){
    assert(m==a.n);
    mat ret(n,a.m);
    for(int i=0;i<n;i++){
      for(int t=0;t<a.m;t++){
	for(int h=0;h<m;h++){
	  ret[i][t]+=(*this)[i][h]*a[h][t];
	}
      }
    }
    return ret;
  }
    
  mat operator / (T a){
    mat<T> ret(M);
    for(int i=0;i<n;i++){
      for(int t=0;t<m;t++){
	ret[i][t]/=a;
      }
    }
    return ret;
  }
    
  mat operator % (T a){
    mat<T> ret(M);
    for(int i=0;i<n;i++){
      for(int t=0;t<m;t++){
	ret[i][t]%=a;
      }
    }
    return ret;
  }
    
  bool operator == (const mat &a) const {
    return a.M==M;
  }
    
  mat operator != (const mat &a) const {return !(*this==a);}
    
  bool operator < (const mat &a) const {
    return M<a.M;
  }
    
  ul size(){return n;}
    
  void resize(ul x,ul y){
    n=x; m=y;
    M.resize(x);
    for(int i=0;i<x;i++){
      M[i].resize(y);
    }
  }
    
  void clear(){
    n=0; m=0;
    M.clear();
  }
    
  T det(){
    assert(n==m);
    assert(0<n && n<=3);
    if(n==1){return M[0][0];}
    if(n==2){return M[0][0]*M[1][1]-M[1][0]*M[0][1];}
    if(n==3){
      T ret=0;
      ret+=M[0][0]*M[1][1]*M[2][2]-M[0][0]*M[1][2]*M[2][1];
      ret-=M[0][1]*M[1][0]*M[2][2]-M[0][1]*M[1][2]*M[2][0];
      ret+=M[0][2]*M[1][0]*M[2][1]-M[0][2]*M[1][1]*M[2][0];
      return ret;
    }
    return T();
  }
    
  mat I(ul k){
    mat<T> ret(k,k);
    for(int i=0;i<k;i++){
      ret[i][i]=1;
    }
    return ret;
  }
    
  mat mod_pow(ull x,ull mod){
    assert(n==m);
    mat ret=I(n);
    mat<T> A(M);
    A%=mod;
    for(int i=0;i<64;i++){
      if(x>>i&1){
	ret*=A;
	ret%=mod;
      }
      A*=A;
      A%=mod;
    }
    return ret;
  }
    
  pair<mat,mat> LUD(){
    assert(n==m);
    mat A=*this;
    mat L=I(n);
    mat U(n,m);
    for(int i=0;i<n;i++){
      for(int t=0;t<n;t++){
	for(int h=0;h<min(i,t);h++){
	  A[i][t]-=L[i][h]*U[h][t];
	}
	if(i>t){
	  L[i][t]=A[i][t]/U[t][t];
	}
	else{
	  U[i][t]=A[i][t]/L[i][i];
	}
      }
    }
    assert(L*U==(*this));
    return {L,U};
  }
};



#endif /*mat_hpp*/
