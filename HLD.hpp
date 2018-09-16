#ifndef HLD_hpp
#define HLD_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

//nodeに値がある場合
template<typename T,typename U> //T::要素,U::作用素
class HLD{
private:
  //0-index
  class late_seg_tree{
  private:
    typedef pair<T,U> node;
    vector<vector<node>> tree;
    ll high;
    T err_T;
    U err_U;
    ll err;

    T F(T,T); //要素のマージ (要素,要素)
    T G(T,U,ll); //作用素->要素 (要素,作用素,場所)
    U H(U,U); //作用素のマージ (作用素,作用素)
    T I(T,U,ll,ll); //作用素->区間要素 (要素,作用素,l,r) [l,r)

    ll bit_size(ll a){
      for(int i=1;i<63;i++){
	if(1<<i >= a){return i;}
      }
      return err;
    }

    //[l,r)
    void update(ll h,ll where,ll l,ll r,U u){
      ll L=where<<(high-h-1);
      ll R=(where+1)<<(high-h-1);
      if(r<=L || R<=l){return;}
      if(h==high-1){tree[h][where].F=G(tree[h][where].F,u,where); return;}
      if(l<=L && R<=r){
	tree[h][where].S=H(tree[h][where].S,u);
	tree[h][where].F=F(tree[h+1][where*2].F,tree[h+1][where*2+1].F);
	tree[h][where].F=I(tree[h][where].F,tree[h][where].S,L,R);
      }
      else{
	update(h+1,where*2,l,r,u);
	update(h+1,where*2+1,l,r,u);
	tree[h][where].F=F(tree[h+1][where*2].F,tree[h+1][where*2+1].F);
	tree[h][where].F=I(tree[h][where].F,tree[h][where].S,L,R);
      }
    }

    T search(ll h,ll where,ll l,ll r){
      ll L=where<<(high-h-1);
      ll R=(where+1)<<(high-h-1);
      if(r<=L || R<=l){return err_T;}
      if(h==high-1){return tree[h][where].F;}
      if(l<=L && R<=r){return tree[h][where].F;}
      else{
	update(h+1,where*2,L,R,tree[h][where].S);
	update(h+1,where*2+1,L,R,tree[h][where].S);
	tree[h][where].S=err_U;
	T ret=err_T;
	ret=F(ret,search(h+1,where*2,l,r));
	ret=F(ret,search(h+1,where*2+1,l,r));
	return ret;
      }
      return err_T;
    }

  public:
    late_seg_tree(ull size,T err_T,U err_U):err_T(err_T),err_U(err_U){
      err=1e18+7;
      high=bit_size(size)+1;
      tree.resize(high);
      for(int i=0;i<high;i++){
	tree[i].resize(1<<i,{err_T,err_U});
      }
    }

    late_seg_tree(vector<T> t,T err_T,U err_U):err_T(err_T),err_U(err_U){
      err=1e18+7;
      high=bit_size(t.size())+1;
      tree.resize(high);
      for(int i=0;i<high;i++){
	tree[i].resize(1<<i,{err_T,err_U});
      }
      for(int i=0;i<t.size();i++){
	tree[high-1][i]={t[i],err_U};
      }
      for(ll h=high-2;h>=0;h--){
	for(int i=0;i<tree[h].size();i++){
	  tree[h][i].F=F(tree[h+1][i*2].F,tree[h+1][i*2+1].F);
	}
      }
    }

    void update(ll l,ll r,U u){
      update(0,0,l,r,u);
    }

    T search(ll l,ll r){
      return search(0,0,l,r);
    }
  };

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

  struct node{
    ll high;
    ll children;
    ll edge_number;
    ll parent;
    vector<ll> child;
    T a;
  };

  struct Edge{
    ll parent;
    ll high;
    ll low;
    ll begin;
    ll end;
    late_seg_tree seg;
  };

  bool made;
  ll v;
  ll root;
  vector<node> nodes;
  LCA lca;
  vector<Edge> E;
  T err_T;
  U err_U;
  vector<vector<ll>> edge;
  T F(T,T); //要素のマージ (要素,要素)
  U P(U,ll,ll,bool); //作用素->セグ木の作用素 (作用素、エッジの始点の高さ、エッジの終点の高さ、向き) true::down false::up

  bool err(const node &a)const{
    if(a.high==-1 && a.children==-1 && a.edge_number==-1 && a.parent==-1 && a.child==vector<ll>()){return true;}
    return false;
  }

  ll dfs(ll where){
    ll count=0;
    for(int i=0;i<edge[where].size();i++){
      if(err(nodes[edge[where][i]])){
	nodes[where].child.push_back(edge[where][i]);
	nodes[edge[where][i]].parent=where;
	nodes[edge[where][i]].high=nodes[where].high+1;
	count+=dfs(edge[where][i]);
      }
    }
    count++;
    nodes[where].children=count;
    return count;
  }

  void MK_TREE(){
    if(made){return;}
    made=true;
    lca.mk_tree();
    nodes[root].parent=root;
    nodes[root].high=0;
    dfs(root);
    ll count=0;
    stack<ll> s;
    s.push(root);
    while(!s.empty()){
      ll w=s.top();
      s.pop();
      if(nodes[w].edge_number!=-1){continue;}
      ll where=w;
      ll parent=nodes[w].parent;
      vector<T> tree;
      ll end=-1;
      while(1){
	tree.push_back(nodes[where].a);
	nodes[where].edge_number=count;
	if(nodes[where].children==1){end=where; break;}
	ll mx=0;
	ll to=-1;
	for(int i=0;i<nodes[where].child.size();i++){
	  ll t=nodes[where].child[i];
	  if(nodes[t].children>mx){mx=nodes[t].children; to=t;}
	  s.push(t);
	}
	where=to;
      }
      E.push_back({parent,nodes[w].high,nodes[end].high,w,end,late_seg_tree(tree,err_T,err_U)});
      count++;
    }
  }

  //[low,high]
  void up_update(ll where,ll low,ll high,U u){
    ll High=E[where].high;
    ll Low=E[where].low;
    u=P(u,High,Low,false);
    high=max(High,high);
    low=min(Low,low);
    high-=High;
    low-=High;
    E[where].seg.update(high,low+1,u);
  }

  //[high,low]
  void down_update(ll where,ll high,ll low,U u){
    ll High=E[where].high;
    ll Low=E[where].low;
    u=P(u,High,Low,true);
    high=max(High,high);
    low=min(Low,low);
    high-=High;
    low-=High;
    E[where].seg.update(high,low+1,u);
  }

  void UPDATE(ll s,ll t,U u){
    ll mid=lca.search_lca(s,t);
    if(s!=mid){
      ll w=s;
      ll high=nodes[mid].high+1;
      while(1){
	ll low=nodes[w].high;
	ll where=nodes[w].edge_number;
	if(low<high){break;}
	up_update(where,low,high,u);
	w=E[where].parent;
      }
    }
    ll w=t;
    ll high=nodes[mid].high;
    while(1){
      ll low=nodes[w].high;
      ll where=nodes[w].edge_number;
      if(low<high){break;}
      down_update(where,high,low,u);
      if(where==0){break;}
      w=E[where].parent;
    }
  }

  //[low,high]
  T up_search(ll where,ll low,ll high){
    ll High=E[where].high;
    ll Low=E[where].low;
    high=max(High,high);
    low=min(Low,low);
    high-=High;
    low-=High;
    return E[where].seg.search(high,low+1);
  }

  //[high,low]
  T down_search(ll where,ll high,ll low){
    ll High=E[where].high;
    ll Low=E[where].low;
    high=max(High,high);
    low=min(Low,low);
    high-=High;
    low-=High;
    return E[where].seg.search(high,low+1);
  }

  T SEARCH(ll s,ll t){
    T ret=err_T;
    ll mid=lca.search_lca(s,t);
    if(s!=mid){
      ll w=s;
      ll high=nodes[mid].high+1;
      while(1){
	ll low=nodes[w].high;
	ll where=nodes[w].edge_number;
	if(low<high){break;}
	ret=F(ret,up_search(where,low,high));
	w=E[where].parent;
      }
    }
    ll w=t;
    ll high=nodes[mid].high;
    while(1){
      ll low=nodes[w].high;
      ll where=nodes[w].edge_number;
      if(low<high){break;}
      ret=F(ret,down_search(where,high,low));
      if(where==0){break;}
      w=E[where].parent;
    }
    return ret;
  }

public:
  HLD(ll v,ll root,T err_T,U err_U):v(v),root(root),err_T(err_T),err_U(err_U),lca(v,root){
    edge.resize(v);
    nodes.resize(v,{-1,-1,-1,-1,{},err_T});
    made=false;
  }

  HLD(ll v,ll root,vector<T> t,T err_T,U err_U):v(v),root(root),err_T(err_T),err_U(err_U),lca(v,root){
    lca(v,root);
    edge.resize(v);
    nodes.resize(v,{-1,-1,-1,-1,{},err_T});
    made=false;
    for(int i=0;i<v;i++){
      nodes[i].a=t[i];
    }
  }

  //無向
  void add_edge(ll from,ll to){
    edge[from].push_back(to);
    edge[to].push_back(from);
    lca.add_edge(from,to);
    lca.add_edge(to,from);
  }

  void update(ll from,ll to,U u){
    MK_TREE();
    UPDATE(from,to,u);
  }

  T search(ll s,ll t){
    MK_TREE();
    return SEARCH(s,t);
  }
};




#endif /*HLD_hpp*/

/*
//区間加算、区間和

//要素のマージ (要素,要素)
template<typename T,typename U>
T HLD<T,U>::F(T a,T b){
  return a+b;
}

//作用素->セグ木の作用素 (作用素、エッジの始点の高さ、エッジの終点の高さ、向き) true::down false::up
template<typename T,typename U>
U HLD<T,U>::P(U u,ll high,ll low,bool f){
  return u;
}

template<typename T,typename U>
T HLD<T,U>::late_seg_tree::F(T a,T b){
  return a+b;
}

template<typename T,typename U>
T HLD<T,U>::late_seg_tree::G(T a,U b,ll where){
  return a+b;
}

template<typename T,typename U>
U HLD<T,U>::late_seg_tree::H(U a,U b){
  return a+b;
}

template<typename T,typename U>
T HLD<T,U>::late_seg_tree::I(T a,U b,ll l,ll r){
  return a+b*(r-l);
}
*/
