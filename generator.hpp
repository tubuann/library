#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<ll,ll> pll;
typedef long double D;
typedef complex<D> P;
#define F first
#define S second
const ll MOD=1000000007;
//const ll MOD=998244353;

template<typename T,typename U>istream & operator >> (istream &i,pair<T,U> &A){i>>A.F>>A.S; return i;}
template<typename T>istream & operator >> (istream &i,vector<T> &A){for(auto &I:A){i>>I;} return i;}
template<typename T,typename U>ostream & operator << (ostream &o,const pair<T,U> &A){o<<A.F<<" "<<A.S; return o;}
template<typename T>ostream & operator << (ostream &o,const vector<T> &A){ll i=A.size(); for(auto &I:A){o<<I<<(--i?" ":"");} return o;}

#ifndef generator_h
#define generator_h


namespace generator_functions{
  const ll seed=3827631762932782765LL;

  mt19937_64 R(seed);

  //[mi,mx)
  ll Int(ll mi,ll mx){
    assert(mx>mi);
    ull w=mx-mi;
    ull k=1;
    while(w>k){k<<=1;}
    ull x=w;
    while(x>=w){x=R()&(k-1);}
    return (ll)x+mi;
  }
  
  template<typename T>
  vector<T>& rand_shuffle(vector<T> &ret){
    int sz=ret.size();
    for(int i=0;i<sz;i++){
      int l=Int(0,i+1);
      if(l!=i){swap(ret[l],ret[i]);}
    }
    return ret;
  }

  //[0,sz)の順列を返す
  vector<int> rand_perm(int sz){
    vector<int> ret(sz);
    for(int i=0;i<sz;i++){
      ret[i]=i;
      int l=Int(0,i+1);
      if(l!=i){swap(ret[l],ret[i]);}
    }
    return ret;
  }

  string int2str(int a,int sz=2){
    assert(a>=0);
    string ret;
    for(int i=0;i<sz;i++){ret+='0'+a%10; a/=10;}
    assert(a==0);
    return ret;
  }


  namespace tree_constructor{
    //i is root         if ret[i]=-1
    //parent(i)=ret[i]  otherwise

    //parents to edges
    vector<pair<int,int>> prts2edge(vector<int> prts){
      int sz=prts.size();
      int idx=0;
      vector<pair<int,int>> ret(sz-1);
      for(int i=0;i<sz;i++){
        if(prts[i]==-1){continue;}
        ret[idx]={prts[i],i};
        if(Int(0,2)==1){swap(ret[idx].F,ret[idx].S);}
        idx++;
      }
      rand_shuffle(ret);
      return ret;
    }

    //f is defined in [1,sz)
    //f(i)<i
    vector<int> make_tree(int sz,function<int(int)> f,bool randomize=true){
      vector<int> ret(sz,-1);
      vector<int> perm=randomize?rand_perm(sz):vector<int>();
      for(int i=1;i<sz;i++){
        int idx=i,p=f(i);
        if(randomize){idx=perm[idx]; p=perm[p];}
        ret[idx]=p;
      }
      return ret;
    }
    
    vector<int> rand_tree(int sz,bool randomize=true){
      function<int(int)> f=[&](int a){return Int(0,a);};
      return make_tree(sz,f,randomize);
    }

    //n分木
    //n=1::線グラフ
    //n=sz::うに
    vector<int> ndiv_tree(int sz,int n,bool randomize=true){
      function<int(int)> f=[&](int a){return (a-1)/n;};
      return make_tree(sz,f,randomize);
    }

    //n::足の本数,n>=0
    vector<int> mukade_tree(int sz,int n,bool randomize=true){
      n++;
      function<int(int)> f=[&](int a){return (a-1)/n*n;};
      return make_tree(sz,f,randomize);
    }
  };
  using namespace tree_constructor;
};
using namespace generator_functions;

#endif /*generator_h*/
