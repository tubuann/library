#ifndef sq_div_hpp
#define sq_div_hp

#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

/*
//区間加算,最小値
ll W(ll a,ll b){
    return (a+b-1)/b;
}

ll size;
vector<ll> a;
vector<ll> sq;
vector<ll> pls;

ll find(ll l,ll r){
    ll ans=E;
    ll L=l/size;
    ll R=r/size;
    for(int i=0;i<sq.size();i++){
        if(L<i && i<R){ans=min(ans,sq[i]+pls[i]);}
    }
    if(L==R){
        for(ll i=l;i<=r;i++){
            ans=min(ans,a[i]+pls[L]);
        }
        return ans;
    }
    for(ll i=l;i<L*size+size && i<a.size();i++){
        ans=min(ans,a[i]+pls[L]);
    }
    for(ll i=size*R;i<=r && i<a.size();i++){
        ans=min(ans,a[i]+pls[R]);
    }
    return ans;
}

void add(ll l,ll r,ll A){
    ll L=l/size;
    ll R=r/size;
    for(int i=0;i<sq.size();i++){
        if(L<i && i<R){pls[i]+=A;}
    }
    if(L==R){
        for(ll i=l;i<=r;i++){
            a[i]+=A;
        }
        ll mi=E;
        for(ll i=L*size;i<L*size+size;i++){
            mi=min(mi,a[i]);
        }
        sq[L]=mi;
        return;
    }
    else{
        for(ll i=l;i<L*size+size && i<a.size();i++){
            a[i]+=A;
        }
        ll mi=E;
        for(ll i=L*size;i<L*size+size && i<a.size();i++){
            mi=min(mi,a[i]);
        }
        sq[L]=mi;
        for(ll i=size*R;i<=r && i<a.size();i++){
            a[i]+=A;
        }
        mi=E;
        for(ll i=R*size;i<R*size+size && i<a.size();i++){
            mi=min(mi,a[i]);
        }
        sq[R]=mi;
    }
}
*/



/*
//ただの平方分割
ll sq_size(ll a){
    for(int i=1;i<100000;i++){
        if(a<=i*i){return i;}
    }
    return E;
}

//0-index
template<typename T>
class sq_div{
private:
    vector<T> a;
    vector<T> sq;
    ll size;
    T err;
    
public:
    sq_div(ll s,ll err):err(err){
        size=sq_size(s);
        a.resize(size*size,err);
        sq.resize(size);
        for(int i=0;i<size;i++){
            T n=a[i*size];
            for(int t=1;t<size;t++){
                n=F(n,a[i*size+t]);
            }
            sq[i]=n;
        }
    }
    
    sq_div(vector<T> t,ll err):err(err){
        size=sq_size(t.size());
        a.resize(size*size,err);
        for(int i=0;i<t.size();i++){
            a[i]=t[i];
        }
        sq.resize(size);
        for(int i=0;i<size;i++){
            T n=a[i*size];
            for(int t=1;t<size;t++){
                n=F(n,a[i*size+t]);
            }
            sq[i]=n;
        }
    }
    
    T ans(ll where){
        return a[where];
    }
    
    //[l,r]
    T ans(ll l,ll r){
        ll L=l/size;
        ll R=r/size;
        if(L==R){
            T ret=a[l];
            for(ll i=l+1;i<=r;i++){
                ret=F(ret,a[i]);
            }
            return ret;
        }
        if(l%size==0){L--;}
        if(r%size==size-1){R++;}
        T ret=err;
        for(ll i=L+1;i<R;i++){
            ret=F(ret,sq[i]);
        }
        for(ll i=l;i<L*size+size;i++){
            ret=F(ret,a[i]);
        }
        for(ll i=R*size;i<=r;i++){
            ret=F(ret,a[i]);
        }
        return ret;
    }
    
    //where::sq[where]
    T sq_ans(ll where){
        return sq[where];
    }
    
    //where::sq[where]
    void remake_sq(ll where){
        T ret=err;
        for(ll i=where*size;i<where*size+size;i++){
            ret=F(ret,a[i]);
        }
        sq[where]=ret;
    }
    
    void change(ll where,T a){
        a[where]=a;
        ll u=where/size;
        remake_sq(u);
    }
    
    T F(T,T);
};


template<typename T>
T sq_div<T>::F(T a,T b){
    return min(a,b);
}
*/


#endif /*sq_div_hpp*/
