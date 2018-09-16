#ifndef SCC_hpp
#define SCC_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second



//強連結成分分解
class SCC{
private:
  vector<vector<ll>> E;
  vector<vector<ll>> rev;
  ll V;
  vector<ll> v;
  vector<ll> group;

  void dfs(ll where,ll &count){
    v[where]=-2;
    for(int i=0;i<E[where].size();i++){
      ll t=E[where][i];
      if(v[t]!=-1){continue;}
      dfs(t,count);
    }
    v[where]=count;
    count++;
  }

  void first(){
    ll count=0;
    for(int i=0;i<V;i++){
      if(v[i]==-1){dfs(i,count);}
    }
  }

  void rev_dfs(ll where,ll count){
    group[where]=count;
    for(int i=0;i<rev[where].size();i++){
      ll t=rev[where][i];
      if(group[t]!=-1){continue;}
      rev_dfs(t,count);
    }
  }

  void second(){
    vector<pll> number;
    for(int i=0;i<V;i++){
      number.push_back({v[i],i});
    }
    sort(number.begin(),number.end(),greater<pll>());
    ll count=0;
    for(int i=0;i<V;i++){
      ll where=number[i].S;
      if(group[where]==-1){
	rev_dfs(where,count);
	count++;
      }
    }
  }

  void clear(ll a){
    for(ll i=a;i<V;i++){
      v[i]=-1;
      group[i]=-1;
    }
  }

public:
  SCC(ll V=0):V(V){
    v.resize(V,-1);
    E.resize(V);
    rev.resize(V);
    group.resize(V,-1);
  }

  void add_edge(ll from,ll to){
    E[from].push_back(to);
    rev[to].push_back(from);
  }

  void add_node(){
    V++;
    v.resize(V);
    E.resize(V);
    rev.resize(V);
    group.resize(V);
  }

  void add_node(ll number){
    V+=number;
    v.resize(V);
    E.resize(V);
    rev.resize(V);
    group.resize(V);
  }

  vector<ll> solve(){
    clear();
    first();
    second();
    return group;
  }

  //グラフの形を保ったまま初期化
  void clear(){
    for(int i=0;i<V;i++){
      v[i]=-1;
      group[i]=-1;
    }
  }
};




#endif /*SCC_hpp*/
