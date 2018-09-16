#ifndef Flow_hpp
#define Flow_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

class Flow{
private:
  struct edge{
    ll to;
    ll cap;
    ll rev;
  };

  ll INF;
  ll v;
  vector<vector<edge>> e;
  vector<bool> used;

  void reset_used(){
    for(int i=0;i<used.size();i++){used[i]=false;}
  }

  ll dfs(ll where,ll to,ll flow){
    if(where==to){return flow;}
    used[where]=true;
    for(int i=0;i<e[where].size();i++){
      edge &E=e[where][i];
      if(!used[E.to] && E.cap>0){
	ll d=dfs(E.to,to,min(flow,E.cap));
	if(d>0){
	  E.cap-=d;
	  e[E.to][E.rev].cap+=d;
	  return d;
	}
      }
    }
    return 0;
  }

public:
  Flow(ll v):v(v){
    e.resize(v);
    used.resize(v,false);
    INF=1e18+7;
  }

  void add_edge(ll from,ll to,ll cap){
    e[from].push_back((edge){to,cap,(ll)e[to].size()});
    e[to].push_back((edge){from,0,(ll)e[from].size()-1});
  }

  ll max_flow(ll s,ll t){
    vector<vector<edge>> ed=e;
    ll flow=0;
    while(1){
      reset_used();
      ll f=dfs(s,t,INF);
      if(f==0){break;}
      flow+=f;
    }
    e=ed;
    return flow;
  }
};



#endif /*Flow_hpp*/
