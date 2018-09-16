#ifndef Binary_search_hpp
#define Binary_search_hpp

#include<bits/stdc++.h>
using namespace std;

template<typename T,typename U> //T::位置 U::探す対象
class Binary_search{
private:
  T l;
  T r;
  bool break_condition(T,T,U); //true::break false::continue
  bool judge(T,U); //true::smaller false::bigger
public:
  Binary_search(T l,T r):l(l),r(r){}

  pair<T,T> search(U u){
    T ld=l;
    T rd=r;
    while(!break_condition(ld,rd,u)){
      T mid=(rd-ld)/2+ld;
      if(mid==ld){break;}
      if(judge(mid,u)){rd=mid;}
      else{ld=mid;}
    }
    return {ld,rd};
  }
};


#endif /*Binary_search_hpp*/


/*
  template<typename T,typename U>
inline bool Binary_search<T,U>::judge(T where,U u){
    return true;
}

template<typename T,typename U>
inline bool Binary_search<T,U>::break_condition(T l,T r,U u){
    return false;
}
*/
