#ifndef LCA_hpp
#define LCA_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second


class LCA{
private:
  typedef pair<ll,vector<ll>> node; //depth,parents
  ll root;
  ll v;
  vector<node> tree;
  vector<vector<ll>> E;
  ll High; //高さのlog

  void bfs(){
    tree[root]={0,{root}};
    queue<ll> q;
    q.push(root);
    vector<bool> done(v,false);
    while(!q.empty()){
      ll where=q.front();
      q.pop();
      if(done[where]){continue;}
      done[where]=true;
      for(int i=0;i<E[where].size();i++){
	if(!done[E[where][i]]){
	  tree[E[where][i]].F=tree[where].F+1;
	  tree[E[where][i]].S={where};
	  q.push(E[where][i]);
	}
      }
    }
  }

public:
  LCA(ll v,ll root):v(v),root(root){
    tree.resize(v);
    E.resize(v);
  }

  //双方向のエッジでもよい
  void add_edge(ll from,ll to){
    E[from].push_back(to);
  }

  //searchの前に行う
  void mk_tree(){
    bfs();
    bool j=true;
    for(int i=0;j;i++){
      j=false;
      for(int t=0;t<v;t++){
	ll P=tree[t].S[i];
	P=tree[P].S[i];
	tree[t].S.push_back(P);
	if(P!=root){j=true;}
      }
    }
    High=tree[root].S.size();
  }

  ll search_parent(ll a,ll h){
    if(tree[a].F<=h){return root;}
    for(ll i=High-1;i>=0;i--){
      if((1<<i)&h){a=tree[a].S[i];}
    }
    return a;
  }

  ll search_lca(ll a,ll b){
    ll dif=tree[a].F-tree[b].F;
    if(0>dif){swap(a,b); dif=abs(dif);}
    a=search_parent(a,dif);
    for(ll i=High-1;i>=0;i--){
      if(tree[a].S[i]!=tree[b].S[i]){
	a=tree[a].S[i];
	b=tree[b].S[i];
      }
    }
    while(a!=b){
      a=tree[a].S[0];
      b=tree[b].S[0];
    }
    return a;
  }

  ll high(ll a){
    return tree[a].F;
  }
};



#endif /*LCA_hpp*/
