#ifndef StackQueue_hpp
#define StackQueue_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T>
struct Stack{
private:
    T* begin;
    int size;
    int end;
    
public:
    Stack(){
        begin=(T*)malloc(sizeof(T));
        size=1;
        end=0;
    }
    
    ~Stack(){free(begin);}
    
    void push(const T &data){
        if(end==size){
            T* New=(T*)realloc(begin,sizeof(T)*(size<<=1));
            if(New==NULL){
                free(begin);
                assert(false);
            }
            begin=New;
        }
        *(begin+(end++))=data;
    }
    
    T top() const {
        assert(end>0);
        return *(begin+(end-1));
    }
    
    void pop(){
        assert(end>0);
        --end;
    }
    
    bool empty() const {return end==0;}
};


template<typename T>
struct Queue{
private:
    Stack<T> L;
    Stack<T> F;
    
    void change(){
        while(!L.empty()){
            F.push(L.top());
            L.pop();
        }
    }
    
public:
    void push(const T &data){
        L.push(data);
    }
    
    void pop(){
        if(F.empty()){change();}
        assert(!F.empty());
        F.pop();
    }
    
    T front(){
        if(F.empty()){change();}
        assert(!F.empty());
        return F.top();
    }
    
    bool empty() const {
        return F.empty() && L.empty();
    }
};



#endif /*StackQueue_hpp*/
