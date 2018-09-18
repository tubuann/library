#ifndef Array_hpp
#define Array_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

template<typename T>
struct Array{
    typedef unsigned long ul;
    typedef T* P;
    deque<P> A;
    
    Array(const ul &size=0,const T &err=T()):A(size){
        for(ul i=0;i<size;i++){
            A[i]=(P)malloc(sizeof(T));
            (*A[i])=err;
        }
    }
    
    Array(const vector<T> &a):A(a.size()){
        for(ul i=0;i<A.size();i++){
            A[i]=(P)malloc(sizeof(T));
            (*A[i])=a[i];
        }
    }
    
    Array(const Array &a):A(a.size()){
        for(ul i=0;i<A.size();i++){
            A[i]=(P)malloc(sizeof(T));
            (*A[i])=a[i];
        }
    }
    
    template<typename U>
    Array(const U &a):A(a.size()){
        for(ul i=0;i<A.size();i++){
            A[i]=(P)malloc(sizeof(T));
            (*A[i])=a[i];
        }
    }
    
    ~Array(){
        for(ul i=0;i<A.size();i++){
            free(A[i]);
        }
        
    }
    
    ul size() const {return A.size();}
    
    bool empty(){return A.empty();}
    
    void clear(){
        for(ul i=0;i<A.size();i++){
            free(A[i]);
        }
        A.clear();
    }
    
    void resize(const ul &size){
        if(A.size()>=size){
            for(ul i=size;i<A.size();i++){
                free(A[i]);
            }
            A.resize(size);
        }
        else{
            ul n=A.size();
            A.resize(size);
            for(ul i=n;i<A.size();i++){
                A[i]=(P)malloc(sizeof(T));
            }
        }
    }
    
    T & operator [] (ul where){
        assert(where<=A.size());
        return *A[where];
    }
    
    bool operator == (const Array &a) const {
        if(a.size()!=A.size()){return false;}
        for(ul i=0;i<A.size();i++){
            if(a[i]!=*A[i]){return false;}
        }
        return true;
    }
    
    bool operator != (const Array &a) const {
        if(a.size()!=A.size()){return true;}
        for(ul i=0;i<A.size();i++){
            if(a[i]!=*A[i]){return true;}
        }
        return false;
    }
    
    bool operator < (const Array &a) const {
        ul mi=min(a.size(),A.size());
        for(ul i=0;i<mi;i++){
            if(*A[i]<a[i]){return true;}
            if(*A[i]>a[i]){return false;}
        }
        return A.size()<a.size();
    }
    
    bool operator <= (const Array &a) const {
        ul mi=min(a.size(),A.size());
        for(ul i=0;i<mi;i++){
            if(*A[i]<a[i]){return true;}
            if(*A[i]>a[i]){return false;}
        }
        return A.size()<=a.size();
    }
    
    bool operator > (const Array &a) const {
        ul mi=min(a.size(),A.size());
        for(ul i=0;i<mi;i++){
            if(*A[i]>a[i]){return true;}
            if(*A[i]<a[i]){return false;}
        }
        return A.size()>a.size();
    }
    
    bool operator >= (const Array &a) const {
        ul mi=min(a.size(),A.size());
        for(ul i=0;i<mi;i++){
            if(*A[i]>a[i]){return true;}
            if(*A[i]<a[i]){return false;}
        }
        return A.size()>=a.size();
    }
    
    Array & operator = (const Array &a){
        ul mi=min(a.size(),A.size());
        for(ul i=0;i<mi;i++){
            (*A[i])=a[i];
        }
        if(a.size()<=A.size()){
            for(ul i=mi;i<A.size();i++){
                free(A[i]);
            }
            A.resize(mi);
        }
        else{
            A.resize(a.size());
            for(ul i=mi;i<a.size();i++){
                A[i]=(P)malloc(sizeof(T));
                (*A[i])=a[i];
            }
        }
        return *this;
    }
    
    void pop_back(){
        assert(A.size()>0);
        free(A[A.size()-1]);
        A.pop_back();
    }
    
    T & push_back(const T &a){
        A.push_back((P)malloc(sizeof(T)));
        return *A[A.size()-1]=a;
    }
    
    void pop_front(){
        assert(A.size()>0);
        free(A[0]);
        A.pop_front();
    }
    
    T & push_front(const T &a){
        A.push_front((P)malloc(sizeof(T)));
        return *A[0]=a;
    }
    
    void swap(const ul &a,const ul &b){
        std::swap(A[a],A[b]);
    }
    
    //[l,r)
    void merge_sort(const ul &l,const ul &r){
        ul k=2; //区間
        vector<P> B(r-l);
        vector<P> C(r-l);
        for(ul i=0;i<r-l;i++){
            C[i]=A[i+l];
        }
        bool toB=true;
        while(r-l>(k>>1)){
            for(ul i=l;i<r;){
                ul L=i;
                ul R=min(i+(k>>1),r);
                const ul LE=R;
                i+=k;
                i=min(i,r);
                for(ul t=L;L!=LE || R!=i;t++){
                    if(toB){
                        if(L!=LE && R!=i){
                            if((*C[L-l])<(*C[R-l])){
                                B[t-l]=C[L-l];
                                L++;
                            }
                            else{
                                B[t-l]=C[R-l];
                                R++;
                            }
                        }
                        else if(L!=LE){
                            B[t-l]=C[L-l];
                            L++;
                        }
                        else{
                            B[t-l]=C[R-l];
                            R++;
                        }
                    }
                    else{
                        if(L!=LE && R!=i){
                            if((*B[L-l])<(*B[R-l])){
                                C[t-l]=B[L-l];
                                L++;
                            }
                            else{
                                C[t-l]=B[R-l];
                                R++;
                            }
                        }
                        else if(L!=LE){
                            C[t-l]=B[L-l];
                            L++;
                        }
                        else{
                            C[t-l]=B[R-l];
                            R++;
                        }
                    }
                }
            }
            toB=!toB;
            k<<=1;
        }
        if(!toB){
            for(ul i=0;i<r-l;i++){
                A[i+l]=B[i];
            }
        }
        else{
            for(ul i=0;i<r-l;i++){
                A[i+l]=C[i];
            }
        }
    }
    
    //[l,r)
    void merge_sort(const ul &l,const ul &r,const function<bool(const T&,const T&)> &comp){
        ul k=2; //区間
        vector<P> B(r-l);
        vector<P> C(r-l);
        for(ul i=0;i<r-l;i++){
            C[i]=A[i+l];
        }
        bool toB=true;
        while(r-l>(k>>1)){
            for(ul i=l;i<r;){
                ul L=i;
                ul R=min(i+(k>>1),r);
                const ul LE=R;
                i+=k;
                i=min(i,r);
                for(ul t=L;L!=LE || R!=i;t++){
                    if(toB){
                        if(L!=LE && R!=i){
                            if(comp((*C[L-l]),(*C[R-l]))){
                                B[t-l]=C[L-l];
                                L++;
                            }
                            else{
                                B[t-l]=C[R-l];
                                R++;
                            }
                        }
                        else if(L!=LE){
                            B[t-l]=C[L-l];
                            L++;
                        }
                        else{
                            B[t-l]=C[R-l];
                            R++;
                        }
                    }
                    else{
                        if(L!=LE && R!=i){
                            if(comp((*B[L-l]),(*B[R-l]))){
                                C[t-l]=B[L-l];
                                L++;
                            }
                            else{
                                C[t-l]=B[R-l];
                                R++;
                            }
                        }
                        else if(L!=LE){
                            C[t-l]=B[L-l];
                            L++;
                        }
                        else{
                            C[t-l]=B[R-l];
                            R++;
                        }
                    }
                }
            }
            toB=!toB;
            k<<=1;
        }
        if(!toB){
            for(ul i=0;i<r-l;i++){
                A[i+l]=B[i];
            }
        }
        else{
            for(ul i=0;i<r-l;i++){
                A[i+l]=C[i];
            }
        }
    }
    
    void partition(const ul &l,const ul &r,const T &m){
        ul L=l;
        ul R=r-1;
        while(L!=R){
            if((*A[L])<m){
                L++;
            }
            else{
                std::swap(A[L],A[R]);
                R--;
            }
        }
    }
    
    void partition(const ul &l,const ul &r,const T &m,const function<bool(const T&,const T&)> &comp){
        ul L=l;
        ul R=r-1;
        while(L!=R){
            if(comp((*A[L]),m)){
                L++;
            }
            else{
                std::swap(A[L],A[R]);
                R--;
            }
        }
    }
    
    ul quick_partition(const ul &l,const ul &r,const ul &m){
        if(r-l==1){return l;}
        ul L=l;
        ul R=r-2;
        std::swap(A[m],A[r-1]);
        bool j;
        while(L!=R){
            j=false;
            if((*A[L])<(*A[r-1])){
                L++;
            }
            else{
                std::swap(A[L],A[R]);
                R--;
            }
        }
        if((*A[L])<(*A[r-1])){
            std::swap(A[L+1],A[r-1]);
            return L+1;
        }
        std::swap(A[L],A[r-1]);
        return L;
    }
    
    ul quick_partition(const ul &l,const ul &r,const ul &m,const function<bool(const T&,const T&)> &comp){
        if(r-l==1){return l;}
        ul L=l;
        ul R=r-2;
        std::swap(A[m],A[r-1]);
        bool j;
        while(L!=R){
            j=false;
            if(comp((*A[L]),(*A[r-1]))){
                L++;
            }
            else{
                std::swap(A[L],A[R]);
                R--;
            }
        }
        if(comp((*A[L]),(*A[r-1]))){
            std::swap(A[L+1],A[r-1]);
            return L+1;
        }
        std::swap(A[L],A[r-1]);
        return L;
    }
    
    void quick_sort(const ul &l,const ul &r,const ul &mx){
        if(r-l<=1){return;}
        if(mx==0){
            merge_sort(l,r);
            return;
        }
        ul m=l+(r-l)/2;
        m=quick_partition(l,r,m);
        quick_sort(l,m,mx-1);
        if(m+2<r){quick_sort(m+1,r,mx-1);}
    }
    
    void quick_sort(const ul &l,const ul &r){
        const ul mx=16;
        if(r-l<=1){return;}
        if(mx==0){
            merge_sort(l,r);
            return;
        }
        ul m=l+(r-l)/2;
        m=quick_partition(l,r,m);
        quick_sort(l,m,mx-1);
        if(m+2<r){quick_sort(m+1,r,mx-1);}
    }
    
    void quick_sort(const ul &l,const ul &r,const function<bool(const T&,const T&)> &comp,const ul &mx){
        if(r-l<=1){return;}
        if(mx==0){
            merge_sort(l,r,comp);
            return;
        }
        ul m=l+(r-l)/2;
        m=quick_partition(l,r,m,comp);
        quick_sort(l,m,comp,mx-1);
        if(m+2<r){quick_sort(m+1,r,comp,mx-1);}
    }
    
    void quick_sort(const ul &l,const ul &r,const function<bool(const T&,const T&)> &comp){
        const ul mx=16;
        if(r-l<=1){return;}
        if(mx==0){
            merge_sort(l,r);
            return;
        }
        ul m=l+(r-l)/2;
        m=quick_partition(l,r,m,comp);
        quick_sort(l,m,comp,mx-1);
        if(m+2<r){quick_sort(m+1,r,comp,mx-1);}
    }
    
    void show() const {
        for(int i=0;i<A.size();i++){
            cout<<(*A[i]);
            if(i!=A.size()-1){cout<<" ";}
        }
        cout<<endl;
    }
    
    void show(const char &C) const {
        for(int i=0;i<A.size();i++){
            cout<<(*A[i]);
            if(i!=A.size()-1){cout<<C;}
        }
        cout<<endl;
    }
    
    void show(const string &S) const {
        for(int i=0;i<A.size();i++){
            cout<<(*A[i]);
            if(i!=A.size()-1){cout<<S;}
        }
        cout<<endl;
    }
    
    void reverse(ul l,ul r){
        r--;
        while(l<r){
            std::swap(A[l],A[r]);
            l++; r--;
        }
    }
};

template<typename T>
void swap(Array<T> &a,Array<T> &b){
    swap(a.A,b.A);
}





#endif /*Array_hpp*/
