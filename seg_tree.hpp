#ifndef seg_tree_hpp
#define seg_tree_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;



ll bit_size(ll a){
    for(int i=0;i<63;i++){
        if(1<<i >= a){return i;}
    }
    return 63;
}


//0-index
template<typename T>
class seg_tree{
private:
  vector<vector<T>> tree;
  ll high;
  T err;

  T search(ll h,ll where,ll l,ll r){
    ll L=where<<(high-1-h);
    ll R=(where+1)<<(high-1-h);
    if(l<=L && R<=r){return tree[h][where];}
    if(r<=L || R<=l){return err;}
    return F(search(h+1,where*2,l,r),search(h+1,where*2+1,l,r));
  }

  void update(ll h,ll where,ll l,ll r,T a){
    ll L=where<<(high-1-h);
    ll R=(where+1)<<(high-1-h);
    if(l<=L && R<=r){tree[h][where]=F(tree[h][where],a); return;}
    if(r<=L || R<=l){return;}
    update(h+1,where*2,l,r,a);
    update(h+1,where*2+1,l,r,a);
  }

public:
  seg_tree(vector<T> t={}){
    high=bit_size(t.size())+1;
    tree.resize(high);
    for(int i=0;i<high;i++){
      tree[i].resize((1<<i),err);
    }
    for(int i=0;i<t.size();i++){
      tree[high-1][i]=t[i];
    }
    for(int i=high-2;i>=0;i--){
      for(int t=0;t<tree[i].size();t++){
	tree[i][t]=F(tree[i+1][t*2],tree[i+1][t*2+1]);
      }
    }
  }

  seg_tree(vector<T> t,T a){
    err=a;
    high=bit_size(t.size())+1;
    tree.resize(high);
    for(int i=0;i<high;i++){
      tree[i].resize((1<<i),a);
    }
    for(int i=0;i<t.size();i++){
      tree[high-1][i]=t[i];
    }
    for(int i=high-2;i>=0;i--){
      for(int t=0;t<tree[i].size();t++){
	tree[i][t]=F(tree[i+1][t*2],tree[i+1][t*2+1]);
      }
    }
  }

  seg_tree(ll size,T a){
    err=a;
    high=bit_size(size)+1;
    tree.resize(high);
    for(int i=0;i<high;i++){
      tree[i].resize((1<<i),err);
    }
    for(int i=0;i<tree[high-1].size();i++){
      tree[high-1][i]=a;
    }
    for(int i=high-2;i>=0;i--){
      for(int t=0;t<tree[i].size();t++){
	tree[i][t]=F(tree[i+1][t*2],tree[i+1][t*2+1]);
      }
    }
  }

  seg_tree(ll size){
    high=bit_size(size)+1;
    tree.resize(high);
    for(int i=0;i<high;i++){
      tree[i].resize((1<<i),err);
    }
  }

  T F(T,T);

  void insert(ll where,T a){
    tree[high-1][where]=a;
    for(int i=high-2;i>=0;i--){
      where/=2;
      tree[i][where]=F(tree[i+1][where*2],tree[i+1][where*2+1]);
    }
  }

  void insert(ll l,ll r,T a){
    update(0,0,l,r,a);
  }

  //[l,r)
  T ans(ll l,ll r){
    return search(0,0,l,r);
  }

  T ans(ll where){
    T ret=tree[high-1][where];
    for(int i=high-2;i>=0;i--){
      where/=2;
      ret=F(ret,tree[i][where]);
    }
    return ret;
  }
};



#endif /*seg_tree_hpp*/

/*
template<typename T>
T seg_tree<T>::F(T a,T b){
    return min(a,b);
}
*/
