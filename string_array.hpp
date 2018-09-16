#ifndef string_array_hpp
#define string_array_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

class string_array{
private:
    vector<string> words;
    vector<ll> number;
    
    //[s,t)
    inline void dfs(ll s,ll t,ll depth){
        vector<pll> A(t-s);
        for(ll i=s;i<t;i++){
            A[i-s].S=number[i];
            if(words[number[i]].size()<=depth){A[i-s].F=-1;}
            else{A[i-s].F=words[number[i]][depth];}
        }
        std::sort(A.begin(),A.end());
        vector<ll> k;
        for(ll i=s;i<t;i++){
            number[i]=A[i-s].S;
            if(i==s && A[i-s].F!=-1){k.push_back(s);}
            if(i!=s && A[i-s].F!=A[i-1-s].F){
                k.push_back(i);
            }
        }
        k.push_back(t);
        for(int i=1;i<k.size();i++){
            dfs(k[i-1],k[i],depth+1);
        }
    }
    
    void sort(){
        for(int i=0;i<number.size();i++){
            number[i]=i;
        }
        dfs(0,number.size(),0);
    }
    
    //[s,t)
    ll binary_search(const ll &s,const ll &t,const ll &depth,const char &c) const {
        ll l=s,r=t-1; //[l,r]
        while(r-l>1){
            ll m=l+(r-l)/2;
            if(words[number[m]].size()<=depth || words[number[m]][depth]<c){l=m;}
            else{r=m;}
        }
        for(ll i=l;i<=r;i++){
            if(words[number[i]].size()>depth && words[number[i]][depth]>=c){return i;}
        }
        return t;
    }
    
public:
    string_array(const vector<string> &S):words(S),number(S.size()){
        sort();
    }
    
    ll lower_bound(const string &S) const {
        ll s=0,t=number.size();
        for(int i=0;i<S.size();i++){
            s=binary_search(s,t,i,S[i]);
            t=binary_search(s,t,i,S[i]+1);
        }
        return s;
    }
    
    ll upper_bound(const string &S) const {
        ll s=0,t=number.size();
        for(int i=0;i<S.size();i++){
            s=binary_search(s,t,i,S[i]);
            t=binary_search(s,t,i,S[i]+1);
        }
        if(S==words[number[s]]){s++;}
        return s;
    }
    
    void show() const {
        for(int i=0;i<number.size();i++){
            cout<<words[number[i]]<<endl;
        }
    }
    
    const string & operator [](const unsigned long &s) const {
        assert(s<number.size());
        return words[number[s]];
    }
    
    unsigned long size(){
        return number.size();
    }
};




#endif /*string_array_hpp*/
