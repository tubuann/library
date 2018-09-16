#ifndef late_seg_tree_hpp
#define late_seg_tree_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define F first
#define S second

//0-index
template<typename T,typename U> //T::要素,U::作用素
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



#endif /*late_seg_tree_hpp*/


/*
//区間加算、区間和
template<typename T,typename U>
T late_seg_tree<T,U>::F(T a,T b){
    return a+b;
}

template<typename T,typename U>
T late_seg_tree<T,U>::G(T a,U b,ll where){
    return a+b;
}

template<typename T,typename U>
U late_seg_tree<T,U>::H(U a,U b){
    return a+b;
}

template<typename T,typename U>
T late_seg_tree<T,U>::I(T a,U b,ll l,ll r){
    return a+b*(r-l);
}

*/


/*
//等差加算,区間和
template<typename T,typename U>
T late_seg_tree<T,U>::F(T a,T b){
    return a+b;
}

template<typename T,typename U>
T late_seg_tree<T,U>::G(T a,U b,ll where){
    return a+b.F+where*b.S;
}

template<typename T,typename U>
U late_seg_tree<T,U>::H(U a,U b){
    return {a.F+b.F,a.S+b.S};
}

template<typename T,typename U>
T late_seg_tree<T,U>::I(T a,U b,ll l,ll r){
    return a+((b.F+l*b.S)+(b.F+(r-1)*b.S))*(r-l)/2;
}
*/
