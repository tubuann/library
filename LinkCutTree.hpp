#ifndef LinkCutTree_hpp
#define LinkCutTree_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second


template<typename K,typename I,typename U>
struct LCT{
    K key;
    K left,right;
    function<bool(K,K)> Comp;
    
    const I I_E;
    const U U_E;
    I item,data;
    U up;
    const function<I(I,I)> F; //左、右
    const function<I(I,U,K,K,int)> G; //左、右,子の数
    const function<U(U,U)> H; //自分、親
    
    
    LCT* P;
    LCT* L;
    LCT* R;
    int children;
    
    
    LCT(const K &key,const function<bool(K,K)> &Comp,const I &I_E,const U &U_E,const function<I(I,I)> &F,const function<I(I,U,K,K,int)> &G,const function<U(U,U)> &H):key(key),left(key),right(right),Comp(Comp),I_E(I_E),U_E(U_E),item(I_E),data(I_E),up(U_E),F(F),G(G),H(H),P(NULL),L(NULL),R(NULL),children(1){}
    
    
    bool is_root() const {return P==NULL;}
    
    bool is_small_root() const {return P==NULL || (P->R!=this && P->L!=this);}
    
    void down(){
        item=G(item,up,key,key,1);
        if(L!=NULL){L->up=L->H(L->up,up); L->data=L->G(L->data,up,L->left,L->right,L->children);}
        if(R!=NULL){R->up=R->H(R->up,up); R->data=R->G(R->data,up,R->left,R->right,R->children);}
        up=U_E;
    }
    
    void RENEW(){
        children=1;
        if(L!=NULL){data=F(L->data,item); left=L->left; children+=L->children;}
        else{data=item; left=key;}
        if(R!=NULL){data=F(data,R->data); right=R->right; children+=R->children;}
        else{right=key;}
        data=G(data,up,left,right,children);
    }
    
    LCT* Rotate_R(){
        assert(L);
        down();
        L->down();
        
        LCT* ret=L;
        ret->P=P;
        if(P!=NULL && P->L==this){P->L=ret;}
        else if(P!=NULL && P->R==this){P->R=ret;}
        
        if(ret->R){L=ret->R; L->P=this;}
        else{L=NULL;}
        
        P=ret;
        ret->R=this;
        
        RENEW();
        ret->RENEW();
        
        return ret;
    }
    
    LCT* Rotate_L(){
        assert(R);
        down();
        R->down();
        
        LCT* ret=R;
        ret->P=P;
        if(P!=NULL && P->L==this){P->L=ret;}
        else if(P!=NULL && P->R==this){P->R=ret;}
        
        if(ret->L){R=ret->L; R->P=this;}
        else{R=NULL;}
        
        P=ret;
        ret->L=this;
        
        RENEW();
        ret->RENEW();
        
        return ret;
    }
    
    void Link(){
        Splay();
        while(!is_root()){
            P->Splay();
            P->down();
            P->R=this;
            P->RENEW();
            Splay();
        }
    }
    
    void Splay(){
        while(!is_small_root()){
            if(P->is_small_root()){
                if(P->L==this){P->Rotate_R();}
                else{P->Rotate_L();}
            }
            else{
                bool p1=(P->L==this);
                bool p2=(P->P->L==P);
                if(p1==p2){
                    if(p1){P->P->Rotate_R()->Rotate_R();}
                    else{P->P->Rotate_L()->Rotate_L();}
                }
                else{
                    if(p1){P->Rotate_R(); P->Rotate_L();}
                    else{P->Rotate_L(); P->Rotate_R();}
                }
            }
        }
    }
    
    LCT* expose(){
        Link();
        LCT* ret=R;
        R=NULL;
        RENEW();
        return ret;
    }
    
    void update(const U &u){
        expose();
        up=H(up,u);
        data=G(data,u,left,right,children);
    }
    
    void small_tree_update(const U &u){
        Splay();
        up=H(up,u);
        data=G(data,u,left,right,children);
    }
    
    void node_update(const U &u){
        Splay();
        item=G(item,u,key,key,1);
        RENEW();
    }
};



#endif /*LinkCutTree_hpp*/

/*
//AOJ_DSL_2_G
void RAQ_RSQ(){
    ll n,q;
    cin>>n>>q;
    auto F=[](ll a,ll b){return a+b;};
    auto G=[](ll a,ll b,ll l,ll r,int children){return a+b*children;};
    auto H=[](ll a,ll b){return a+b;};
    vector<LCT<ll,ll,ll>> A(n,LCT<ll,ll,ll>(0,greater<ll>(),0,0,F,G,H));
    for(int i=0;i<n;i++){
        A[i].key=i;
        if(i!=0){A[i].P=&A[i-1];}
        A[i].RENEW();
    }
    while(q--){
        ll com;
        cin>>com;
        if(com){
            ll x,y;
            cin>>x>>y;
            x--; y--;
            x--;
            A[y].expose();
            ll ans=A[y].data;
            if(x>=0){A[x].expose(); ans-=A[x].data;}
            cout<<ans<<endl;
        }
        else{
            ll x,y,t;
            cin>>x>>y>>t;
            x--; y--;
            A[y].update(t);
            if(x!=0){
                x--;
                A[x].update(-t);
            }
        }
    }
}

//AOJ_DSL_2_F
void RUQ_RMQ(){
    ll n,q;
    cin>>n>>q;
    auto F=[](ll a,ll b){return min(a,b);};
    auto G=[](ll a,ll b,ll l,ll r,int children){return (b==-E?a:b);};
    auto H=[](ll a,ll b){return (b==-E?a:b);};
    vector<LCT<ll,ll,ll>> A(n,LCT<ll,ll,ll>(0,greater<ll>(),(1LL<<31)-1,-E,F,G,H));
    for(int i=0;i<n;i++){
        A[i].key=i;
        if(i!=0){A[i].P=&A[i-1];}
        A[i].RENEW();
    }
    while(q--){
        ll com;
        cin>>com;
        if(com){
            ll x,y;
            cin>>x>>y;
            x--;
            A[y].expose();
            if(x>=0){cout<<A[x].expose()->data<<endl;}
            else{cout<<A[y].data<<endl;}
        }
        else{
            ll x,y,t;
            cin>>x>>y>>t;
            A[y].expose();
            if(x!=0){
                x--;
                A[x].expose()->small_tree_update(t);
            }
            else{
                A[y].small_tree_update(t);
            }
        }
    }
}

//AOJ_DGL_5_D
void AQ_RSQ_onTree(){
    ll n,q;
    cin>>n;
    auto F=[](ll a,ll b){return a+b;};
    auto G=[](ll a,ll b,ll l,ll r,int children){return a+b*children;};
    auto H=[](ll a,ll b){return a+b;};
    vector<LCT<ll,ll,ll>> A(n,LCT<ll,ll,ll>(0,greater<ll>(),0,0,F,G,H));
    for(int i=0;i<n;i++){
        A[i].key=i;
        ll k;
        cin>>k;
        while(k--){
            ll c;
            cin>>c;
            A[c].P=&A[i];
        }
        A[i].RENEW();
    }
    cin>>q;
    while(q--){
        ll com;
        cin>>com;
        if(com){
            ll x;
            cin>>x;
            A[x].expose();
            cout<<A[x].data<<endl;
        }
        else{
            ll v,w;
            cin>>v>>w;
            A[v].node_update(w);
        }
    }
}

//AOJ_DGL_5_E
void RAQ_RSQ_onTree(){
    ll n,q;
    cin>>n;
    auto F=[](ll a,ll b){return a+b;};
    auto G=[](ll a,ll b,ll l,ll r,int children){return a+b*children;};
    auto H=[](ll a,ll b){return a+b;};
    vector<LCT<ll,ll,ll>> A(n,LCT<ll,ll,ll>(0,greater<ll>(),0,0,F,G,H));
    ll sum=0;
    for(int i=0;i<n;i++){
        A[i].key=i;
        ll k;
        cin>>k;
        while(k--){
            ll c;
            cin>>c;
            A[c].P=&A[i];
        }
        A[i].RENEW();
    }
    cin>>q;
    while(q--){
        ll com;
        cin>>com;
        if(com){
            ll x;
            cin>>x;
            A[x].expose();
            cout<<A[x].data-sum<<endl;
        }
        else{
            ll v,w;
            cin>>v>>w;
            A[v].update(w);
            sum+=w;
        }
    }
}

*/
