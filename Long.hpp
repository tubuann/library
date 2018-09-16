#ifndef Long_hpp
#define Long_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

class Long{
private:
  typedef unsigned long ul;
  //true::+ false::-
  bool sign;
  //left::small right::big
  deque<bool> N;

  void clean(){
    while(N.size()>0 && N[N.size()-1]==false){
      N.pop_back();
    }
  }

  bool bit(ul k) const {
    assert(k<N.size());
    return N[k];
  }

  void resize(ul k){N.resize(k);}

public:
  Long(deque<bool> N={},bool sign=true):N(N),sign(sign){clean();}

  Long(ll n){
    sign=true;
    if(n<0){sign=false; n*=-1;}
    for(int i=0;i<63;i++){
      N.push_back(n>>i&1);
    }
    clean();
  }

  //right::big left::small
  Long(vector<ll> n,bool sign=true,ll x=10):sign(sign){
    Long ret(0);
    Long k(1);
    reverse(n.begin(),n.end());
    for(ul i=0;i<n.size();i++){
      ret=ret+k*n[i];
      k=k*x;
    }
    N=ret.N;
  }

  //10進数表記
  Long(string s){
    sign=true;
    Long ret(0);
    Long k(1);
    Long x(10);
    reverse(s.begin(),s.end());
    if(s[s.size()-1]=='-'){sign=false; s.pop_back();}
    for(ul i=0;i<s.size();i++){
      ret=ret+k*(s[i]-'0');
      k=k*x;
    }
    N=ret.N;
  }

  Long(vector<Long> A,ll bit_size,bool sign=true):sign(sign){
    for(int i=0;i<A.size();i++){
      A[i].resize(bit_size);
      for(int t=0;t<bit_size;t++){
	N.push_back(A[i][t]);
      }
    }
    clean();
  }

  bool & operator [] (ul k){
    assert(k<N.size());
    return N[k];
  }

  Long operator << (ul k){
    Long ret(N);
    for(ul i=0;i<k;i++){
      ret.N.push_front(false);
    }
    return ret;
  }

  Long operator >> (ul k){
    Long ret(N);
    for(ul i=0;i<k && ret.size()>0;i++){
      ret.N.pop_front();
    }
    return ret;
  }

  bool operator < (const Long &a) const {
    Long l(N,sign);
    if(a==l){return false;}
    if(a.sign==true && sign==true){
      if(a.size()>N.size()){return true;}
      if(a.size()<N.size()){return false;}
      for(ll i=a.size()-1;i>=0;i--){
	if(a.bit(i)==N[i]){continue;}
	if(a.bit(i)){return true;}
	return false;
      }
      return false;
    }
    if(a.sign==true && sign==false){
      return true;
    }
    if(a.sign==false && sign==true){
      return false;
    }
    if(a.sign==false && sign==false){
      if(a.size()<N.size()){return true;}
      if(a.size()>N.size()){return false;}
      for(ll i=a.size()-1;i>=0;i--){
	if(a.bit(i)==N[i]){continue;}
	if(a.bit(i)){return false;}
	return true;
      }
    }
    return false;
  }

  bool operator <= (const Long &a) const {
    Long l(N,sign);
    if(a==l){return true;}
    return l<a;
  }

  bool operator > (const Long &a) const {
    Long l(N,sign);
    return a<l;
  }

  bool operator >= (const Long &a) const {
    Long l(N,sign);
    return a<=l;
  }

  bool operator == (const Long &a) const {
    if(a.size()!=N.size()){return false;}
    if(a.size()==0){return true;}
    if(a.sign!=sign){return false;}
    for(int i=0;i<a.size();i++){
      if(a.bit(i)!=N[i]){return false;}
    }
    return true;
  }

  bool operator != (const Long &a) const {
    Long l(N,sign);
    return !(l==a);
  }

  Long operator & (Long a){
    Long l(N,sign);
    ll mx=max(l.size(),a.size());
    a.resize(mx);
    l.resize(mx);
    for(ul i=0;i<mx;i++){
      if(a[i] && l[i]){
	a[i]=1;
      }
      else{
	a[i]=0;
      }
    }
    a.sign=true;
    a.clean();
    return a;
  }

  Long operator | (Long a){
    Long l(N,sign);
    ll mx=max(l.size(),a.size());
    a.resize(mx);
    l.resize(mx);
    for(ul i=0;i<mx;i++){
      if(a[i] || l[i]){
	a[i]=1;
      }
      else{
	a[i]=0;
      }
    }
    a.sign=true;
    a.clean();
    return a;
  }

  Long operator xor (Long a){
    Long l(N,sign);
    ll mx=max(l.size(),a.size());
    a.resize(mx);
    l.resize(mx);
    for(ul i=0;i<mx;i++){
      if(a[i]!=l[i]){
	a[i]=1;
      }
      else{
	a[i]=0;
      }
    }
    a.sign=true;
    a.clean();
    return a;
  }

  Long operator + (Long a){
    Long l(N,sign);
    ll mx=max(l.size(),a.size())+1;
    if(a.sign==l.sign){
      a.resize(mx);
      l.resize(mx);
      bool k=false;
      for(ul i=0;i<mx;i++){
	int count=0;
	if(a[i]){count++;}
	if(l[i]){count++;}
	if(k){count++;}
	a[i]=count%2;
	k=count/2;
      }
      a.clean();
      return a;
    }
    if(a.sign==true){swap(l,a);}
    if(l==re_sign(a)){return Long();}
    if(l>re_sign(a)){
      bool k=false;
      l.resize(mx);
      a.resize(mx);
      for(ul i=0;i<mx;i++){
	int count=0;
	if(l[i]){count++;}
	if(a[i]){count--;}
	if(k){count--;}
	l[i]=count%2;
	if(count<0){k=true;}
	else{k=false;}
      }
      l.clean();
      return l;
    }
    bool k=false;
    l.resize(mx);
    a.resize(mx);
    for(ul i=0;i<mx;i++){
      int count=0;
      if(a[i]){count++;}
      if(l[i]){count--;}
      if(k){count--;}
      a[i]=count%2;
      if(count<0){k=true;}
      else{k=false;}
    }
    a.clean();
    return a;
  }

  Long operator - (Long a){
    Long l(N,sign);
    return l+re_sign(a);
  }

  Long operator * (Long a){
    Long l(N,sign);
    Long ret(0);
    bool f=true;
    if(a.sign==false){a=re_sign(a); f=!f;}
    if(l.sign==false){l=re_sign(l); f=!f;}
    for(ll i=0;i<a.size();i++){
      if(a[i]){
	ret=ret+(l<<i);
      }
    }
    if(!f){ret=re_sign(ret);}
    return ret;
  }

  Long operator * (ll a){
    Long l(N,sign);
    return l*Long(a);
  }

  Long operator / (Long a){
    assert(a.size()!=0);
    Long l(N,sign);
    Long ret(0);
    Long I(1);
    if(abs(l)<abs(a)){return Long();}
    ll k=l.size()-a.size();
    bool f=true;
    if(a.sign==false){a=re_sign(a); f=!f;}
    if(l.sign==false){l=re_sign(l); f=!f;}
    a=a<<k;
    I=I<<k;
    for(ll i=k;i>=0;i--){
      while(l>=a){
	l=l-a;
	ret=ret+I;
      }
      a=a>>1;
      I=I>>1;
    }
    if(!f){ret=re_sign(ret);}
    return ret;
  }

  Long operator % (Long a){
    assert(a.size()!=0);
    Long l(N,sign);
    if(abs(l)<abs(a)){return l;}
    ll k=l.size()-a.size();
    bool f=true;
    if(a.sign==false){a=re_sign(a); f=!f;}
    if(l.sign==false){l=re_sign(l); f=!f;}
    a=a<<k;
    for(ll i=k;i>=0;i--){
      while(l>=a){
	l=l-a;
      }
      a=a>>1;
    }
    if(!f){l=re_sign(l);}
    return l;
  }

  Long pow(Long x){
    Long a(N,sign);
    assert(x>=0);
    Long ret(1);
    for(ull i=0;i<x.size();i++){
      if(x[i]){ret=ret*a;}
      a=a*a;
    }
    return ret;
  }

  Long mod_pow(Long x,Long mod){
    Long a(N,sign);
    a=a%mod;
    assert(x>=0);
    Long ret(1);
    for(ull i=0;i<x.size();i++){
      if(x[i]){ret=ret*a; ret=ret%mod;}
      a=a*a;
      a=a%mod;
    }
    return ret;
  }

  Long abs(Long a){
    if(a.sign==false){a=re_sign(a);}
    return a;
  }

  Long re_sign(Long a){a.sign=!a.sign; return a;}

  ul size() const {return N.size();}

  void clear(){
    sign=true;
    N.clear();
  }

  //10進数表記
  string to_string(){
    if(N.size()==0){return {'0'};}
    pair<vector<ll>,bool> a=to_vector(10);
    string s;
    if(a.S==false){s.push_back('-');}
    for(ul i=0;i<a.F.size();i++){
      s.push_back('0'+a.F[i]);
    }
    return s;
  }

  pair<vector<Long>,bool> to_vector(Long X){
    assert(X>Long(1));
    vector<Long> ret;
    Long l(N,sign);
    l=abs(l);
    while(l.size()>0){
      ret.push_back(l%X);
      l=l/X;
    }
    reverse(ret.begin(),ret.end());
    return {ret,sign};
  }

  pair<vector<Long>,bool> to_bit_vector(ul bit_size){
    vector<Long> ret;
    for(ll i=0;i<N.size();i+=bit_size){
      deque<bool> R(bit_size,false);
      for(ll t=0;i+t<N.size() && t<bit_size;t++){
	if(N[i+t]){R[t]=true;}
      }
      ret.push_back(Long(R,true));
    }
    return {ret,sign};
  }
  
  pair<vector<ll>,bool> to_vector(ll x){
    assert(x>1);
    vector<ll> ret(N.size()+10,0);
    vector<ll> k(N.size()+10,0);
    k[0]=1;
    for(ul i=0;i<N.size();i++){
      if(N[i]){
	for(ul t=0;t<N.size();t++){
	  ret[t]+=k[t];
	  if(ret[t]>=x){
	    ret[t+1]+=ret[t]/x;
	    ret[t]%=x;
	  }
	}
      }
      for(ul t=0;t<N.size();t++){
	k[t]*=2;
      }
      for(ul t=0;t<N.size();t++){
	if(k[t]>=x){
	  k[t+1]+=k[t]/x;
	  k[t]%=x;
	}
      }
    }
    while(ret.size()>0 && ret[ret.size()-1]==0){ret.pop_back();}
    reverse(ret.begin(),ret.end());
    return {ret,sign};
  }

  ll to_ll(Long l){
    ll k=0;
    ll a=1;
    for(int i=0;i<l.size();i++){
      if(l[i]){k+=a;}
      a*=2;
    }
    if(!l.sign){k*=-1;}
    return k;
  }

  ll out(){
    ll k=0;
    ll a=1;
    for(int i=0;i<N.size();i++){
      if(N[i]){k+=a;}
      a*=2;
    }
    if(!sign){k*=-1;}
    return k;
  }
};



#endif /*Long_hpp*/
