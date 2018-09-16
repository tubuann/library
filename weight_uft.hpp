#ifndef weight_uft_hpp
#define weight_uft_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
#define F first
#define S second


/*
//high
template<typename T>
class weight_uft{
private:
    typedef pair<ull,T> parent_weight;
    vector<pair<parent_weight,ull>> uft; //{parent_weight,high}
    ull size;
    T err;
public:
    weight_uft(ull size,T err=(T)(1e9)):size(size),err(err){
        uft.resize(size);
        for(int i=0;i<size;i++){
            uft[i]={{i,(T)0},0};
        }
    }
    
    parent_weight search(ull where){
        if(uft[where].F.F==where){return uft[where].F;}
        parent_weight P=search(uft[where].F.F);
        uft[where].F.F=P.F;
        uft[where].F.S+=P.S;
        return uft[where].F;
    }
    
    bool same(ull a,ull b){
        if(search(a).F==search(b).F){return true;}
        return false;
    }
    
    T dist(ull from,ull to){
        if(!same(from,to)){return err;}
        return search(from).S-search(to).S;
    }
    
    bool add(ull from,ull to,T d){
        if(same(from,to) && dist(from,to)!=d){return false;}
        if(same(from,to)){return true;}
        parent_weight f=search(from);
        parent_weight t=search(to);
        if(uft[t.F].S>uft[f.F].S){
            uft[f.F].F.F=t.F;
            uft[f.F].F.S=d-f.S+t.S;
            uft[t.F].S=max(uft[t.F].S,uft[f.F].S+1);
        }
        else{
            uft[t.F].F.F=f.F;
            uft[t.F].F.S=f.S-t.S-d;
            uft[f.F].S=max(uft[f.F].S,uft[t.F].S+1);
        }
        return true;
    }
};
*/

/*
//node
template<typename T>
class weight_uft{
private:
    typedef pair<ull,T> parent_weight;
    vector<pair<parent_weight,ull>> uft; //{parent_weight,node}
    ull size;
    T err;
public:
    weight_uft(ull size,T err=(T)(1e9)):size(size),err(err){
        uft.resize(size);
        for(int i=0;i<size;i++){
            uft[i]={{i,(T)0},1};
        }
    }
    
    parent_weight search(ull where){
        if(uft[where].F.F==where){return uft[where].F;}
        parent_weight P=search(uft[where].F.F);
        uft[where].F.F=P.F;
        uft[where].F.S+=P.S;
        return uft[where].F;
    }
    
    bool same(ull a,ull b){
        if(search(a).F==search(b).F){return true;}
        return false;
    }
    
    T dist(ull from,ull to){
        if(!same(from,to)){return err;}
        return search(from).S-search(to).S;
    }
    
    bool add(ull from,ull to,T d){
        if(same(from,to) && dist(from,to)!=d){return false;}
        if(same(from,to)){return true;}
        parent_weight f=search(from);
        parent_weight t=search(to);
        if(uft[t.F].S>uft[f.F].S){
            uft[f.F].F.F=t.F;
            uft[f.F].F.S=d-f.S+t.S;
            uft[t.F].S=uft[t.F].S+uft[f.F].S;
        }
        else{
            uft[t.F].F.F=f.F;
            uft[t.F].F.S=f.S-t.S-d;
            uft[f.F].S=uft[f.F].S+uft[t.F].S;
        }
        return true;
    }
};
*/





/*
//normal
template<typename T>
class weight_uft{
private:
  typedef pair<ull,T> parent_weight;
  vector<parent_weight> uft;
  ull size;
  T err;
public:
  weight_uft(ull size,T err=(T)(1e9)):size(size),err(err){
    uft.resize(size);
    for(int i=0;i<size;i++){
      uft[i]={i,(T)0};
    }
  }

  parent_weight search(ull where){
    if(uft[where].F==where){return uft[where];}
    parent_weight P=search(uft[where].F);
    uft[where].F=P.F;
    uft[where].S+=P.S;
    return uft[where];
  }

  bool same(ull a,ull b){
    if(search(a).F==search(b).F){return true;}
    return false;
  }

  T dist(ull from,ull to){
    if(!same(from,to)){return err;}
    return search(from).S-search(to).S;
  }

  bool add(ull from,ull to,T d){
    if(same(from,to) && dist(from,to)!=d){return false;}
    if(same(from,to)){return true;}
    parent_weight f=search(from);
    parent_weight t=search(to);
    uft[f.F].F=t.F;
    uft[f.F].S=d-f.S+t.S;
    return true;
  }
};
*/
#endif /*weight_uft_hpp*/
