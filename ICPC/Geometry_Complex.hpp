#ifndef Geometry_Complex_hpp
#define Geometry_Complex_hpp

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//BEGIN CUT HERE
namespace Geometry{
#define F first
#define S second
  typedef long double D;
  typedef complex<long double> P;
  typedef pair<P,D> C;

  const D EPS=1e-9;
  const D PI=asin(1)*2;
  const D INF=1e18;

  static bool comp(const P &p1,const P &p2){
    if(p1.real()==p2.real()){return p1.imag()<p2.imag();}
    return p1.real()<p2.real();
  }

  static bool comp_y(const P &p1,const P &p2){
    if(p1.imag()==p2.imag()){return p1.real()<p2.real();}
    return p1.imag()<p2.imag();
  }

  static bool eqls(const P &p1,const P &p2){
    return abs(p1-p2)<EPS;
  }

  D dot(P p1,P p2){
    return p1.real()*p2.real()+p1.imag()*p2.imag();
  }

  D cross(P p1,P p2){
    return p1.real()*p2.imag()-p1.imag()*p2.real();
  }

  P project(P vec,P x){
    return vec*(x/vec).real();
  }

  P project(P p1,P p2,P x){
    return p1+project(p2-p1,x-p1);
  }

  P reflect(P vec,P x){
    return vec*conj(x/vec);
  }

  P reflect(P p1,P p2,P x){
    return p1+reflect(p2-p1,x-p1);
  }

  bool intersectSL(P p1,P p2,P vec){
    vec/=abs(vec); p1/=vec; p2/=vec;
    return (p1.imag()<EPS && p2.imag()>-EPS)
      || (p1.imag()>-EPS && p2.imag()<EPS);
  }

  bool intersectSL(P p1,P p2,P p3,P p4){
    return intersectSL(p1-p4,p2-p4,p3-p4);
  }

  bool intersectSS(P p1,P p2,P p3,P p4){
    if(dot(p2-p1,p3-p1)<-EPS && dot(p2-p1,p4-p1)<-EPS){return false;}
    if(dot(p1-p2,p3-p2)<-EPS && dot(p1-p2,p4-p2)<-EPS){return false;}
    return intersectSL(p1,p2,p3,p4) && intersectSL(p3,p4,p1,p2);
  }

  D distLP(P vec,P x){
    return abs((x/vec).imag())*abs(vec);
  }

  D distLP(P p1,P p2,P x){
    return distLP(p2-p1,x-p1);
  }

  D distSP(P p1,P p2,P x){
    if(dot(p2-p1,x-p1)<-EPS){return abs(x-p1);}
    if(dot(p1-p2,x-p2)<-EPS){return abs(x-p2);}
    return distLP(p1,p2,x);
  }

  D distSS(P p1,P p2,P p3,P p4){
    if(intersectSS(p1,p2,p3,p4)){return 0.0;}
    return min({distSP(p1,p2,p3),distSP(p1,p2,p4),
                distSP(p3,p4,p1),distSP(p3,p4,p2)});
  }

  P crosspointLL(P p1,P p2,P vec){
    if(abs(cross(p2-p1,vec))<EPS){return vec;}
    return vec*cross(p2-p1,p2)/cross(p2-p1,vec);
  }

  P crosspointLL(P p1,P p2,P p3,P p4){
    return p4+crosspointLL(p1-p4,p2-p4,p3-p4);
  }

  P crosspointSS(P p1,P p2,P p3,P p4){
    if(distSP(p1,p2,p3)<EPS){return p3;}
    if(distSP(p1,p2,p4)<EPS){return p4;}
    return crosspointLL(p1,p2,p3,p4);
  }

  bool intersectShL(P p1,P p2,P vec){
    vec/=abs(vec);
    return intersectSL(p1,p2,vec) &&
      crosspointLL(p1/vec,p2/vec,vec/vec).real()>-EPS;
  }

  bool intersectShL(P p1,P p2,P p3,P p4){
    return intersectShL(p1-p3,p2-p3,p4-p3);
  }

  //1::in,0::on edge,-1::out
  int contain(const vector<P> &poly,const P &p){
    vector<P> A={{65537,96847},{-24061,6701},{56369,-86509},
                 {-93763,-78049},{56957,10007}};
    int s=A.size();
    vector<bool> cnt(s,false);
    for(int i=0;i<(int)poly.size();i++){
      int k=(i+1)%poly.size();
      if(distSP(poly[i],poly[k],p)<EPS){return 0;}
      for(int j=0;j<s;j++){
        if(intersectShL(poly[i],poly[k],p,p+A[j])){cnt[j]=!cnt[j];}
      }
    }
    int in=0;
    for(int j=0;j<s;j++){if(cnt[j]){in++;}}
    return in>s/2?1:-1;
  }

  vector<P> convexcut(const vector<P> &poly,P p1,P p2){
    vector<P> ret;
    for(int i=0;i<(int)poly.size();i++){
      int j=(i+1)%poly.size();
      if(cross(p2-p1,poly[i]-p1)>-EPS){ret.push_back(poly[i]);}
      if(intersectSL(poly[i],poly[j],p1,p2) &&
         distLP(p1,p2,poly[i])>EPS && distLP(p1,p2,poly[j])>EPS){
        ret.push_back(crosspointLL(poly[i],poly[j],p1,p2));
      }
    }
    return ret;
  }

  D area(const vector<P> &poly){
    D ans=0;
    for(int i=2;i<(int)poly.size();i++){
      ans+=cross(poly[i-1]-poly[0],poly[i]-poly[0]);
    }
    return abs(ans)/2;
  }

  vector<P> convexhull(vector<P> pts){
    vector<P> ret;
    sort(pts.begin(),pts.end(),comp);
    auto fnc=
      [&](){
        for(auto &I:pts){
          if(!ret.empty() && abs(I-ret.back())<EPS){continue;}
          while(ret.size()>1){
            P A=ret.back()-ret[ret.size()-2];
            P B=I-ret.back();
            if(cross(A,B)<-EPS){
              ret.pop_back();
            }else if(abs(cross(A,B))<EPS && dot(A,B)>EPS){
              ret.pop_back();
            }else{
              break;
            }
          }
          ret.push_back(I);
        }
      };
    fnc();
    reverse(pts.begin(),pts.end());
    fnc();
    if(ret.size()>1 && ret[0]==ret.back()){ret.pop_back();}
    return ret;
  }

  //4::seperate,3::circumscribe,2::intersect,
  //1::inscribe,0::contain,-1::same
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
    for(auto &I:crosspointLC(p1,p2,c)){
      if(distSP(p1,p2,I)<EPS){ret.push_back(I);}
    }
    return ret;
  }

  vector<P> crosspointCC(C c1,C c2){
    vector<P> ret;
    P vec=c2.F-c1.F;
    D base=(c1.S*c1.S+norm(vec)-c2.S*c2.S)/(2*abs(vec));
    D h=sqrt(c1.S*c1.S-base*base);
    vec/=abs(vec);
    ret.push_back(c1.F+vec*P(base,-h));
    ret.push_back(c1.F+vec*P(base,h));
    return ret;
  }

  vector<P> tangentCP(C c,P p){
    return crosspointCC(c,C(p,sqrt(norm(c.F-p)-c.S*c.S)));
  }

  vector<pair<P,P>> tangentCC(C c1,C c2){
    vector<pair<P,P>> ret;
    P d=c2.F-c1.F;
    for(D i:{-1,1}){
      D r=c1.S+c2.S*i;
      if(intersectCC(c1,c2)>i+1){
        for(P s:{-1i,1i}){
          P p=r+s*sqrt(norm(d)-norm(r));
          ret.emplace_back(c1.F+d*c1.S/norm(d)*p,
                           c2.F-d*i*c2.S/norm(d)*p);
        }
      }
    }
    return ret;
  }

  D area(const vector<P> &poly,C c){
    D ret=0;
    for(int i=0;i<(int)poly.size();i++){
      P a=poly[i]-c.F,b=poly[(i+1)%poly.size()]-c.F;
      if(abs(a)<c.S+EPS && abs(b)<c.S+EPS){
        ret+=cross(a,b);
      }else{
        vector<P> A=crosspointSC(a,b,{0,c.S});
        if(A.empty()){ret+=c.S*c.S*arg(b/a);}
        else{
          ret+=(abs(a)<c.S?
                cross(a,A[0]):
                c.S*c.S*arg(A[0]/a));
          ret+=(abs(b)<c.S?
                cross(A.back(),b):
                c.S*c.S*arg(b/A.back()));
          ret+=cross(A[0],A.back());
        }
      }
    }
    return abs(ret)/2;
  }

  D area(C c1,C c2){
    int a=intersectCC(c1,c2);
    if(a>2){return 0;}
    else if(a<2){
      D mi=min(c1.S,c2.S);
      return mi*mi*PI;
    }
    D ret=0,d=abs(c1.F-c2.F);
    for(int i=0;i<2;i++){
      D ag=acos((d*d+c1.S*c1.S-c2.S*c2.S)/(2*d*c1.S))*2;
      ret+=(ag-sin(ag))*c1.S*c1.S/2;
      swap(c1,c2);
    }
    return ret;
  }

  //counter-clockwise
  D diameter(const vector<P> &poly){
    D ret=0;
    ll l=0,r=0,n=poly.size();
    if(n==2){return abs(poly[0]-poly[1]);}
    for(int i=0;i<n;i++){
      if(comp(poly[l],poly[i])){l=i;}
      if(comp(poly[i],poly[r])){r=i;}
    }
    ll sl=r,sr=l;
    while(sl!=l || sr!=r){
      ret=max(ret,abs(poly[r]-poly[l]));
      if(cross(poly[(l+1)%n]-poly[l],
               poly[(r+1)%n]-poly[r])<0){
        (++l)%=n;
      }else{
        (++r)%=n;
      }
    }
    return ret;
  }

  D closestpair(vector<P> pt){
    sort(pt.begin(),pt.end(),comp);
    D ret=INF;
    int N=pt.size();
    for(int i=1;i<N;i<<=1){
      for(int j=0;i+j<N;j+=i*2){
        int m=i+j;
        vector<P> R;
        D l=-INF,r=INF;
        for(int k=j;k<m;k++){l=max(l,pt[k].real());}
        for(int k=0;m+k<N && k<i;k++){r=min(r,pt[m+k].real());}
        for(int k=0;m+k<N && k<i;k++){
          if(pt[m+k].real()-l<ret){R.push_back(pt[m+k]);}
        }
        int idx=0;
        for(int k=j;k<m;k++){
          if(r-pt[k].real()>ret){continue;}
          int M=R.size();
          while(idx<M && pt[k].imag()-R[idx].imag()>ret){idx++;}
          for(int s=idx;s<M && R[s].imag()-pt[k].imag()<ret;s++){
            ret=min(ret,abs(R[s]-pt[k]));
          }
        }
        auto ed=(j+i*2<N?pt.begin()+j+2*i:pt.end());
        inplace_merge(pt.begin()+j,pt.begin()+m,ed,comp_y);
      }
    }
    return ret;
  }

  P centerofgravity(const vector<P> &pt){
    P ret(0,0);
    D wt=0;
    for(int i=2;i<(int)pt.size();i++){
      D w2=cross(pt[i-1]-pt[0],pt[i]-pt[0]);
      P p=(pt[0]+pt[i-1]+pt[i])/(D)3;
      wt+=w2;
      ret+=p*w2;
    }
    return ret/wt;
  }

  void segment_arrangement(const vector<pair<P,P>> &L,
                           vector<pair<int,int>> &seg,vector<P> &pt){
    int N=L.size();
    for(int i=0;i<N;i++){
      pt.push_back(L[i].F);
      pt.push_back(L[i].S);
      for(int j=i+1;j<N;j++){
        if(intersectSS(L[i].F,L[i].S,L[j].F,L[j].S)){
          pt.push_back(crosspointSS(L[i].F,L[i].S,L[j].F,L[j].S));
        }
      }
    }
    auto le=[](P a,P b){return eqls(a,b)?false:comp(a,b);};
    sort(pt.begin(),pt.end(),le);
    pt.erase(unique(pt.begin(),pt.end(),eqls),pt.end());
    for(auto &I:L){
      vector<pair<D,int>> on;
      for(int j=0;j<(int)pt.size();j++){
        if(distSP(I.F,I.S,pt[j])<EPS){
          on.emplace_back(abs(pt[j]-I.F),j);
        }
      }
      sort(on.begin(),on.end());
      for(int j=1;j<(int)on.size();j++){
        seg.emplace_back(on[j-1].S,on[j].S);
      }
    }
    sort(seg.begin(),seg.end());
    seg.erase(unique(seg.begin(),seg.end()),seg.end());
  }

  vector<P> convex_of_segments(const vector<pair<P,P>> &L){
    vector<pair<int,int>> seg;
    vector<P> pt;
    segment_arrangement(L,seg,pt);
    vector<vector<int>> edge(pt.size());
    for(auto &I:seg){
      edge[I.F].push_back(I.S);
      edge[I.S].push_back(I.F);
    }
    vector<P> ret;
    function<void(int,int)> dfs=
      [&](int v,int pre){
        if(pre!=-1 && v==0){return;}
        ret.push_back(pt[v]);
        vector<pair<D,int>> nx;
        for(auto &u:edge[v]){
          P dom=(pre==-1||eqls(pt[v],pt[pre]))?P(1):pt[v]-pt[pre];
          D a=arg((pt[u]-pt[v])/dom);
          if(abs(a+PI)<EPS){a=PI;}
          nx.emplace_back(a,u);
        }
        sort(nx.begin(),nx.end());
        dfs(nx[0].S,v);
      };
    dfs(0,-1);
    return ret;
  }

  istream & operator >> (istream &i,P &p){
    D x,y; i>>x>>y; p={x,y}; return i;
  }
  istream & operator >> (istream &i,C &p){
    D x,y; i>>x>>y>>p.S; p.F={x,y}; return i;
  }
};

using namespace Geometry;
//END CUT HERE


#endif /*Geometry_Complex_hpp*/
