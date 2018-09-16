#ifndef Geometry2_hpp
#define Geometry2_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

const double EPS=1e-7;
#define equals(a,b) (fabs(a-b)<EPS)

struct point{
  double x,y;
    
  point(double x=0,double y=0):x(x),y(y){}
    
  point operator + (const point &P) const {
    return point(x+P.x,y+P.y);
  }
    
  point operator - (const point &P) const {
    return point(x-P.x,y-P.y);
  }
    
  point operator * (const double &D) const {
    return point(x*D,y*D);
  }
    
  point operator / (const double &D) const {
    return point(x/D,y/D);
  }
    
  bool operator == (const point &P) const {
    if(fabs(x-P.x)<EPS && fabs(y-P.y)<EPS){return true;}
    if(fabs(x-P.x)/max(fabs(x),fabs(P.x))<EPS && fabs(y-P.y)/max(fabs(y),fabs(P.y))<EPS){return true;}
    return false;
  }
    
  bool operator != (const point &P) const {
    return !((*this)==P);
  }
    
  double norm() const {
    return x*x+y*y;
  }
    
  double abs() const {
    return sqrt(norm());
  }
    
  //ax=y
  double equation() const {
    return y/x;
  }
};

double dot(const point &a,const point &b){
  return a.x*b.x+a.y*b.y;
}

double cross(const point &a,const point &b){
  return a.x*b.y-a.y*b.x;
}

point mid_point(const point &a,const point &b){
  return point(a.x+b.x,a.y+b.y)/2;
}

struct line{
  point s,t;
    
  line(point s,point t):s(s),t(t){}
    
  bool operator == (const line &L) const {
    return s==L.s && t==L.t;
  }
    
  //ax+b=y
  pair<double,double> equation() const {
    double a=(t-s).equation();
    double b=t.y-t.x*a;
    return {a,b};
  }
};

//直行判定
bool isOrthogonal(const point &a,const point &b){
  return equals(dot(a,b),0.0);
}

bool isOrthogonal(const line &a,const line &b){
  return isOrthogonal(a.t-a.s,b.t-b.s);
}

//平行判定
bool isParallel(const point &a,const point &b){
  return equals(cross(a,b),0.0);
}

bool isParallel(const line &a,const line &b){
  return isParallel(a.t-a.s,b.t-b.s);
}

//射影
point project(const line &L,const point &P){
  point base=L.t-L.s;
  double r=dot(P-L.s,base)/base.norm();
  return L.s+base*r;
}

//点と点の距離
double getDistancePP(const point &a,const point &b){
  return (a-b).abs();
}

//直線と点の距離
double getDistanceLP(const line &L,const point &P){
  return fabs(cross(L.t-L.s,P-L.s)/(L.t-L.s).abs());
}

//線分と点の距離
double getDistanceSP(const line &L,const point &P){
  if(dot(L.t-L.s,P-L.s)<0.0){return (P-L.s).abs();}
  if(dot(L.s-L.t,P-L.t)<0.0){return (P-L.t).abs();}
  return getDistanceLP(L,P);
}


static const int COUNTER_CLOCKWISE=1;
static const int CLOCKWISE=-1;
static const int ONLINE_BACK=2;
static const int ONLINE_FRONT=-2;
static const int ON_SEGMENT=0;

int ccw(const point &p0,const point &p1,const point &p2){
  point a=p1-p0;
  point b=p2-p0;
  if(cross(a,b)>EPS){return COUNTER_CLOCKWISE;}
  if(cross(a,b)<-EPS){return CLOCKWISE;}
  if(dot(a,b)<-EPS){return ONLINE_BACK;}
  if(a.norm()<b.norm()){return ONLINE_FRONT;}
  return ON_SEGMENT;
}

bool intersect(const point &p1,const point &p2,const point &p3,const point &p4){
  return ccw(p1,p2,p3)*ccw(p1,p2,p4)<=0 && ccw(p3,p4,p1)*ccw(p3,p4,p2)<=0;
}

//線分と線分の交差判定
bool intersect(const line &a,const line &b){
  return intersect(a.s,a.t,b.s,b.t);
}

//線分と線分の交点
point XpointSS(const line &a,const line &b){
  point base=b.t-b.s;
  double d1=fabs(cross(base,a.s-b.s));
  double d2=fabs(cross(base,a.t-b.s));
  double t=d1/(d1+d2);
  return a.s+(a.t-a.s)*t;
}



void show(const point &p){cout<<p.x<<" "<<p.y<<endl;}



typedef vector<point> polygon;

bool isInConvex(const polygon &poly,const point &P){
  int sign=ccw(poly[0],poly[1],P);
  for(int i=2;i<poly.size();i++){
    if(ccw(poly[i-1],poly[i],P)!=sign){return false;}
  }
  if(ccw(poly[poly.size()-1],poly[0],P)!=sign){return false;}
  return true;
}

//0::false 1::is_in //2::on_line
ll is_in_polygon(const polygon &P,const point &a){
  bool x=false;
  for(int i=1;i<=P.size();i++){
    point A=a-P[i-1];
    point B=a-P[i%P.size()];
    if(abs(cross(A,B))<EPS && dot(A,B)<EPS){return 0;}
    if(A.y>B.y){swap(A,B);}
    if(A.y<EPS && EPS<B.y && cross(A,B)>EPS){x=!x;}
  }
  return (x?1:0);
}

static const point err(1e18,1e18);

//直交ベクトル
point OrthogonalVector(const line &L){
  point a=L.t-L.s;
  return point(a.y,a.x*-1);
}

line mid_line(const point &a,const point &b){
  point s=mid_point(a,b);
  point t=s+OrthogonalVector(line(a,b));
  return line(s,t);
}

//線分が直線と交わるか
bool XSL(const line &a,const line &b){
  int A=ccw(b.s,b.t,a.s);
  int B=ccw(b.s,b.t,a.t);
  if(A==ONLINE_BACK || A==ONLINE_FRONT){return true;}
  if(B==ONLINE_BACK || B==ONLINE_FRONT){return true;}
  if(A*B<=0){return true;}
  return false;
}

//直線と直線の交点
point XpointLL(const line &a,const line &b){
  if(a.s==a.t || b.s==b.t){return err;}
  if(a.s==b.s || a.s==b.t){return a.s;}
  if(a.t==b.s || a.t==b.t){return a.t;}
  if(isParallel(a,b)){return err;}
  if(isOrthogonal(a,b)){return project(a,b.s);}
  if(intersect(a,b)){return XpointSS(a,b);}
  //ccw(a.s,a.t,b.s)*ccw(a.s,a.t,b.t)<=0
  if(XSL(b,a)){
    double d1=getDistancePP(project(a,b.s),b.s);
    double d2=getDistancePP(project(a,b.t),b.t);
    point base=b.t-b.s;
    return b.s+base*d1/(d2+d1);
  }
  //ccw(b.s,b.t,a.s)*ccw(b.s,b.t,a.t)<=0
  if(XSL(a,b)){
    double d1=getDistancePP(project(b,a.s),a.s);
    double d2=getDistancePP(project(b,a.t),a.t);
    point base=a.t-a.s;
    return a.s+base*d1/(d2+d1);
  }
  //ここまでok
  double d1=getDistancePP(project(a,b.s),b.s);
  double d2=getDistancePP(project(a,b.t),b.t);
  if(d1<d2){
    return b.s+(b.s-b.t)*(d1/(d2-d1));
  }
  return b.t+(b.t-b.s)*(d2/(d1-d2));
}

//間に合わせ
bool X(const line &a,const point &P){
  double mix=min(a.s.x,a.t.x);
  double mxx=max(a.s.x,a.t.x);
  double miy=min(a.s.y,a.t.y);
  double mxy=max(a.s.y,a.t.y);
  if(mxx>=P.x && P.x>=mix && mxy>=P.y && P.y>=miy){return true;}
  return false;
}

//線分と直線の交点
point XpointSL(const line &a,const line &b){
  point ret=XpointLL(b,a);
  if(ret!=XpointLL(a,b)){
    show(a.s);show(a.t);
    show(b.s);show(b.t);
    show(ret);show(XpointLL(a,b));
    assert(false);
  }
  //assert(ret==XpointLL(a,b));
  if(ret==err){return err;}
  if(X(a,ret)){return ret;}
  //if(ccw(a.s,a.t,ret)==ON_SEGMENT){return ret;}
  return err;
}

//外心
point Circumcenter(const point &a,const point &b,const point &c){
  if(a==b || b==c || c==a){return err;}
  int w=ccw(a,b,c);
  if(w!=COUNTER_CLOCKWISE && w!=CLOCKWISE){return err;}
  line l1=mid_line(a,b);
  line l2=mid_line(a,c);
  return XpointLL(l1,l2);
}



#endif /*Geometry2_hpp*/
