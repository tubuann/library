#ifndef Label_LCA_hpp
#define Label_LCA_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

/*
 verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=jp
*/
class Label_LCA{
private:
    ll v;
    ll root;
    vector<vector<ll>> edge;
    vector<ll> number_to_node; //number::行きがけ順(親、左、右)
    vector<ll> node_to_number;
    vector<pll> dp; //部分木のサイズ、Hevy child
    vector<vector<ll>> Label;
    bool made;
    
    void dfs(const ll &where,const ll &parent,ll &count){
        node_to_number[where]=count;
        number_to_node[count]=where;
        dp[where]={1,-1};
        ll mx=0;
        for(int i=0;i<edge[where].size();i++){
            const ll &to=edge[where][i];
            if(to==parent){continue;}
            count++;
            dfs(to,where,count);
            dp[where].F+=dp[to].F;
            if(mx<dp[to].F){
                mx=dp[to].F;
                dp[where].S=to;
            }
        }
    }
    
    void dfs2(const ll &where,const ll &parent){
        const ll &H=dp[where].S;
        if(H!=-1){
            Label[H]=Label[where];
            Label[H][Label[H].size()-1]=node_to_number[H];
            dfs2(H,where);
        }
        for(int i=0;i<edge[where].size();i++){
            const ll &to=edge[where][i];
            if(to==parent || to==H){continue;}
            Label[to]=Label[where];
            Label[to].push_back(node_to_number[to]);
            Label[to].push_back(node_to_number[to]);
            dfs2(to,where);
        }
    }
    
    void mk_tree(){
        ll count=0;
        dfs(root,-1,count);
        Label[root]={0,0};
        dfs2(root,-1);
        made=true;
    }
    
public:
    Label_LCA(ll V,ll root):v(V),root(root),edge(V),number_to_node(V),node_to_number(V),dp(V),Label(V),made(false){}
    
    void add_edge(ll u,ll v){
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    
    ll search_lca(ll a,ll b){
        if(!made){mk_tree();}
        if(a==b){return a;}
        const ll mx=5;
        const vector<ll> &A=Label[a];
        const vector<ll> &B=Label[b];
        ll r=min(A.size(),B.size())-1;
        if(A[r]==B[r]){return number_to_node[A[r]];}
        if(r>=mx && A[mx-1]==B[mx-1]){
            ll l=mx;
            while(r-l>=2){
                ll m=l+(r-l)/2;
                if(A[m]==B[m]){l=m+1;}
                else{r=m;}
            }
            for(ll i=l;i<=r;i++){
                if(A[i]!=B[i]){
                    if(i%2==0){
                        return number_to_node[A[i-1]];
                    }
                    else{
                        return number_to_node[min(A[i],B[i])];
                    }
                }
            }
            return -1;
        }
        for(int i=0;i<mx;i++){
            if(A[i]!=B[i]){
                if(i%2==0){
                    return number_to_node[A[i-1]];
                }
                else{
                    return number_to_node[min(A[i],B[i])];
                }
            }
        }
        return -1;
    }
    
    ll liner_search_lca(ll a,ll b){
        if(!made){mk_tree();}
        if(a==b){return a;}
        const vector<ll> &A=Label[a];
        const vector<ll> &B=Label[b];
        for(int i=0;i<min(A.size(),B.size());i++){
            if(A[i]!=B[i]){
                if(i%2==0){
                    return number_to_node[A[i-1]];
                }
                else{
                    return number_to_node[min(A[i],B[i])];
                }
            }
        }
        if(A.size()<B.size()){
            return number_to_node[B[A.size()-1]];
        }
        return number_to_node[A[B.size()-1]];
    }
    
    ll binary_search_lca(ll a,ll b){
        if(!made){mk_tree();}
        if(a==b){return a;}
        const vector<ll> &A=Label[a];
        const vector<ll> &B=Label[b];
        ll l=0;
        ll r=min(A.size(),B.size())-1;
        if(A[r]==B[r]){return number_to_node[A[r]];}
        while(r-l>=2){
            ll m=l+(r-l)/2;
            if(A[m]==B[m]){l=m+1;}
            else{r=m;}
        }
        for(ll i=l;i<=r;i++){
            if(A[i]!=B[i]){
                if(i%2==0){
                    return number_to_node[A[i-1]];
                }
                else{
                    return number_to_node[min(A[i],B[i])];
                }
            }
        }
        return -1;
    }
    
    void test(){
        cout<<"test"<<endl;
        for(int i=0;i<v;i++){
            cout<<Label[i].size()<<endl;
        }
        cout<<endl;
    }
};



#endif /*Label_LCA_hpp*/
