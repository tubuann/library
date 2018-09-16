#ifndef Bridge_hpp
#define Bridge_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second

//無向
class Bridge{
private:
  typedef vector<vector<ll>> edge;
  edge E;
  ll v;
  vector<pll> count;

  ll dfs(ll w,ll depth,ll parent){
    if(count[w].F!=-1){return 1e18;}
    count[w]={depth,depth};
    bool p=true;
    for(int i=0;i<E[w].size();i++){
      if(E[w][i]==parent){
	if(!p){count[w].S=min(count[E[w][i]].F,count[w].S);}
	p=false;
      }
      else if(count[E[w][i]].F==-1){count[w].S=min(dfs(E[w][i],depth+1,w),count[w].S);}
      else{count[w].S=min(count[E[w][i]].F,count[w].S);}
    }
    return count[w].S;
  }

public:
  Bridge(ll v,edge e={}):v(v),E(e){
    E.resize(v);
    count.resize(v,{-1,-1});
  }

  void add_edge(ll from,ll to){
    E[from].push_back(to);
    E[to].push_back(from);
  }

  void search(){
    dfs(0,1,-1);
  }

  bool is_bridge(ll u,ll v){
    if(count[u].F==count[v].F){return false;}
    if(count[u].F>count[v].F){swap(u,v);}
    if(count[u].F>=count[v].S){return false;}
    return true;
  }

  vector<pll> bridge(){
    vector<pll> ret;
    for(int i=0;i<v;i++){
      for(int t=0;t<E[i].size();t++){
	if(i<E[i][t] && is_bridge(i,E[i][t])){ret.push_back({i,E[i][t]});}
      }
    }
    return ret;
  }

  void test(){
    for(int i=0;i<v;i++){
      cout<<"test "<<i<<" "<<count[i].F<<" "<<count[i].S<<endl;
    }
  }
};
 

#endif /*Bridge_hpp*/
