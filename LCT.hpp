#ifndef LCT_hpp
#define LCT_hpp

#include "LCA.hpp"
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second



template<typename T,typename U> //要素、作用素
class LCT{
private:
  struct node{
    ll idx;
    ll Lidx,Ridx;
    node* l;
    node* r;
    node* p;
    T a;
    T sum;
    U u;
    //U inv;
    bool is_root;
        
    node(T a,U u):a(a),sum(a),u(u),l(NULL),r(NULL),p(NULL),is_root(false),Lidx(-1),Ridx(-1),idx(-1){}
  };
    
  typedef node* P;

  struct iterator{
    P where;
        
    iterator(const P &where):where(where){}
        
    iterator(const node &where):where(&where){}
        
    iterator & operator = (const node* &w){
      where=w;
      return *this;
    }
        
    iterator & operator = (const node &w){
      where=&w;
      return *this;
    }
        
    iterator & operator = (const iterator &I){
      where=I.where;
      return *this;
    }
        
    bool operator == (const iterator &I) const {
      return where==I.where;
    }
        
    bool operator != (const iterator &I) const {
      return where!=I.where;
    }
        
    ll & idx(){return (*where).idx;}
        
    ll & L(){return (*where).Lidx;}
        
    ll & R(){return (*where).Ridx;}
        
    node* & l(){return (*where).l;}
        
    node* & r(){return (*where).r;}
        
    node* & p(){return (*where).p;}
        
    T & a(){return (*where).a;}
        
    T & sum(){return (*where).sum;}
        
    U & u(){return (*where).u;}
        
    //U & inv(){return (*where).inv;}
        
    bool & is_root(){return (*where).is_root;}
        
    iterator & to_up(){
      where=(*where).p;
      return *this;
    }
        
    iterator & to_left(){
      where=(*where).l;
      return *this;
    }
        
    iterator & to_right(){
      where=(*where).r;
      return *this;
    }
  };
    
  typedef iterator I;
    
  T F(T,T); //(要素,要素)->要素 要素同士のマージ
  T G(T,ll,ll,U); //(区間,作用素)->要素 区間に作用素を作用させる [high,low]
  U H(U,U); //(作用素,作用素)->作用素 作用素同士のマージ
  U J(U,bool,ll,ll,ll); //(作用素,向き,区間)->作用素 作用素から木の作用素を作る true::down false::up
    
  vector<P> index; //idxとは別
  T err_T;
  U err_U;
  I root;
  ll Proot;
  LCA lca;
  list<node> tree;
    
  //高さ、番号 [s,t)
  I mk_binarytree(const vector<ll> &a,ll s,ll t){
    if(t-s<=0){return NULL;}
    if(t-s==1){
      renew(index[a[s]]);
      return index[a[s]];
    }
    ll m=s+(t-s)/2;
    I W(index[a[m]]);
    I l=mk_binarytree(a,s,m);
    I r=mk_binarytree(a,m+1,t);
    W.l()=l.where;
    W.r()=r.where;
    if(r.where!=NULL){
      r.p()=W.where;
    }
    if(l.where!=NULL){
      l.p()=W.where;
    }
    renew(W);
    return W;
  }
    
  void dfs(vector<vector<ll>> &edge,vector<pll> &Tree,ll where,ll parent){
    ll child=1;
    ll mx=-1;
    ll C=-1;
    for(int i=0;i<edge[where].size();i++){
      ll to=edge[where][i];
      if(to==parent){continue;}
      else{
	dfs(edge,Tree,to,where);
	child+=Tree[to].F;
	if(Tree[to].F>mx){mx=Tree[to].F; C=to;}
      }
    }
    Tree[where]={child,C};
  }
    
  void mk_tree(vector<vector<ll>> &edge){
    for(int i=0;i<edge.size();i++){
      for(int t=0;t<edge[i].size();t++){
	lca.add_edge(i,edge[i][t]);
      }
    }
    lca.mk_tree();
    for(int i=0;i<edge.size();i++){
      I W(index[i]);
      W.idx()=lca.high(i);
      W.R()=W.idx();
      W.L()=W.idx();
    }
    vector<pll> Tree(edge.size()); //部分木、ヘビーエッジ
    dfs(edge,Tree,Proot,-1);
    stack<pll> s; //where,parent
    s.push({0,-1});
    while(!s.empty()){
      vector<ll> A;
      pll w=s.top(); s.pop();
      ll P=w.S;
      while(1){
	ll to=Tree[w.F].S;
	for(int i=0;i<edge[w.F].size();i++){
	  ll k=edge[w.F][i];
	  if(k==to || k==w.S){continue;}
	  s.push({k,w.F});
	}
	A.push_back(w.F);
	if(to==-1){
	  I W=mk_binarytree(A,0,A.size());
	  W.is_root()=true;
	  if(P==-1){root=W.where;}
	  else{W.p()=index[P];}
	  break;
	}
	w.S=w.F;
	w.F=to;
      }
    }
  }
    
  inline void merge(I W){
    W.sum()=W.a();
    I l(W.l());
    I r(W.r());
    if(W.l()!=NULL){
      W.sum()=F(l.sum(),W.sum());
    }
    if(W.r()!=NULL){
      W.sum()=F(W.sum(),r.sum());
    }
    W.sum()=G(W.sum(),W.L(),W.R(),W.u());
  }
    
  inline void down(I W){
    W.a()=G(W.a(),W.idx(),W.idx(),W.u());
    I l(W.l());
    I r(W.r());
    if(W.l()!=NULL){
      l.u()=H(W.u(),l.u());
      merge(l);
    }
    if(W.r()!=NULL){
      r.u()=H(W.u(),r.u());
      merge(r);
    }
    W.u()=err_U;
  }
    
  I rotateL(I W){
    assert(W.r()!=NULL);
    I r(W.r());
    I rl(r.l());
    down(r);
    //rl
    if(r.l()!=NULL){
      rl.p()=W.where;
    }
    //r
    r.p()=W.p();
    r.l()=W.where;
    r.L()=W.L();
    //p
    if(root==W){root=r; r.is_root()=true; W.is_root()=false;}
    else if(W.is_root()){r.is_root()=true; W.is_root()=false;}
    else{
      I p(W.p());
      if(p.l()==W.where){p.l()=r.where;}
      else{p.r()=r.where;}
    }
    //W
    W.p()=r.where;
    W.r()=rl.where;
    if(rl.where!=NULL){W.R()=rl.R();}
    else{W.R()=W.idx();}
        
    r.u()=W.u();
    W.u()=err_U;
    merge(W);
    merge(r);
        
    return r;
  }
    
  I rotateR(I W){
    assert(W.l()!=NULL);
    I l(W.l());
    I lr(l.r());
    down(l);
    //lr
    if(l.r()!=NULL){
      lr.p()=W.where;
    }
    //l
    l.p()=W.p();
    l.r()=W.where;
    l.R()=W.R();
    //p
    if(root==W){root=l; l.is_root()=true; W.is_root()=false;}
    else if(W.is_root()){l.is_root()=true; W.is_root()=false;}
    else{
      I p(W.p());
      if(p.l()==W.where){p.l()=l.where;}
      else{p.r()=l.where;}
    }
    //W
    W.p()=l.where;
    W.l()=lr.where;
    if(lr.where!=NULL){W.L()=lr.L();}
    else{W.L()=W.idx();}
        
    l.u()=W.u();
    W.u()=err_U;
    merge(W);
    merge(l);
        
    return l;
  }
    
  void splay(I W){
    while(W.is_root()==false){
      I p(W.p());
      if(p.is_root()){
	if(p.l()==W.where){
	  rotateR(p);
	}
	else{
	  rotateL(p);
	}
      }
      else{
	I pp(p.p());
	if(pp.l()==p.where && p.l()==W.where){
	  rotateR(pp);
	  rotateR(p);
	}
	else if(pp.l()==p.where && p.r()==W.where){
	  rotateL(p);
	  rotateR(pp);
	}
	else if(pp.r()==p.where && p.r()==W.where){
	  rotateL(pp);
	  rotateL(p);
	}
	else if(pp.r()==p.where && p.l()==W.where){
	  rotateR(p);
	  rotateL(pp);
	}
      }
    }
  }
    
  void renew(I W){
    W.sum()=W.a();
    W.L()=W.idx();
    W.R()=W.idx();
    if(W.l()!=NULL){
      I l(W.l());
      W.sum()=F(l.sum(),W.sum());
      W.L()=l.L();
    }
    if(W.r()!=NULL){
      I r(W.r());
      W.sum()=F(W.sum(),r.sum());
      W.R()=r.R();
    }
    W.sum()=G(W.sum(),W.L(),W.R(),W.u());
  }
    
  void Link(I W){
    splay(W);
    while(W!=root){
      I p(W.p());
      splay(p);
      down(p);
      if(p.r()!=NULL){
	I r(p.r());
	r.is_root()=true;
      }
      p.r()=W.where;
      W.is_root()=false;
      renew(p);
      splay(W);
    }
  }

  /* 
  ll number(I W){
    node* w=W.where;
    for(int i=0;i<index.size();i++){
      if(index[i]==w){return i;}
    }
    return -1;
  }
  */

  //[L,R]
  void update(I W,U u,ll L,ll R){
    //number(W);
    if(R<W.L() || W.R()<L){return;}
    if(L<=W.L() && W.R()<=R){
      W.u()=H(W.u(),u);
      merge(W);
      return;
    }
    else{
      if(L<=W.idx() && W.idx()<=R){
          W.a()=G(W.a(),W.idx(),W.idx(),u);
      }
      if(W.l()!=NULL){update(W.l(),u,L,R);}
      if(W.r()!=NULL){update(W.r(),u,L,R);}
      merge(W);
    }
  }
    
  T sum(I W,ll L,ll R){
    if(R<W.L() || W.R()<L){return err_T;}
    if(L<=W.L() && W.R()<=R){
      return W.sum();
    }
    else{
      down(W);
      T ret=err_T;
      if(L<=W.idx() && W.idx()<=R){
	ret=F(ret,W.a());
      }
      if(W.l()!=NULL){ret=F(sum(W.l(),L,R),ret);}
      if(W.r()!=NULL){ret=F(ret,sum(W.r(),L,R));}
      return ret;
    }
    return err_T;
  }
    
    
    
public:
  LCT(vector<vector<ll>> &edge,ll rootnum,T err_T,U err_U):lca(edge.size(),rootnum),Proot(rootnum),err_T(err_T),err_U(err_U),root(NULL){
    index.resize(edge.size());
    for(int i=0;i<edge.size();i++){
      tree.push_front(node(err_T,err_U));
      index[i]=&(*tree.begin());
    }
    mk_tree(edge);
  }
    
  LCT(vector<vector<ll>> &edge,ll Proot,vector<ll> v,T err_T,U err_U):Proot(Proot),err_T(err_T),err_U(err_U),lca(edge.size(),Proot){
    index.resize(edge.size());
    for(int i=0;i<edge.size();i++){
      tree.push_front(node(v[i],err_U));
      index[i]=&(*tree.begin());
    }
    mk_tree(edge);
  }
    
  //[s,m),[m,t]
  void update(ll s,ll t,U u){
    ll m=lca.search_lca(s,t);
    I S=index[s];
    I To(index[t]);
    if(s!=m){
      Link(S);
      update(S,J(u,false,lca.high(s),lca.high(m),lca.high(t)),lca.high(m)+1,lca.high(s));
    }
    Link(To);
    update(To,J(u,true,lca.high(s),lca.high(m),lca.high(t)),lca.high(m),lca.high(t));
  }
    
  //[s,m),[m,t]
  T search(ll s,ll t){
    ll m=lca.search_lca(s,t);
    I S=index[s];
    I To(index[t]);
    T ret=err_T;
    if(s!=m){
      Link(S);
      ret=F(ret,sum(S,lca.high(m)+1,lca.high(s)));
    }
    Link(To);
    ret=F(ret,sum(To,lca.high(m),lca.high(t)));
    return ret;
  }
};



#endif /*LCT_hpp*/




/*
//等差数列
//(要素,要素)->要素 要素同士のマージ
template<typename T,typename U>
T LCT<T,U>::F(T a,T b){
    return (a+b)%MOD;
}

//(区間,作用素)->要素 区間に作用素を作用させる [high,low]
template<typename T,typename U>
T LCT<T,U>::G(T a,ll high,ll low,U u){
    u.F%=MOD; u.S%=MOD;
    T avr=u.F+u.S*high;
    avr+=u.F+u.S*low;
    avr*=low-high+1;
    assert(avr%2==0);
    avr/=2;
    return a+avr;
}

//(作用素,作用素)->作用素 作用素同士のマージ
template<typename T,typename U>
U LCT<T,U>::H(U a,U b){
    return {(a.F+b.F)%MOD,(a.S+b.S)%MOD};
}

//(作用素,向き,区間)->作用素 作用素から木の作用素を作る true::down false::up
template<typename T,typename U>
U LCT<T,U>::J(U u,bool down,ll s,ll m,ll t){
    u.F%=MOD; u.S%=MOD;
    if(down){
        u.F+=(s-m)*u.S;
        u.F-=u.S*m;
        u.F%=MOD;
    }
    else{
        u.F+=u.S*s;
        u.F%=MOD;
        u.S*=-1;
    }
    return u;
}
*/

/*
//一点加算区間和
//(要素,要素)->要素 要素同士のマージ
template<typename T,typename U>
T LCT<T,U>::F(T a,T b){
    return a+b;
}

//(区間,作用素)->要素 区間に作用素を作用させる [high,low]
template<typename T,typename U>
T LCT<T,U>::G(T a,ll high,ll low,U u){
    return a+u;
}

//(作用素,作用素)->作用素 作用素同士のマージ
template<typename T,typename U>
U LCT<T,U>::H(U a,U b){
    return a+b;
}

//(作用素,向き,区間)->作用素 作用素から木の作用素を作る true::down false::up
template<typename T,typename U>
U LCT<T,U>::J(U u,bool down,ll s,ll m,ll t){
    return u;
}
*/
