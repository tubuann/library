#ifndef press_hpp
#define press_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
#define F first
#define S second

template<typename T>
vector<T> press(vector<T> a,T start,T dist){
  vector<T> b=a;
  sort(b.begin(),b.end());
  T count=start;
  map<T,T> M;
  for(int i=0;i<b.size();i++){
    if(M.find(b[i])==M.end()){M[b[i]]=count; count+=dist;}
  }
  for(int i=0;i<a.size();i++){
    a[i]=M[a[i]];
  }
  return a;
}

vector<pll> press(vector<pll> a,ll start,ll dist){
  vector<ll> x,y;
  for(int i=0;i<a.size();i++){
    x.push_back(a[i].F);
    y.push_back(a[i].S);
  }
  x=press(x,start,dist);
  y=press(y,start,dist);
  for(int i=0;i<a.size();i++){
    a[i]={x[i],y[i]};
  }
  return a;
}



#endif /*press_hpp*/
