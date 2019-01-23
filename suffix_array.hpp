#ifndef suffix_array_hpp
#define suffix_array_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
#define F first
#define S second


/*
検索を高速にしたい場合はローリングハッシュなどを使う
*/
class suffix_array{
private:
    typedef unsigned long ul;
    
    struct node{
        ll begin;
        ll Rank;
        node* next;
        
        inline bool operator < (const node &N) const {
            if(Rank==N.Rank){
                return (next==NULL?-1:next->Rank)<(N.next==NULL?-1:N.next->Rank);
            }
            return Rank<N.Rank;
        }
        
        node(ll begin=0,ll Rank=0,node* next=NULL):begin(begin),Rank(Rank),next(next){}
    };
    
    inline static bool pointer_cmp(node* &a,node* &b){return (*a)<(*b);}
    
    vector<node*> sa;
    vector<ll> Rank;
    const string s;
    
    void build(){
        for(int i=0;i<s.size();i++){
            *sa[i]={i,s[i],sa[i+1]};
        }
        sa[s.size()]->begin=s.size();
        sa[s.size()]->Rank=-1;
        sa[s.size()]->next=NULL;
        vector<node*> Next(s.size()+1);
        for(ll k=1;k<=s.size();k<<=1){
            sort(sa.begin(),sa.end(),pointer_cmp);
            Rank[sa[0]->begin]=0;
            Next[0]=(sa[0]->next==NULL?NULL:sa[0]->next->next);
            for(int i=1;i<=s.size();i++){
                Rank[sa[i]->begin]=Rank[sa[i-1]->begin]+(*sa[i-1]<*sa[i]?1:0);
                Next[i]=(sa[i]->next==NULL?NULL:sa[i]->next->next);
            }
            for(int i=0;i<=s.size();i++){
                sa[i]->Rank=Rank[sa[i]->begin];
                sa[i]->next=Next[i];
            }
        }
        for(int i=0;i<=s.size();i++){
            Next[sa[i]->begin]=sa[i];
        }
        for(int i=0;i<=s.size();i++){
            sa[i]->next=sa[i]->begin==s.size()?NULL:Next[sa[i]->begin+1];
        }
    }
    
    //1::greater 0::same -1::less
    int compare(const ul &saf,const string &str){
        for(int i=0;i<str.size();i++){
            if(sa[saf]->begin+i>=s.size()){return -1;}
            if(s[sa[saf]->begin+i]!=str[i]){return s[sa[saf]->begin+i]<str[i]?-1:1;}
        }
        return 0;
    }
    
public:
    suffix_array(const string &str):s(str),Rank(str.size()+1),sa(str.size()+1){
        for(int i=0;i<=str.size();i++){
            sa[i]=(node*)malloc(sizeof(node));
        }
        build();
    }
    
    ll rank(const ul &where) const {return Rank[where];}
    
    ul size() const {return sa.size();}
    
    const node & operator [] (const ul &where) const {return *sa[where];}
    
    //返すのはsuffixの番号
    ul lower_bound(const string &sub){
        ll l=0;
        ll r=s.size();
        while(r-l>4){
            ll m=l+(r-l)/2;
            if(compare(m,sub)==-1){l=m+1;}
            else{r=m;}
        }
        for(ll i=l;i<=r;i++){
            if(compare(i,sub)>=0){return i;}
        }
        return r+1;
    }
    
    //返すのはsuffixの番号
    ul upper_bound(const string &sub){
        ll l=0;
        ll r=s.size();
        while(r-l>4){
            ll m=l+(r-l)/2;
            if(compare(m,sub)<=0){l=m+1;}
            else{r=m;}
        }
        for(ll i=l;i<=r;i++){
            if(compare(i,sub)>0){return i;}
        }
        return r+1;
    }
    
    bool match(const string &sub){
        ll l=0;
        ll r=s.size();
        while(r-l>4){
            ll m=l+(r-l)/2;
            int st=compare(m,sub);
            if(st==0){return true;}
            else if(st==-1){l=m+1;}
            else{r=m-1;}
        }
        for(ll i=l;i<=r;i++){
            if(compare(i,sub)==0){return true;}
        }
        return false;
    }
};


#endif /*suffix_array_hpp*/
