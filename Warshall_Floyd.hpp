#ifndef Warshall_Floyd_hpp
#define Warshall_Floyd_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

template<typename T>
class Warshall_Floyd{
private:
  typedef vector<vector<T>> edge;
  ll v;
  edge E;
  T err;

public:
  Warshall_Floyd(ll v,T err):v(v),err(err){E.resize(v,vector<T>(v,err));}

  void add_edge(ll from,ll to,T cost){
    E[from][to]=min(E[from][to],cost);
  }

  edge search(){
    return search(E);
  }

  edge search(edge e){
    for(int k=0;k<e.size();k++){
      for(int i=0;i<e.size();i++){
	for(int t=0;t<e.size();t++){
	  e[i][t]=min(e[i][t],e[i][k]+e[k][t]);
	}
      }
    }
    return e;
  }
};




#endif /*Warshall_Floyd_hpp*/
