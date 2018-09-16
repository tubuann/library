#ifndef Chu_Liu_hpp
#define Chu_Liu_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define F first
#define S second

template<typename T>
class Chu_Liu{
private:
  typedef pair<T,ll> edge; //cost,from
  vector<vector<edge>> E;
  ll V;
  T err;


public:
  Chu_Liu(ll V,T err):V(V),err(err){E.resize(V);}

  void add_edge(ll from,ll to,T cost){E[to].push_back({cost,from});}

  void sort_edge(vector<vector<edge>> &e){
    for(int i=0;i<e.size();i++){sort(e[i].begin(),e[i].end());}
  }

  T search(ll root){return search(root,V,E);}

  T search(ll root,ll v,vector<vector<edge>> e){
    if(v<=1){return (T)0;}
    vector<edge> mins(v,{(T)0,root});
    vector<ll> group(v);
    vector<bool> closed(v,false);
    T cost=0;
    ll count=1;
    for(int i=0;i<v;i++){group[i]=i+1;}
    group[root]=0;
    sort_edge(e);
    for(int i=0;i<v;i++){
      if(i==root){continue;}
      assert(e[i].size()>0);
      mins[i]=e[i][0];
    }

    vector<bool> used(v,false);
    used[root]=true;
    for(int i=0;i<v;i++){
      if(used[i]){continue;}
      vector<ll> chain;
      ll where=i;
      set<ll> done;
      while(!used[where]){
	done.insert(where);
	chain.push_back(where);
	used[where]=true;
	where=mins[where].S;
      }
      if(group[where]==0){
	for(int t=0;t<chain.size();t++){
	  group[chain[t]]=0;
	  cost+=mins[chain[t]].F;
	}
      }
      else if(done.find(where)!=done.end()){
	bool in_cycle=false;
	for(int t=0;t<chain.size();t++){
	  if(chain[t]==where){in_cycle=true;}
	  group[chain[t]]=count;
	  if(!in_cycle){count++;}
	  if(in_cycle){
	    closed[chain[t]]=true;
	    cost+=mins[chain[t]].F;
	  }
	}
	count++;
      }
      else{
	for(int t=0;t<chain.size();t++){
	  group[chain[t]]=count;
	  count++;
	}
      }
    }

    vector<vector<edge>> new_edge;
    new_edge.resize(count);
    for(int i=0;i<v;i++){
      if(group[i]==0){continue;}
      if(!closed[i]){
	for(int t=0;t<e[i].size();t++){
	  if(group[e[i][t].S]==group[i]){continue;}
	  e[i][t].S=group[e[i][t].S];
	  new_edge[group[i]].push_back(e[i][t]);
	}
	continue;
      }
      for(int t=1;t<e[i].size();t++){
	if(group[e[i][t].S]==group[i]){continue;}
	e[i][t].F-=mins[i].F;
	e[i][t].S=group[e[i][t].S];
	new_edge[group[i]].push_back(e[i][t]);
      }
    }
    cost+=search(0,count,new_edge);
    return cost;
  }
};


#endif /*Chu_Liu_hpp*/
