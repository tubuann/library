#ifndef hash_map_hpp
#define hash_map_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define F first
#define S second


//メモリー容量に気をつける
template<typename Key,typename T>
class hash_map{
private:
  typedef pair<Key,T> P;
  vector<P> map;
  vector<bool> used;
  const ll mod=9996211;
  const ll mod2=1000000007;
  const ll large_mod=39293857263967;
  const ll small_mod=5984471;
  const ll prime=8018477;

  ll hash(Key);

  ll pls(ll a){return (a+prime)%mod;}

  T F(T,T);

  ll mod_pow(ll a,ll x,ll mod){
    a%=mod;
    ll ret=1;
    for(ll i=0;i<63;i++){
      if(x>>i&1){ret*=a; ret%=mod;}
      a*=a;
    }
    return ret;
  }

public:
  hash_map(){
    map.resize(mod+1);
    used.resize(mod,false);
  }

  P* end(){return &map[mod];}

  P* find(Key k){
    ll w=hash(k);
    for(ll i=0;i<mod;i++){
      if(!used[w]){break;}
      if(map[w].F==k){return &map[w];}
      w=pls(w);
    }
    return end();
  }

  P* insert(Key k,T t){
    ll w=hash(k);
    for(ll i=0;i<mod;i++){
      if(!used[w] || map[w].F==k){
	used[w]=true;
	map[w].F=k;
	map[w].S=t;
	return &map[w];
      }
      w=pls(w);
    }
    return end();
  }

  P* merge(Key k,T t){
    ll w=hash(k);
    for(ll i=0;i<mod;i++){
      if(!used[w] || map[w].F==k){
	used[w]=true;
	map[w].F=k;
	map[w].S=F(map[w].S,t);
	return &map[w];
      }
      w=pls(w);
    }
    return end();
  }
};



#endif /*hash_map_hpp*/



/*
//keyがlong longの場合
template<typename Key,typename T>
ll hash_map<Key,T>::hash(Key k){
    mt19937 mt(k+large_mod);
    mt(); mt(); mt();
    return mt()%mod;
}

template<typename Key,typename T>
T hash_map<Key,T>::F(T a,T b){return a+b;}
*/
