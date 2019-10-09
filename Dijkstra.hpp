#ifndef Dijkstra_hpp
#define Dijkstra_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define F first
#define S second


template<typename T>
class Dijkstra{
private:
    typedef pair<T,ll> edge; //cost,to
    typedef edge node;
    typedef pair<T,vector<ll>> pass;
    
    template<typename U>
    vector<U> pls(vector<U> a,vector<U> b){
        for(int i=0;i<b.size();i++){a.push_back(b[i]);}
        return a;
    }
    
    template<typename U>
    vector<U> pls(vector<U> a,U b){
        a.push_back(b);
        return a;
    }
    
    ll v;
    vector<vector<edge>> E;
    T err;
public:
    Dijkstra(ll v,T err):v(v),err(err){E.resize(v);}
    
    void add_edge(ll from,ll to,T cost){
        E[from].push_back({cost,to});
    }
    
    //MLE注意
    pass pass_search(ll root,ll to){
        return pass_search(root)[to];
    }
    
    //MLE注意
    vector<pass> pass_search(ll root){
        vector<pass> ret(v,{err,vector<ll>()});
        ret[root]={0,{root}};
        priority_queue<node,vector<node>,greater<node>> q;
        q.push({0,root});
        vector<bool> used(v,false);
        while(!q.empty()){
            node where=q.top();
            q.pop();
            if(used[where.S]){continue;}
            used[where.S]=true;
            for(int i=0;i<E[where.S].size();i++){
                if(ret[E[where.S][i].S].F>where.F+E[where.S][i].F){
                    ret[E[where.S][i].S].F=where.F+E[where.S][i].F;
                    ret[E[where.S][i].S].S=pls(ret[where.S].S,where.S);
                    q.push({ret[E[where.S][i].S].F,E[where.S][i].S});
                }
            }
        }
        return ret;
    }
    
    vector<T> search(ll root){
        vector<T> ret(v,err);
        ret[root]=0;
        priority_queue<node,vector<node>,greater<node>> q;
        q.push({0,root});
        vector<bool> used(v,false);
        while(!q.empty()){
            node where=q.top();
            q.pop();
            if(used[where.S]){continue;}
            used[where.S]=true;
            for(int i=0;i<E[where.S].size();i++){
                if(ret[E[where.S][i].S]>where.F+E[where.S][i].F){
                    ret[E[where.S][i].S]=where.F+E[where.S][i].F;
                    q.push({ret[E[where.S][i].S],E[where.S][i].S});
                }
            }
        }
        return ret;
    }
    
    T search(ll root,ll to){return search(root)[to];}
};




#endif /*Dijkstra_hpp*/
