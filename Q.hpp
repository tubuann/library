#ifndef Q_hpp
#define Q_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second



template<typename Int>
struct Q{
    Int up,down;
    
    Q(Int a=0,Int b=1):up(a),down(b){normalize();}
    
    Q(const Q &A):up(A.up),down(A.down){}
    
    Q& normalize(){if(down<0){down*=-1; up*=-1;} return *this;}
    
    Int gcd(Int a,Int b){while(b!=0){a%=b; swap(a,b);} return a;}
    
    Q& opt(){Int g=gcd(abs(up),abs(down)); up/=g; down/=g; return *this;}
    
    Q& operator *= (const Q &A){up*=A.up; down*=A.down; return *this;}
    
    Q& operator /= (const Q &A){up*=A.down; down*=A.up; return *this;}
    
    Q& operator += (const Q &A){up*=A.down; up+=A.up*down; down*=A.down; return *this;}
    
    Q& operator -= (const Q &A){up*=A.down; up-=A.up*down; down*=A.down; return *this;}
    
    Q operator * (const Q &A) const {Q ret(*this); ret*=A; return ret;}
    
    Q operator / (const Q &A) const {Q ret(*this); ret/=A; return ret;}
    
    Q operator + (const Q &A) const {Q ret(*this); ret+=A; return ret;}
    
    Q operator - (const Q &A) const {Q ret(*this); ret-=A; return ret;}
    
    bool operator < (const Q &A) const {return up*A.down<A.up*down;}
    
    bool operator <= (const Q &A) const {return up*A.down<=A.up*down;}
    
    bool operator > (const Q &A) const {return up*A.down>A.up*down;}
    
    bool operator >= (const Q &A) const {return up*A.down>=A.up*down;}
    
    bool operator == (const Q &A) const {return up*A.down==down*A.up;}
    
    bool operator != (const Q &A) const {return up*A.down!=down*A.up;}
};



#endif /*Q_hpp*/
