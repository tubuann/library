#ifndef str_hpp
#define str_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second


namespace str{
    vector<ll> Manacher(const string &s){
        vector<ll> ret(s.size(),0);
        int j=0;
        for(int i=0;i<s.size();){
            while(i>=j && i+j<s.size() && s[i-j]==s[i+j]){j++;}
            ret[i]=j;
            int k=1;
            while(k<j && ret[i-k]+k<j){ret[i+k]=ret[i-k]; k++;}
            i+=k; j-=k;
        }
        return ret;
    }
    
    vector<ll> Z_Algorithm(const string &s){
        vector<ll> ret(s.size(),0);
        ret[0]=s.size();
        int j=0;
        for(int i=1;i<s.size();){
            while(i+j<s.size() && s[j]==s[i+j]){j++;}
            ret[i]=j;
            if(j==0){i++; continue;}
            int k=1;
            while(k+ret[k]<j){ret[i+k]=ret[k]; k++;}
            i+=k; j-=k;
        }
        return ret;
    }
    
    //1-indexed
    vector<ll> MP(const string &s){
        vector<ll> ret(s.size()+1,-1);
        ll j=-1;
        for(int i=0;i<s.size();i++){
            while(j>=0 && s[i]!=s[j]){j=ret[j];}
            j++;
            ret[i+1]=j;
        }
        return ret;
    }
};




#endif /*str_hpp*/
