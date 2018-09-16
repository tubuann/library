#ifndef Connection_hpp
#define Connection_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second

class Connection{
private:
  ll v;
  vector<vector<ll>> E;
  vector<ll> tree; //depth
  vector<bool> con;

  pll dfs(ll where,ll count){
    tree[where]=count;
    ll c=0;
    ll mx_c=0;
    ll mi_c=count;
    ll mi_m=count;
    count++;
    for(int i=0;i<E[where].size();i++){
      ll t=E[where][i];
      if(tree[t]==-1){
	pll child=dfs(t,count);
	mx_c=max(mx_c,child.F);
	mi_c=min(mi_c,child.F);
	c++;
      }
      else{
	mi_m=min(mi_m,tree[t]);
      }
    }
    if(mx_c!=tree[where]){con[where]=false;}
    return {min(mi_c,mi_m),c};
  }

  void clear(){
    tree.resize(v);
    con.resize(v);
    for(int i=0;i<v;i++){
      tree[i]=-1;
      con[i]=true;
    }
  }

public:
  Connection(ll v):v(v){
    E.resize(v);
  }

  void add_edge(ll from,ll to){
    E[from].push_back(to);
    E[to].push_back(from);
  }

  vector<ll> search(){
    clear();
    vector<ll> ret;
    for(int i=0;i<v;i++){
      if(tree[i]==-1){
	ll r=dfs(i,0).S;
	if(r<2){con[i]=false;}
      }
    }
    for(int i=0;i<v;i++){
      if(con[i]){
	ret.push_back(i);
      }
    }
    return ret;
  }
};





#endif /*Connection_hpp*/
