#ifndef weight_LCA_hpp
#define weight_LCA_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second


class weight_LCA{
private:
  typedef pair<ll,vector<pll>> node; //depth,parents,cost
  ll root;
  ll v;
  vector<node> tree;
  vector<vector<pll>> E; //to,cost
  ll High; //高さのlog

  void bfs(){
    tree[root]={0,{{root,0}}};
    queue<ll> q;
    q.push(root);
    vector<bool> done(v,false);
    while(!q.empty()){
      ll where=q.front();
      q.pop();
      if(done[where]){continue;}
      done[where]=true;
      for(int i=0;i<E[where].size();i++){
	if(!done[E[where][i].F]){
	  tree[E[where][i].F].F=tree[where].F+1;
	  tree[E[where][i].F].S={{where,E[where][i].S}};
	  q.push(E[where][i].F);
	}
      }
    }
  }

public:
  weight_LCA(ll v,ll root):v(v),root(root){
    tree.resize(v);
    E.resize(v);
  }

  //双方向のエッジでもよい
  void add_edge(ll from,ll to,ll cost){
    E[from].push_back({to,cost});
  }

  //searchの前に行う
  void mk_tree(){
    bfs();
    bool j=true;
    for(int i=0;j;i++){
      j=false;
      for(int t=0;t<v;t++){
	ll cost=tree[t].S[i].S;
	ll P=tree[t].S[i].F;
	cost+=tree[P].S[i].S;
	P=tree[P].S[i].F;
	tree[t].S.push_back({P,cost});
	if(P!=root){j=true;}
      }
    }
    High=tree[root].S.size();
  }

    //parent,cost
    pll search_parent(ll a,ll h){
        if(tree[a].F<=h){return {root,tree[a].S[High-1].S};}
        ll cost=0;
        for(ll i=High-1;i>=0;i--){
            if((1<<i)&h){
                cost+=tree[a].S[i].S;
                a=tree[a].S[i].F;
            }
        }
        return {a,cost};
    }

    //parent,a_cost_b_cost
    pair<ll,pll> search_lca(ll a,ll b){
        ll dif=tree[a].F-tree[b].F;
        ll a_cost=0;
        ll b_cost=0;
        if(0>dif){
            pll k=search_parent(b,-1*dif);
            b=k.F;
            b_cost+=k.S;
        }
        else{
            pll k=search_parent(a,dif);
            a=k.F;
            a_cost+=k.S;
        }
        for(ll i=High-1;i>=0;i--){
            if(tree[a].S[i].F!=tree[b].S[i].F){
                a_cost+=tree[a].S[i].S;
                a=tree[a].S[i].F;
                b_cost+=tree[b].S[i].S;
                b=tree[b].S[i].F;
            }
        }
        while(a!=b){
            a_cost+=tree[a].S[0].S;
            a=tree[a].S[0].F;
            b_cost+=tree[b].S[0].S;
            b=tree[b].S[0].F;
        }
        return {a,{a_cost,b_cost}};
    }

  ll high(ll a){
    return tree[a].F;
  }
};






#endif /*weight_LCA_hpp*/
