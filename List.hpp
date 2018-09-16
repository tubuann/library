#ifndef List_hpp
#define List_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T>
class List{
private:
    typedef unsigned long ul;
    
    struct node{
        node* front;
        node* back;
        T a;
    };
    
    ul Size;
    node* root;
    
    node* create(T a){
        node* New=(node*)malloc(sizeof(node));
        assert(New!=NULL);
        (*New).a=a;
        return New;
    }
    
public:
    struct iterator{
        node* where;
        
        iterator(node* where):where(where){}
        
        iterator(T* t){
            char* C=(char*)t;
            C-=2*sizeof(node*);
            where=(node*)C;
        }
        
        iterator & operator ++ (){
            where=(*where).back;
            return *this;
        }
        
        iterator & operator -- (){
            where=(*where).front;
            return *this;
        }
        
        iterator operator ++ (int){
            iterator ret=*this;
            where=(*where).back;
            return ret;
        }
        
        iterator operator -- (int){
            iterator ret=*this;
            where=(*where).front;
            return ret;
        }
        
        iterator & operator = (const node* &w){
            where=w;
            return *this;
        }
        
        iterator & operator = (const iterator &I){
            where=I.where;
            return *this;
        }
        
        bool operator == (const iterator &I) const {
            return where==I.where;
        }
        
        bool operator != (const iterator &I) const {
            return where!=I.where;
        }
        
        T & operator * (){
            return (*where).a;
        }
        
        T* pointer(){
            return &(*where).a;
        }
    };
    
    List(){
        Size=0;
        root=create(T());
        (*root).back=root;
        (*root).front=root;
    }
    
    ~List(){
        iterator I=begin();
        while(I!=root){
            iterator E=I;
            I=(*I.where).back;
            free(E.where);
        }
        free(root);
    }
    
    iterator begin(){return iterator((*root).back);}
    
    iterator end(){return iterator(root);}
    
    ul size(){return Size;}
    
    iterator push_back(T a){
        node* New=create(a);
        node* F=(*root).front;
        (*F).back=New;
        (*New).front=F;
        (*root).front=New;
        (*New).back=root;
        Size++;
        return iterator(New);
    }
    
    iterator push_front(T a){
        node* New=create(a);
        node* B=(*root).back;
        (*root).back=New;
        (*New).front=root;
        (*B).front=New;
        (*New).back=B;
        Size++;
        return iterator(New);
    }
    
    iterator pop_back(){
        if(Size==0){return root;}
        node* E=(*root).front;
        node* F=(*E).front;
        (*F).back=root;
        (*root).front=F;
        free(E);
        Size--;
        return iterator(root);
    }
    
    iterator pop_front(){
        if(Size==0){return root;}
        node* E=(*root).back;
        node* B=(*E).back;
        (*B).front=root;
        (*root).back=B;
        free(E);
        Size--;
        return iterator(B);
    }
    
    iterator erase(iterator where){
        node* E=where.where;
        if(Size==0 || E==root){return iterator(root);}
        node* F=(*E).front;
        node* B=(*E).back;
        (*F).back=B;
        (*B).front=F;
        free(E);
        Size--;
        return iterator(B);
    }
    
    iterator erase(T* where){
        return erase(iterator(where));
    }
    
    iterator erase(node* E){
        if(Size==0 || E==root){return iterator(root);}
        node* F=(*E).front;
        node* B=(*E).back;
        (*F).back=B;
        (*B).front=F;
        free(E);
        Size--;
        return iterator(B);
    }
};


#endif /*List_hpp*/
