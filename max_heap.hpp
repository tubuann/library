#ifndef max_heap_hpp
#define max_heap_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;

//1-index
template<typename T>
class max_heap{
private:
  vector<T> tree;
  bool F(T,T); //me,parent true->change
  bool G(T,T); //child,child true->left false->right

  void heap(ull where){
    if(where==1){return;}
    if(F(tree[where],tree[where/2])){
      swap(tree[where],tree[where/2]);
      heap(where/2);
    }
  }

  ull last(){return tree.size()-1;}

  void merge(ll where){
    ll l=where*2;
    ll r=where*2+1;
    if(tree.size()-1<l){
      if(where==last()){tree.erase(--tree.end()); return;}
      tree[where]=tree[last()];
      heap(where);
      tree.erase(--tree.end());
      return;
    }
    if(tree.size()-1<r){
      tree[where]=tree[l];
      merge(l);
      return;
    }
    if(G(tree[l],tree[r])){
      tree[where]=tree[l];
      merge(l);
    }
    else{
      tree[where]=tree[r];
      merge(r);
    }
  }

public:
  max_heap(){tree.resize(1);}

  void push(T a){
    tree.push_back(a);
    heap(tree.size()-1);
  }

  T front(){
    assert(!empty());
    T ret=tree[1];
    merge(1);
    return ret;
  }

  void clear(){tree.clear();}

  ull size(){return tree.size();}

  bool empty(){
    if(tree.size()==1){return true;}
    return false;
  }
};



#endif /*max_heap_hpp*/

/*
//max_heap
template<typename T>
bool max_heap<T>::F(T where,T parent){
    if(where>parent){return true;}
    return false;
}

template<typename T>
bool max_heap<T>::G(T a,T b){
    if(a>b){return true;}
    return false;
}
*/

/*
//min_heap
template<typename T>
bool max_heap<T>::F(T where,T parent){
    if(where<parent){return true;}
    return false;
}

template<typename T>
bool max_heap<T>::G(T a,T b){
    if(a<b){return true;}
    return false;
}
*/
