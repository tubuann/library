#ifndef Query_hpp
#define Query_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

namespace Mo{
    //長さNの数列上、Q個のクエリに答える
    //insert::数列のi番目の値を挿入する
    //delete::数列のi番目の値を削除
    //cul::i番目のクエリに対して答える
    template<typename Data>
    vector<Data> mo(int N,int Q,const vector<pair<int,int>> &sec,function<void(int)> insert,function<void(int)> del,function<Data(int)> cul){
        vector<Data> ret(Q);
        int SIZE=max<int>(sqrt(N),1);
        vector<int> ord(Q);
        for(int i=0;i<Q;i++){ord[i]=i;}
        sort(ord.begin(),ord.end(),[&](int a,int b){return sec[a].F/SIZE==sec[b].F/SIZE?sec[a].S<sec[b].S:sec[a].F<sec[b].F;});
        int left=0,right=0;
        auto move=[&](int l,int r){
            while(left>l){insert(--left);}
            while(right<r){insert(right++);}
            while(left<l){del(left++);}
            while(right>r){del(--right);}
        };
        int idx=0;
        for(int i=0;i<N;i+=SIZE){
            while(idx<Q && sec[ord[idx]].F<i+SIZE){
                int num=ord[idx++];
                move(sec[num].F,sec[num].S);
                ret[num]=cul(num);
            }
        }
        return ret;
    }
}

using namespace Mo;



#endif /*Query_hpp*/
