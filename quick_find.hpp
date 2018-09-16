#ifndef quick_find_hpp
#define quick_find_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

template<typename T> //要素
class quick_find{
private:
  vector<vector<ll>> tree;
  unordered_map<T,ll> element_number; //要素->number
  unordered_map<ll,T> number_element; //number->要素
  unordered_map<ll,ll> number_where; //number->parent

public:
  quick_find(vector<T> e){
    tree.resize(e.size());
    for(int i=0;i<e.size();i++){
      element_number[e[i]]=i;
      number_element[i]=e[i];
      number_where[i]=i;
      tree[i].push_back(i);
    }
  }

  bool is_same(T a,T b){
    if(parent(a)==parent(b)){return true;}
    return false;
  }

  ll parent(T a){return number_where[element_number[a]];}

  void mk_same(T a,T b){
    if(is_same(a,b)){return;}
    if(tree[parent(a)].size()>tree[parent(b)].size()){
      ll P=parent(b);
      for(ll i=0;i<tree[P].size();i++){
	tree[parent(a)].push_back(tree[P][i]);
	number_where[tree[P][i]]=parent(a);
      }
      tree[P].clear();
    }
    else{
      ll P=parent(a);
      for(ll i=0;i<tree[P].size();i++){
	tree[parent(b)].push_back(tree[P][i]);
	number_where[tree[P][i]]=parent(b);
      }
      tree[P].clear();
    }
  }

  vector<T> same(T a){
    ll P=parent(a);
    vector<T> ret;
    for(int i=0;i<tree[P].size();i++){
      ret.push_back(number_element[tree[P][i]]);
    }
    return ret;
  }
};



#endif /*quick_find_hpp*/
