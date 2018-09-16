#ifndef HL_LCA_hpp
#define HL_LCA_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

/*
 verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=jp
 */
class HL_LCA{
private:
    struct E{
        vector<int> N;
        vector<vector<int>> C;
        
        E(unsigned long size):N(size),C(size){}
        
        unsigned long size(){return N.size();}
    };
    
    int v;
    int root;
    vector<vector<int>> edge;
    vector<vector<pair<int,int>>> node;
    vector<pair<int,int>> dp;
    vector<E> Edge;
    
    void dfs(int where,int parent){
        int children=1;
        int mx=0;
        int Hedge=-1;
        for(int i=0;i<edge[where].size();i++){
            int to=edge[where][i];
            if(to==parent){continue;}
            dfs(to,where);
            children+=dp[to].first;
            if(mx<dp[to].first){mx=dp[to].first; Hedge=to;}
        }
        dp[where]={children,Hedge};
    }
    
    void build(){
        dfs(root,-1);
        queue<pair<pair<int,int>,pair<int,int>>> q; //自分,自分の親,親のエッジ、親の深さ
        q.push({{root,-1},{-1,-1}});
        while(!q.empty()){
            vector<int> Hedge;
            pair<pair<int,int>,pair<int,int>> W=q.front(); q.pop();
            pair<int,int> R=W.second;
            pair<int,int> w=W.first;
            node[w.first].push_back({0,0});
            while(w.first!=-1){
                Hedge.push_back(w.first);
                node[w.first]=node[Hedge[0]];
                node[w.first][node[w.first].size()-1]={Hedge.size()-1,0};
                int to=dp[w.first].second;
                int count=1;
                for(int i=0;i<edge[w.first].size();i++){
                    int k=edge[w.first][i];
                    if(k==to || k==w.second){continue;}
                    q.push({{k,w.first},{Edge.size(),Hedge.size()-1}});
                    node[k]=node[w.first];
                    node[k][node[k].size()-1].second=count;
                    count++;
                }
                w.second=w.first;
                w.first=to;
            }
            Edge.push_back(E(Hedge.size()));
            E &e=Edge[Edge.size()-1];
            for(int i=0;i<Hedge.size();i++){
                e.N[i]=Hedge[i];
            }
            if(R.first!=-1){
                Edge[R.first].C[R.second].push_back((int)Edge.size()-1);
            }
        }
    }
    
    int search(const vector<pair<int,int>> &A) const {
        int W=0;
        for(int i=0;i<A.size();i++){
            if(A[i].second==0){return Edge[W].N[A[i].first];}
            W=Edge[W].C[A[i].first][A[i].second-1];
        }
        return -1;
    }
    
public:
    HL_LCA(const int &v,const int &root,const vector<vector<int>> &edge):v(v),root(root),edge(edge),node(v),dp(v,{-1,-1}){
        assert(v==edge.size());
        build();
    }
    
    int search_lca(const int &a,const int &b){
        if(a==b){return a;}
        vector<pair<int,int>> M;
        const vector<pair<int,int>> &A=node[a],&B=node[b];
        for(int i=0;i<A.size() && i<B.size();i++){
            if(A[i]!=B[i] || A[i].second==0){
                M.push_back({min(A[i].first,B[i].first),0});
                return search(M);
            }
            else{
                M.push_back(A[i]);
            }
        }
        return -1;
    }
    
    
    
    void test(){
        for(int i=0;i<node.size();i++){
            cout<<i;
            for(int t=0;t<node[i].size();t++){
                cout<<"  "<<node[i][t].first<<" "<<node[i][t].second;
            }
            cout<<endl;
        }
        /*
         for(int i=0;i<Edge.size();i++){
         for(int t=0;t<Edge[i].size();t++){
         cout<<Edge[i].N[t]<<" ";
         for(int h=0;h<Edge[i].C[t].size();h++){
         cout<<" "<<Edge[i].C[t][h];
         }
         cout<<endl;
         }
         cout<<endl<<endl;
         }
         */
    }
};




#endif /*HL_LCA_hpp*/
