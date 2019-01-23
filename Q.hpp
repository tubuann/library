#ifndef Q_hpp
#define Q_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second



struct Q{
    ll up,down;
    
    Q(ll a=1):up(a),down(1){}
    
    Q(ll a,ll b):up(a),down(b){}
    
    Q(const Q &A):up(A.up),down(A.down){}
    
    ll gcd(ll a,ll b){
        if(a%b==0){return b;}
        return gcd(b,a%b);
    }
    
    Q& operator *= (const Q &A){up*=A.up; down*=A.down; return *this;}
    
    Q& operator /= (const Q &A){up*=A.down; down*=A.up; return *this;}
    
    Q& operator += (const Q &A){up*=A.down; up+=A.up*down; down*=A.down; return *this;}
    
    Q& operator -= (const Q &A){up*=A.down; up-=A.up*down; down*=A.down; return *this;}
    
    Q& normalize(){ll g=gcd(abs(up),abs(down)); up/=g; down/=g; if(down<0){down*=-1; up*=-1;} return *this;}
    
    Q operator * (const Q &A) const {Q ret(*this); ret*=A; return ret;}
    
    Q operator / (const Q &A) const {Q ret(*this); ret/=A; return ret;}
    
    Q operator + (const Q &A) const {Q ret(*this); ret+=A; return ret;}
    
    Q operator - (const Q &A) const {Q ret(*this); ret-=A; return ret;}
    
    bool operator < (const Q &A) const {return (down*A.down>0?up*A.down<down*A.up:up*A.down>down*A.up);}
    
    bool operator <= (const Q &A) const {return (down*A.down>0?up*A.down<=down*A.up:up*A.down>=down*A.up);}
    
    bool operator > (const Q &A) const {return (down*A.down>0?up*A.down>down*A.up:up*A.down<down*A.up);}
    
    bool operator >= (const Q &A) const {return (down*A.down>0?up*A.down>=down*A.up:up*A.down<=down*A.up);}
    
    bool operator == (const Q &A) const {return up*A.down==down*A.up;}
    
    bool operator != (const Q &A) const {return up*A.down!=down*A.up;}
};



#endif /*Q_hpp*/
