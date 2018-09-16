#ifndef Topological_Sort_hpp
#define Topological_Sort_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

class Topological_Sort{
private:
  ll v;
  vector<vector<ll>> E;
  vector<ll> count;

public:
  Topological_Sort(ll v):v(v){
    E.resize(v);
    count.resize(v,0);
  }

  void add_edge(ll from,ll to){
    E[from].push_back(to);
    count[to]++;
  }

  vector<ll> sort(){
    vector<ll> c=count;
    vector<ll> ret;
    for(int i=0;i<v;i++){
      if(c[i]==0){ret.push_back(i);}
    }
    for(int i=0;i<ret.size();i++){
      for(int t=0;t<E[ret[i]].size();t++){
	ll to=E[ret[i]][t];
	c[to]--;
	if(c[to]==0){ret.push_back(to);}
      }
    }
    return ret;
  }
};



#endif /*Topological_Sort_hpp*/
