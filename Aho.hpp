#ifndef Aho_hpp
#define Aho_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second


struct Aho{
    struct node{
        ll idx;
        char c;
        map<char,node*> next;
        node* parent;
        node* back;
        
        bool used;
        
        node(){
            idx=0;
            c=-1;
            parent=NULL;
            back=NULL;
            used=false;
        }
    };
    
    node root;
    ll size;
    
    ll add(const string &s){
        node* where=&root;
        for(int i=0;i<s.size();i++){
            if(where->next.find(s[i])==where->next.end()){
                node* P=(node*)calloc(1,sizeof(node));
                *P=node();
                where->next[s[i]]=P;
                P->parent=where;
                where=P;
                where->idx=size++;
                where->c=s[i];
            }
            else{
                where=where->next[s[i]];
            }
        }
        return where->idx;
    }
    
    void build(){
        queue<node*> Q;
        for(auto i=root.next.begin();i!=root.next.end();++i){
            Q.push(i->second);
        }
        while(!Q.empty()){
            node* where=Q.front();
            Q.pop();
            if(where->parent==&root){
                where->back=&root;
            }
            else{
                node* P=where->parent->back;
                while(1){
                    if(P==&root && P->next.find(where->c)==P->next.end()){where->back=&root; break;}
                    if(P->next.find(where->c)!=P->next.end()){
                        where->back=P->next.find(where->c)->second;
                        break;
                    }
                    P=P->back;
                }
            }
            for(auto i=where->next.begin();i!=where->next.end();++i){
                Q.push(i->second);
            }
        }
    }
    
    vector<ll> search(const string &s){
        vector<ll> used;
        vector<node*> B;
        node* where=&root;
        for(int i=0;i<s.size();i++){
            while(where!=&root && where->next.find(s[i])==where->next.end()){
                where=where->back;
            }
            if(where->next.find(s[i])==where->next.end()){continue;}
            where=where->next.find(s[i])->second;
            if(!where->used){
                queue<node*> q;
                q.push(where);
                while(!q.empty()){
                    node* W=q.front();
                    q.pop();
                    W->used=true;
                    used.push_back(W->idx);
                    B.push_back(W);
                    if(!W->parent->used){
                        q.push(W->parent);
                    }
                    if(!W->back->used){
                        q.push(W->back);
                    }
                }
            }
        }
        sort(used.begin(),used.end());
        for(auto &i:B){i->used=false;}
        return used;
    }
    
    Aho():root(),size(1){root.back=&root; root.used=true;}
};


#endif /*Aho_hpp*/
