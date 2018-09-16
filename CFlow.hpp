#ifndef CFlow_hpp
#define CFlow_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second

class CFlow{
private:
  struct edge{
    ll to;
    ll cap;
    ll rev;
    ll cost;
  };
    
  struct node{
    ll cost;
    ll flow;
    ll number;
    ll from;
    ll edge;
        
    //cost::smaller flow::bigger
    bool operator < (const node &a) const {
      if(a.cost<this->cost){return true;}
      else if(a.cost==this->cost && a.flow>this->flow){return true;}
      return false;
    }
  };
    
  ll INF;
  ll v;
  vector<vector<edge>> e;
    
public:
  CFlow(ll v):v(v){
    e.resize(v);
    INF=1e18+7;
  }
    
  void add_edge(ll from,ll to,ll cap,ll cost){
    e[from].push_back((edge){to,cap,(ll)e[to].size(),cost});
    e[to].push_back((edge){from,0,(ll)e[from].size()-1,-1*cost});
  }
    
  pll min_cost(ll s,ll t,ll flow){
    vector<vector<edge>> ed=e;
    ll cost=0;
    ll D=flow;
    vector<ll> h(v,0);
    while(flow>0){
      priority_queue<node> q;
      vector<node> V(v,{INF,0,-1,-1,-1});
      V[s]={0,flow,s,s,-1};
      q.push({0,flow,s,s,-1});
      while(!q.empty()){
	node N=q.top(); q.pop();
	ll w=N.number;
	if(N<V[w]){continue;}
	for(int i=0;i<e[w].size();i++){
	  edge &E=e[w][i];
	  node New={V[w].cost+E.cost+h[w]-h[E.to],min(N.flow,E.cap),E.to,w,i};
	  if(E.cap>0 && V[E.to]<New){
	    V[E.to]=New;
	    q.push(New);
	  }
	}
      }
      if(V[t].flow==0){break;}
      for(int i=0;i<v;i++){h[i]+=V[i].cost;}
      flow-=V[t].flow;
      ll w=t;
      while(w!=s){
	ll to=w;
	w=V[w].from;
	edge &E=e[w][V[to].edge];
	E.cap-=V[t].flow;
	e[E.to][E.rev].cap+=V[t].flow;
	cost+=V[t].flow*E.cost;
      }
      if(flow==0){break;}
    }
    e=ed;
    return {D-flow,cost};
  }
};




#endif /*CFlow_hpp*/
