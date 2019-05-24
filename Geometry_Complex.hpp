#ifndef Geometry_Complex_hpp
#define Geometry_Complex_hpp

#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second

template<typename D=long double,typename P=complex<long double>>
struct Geometry{
    const D EPS=1e-9;
    const D PI=asin(1)*2;
    typedef pair<P,D> C;
    
    const static bool comp(const P &p1,const P &p2){return p1.real()==p2.real()?p1.imag()<p2.imag():p1.real()<p2.real();}
    
    D dot(P p1,P p2){return p1.real()*p2.real()+p1.imag()*p2.imag();}
    
    D cross(P p1,P p2){return p1.real()*p2.imag()-p1.imag()*p2.real();}
    
    P project(P vec,P x){return vec*(x/vec).real();}
    
    P project(P p1,P p2,P x){return p1+project(p2-p1,x-p1);}
    
    P reflect(P vec,P x){return vec*conj(x/vec);}
    
    P reflect(P p1,P p2,P x){return p1+reflect(p2-p1,x-p1);}
    
    bool intersectSL(P p1,P p2,P vec){vec/=abs(vec); p1/=vec; p2/=vec; return (p1.imag()<EPS && p2.imag()>-EPS) || (p1.imag()>-EPS && p2.imag()<EPS);}
    
    bool intersectSL(P p1,P p2,P p3,P p4){return intersectSL(p1-p4,p2-p4,p3-p4);}
    
    bool intersectSS(P p1,P p2,P p3,P p4){return (dot(p2-p1,p3-p1)<-EPS && dot(p2-p1,p4-p1)<-EPS) || (dot(p1-p2,p3-p2)<-EPS && dot(p1-p2,p4-p2)<-EPS)?false:intersectSL(p1,p2,p3,p4) && intersectSL(p3,p4,p1,p2);}
    
    bool intersectShL(P p1,P p2,P vec){vec/=abs(vec); return intersectSL(p1,p2,vec) && crosspointLL(p1/vec,p2/vec,vec/vec).real()>-EPS;}
    
    bool intersectShL(P p1,P p2,P p3,P p4){return intersectShL(p1-p3,p2-p3,p4-p3);}
    
    D distLP(P vec,P x){return abs((x/vec).imag())*abs(vec);}
    
    D distLP(P p1,P p2,P x){return distLP(p2-p1,x-p1);}
    
    D distSP(P p1,P p2,P x){return dot(p2-p1,x-p1)<-EPS?abs(x-p1):dot(p1-p2,x-p2)<-EPS?abs(x-p2):distLP(p1,p2,x);}
    
    D distSS(P p1,P p2,P p3,P p4){return intersectSS(p1,p2,p3,p4)?0.0:min(min(distSP(p1,p2,p3),distSP(p1,p2,p4)),min(distSP(p3,p4,p1),distSP(p3,p4,p2)));}
    
    P crosspointLL(P p1,P p2,P vec){return abs(cross(p2-p1,vec))<EPS?vec:vec*cross(p2-p1,p2)/cross(p2-p1,vec);}
    
    P crosspointLL(P p1,P p2,P p3,P p4){return p4+crosspointLL(p1-p4,p2-p4,p3-p4);}
    
    P crosspointSS(P p1,P p2,P p3,P p4){return distSP(p1,p2,p3)<EPS?p3:distSP(p1,p2,p4)<EPS?p4:crosspointLL(p1,p2,p3,p4);}
    
    //1::in,0::on edge,-1::out
    int contain(const vector<P> &poly,const P &p){
        vector<P> A={{65537,96847},{-24061,6701},{56369,-86509},{-93763,-78049},{56957,10007}};
        vector<bool> cnt(5,false);
        for(int i=1;i<=poly.size();i++){
            if(distSP(poly[i-1],poly[i%poly.size()],p)<EPS){return 0;}
            for(int j=0;j<5;j++){
                if(intersectShL(poly[i-1],poly[i%poly.size()],p,p+A[j])){cnt[j]=!cnt[j];}
            }
        }
        int in=0;
        for(int j=0;j<5;j++){if(cnt[j]){in++;}}
        return in>=3?1:-1;
    }
    
    vector<P> convexcut(const vector<P> &poly,P p1,P p2){
        vector<P> ret;
        for(int i=1;i<=poly.size();i++){
            if(cross(p2-p1,poly[i-1]-p1)>-EPS){ret.push_back(poly[i-1]);}
            if(intersectSL(poly[i-1],poly[i%poly.size()],p1,p2) && distLP(p1,p2,poly[i-1])>EPS && distLP(p1,p2,poly[i%poly.size()])>EPS){ret.push_back(crosspointLL(poly[i-1],poly[i%poly.size()],p1,p2));}
        }
        return ret;
    }
    
    D area(const vector<P> &poly){
        D ans=0;
        for(int i=2;i<poly.size();i++){ans+=cross(poly[i-1]-poly[0],poly[i]-poly[0]);}
        return abs(ans)/2;
    }
    
    vector<P> convexhull(vector<P> pts){
        vector<P> ret;
        sort(pts.begin(),pts.end(),comp);
        for(auto &I:pts){
            if(!ret.empty() && I==ret.back()){continue;}
            while(ret.size()>=2 && cross(ret.back()-ret[ret.size()-2],I-ret.back())<-EPS){ret.pop_back();}
            ret.push_back(I);
        }
        reverse(pts.begin(),pts.end());
        for(auto &I:pts){
            if(!ret.empty() && I==ret.back()){continue;}
            while(ret.size()>=2 && cross(ret.back()-ret[ret.size()-2],I-ret.back())<-EPS){ret.pop_back();}
            ret.push_back(I);
        }
        if(ret[0]==ret.back()){ret.pop_back();}
        return ret;
    }
    
    //4::seperate,3::circumscribe,2::intersect,1::inscribe,0::contain,-1::same
    int intersectCC(C c1,C c2){
        D d=abs(c1.F-c2.F),r=c1.S+c2.S,dif=abs(c2.S-c1.S);
        if(d<EPS && dif<EPS){return -1;}
        if(d-r>EPS){return 4;}
        if(d-r>-EPS){return 3;}
        if(d-dif>EPS){return 2;}
        if(d-dif>-EPS){return 1;}
        return 0;
    }
    
    vector<P> crosspointLC(P p1,P p2,C c){
        vector<P> ret;
        P pr=project(p1,p2,c.F);
        D d=distLP(p1,p2,c.F);
        if(d-c.S>EPS){return ret;}
        if(d-c.S>-EPS){ret.push_back(pr); return ret;}
        P vec=p2-p1; vec*=sqrt(c.S*c.S-d*d)/abs(vec);
        ret.push_back(pr-vec);
        ret.push_back(pr+vec);
        return ret;
    }
    
    vector<P> crosspointSC(P p1,P p2,C c){
        vector<P> ret;
        for(auto &I:crosspointLC(p1,p2,c)){if(distSP(p1,p2,I)<EPS){ret.push_back(I);}}
        return ret;
    }
    
    vector<P> crosspointCC(C c1,C c2){
        vector<P> ret;
        P vec=c2.F-c1.F;
        D base=(c1.S*c1.S+norm(vec)-c2.S*c2.S)/(2*abs(vec));
        D h=sqrt(c1.S*c1.S-base*base);
        vec/=abs(vec);
        ret.push_back(c1.F+vec*P(base,h));
        ret.push_back(c1.F+vec*P(base,-h));
        return ret;
    }
    
    vector<P> tangentCP(C c,P p){return crosspointCC(c,C(p,sqrt(norm(c.F-p)-c.S*c.S)));}
    
    vector<pair<P,P>> tangentCC(C c1,C c2){
        vector<pair<P,P>> ret;
        P d=c2.F-c1.F;
        for(D i:{-1,1}){
            D r=c1.S+c2.S*i;
            if(intersectCC(c1,c2)>i+1){
                for(P s:{-1i,1i}){
                    P p=r+s*sqrt(norm(d)-norm(r));
                    ret.push_back({c1.F+d*c1.S/norm(d)*p,c2.F-d*i*c2.S/norm(d)*p});
                }
            }
        }
        return ret;
    }
    
    D area(const vector<P> &poly,C c){
        D ret=0;
        for(int i=0;i<poly.size();i++){
            P a=poly[i]-c.F,b=poly[(i+1)%poly.size()]-c.F;
            if(abs(a)<c.S+EPS && abs(b)<c.S+EPS){ret+=cross(a,b);}
            else{
                vector<P> A=crosspointSC(a,b,{0,c.S});
                if(A.empty()){ret+=c.S*c.S*arg(b/a);}
                else{
                    ret+=(abs(a)<c.S?cross(a,A[0]):c.S*c.S*arg(A[0]/a));
                    ret+=(abs(b)<c.S?cross(A.back(),b):c.S*c.S*arg(b/A.back()));
                    if(A.size()==2){ret+=cross(A[0],A[1]);}
                }
            }
        }
        return abs(ret)/2;
    }
};


typedef long double D;
typedef complex<long double> P;
typedef pair<P,D> C;

istream & operator >> (istream &i,P &p){D x,y; i>>x>>y; p={x,y}; return i;}
istream & operator >> (istream &i,C &p){D x,y; i>>x>>y>>p.S; p.F={x,y}; return i;}


#endif /*Geometry_Complex_hpp*/
