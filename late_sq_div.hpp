#ifndef late_sq_dvi_hpp
#define late_sq_dvi_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;


ll sq_size(ll a){
  for(int i=1;i<100000;i++){
    if(i*i>=a){return i;}
  }
  return 1e18+7;
}

template<typename T>
class late_sq_div{
private:
  typedef pair<ll,T> time_T; //big::new small::old
  vector<vector<time_T>> tree;
  vector<time_T> late;
  ll size;
  T err;
  ll time;

  void update(ll where){
    assert(0<=where && where<size);
    T ret=err;
    for(ll i=where*size;i<(where+1)*size;i++){
      tree[1][i]=max(tree[1][i],late[where]);
      tree[1][i].F=time;
      ret=F(tree[1][i].S,ret);
    }
    tree[0][where]={time,ret};
    time++;
  }

  //[l,r)
  void change(ll l,ll r,ll where,T x){
    if(r<=where*size || (where+1)*size<=l){return;}
    if(l<=where*size && (where+1)*size<=r){
      tree[0][where]={time,x};
      late[where]={time,x};
      time++;
      return;
    }
    for(ll i=max(where*size,l);i<min(r,(where+1)*size);i++){
      tree[1][i]={time,x};
    }
    update(where);
    time++;
  }

  T ans(ll l,ll r,ll where){
    if(r<=where*size || (where+1)*size<=l){return err;}
    if(l<=where*size && (where+1)*size<=r){return tree[0][where].S;}
    T ret=err;
    update(where);
    for(ll i=max(where*size,l);i<min(r,(where+1)*size);i++){
      ret=F(ret,tree[1][i].S);
    }
    return ret;
  }

public:
  late_sq_div(ll s=0,T a=0,T err=0):err(err){
    time=0;
    size=sq_size(s);
    late.resize(size,{time,err});
    tree.resize(2);
    tree[0].resize(size,{time,err});
    tree[1].resize(size*size,{time,err});
    time++;
    for(ll i=0;i<s;i++){tree[1][i]={time,a};}
    for(ll i=0;i<size;i++){update(i);}
    time++;
  }

  T F(T,T);

  //[l,r)
  void change(ll l,ll r,T x){
    for(int i=0;i<size;i++){
      change(l,r,i,x);
    }
  }

  //[l,r)
  T ans(ll l,ll r){
    T ret=err;
    for(int i=0;i<size;i++){
      ret=F(ret,ans(l,r,i));
    }
    return ret;
  }

  T ans(ll where){
    return max(tree[1][where],late[where]).S;
  }
};




#endif /*late_sq_dvi_hpp*/

/*
template<typename T>
T late_sq_div<T>::F(T a,T b){return min(a,b);}
*/
